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

        int socketFD{};

        int port{};

        vector<thread> threadsOfServer{};

    public:

        virtual bool open(int port) = 0;

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

        virtual void pushToClientQueue(int clientSocket) = 0;

        virtual int getClientFromQueue() = 0;

        virtual int getSizeOfQueue() = 0;

        virtual void closeClientSocket(int numberClient) {
            if (numberClient >= 0) {
                close(numberClient);

            } else {
                cerr << "Could not close client: " << numberClient << endl;
            }
        }

        virtual void popClientFromQueue(int numberClient) = 0;

        virtual ~Server() = default;

    };
}
#endif //MILESTONE_2_SERVER_H
