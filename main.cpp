#include <iostream>
#include "Server/MySerialServer.h"
#include "ClientHandler/MyTestClientHandler.h"
#include "ClientHandler/FileCacheManager.h"
#include "Searchers/BreadthFirstSearch.h"
#include "Solvers/MatrixSolver.h"
#include "Searchers/Astar.h"

int main() {
    MySerialServer s;
    auto *searcher = new Astar();
    auto *solver = new MatrixSolver(searcher);
    auto *cacheManager = new FileCacheManager<string>(5);
    MyTestClientHandler<string, string> handler(solver, cacheManager);
    if (s.open(5600, &handler)) {
        s.start();
        s.joinThreads();
    }
    delete searcher;
    delete solver;
    delete cacheManager;
    return 0;
}
