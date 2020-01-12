#include <iostream>
#include "Server/MySerialServer.h"
#include "ClientHandler/MyTestClientHandler.h"
#include "Solvers/StringReverser.h"
#include "ClientHandler/FileCacheManager.h"
#include "Searchers/Astar.h"
#include "Solvers/MatrixSolver.h"

int main() {
    MySerialServer s;
//    StringReverser *solver = new StringReverser();
    auto *searcher = new Astar();
    MatrixSolver *solver = new MatrixSolver(searcher);
    FileCacheManager<string> *cacheManager = new FileCacheManager<string>(5);
    MyTestClientHandler<string, string> handler(solver, cacheManager);
    if (s.open(5600, &handler)) {
        s.start();
        s.joinThreads();
    }
    s.stop();
    return 0;
}
