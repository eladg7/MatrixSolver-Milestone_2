#ifndef MILESTONE_2_TCPSERVER_H
#define MILESTONE_2_TCPSERVER_H

#include <netinet/in.h>
#include "Server.h"

#define MAX_CONNECTED 10

using namespace server_side;

template<typename P, typename S>
class TCPServer : public Server<P, S> {
protected:
    sockaddr_in address{};

    virtual int openSocket() {
        this->socketFD = socket(AF_INET, SOCK_STREAM, 0);
        if (this->socketFD == -1) {
            //error
            std::cerr << "Could not create a socket" << std::endl;
            return -1;
        }

        return 0;
    }

    virtual int bindSocket() {
        //bind socket to IP address
        // we first need to create the sockaddr obj.
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
        address.sin_port = htons(this->port);

        if (bind(this->socketFD, (struct sockaddr *) &address, sizeof(address)) == -1) {
            std::cerr << "Could not bind the socket to an IP" << std::endl;
            return -2;
        }
        return 0;
    }

    virtual int listenToClients() {
        if (listen(this->socketFD, MAX_CONNECTED) == -1) {
            std::cerr << "Error during listening command" << std::endl;
            return -3;
        }
        std::cout << "Server is now listening ..." << std::endl;
        return 0;
    }

    virtual int acceptClient() = 0;

    virtual bool open(int port, ClientHandler<P, S> c) {
        int result = this->openSocket();
        if (result < 0) {
            this->stop();
            return false;
        }

        result = bindSocket();
        if (result < 0) {
            this->stop();
            return false;
        }

        result = listenToClients();
        if (result < 0) {
            this->stop();
            return false;
        }

        this->clientHandler = c;
        this->isRunning = true;
        return true;
    }

};

#endif //MILESTONE_2_TCPSERVER_H