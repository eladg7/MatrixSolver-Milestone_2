#include <iostream>
#include "NodesEvaluatedTester.h"
#include "../Searchers/BestFirstSearch.h"
#include "../Searchers/BreadthFirstSearch.h"
#include "../Searchers/DepthFirstSearch.h"

void NodesEvaluatedTester::testAllMazes(unsigned int timesPerAlgorithm) {
    auto *searcher = new Astar();
    auto *solver = new MatrixSolver(searcher);

    vector<string> mazes;
    for (int i = 10; i <= 50; i++) {
        mazes.push_back(generateMaze(i, i));
    }

    tuple<double, int> astarLowest;
    tuple<double, int> BestFSLowest;
    tuple<double, int> BFSLowest;
    tuple<double, int> DFSLowest;
    for (auto maze : mazes) {
        astarLowest = getMazeSolvingCost(maze, new Astar());
        BestFSLowest = getMazeSolvingCost(maze, new BestFirstSearch());
        BFSLowest = getMazeSolvingCost(maze, new BreadthFirstSearch());
        DFSLowest = getMazeSolvingCost(maze, new DepthFirstSearch());
        printResults(astarLowest, BestFSLowest, BFSLowest, DFSLowest);
    }

    delete solver;
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

tuple<double, int> NodesEvaluatedTester::getMazeSolvingCost(string &maze, Searcher *searcher) {
    auto solver = new MatrixSolver(searcher);
    auto pathCost = solver->solve(maze);
    int lowest = solver->getNumberOfNodesEvaluated();
    tuple<double, int> cost;
    if (!pathCost.empty()) {
        cost = make_tuple(pathCost.back()->getCurrentCost(), lowest);
    } else {
        cost = make_tuple(numeric_limits<int>::max(), lowest);
    }

    delete solver;
    delete searcher;
    return cost;
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