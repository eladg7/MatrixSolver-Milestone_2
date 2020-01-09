#ifndef MILESTONE_2_MYSERIALSERVER_H
#define MILESTONE_2_MYSERIALSERVER_H

#include <queue>
#include <thread>
#include "TCPServer.h"

using namespace server_side;

template<typename P, typename S>
class MySerialServer : public TCPServer<P, S> {
private:
    queue<int> clientsSocketQueue{};
    unordered_map<string, thread> runningThreadsMap;
    int *acceptingClientThreadPointer{};
    int *handlingClientThreadPointer{};
public:
    virtual bool open(int port, ClientHandler<P, S> c) {
        if (!TCPServer<P, S>::open(port, c)) {
            cerr << "Could not open server" << endl;
            return false;
        }
    }

    virtual void stop() {
        this->isRunning = false;
        thread th1(*acceptingClientThreadPointer);
        thread th2(*handlingClientThreadPointer);
        th1.join();
        th2.join();
        close(this->socketFD);
    }

    virtual void start() {
        thread acceptThread(acceptingClientThread, ref(*this));
        thread handleThread(handlingClientThread, ref(*this));
        runningThreadsMap["acceptingClientThread"] = &acceptThread;
    }

    static void acceptingClientThread(MySerialServer &server) {
        server.acceptingClientThreadPointer = this_thread::get_id();
        while (server.isRunning) {
            while (server.isRunning && server.clientsSocketQueue.size() > MAX_CONNECTED) {
                usleep(10000);
            }
            server.acceptClients();
            usleep(5000);
        }
    }

    static void handlingClientThread(MySerialServer &server) {
        server.handlingClientThreadPointer = this_thread::get_id();
        while (server.isRunning) {
            server.clientHandler.handleClient(server.clientsSocketQueue.front(), &server.isRunning);
            server.clientsSocketQueue.pop();
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
            this->clientsSocketQueue.push(clientSocket);

            return 0;
        }

        return -1;
    }
};

#endif //MILESTONE_2_MYSERIALSERVER_H
