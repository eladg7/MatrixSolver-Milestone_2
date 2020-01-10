#ifndef MILESTONE_2_MYSERIALSERVER_H
#define MILESTONE_2_MYSERIALSERVER_H

#include <queue>
#include <thread>
#include <mutex>
#include <algorithm>
#include <functional>
#include "TCPServer.h"

using namespace server_side;

class MySerialServer : public TCPServer {
private:
    queue<int> clientsSocketQueue{};
    mutex mutexServer;
public:
    virtual bool open(int port, ClientHandler *c) {
        if (!TCPServer::open(port, c)) {
            cerr << "Could not open server" << endl;
            return false;
        }
    }

    virtual void stop() {
        this->isRunning = false;
        close(this->socketFD);
    }

    virtual void joinThreads() {
        std::for_each(threadsOfServer.begin(),threadsOfServer.end(),
                std::mem_fn(&std::thread::join));
    }

    virtual void start() {
        threadsOfServer.clear();
        thread acceptThread(acceptingClientThread, this);
//        thread handleThread(handlingClientThread, this);
        threadsOfServer.push_back(move(acceptThread));
//        threadsOfServer.push_back(move(handleThread));
    }

    static void acceptingClientThread(MySerialServer *server) {
        while (server->isRunning) {
            int result = server->acceptClient();
            if (result < 0) {
                break;
            }
            server->clientHandler->handleClient(
                    server->clientsSocketQueue.front(), &server->isRunning);
            server->mutexServer.lock();
            server->clientsSocketQueue.pop();
            server->mutexServer.unlock();
            usleep(5000);
        }
    }

//    static void handlingClientThread(MySerialServer *server) {
//        while (server->isRunning) {
//            server->clientHandler->handleClient(
//                    server->clientsSocketQueue.front(), &server->isRunning);
//            server->mutexServer.lock();
//            server->clientsSocketQueue.pop();
//            server->mutexServer.unlock();
//
//            usleep(5000);
//        }
//    }

    virtual int acceptClient() {
        if (this->clientsSocketQueue.size() < MAX_CONNECTED) {
            int clientSocket = accept(this->socketFD, (struct sockaddr *) &this->address,
                                      (socklen_t *) &this->address);
            if (clientSocket < 0) {
                cerr << "Cannot accept connection of client" << endl;
                stop();
                return -2;
            }

            cout << "Connection successful" << endl;
            mutexServer.lock();
            this->clientsSocketQueue.push(clientSocket);
            mutexServer.unlock();

            return 0;
        }

        return 1;
    }
};

#endif //MILESTONE_2_MYSERIALSERVER_H
