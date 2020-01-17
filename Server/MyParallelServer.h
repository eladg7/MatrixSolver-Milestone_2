//
// Created by yekaterina on 17/01/2020.
//

#ifndef MILESTONE_2_MYPARALLELSERVER_H
#define MILESTONE_2_MYPARALLELSERVER_H

#include "TCPServer.h"

using namespace server_side;

class MyParallelServer : public TCPServer {
private:
    unordered_map<int, ClientHandler *> clientsMap;
    vector<ClientHandler *> unusedHandlers;

    void runningAcceptClientThread();

public:
    explicit MyParallelServer(const vector<ClientHandler *> &c) {
        unusedHandlers = c;
    }

    static void runningHandleOneClient(MyParallelServer *server, int clientHandlerNumber);

    void start() override;

    virtual void popClientFromQueue(int numberClient);

    virtual void pushToClientQueue(int clientSocket);

    virtual int getClientFromQueue();

    virtual int getSizeOfQueue();

    static void acceptingClientThread(MyParallelServer *server);

    ClientHandler *getClientHandlerFromQueue(int client);
};


#endif //MILESTONE_2_MYPARALLELSERVER_H
