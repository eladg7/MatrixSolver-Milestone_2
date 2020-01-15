#ifndef MILESTONE_2_SERVER_H
#define MILESTONE_2_SERVER_H

#include <algorithm>
#include <functional>
#include <thread>
#include "../ClientHandler/ClientHandler.h"

namespace server_side {
    class Server {
    protected:
        bool isRunning = false;

        ClientHandler *clientHandler{};

        int socketFD{};

        int port{};

        vector<thread> threadsOfServer{};

    public:
        virtual bool open(int port, ClientHandler *c) = 0;

        virtual void stop() {
            this->isRunning = false;
            close(this->socketFD);
            cout << "Closed server socket." << endl;
        }

        virtual bool isServerRunning() {
            return this->isRunning;
        }

        virtual void start() = 0;


        virtual void joinThreads() {
            std::for_each(threadsOfServer.begin(), threadsOfServer.end(),
                          std::mem_fn(&std::thread::join));
        }
        ~Server() = default;

    };
}
#endif //MILESTONE_2_SERVER_H
