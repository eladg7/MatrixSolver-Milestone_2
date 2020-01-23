#ifndef MILESTONE_2_NODESEVALUATEDTESTER_H
#define MILESTONE_2_NODESEVALUATEDTESTER_H

#include "../Searchers/Searcher.h"
#include "../Searchables/MatrixMaze.h"
#include "../Solvers/MatrixSolver.h"
#include "../Searchers/Astar.h"
#include <chrono>
#include <random>

using namespace std;

class NodesEvaluatedTester {
private:
    static tuple<double, int> getMazeSolvingCost(string &maze, Searcher *searcher, int size);

    static string generateMaze(int N, int M);

    static void printResults(tuple<double, int> astarLowest, tuple<double, int> BestFSLowest,
                             tuple<double, int> BFSLowest, tuple<double, int> DFSLowest);

    static tuple<string, double> getLowest(tuple<double, int> astarLowest, tuple<double, int> BestFSLowest,
                                           tuple<double, int> BFSLowest, tuple<double, int> DFSLowest);

    static vector<string> getMatrixFromFile(vector<string> filesNames);

    static void createSolutionFile(const string &solution, const string &searcherName, const string &dimension);

public:
    static void testAllMazes(unsigned int timesPerAlgorithm);

    ~NodesEvaluatedTester() = default;
};

#endif //MILESTONE_2_NODESEVALUATEDTESTER_H
