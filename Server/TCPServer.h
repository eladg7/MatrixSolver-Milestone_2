#ifndef MILESTONE_2_TCPSERVER_H
#define MILESTONE_2_TCPSERVER_H

#include <netinet/in.h>
#include <queue>
#include <mutex>
#include "Server.h"

#define MAX_CONNECTED 10

using namespace server_side;


class TCPServer : public Server {
protected:
    sockaddr_in address{};
    mutex mutexServer;

    virtual int openSocket();

    virtual int bindSocket();

    virtual int listenToClients();


public:
    bool getIsRunning() { return isRunning; }

    int acceptClient();

    virtual bool open(int port);

};

#endif //MILESTONE_2_TCPSERVER_H
