cmake_minimum_required(VERSION 3.15)
project(Milestone_2)

set(CMAKE_CXX_STANDARD 14)

add_executable(Milestone_2 main.cpp
        Server/Server.h
        ClientHandler/ClientHandler.h ClientHandler/AbstractCacheManager.h
        ClientHandler/Solver.h
        ClientHandler/CacheManager.h
        Server/MySerialServer.h Server/MySerialServer.cpp
        ClientHandler/FileCacheManager.h)