#include "boot.h"
#include "MyParallelServer.h"
#include "../Searchers/Astar.h"

int boot::Main::main(unsigned int port) {
    if (port <= 0) {
        return -1;
    }
    auto *searcher = new BestFirstSearch();
    auto *solver = new StringReverser();
    auto *cacheManager = new FileCacheManager<char>(5, typeid(StringReverser).name());
    auto *handler = new MyTestClientHandler<string, string, char>(solver, cacheManager);
    Server *s = new MySerialServer(handler);
    if (s->open(port)) {
        s->start();
        s->joinThreads();
    }
    delete searcher;
    delete solver;
    delete cacheManager;
    delete s;
    return 0;
}

int boot::ParallelServerMain::main(unsigned int port) {
    if (port <= 0) {
        return -1;
    }
//    auto *searcher = new BestFirstSearch();
//    auto *solver = new MatrixSolver(searcher);
    auto *cacheManager = new FileCacheManager<char>(5, typeid(MatrixSolver).name());
//    ClientHandler handler = new MyTestClientHandler<string, vector<State >, char>(solver, cacheManager);
//    MySerialServer s(handler);

    vector<ClientHandler *> handlerVector;
    for (int i = 0; i < MAX_CONNECTED; i++) {
        auto *searcher = new BestFirstSearch();
        auto *solver = new MatrixSolver(searcher);
        ClientHandler *handler = new MyTestClientHandler<string, vector<State *>, char>(solver, cacheManager);
        handlerVector.push_back(handler);
    }
    MyParallelServer s(handlerVector);
    if (s.open(port)) {
        s.start();
        s.joinThreads();
    }

    delete cacheManager;
    for (int i = 0; i < MAX_CONNECTED; i++) {
        ClientHandler *handler = handlerVector.back();
        handlerVector.pop_back();
        delete handler;
    }
    return 0;
}

int boot::SerialServerMain::main(unsigned int port) {
    if (port <= 0) {
        return -1;
    }

    auto *searcher = new Astar();
    auto *solver = new MatrixSolver(searcher);
    auto *cacheManager = new FileCacheManager<char>(5, typeid(MatrixSolver).name());
    ClientHandler *handler = new MyTestClientHandler<string, vector<State *>, char>(solver, cacheManager);
    MySerialServer s(handler);
    if (s.open(port)) {
        s.start();
        s.joinThreads();
    }
    delete solver;
    delete cacheManager;
    return 0;
}