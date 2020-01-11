cmake_minimum_required(VERSION 3.15)
project(Milestone_2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)
add_executable(Milestone_2 main.cpp
        Server/Server.h Server/TCPServer.h
        ClientHandler/ClientHandler.h ClientHandler/AbstractCacheManager.h
        Solvers/Solver.h
        ClientHandler/CacheManager.h
        Server/MySerialServer.h Server/MySerialServer.cpp
        ClientHandler/FileCacheManager.h
        ClientHandler/MyTestClientHandler.h
        Solvers/StringReverser.h
        StringUtils.h
        Searchables/Searchable.h Searchables/State.h Searchables/State.cpp
        Searchers/Searcher.h Searchers/CustomPriorityQueue.h
        Searchers/BestFirstSearch.cpp Searchers/BestFirstSearch.h
        Searchers/AbstractQueueSearchers.h Searchers/AbstractQueueSearchers.cpp
        Searchers/BreadthFirstSearch.cpp Searchers/BreadthFirstSearch.h
        Searchers/DepthFirstSearch.cpp Searchers/DepthFirstSearch.h)