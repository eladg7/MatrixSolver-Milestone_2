#include <iostream>
#include "Server/MySerialServer.h"
#include "ClientHandler/MyTestClientHandler.h"
#include "Solvers/StringReverser.h"
#include "ClientHandler/FileCacheManager.h"
#include "Solvers/MatrixSolver.h"
#include "Searchers/BreadthFirstSearch.h"

int main() {
    MySerialServer s;
    Searcher *searcher = new BreadthFirstSearch();
    MatrixSolver *solver = new MatrixSolver(searcher);
    FileCacheManager<string> *cacheManager = new FileCacheManager<string>(5);
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
