#include "TCPServer.h"


int TCPServer::openSocket() {
    this->socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (this->socketFD == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
        return -1;
    }
    //set timeout for receive operations
    struct timeval tv{};
    __time_t timeout_in_seconds = 20;
    tv.tv_sec = timeout_in_seconds;
    tv.tv_usec = 0;
    setsockopt(this->socketFD, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv, sizeof tv);

    return 0;
}

int TCPServer::bindSocket() {
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

int TCPServer::listenToClients() {
    if (listen(this->socketFD, MAX_CONNECTED) == -1) {
        std::cerr << "Error during listening command" << std::endl;
        return -3;
    }
    std::cout << "Server is now listening ..." << std::endl;
    return 0;
}


int TCPServer::acceptClient() {
    if (getSizeOfQueue() < MAX_CONNECTED) {
        int len = sizeof(this->address);
        int clientSocket = accept(this->socketFD,
                                  (struct sockaddr *) &this->address,
                                  (socklen_t *) &len);
        if (clientSocket < 0) {
            cout << "No more clients in queue." << endl;
            return -2;
        }

        cout << "Connection successful" << endl;
        pushToClientQueue(clientSocket);

        return 0;
    }
    return 1;
}


bool TCPServer::open(int port) {
    this->port = port;
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

    this->isRunning = true;
    return true;
}