cmake_minimum_required(VERSION 3.15)
project(Milestone_2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)
add_executable(Milestone_2 main.cpp
        Server/Server.h Server/TCPServer.h
        ClientHandler/ClientHandler.h ClientHandler/AbstractCacheManager.h
        Solvers/Solver.h Solvers/StringReverser.h StringUtils.h
        ClientHandler/CacheManager.h
        Server/MySerialServer.h Server/MySerialServer.cpp
        ClientHandler/FileCacheManager.h
        ClientHandler/MyTestClientHandler.h
        Searchables/Searchable.h Searchables/State.h
        Searchers/Searcher.h Searchers/CustomPriorityQueue.h
        Searchers/BestFirstSearch.cpp Searchers/BestFirstSearch.h
        Searchers/AbstractQueueSearchers.h Searchers/AbstractQueueSearchers.cpp
        Searchers/BreadthFirstSearch.cpp Searchers/BreadthFirstSearch.h
        Searchers/DepthFirstSearch.cpp Searchers/DepthFirstSearch.h
        Solvers/MatrixSolver.h Solvers/MatrixSolver.cpp
        Searchers/Astar.h Searchers/Astar.cpp
        AlgoritmsTesting/NodesEvaluatedTester.h AlgoritmsTesting/NodesEvaluatedTester.cpp Server/MyParallelServer.cpp Server/MyParallelServer.h Server/TCPServer.cpp)

