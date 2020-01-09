#ifndef MILESTONE_2_SERVER_H
#define MILESTONE_2_SERVER_H

#include "../ClientHandler/ClientHandler.h"

namespace server_side {
    class Server {
    protected:
        bool isRunning = false;

        ClientHandler *clientHandler;

        int socketFD{};

        int port{};

        vector<thread> threadsOfServer;

    public:
        virtual bool open(int port, ClientHandler *c) = 0;

        virtual void stop() = 0;

        virtual bool isServerRunning() {
            return this->isRunning;
        }

        virtual void start() = 0;

        virtual void joinThreads() {
            auto it = threadsOfServer.begin();
            while (it != threadsOfServer.end()) {
                it->join();
                it++;
            }
        }

        ~Server() = default;
    };
}
#endif //MILESTONE_2_SERVER_H
