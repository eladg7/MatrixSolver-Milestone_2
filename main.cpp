#include <iostream>
#include "Server/MySerialServer.h"
#include "ClientHandler/MyTestClientHandler.h"
#include "Solvers/StringReverser.h"
#include "ClientHandler/FileCacheManager.h"
#include "Searchers/BreadthFirstSearch.h"
#include "Solvers/MatrixSolver.h"
#include "Searchers/BestFirstSearch.h"

int main() {
    MySerialServer s;
//    StringReverser *solver = new StringReverser();
    auto *searcher = new BestFirstSearch();
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
