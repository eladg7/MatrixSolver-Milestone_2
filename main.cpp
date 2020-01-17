#include <iostream>
#include <random>
#include "Server/MySerialServer.h"
#include "ClientHandler/MyTestClientHandler.h"
#include "ClientHandler/FileCacheManager.h"
#include "Searchers/BreadthFirstSearch.h"
#include "Solvers/MatrixSolver.h"
#include "Searchers/Astar.h"
#include <chrono>
#include "Searchers/BestFirstSearch.h"
#include "AlgoritmsTesting/NodesEvaluatedTester.h"

int main() {

    auto *searcher = new BestFirstSearch();
    auto *solver = new MatrixSolver(searcher);
    auto *cacheManager = new FileCacheManager<char>(5, typeid(MatrixSolver).name());
    ClientHandler *handler = new MyTestClientHandler<string, vector<State *>, char>(solver, cacheManager);
    MySerialServer s(handler);
    if (s.open(5600)) {
        s.start();
        s.joinThreads();
    }
    delete searcher;
    delete solver;
    delete cacheManager;
    return 0;
}
