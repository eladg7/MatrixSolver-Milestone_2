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
    mutex mutexSerialServer;
    void runningAcceptClientThread();

public:
    bool open(int port, ClientHandler *c) override;

    void start() override;

    virtual int acceptClient();

    bool getIsRunning() { return isRunning; }

    void popClientFromQueue();

    int getClientFD();

    static void acceptingClientThread(MySerialServer *server);



    };

#endif //MILESTONE_2_MYSERIALSERVER_H
