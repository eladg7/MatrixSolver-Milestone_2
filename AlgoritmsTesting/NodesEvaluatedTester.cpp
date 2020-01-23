#include <iostream>
#include <fstream>
#include <unistd.h>
#include "NodesEvaluatedTester.h"
#include "../Searchers/BestFirstSearch.h"
#include "../Searchers/BreadthFirstSearch.h"
#include "../Searchers/DepthFirstSearch.h"

void NodesEvaluatedTester::testAllMazes(unsigned int timesPerAlgorithm) {
    auto *searcher = new Astar();
    auto *solver = new MatrixSolver(searcher);

    vector<string> mazes = getMatrixFromFile(
            {"Matrix1.txt", "Matrix2.txt", "Matrix3.txt", "Matrix4.txt", "Matrix5.txt",
             "Matrix6.txt", "Matrix7.txt", "Matrix8.txt", "Matrix9.txt", "Matrix10.txt"});
//    for (int i = 10; i <= 50; i++) {
//        mazes.push_back(generateMaze(i, i));
//    }


    tuple<double, int> astarLowest;
    tuple<double, int> BestFSLowest;
    tuple<double, int> BFSLowest;
    tuple<double, int> DFSLowest;
    vector<int> size = {50, 47, 45, 40, 35, 30, 25, 20, 15, 10};
    for (auto maze : mazes) {
        astarLowest = getMazeSolvingCost(maze, new Astar(), size.back());
        BestFSLowest = getMazeSolvingCost(maze, new BestFirstSearch(), size.back());
        BFSLowest = getMazeSolvingCost(maze, new BreadthFirstSearch(), size.back());
        DFSLowest = getMazeSolvingCost(maze, new DepthFirstSearch(), size.back());
        printResults(astarLowest, BestFSLowest, BFSLowest, DFSLowest);
        size.pop_back();
    }

    delete solver;
}

vector<string> NodesEvaluatedTester::getMatrixFromFile(vector<string> filesNames) {
    vector<string> result;
    string temp;
    string line;
    ifstream infile;
    while (!filesNames.empty()) {
        infile.open(filesNames.back(), ifstream::in);
        if (infile.is_open()) {
            while (getline(infile, line)) {
                temp += line;
                temp += "\n";
            }
            if (!temp.empty()) {
                temp.pop_back();
                StringUtils::eraseAllSubStr(temp, "\nend");
                result.push_back(temp);
            }
            temp.clear();
            infile.close();
        }
        filesNames.pop_back();
    }

    //  reverse i because we read it from the end to beginning
    reverse(result.begin(), result.end());
    return result;
}

tuple<string, double> NodesEvaluatedTester::getLowest(tuple<double, int> astarLowest, tuple<double, int> BestFSLowest,
                                                      tuple<double, int> BFSLowest, tuple<double, int> DFSLowest) {
    auto lowest = astarLowest;
    tuple<string, double> best = make_tuple("Astar", get<1>(astarLowest));
    if ((get<0>(BestFSLowest) < get<0>(astarLowest)) ||
        (get<0>(BestFSLowest) == get<0>(astarLowest)
         && get<1>(BestFSLowest) < get<1>(astarLowest))) {
        best = make_tuple("BestFirstSearch", get<1>(BestFSLowest));
        lowest = BestFSLowest;
    }

    if ((get<0>(BFSLowest) < get<0>(lowest)) ||
        (get<0>(BFSLowest) == get<0>(lowest)
         && get<1>(BFSLowest) < get<1>(lowest))) {
        best = make_tuple("BFSSearch", get<1>(BFSLowest));
        lowest = BFSLowest;
    }

    if ((get<0>(DFSLowest) < get<0>(lowest)) ||
        (get<0>(DFSLowest) == get<0>(lowest)
         && get<1>(DFSLowest) < get<1>(lowest))) {
        best = make_tuple("DFSSearch", get<1>(DFSLowest));
    }

    return best;
}

void NodesEvaluatedTester::printResults(tuple<double, int> astarLowest, tuple<double, int> BestFSLowest,
                                        tuple<double, int> BFSLowest, tuple<double, int> DFSLowest) {
    auto best = getLowest(astarLowest, BestFSLowest, BFSLowest, DFSLowest);

    cout << "The results are:\n\tAstar: " << get<1>(astarLowest) << " and reached lowest cost of:"
         << get<0>(astarLowest) << "\n\tBestFirstSearch: " << get<1>(BestFSLowest) << " and reached lowest cost of:"
         << get<0>(BestFSLowest) << "\n\tBreadthFirstSearch: " << get<1>(BFSLowest) << " and reached lowest cost of:"
         << get<0>(BFSLowest) << "\n\tDepthFirstSearch: " << get<1>(DFSLowest) << " and reached lowest cost of:"
         << get<0>(DFSLowest) << "\nThe fastest One is: " << get<0>(best) << ", with " << get<1>(best)
         << " nodes evaluated."
         << endl;
}

tuple<double, int> NodesEvaluatedTester::getMazeSolvingCost(string &maze, Searcher *searcher, int size) {
    auto solver = new MatrixSolver(searcher);
    auto pathCost = solver->solve(maze);
    int lowest = solver->getNumberOfNodesEvaluated();
    tuple<double, int> cost;
    if (!pathCost.empty()) {
        cost = make_tuple(pathCost.back()->getCurrentCost(), lowest);
        auto temp = to_string(size) + "x" + to_string(size);
        createSolutionFile(solver->toString(pathCost), solver->getSearcherName(), temp);
    } else {
        cost = make_tuple(numeric_limits<int>::max(), lowest);
    }

    delete solver;
    return cost;
}

void NodesEvaluatedTester::createSolutionFile(const string &solution,
                                              const string &searcherName, const string &dimension) {
    if (!solution.empty()) {
        ofstream fileObj;

        char cwd[256] = {0};
        getcwd(cwd, sizeof(cwd));
        strcat(cwd, "/");
        fileObj.open(cwd + searcherName + "_" + dimension + ".bin", ios::binary | ios::out);
        if (!fileObj) {
            throw "Error creating file.";
        }

        fileObj.write((char *) solution.c_str(), solution.length());
        try {
            fileObj.close();
        } catch (exception &e) {
            throw "Couldn't close file.";
        }
    }
}

string NodesEvaluatedTester::generateMaze(int N, int M) {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(-1, 100);
    string maze;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            maze += to_string(distribution(generator));
            if (j != M - 1) {
                maze += ",";
            }
        }
        maze += "\n";
    }
    maze += "0,0\n" + to_string(N - 1) + "," + to_string(M - 1) + "\n";

    return maze;
}