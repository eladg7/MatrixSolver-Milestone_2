#ifndef MILESTONE_2_MYSERIALSERVER_H
#define MILESTONE_2_MYSERIALSERVER_H

#include <queue>
#include <thread>
#include <mutex>
#include "TCPServer.h"

using namespace server_side;

template<typename P, typename S>
class MySerialServer : public TCPServer<P, S> {
private:
    queue<int> clientsSocketQueue{};
    vector<thread> threadsOfServer;
    mutex mutexServer;
public:
    virtual bool open(int port, ClientHandler<P, S> *c) {
        if (!TCPServer<P, S>::open(port, c)) {
            cerr << "Could not open server" << endl;
            return false;
        }
    }

    virtual void stop() {
        this->isRunning = false;
        auto it=threadsOfServer.begin();
        while(it != threadsOfServer.end()){//stop all threads of server.
            it->join();
            it++;
        }
        close(this->socketFD);
    }

    virtual void start() {
        thread acceptThread(acceptingClientThread, this);
        thread handleThread(handlingClientThread, this);
        threadsOfServer.push_back(move(acceptThread));
        threadsOfServer.push_back(move(handleThread));
    }

    static void acceptingClientThread(MySerialServer *server) {
        while (server->isRunning) {
            while (server->isRunning
            && server->clientsSocketQueue.size() > MAX_CONNECTED) {
                usleep(10000);
            }
            server->acceptClient();
            usleep(5000);
        }
    }

    static void handlingClientThread(MySerialServer *server) {
        while (server->isRunning) {
            server->clientHandler->handleClient(
                    server->clientsSocketQueue.front(), &server->isRunning);
            server->mutexServer.lock();
            server->clientsSocketQueue.pop();
            server->mutexServer.unlock();

            usleep(5000);
        }
    }

    virtual int acceptClient() {
        if (this->clientsSocketQueue.size() < MAX_CONNECTED) {
            int clientSocket = accept(this->socketFD, (struct sockaddr *) &this->address,
                                      (socklen_t *) &this->address);
            if (clientSocket < 0) {
                cerr << "Cannot accept connection of client socket #:" << clientSocket << endl;
                return -2;
            }

            cout << "Connection successful" << endl;
            mutexServer.lock();
            this->clientsSocketQueue.push(clientSocket);
            mutexServer.unlock();

            return 0;
        }

        return -1;
    }
};

#endif //MILESTONE_2_MYSERIALSERVER_H
