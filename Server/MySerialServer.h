#ifndef MILESTONE_2_MYSERIALSERVER_H
#define MILESTONE_2_MYSERIALSERVER_H

#include <queue>
#include <thread>
#include <mutex>
#include "TCPServer.h"

using namespace server_side;

class MySerialServer : public TCPServer {
private:
    queue<int> clientsSocketQueue{};
    ClientHandler *clientHandler;

    void runningAcceptClientThread();


public:
    explicit MySerialServer(ClientHandler *c) {
        clientHandler = c;
    }

    void start() override;

    virtual void popClientFromQueue(int numberClient);

    virtual void pushToClientQueue(int clientSocket);

    virtual int getClientFromQueue();

    virtual int getSizeOfQueue();

    static void acceptingClientThread(MySerialServer *server);
};

#endif //MILESTONE_2_MYSERIALSERVER_H
