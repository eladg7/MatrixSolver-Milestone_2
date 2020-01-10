
#include "MySerialServer.h"

bool MySerialServer::open(int port, ClientHandler *c) {
    if (!TCPServer::open(port, c)) {
        cerr << "Could not open server" << endl;
        return false;
    }
}

void MySerialServer::start() {
    threadsOfServer.clear();
    thread acceptThread(acceptingClientThread, this);
    threadsOfServer.push_back(move(acceptThread));
}

int MySerialServer::acceptClient() {
    if (this->clientsSocketQueue.size() < MAX_CONNECTED) {
        int clientSocket = accept(this->socketFD,
                                  (struct sockaddr *) &this->address,
                                  (socklen_t *) &this->address);
        if (clientSocket < 0) {
            cerr << "Cannot accept connection of client" << endl;
            stop();
            return -2;
        }

        cout << "Connection successful" << endl;
        pushToClientQueue(clientSocket);

        return 0;
    }

    return 1;
}

void MySerialServer::pushToClientQueue(int clientSocket) {
    mutexSerialServer.lock();
    this->clientsSocketQueue.push(clientSocket);
    mutexSerialServer.unlock();
}

void MySerialServer::popClientFromQueue() {
    mutexSerialServer.lock();
    clientsSocketQueue.pop();
    mutexSerialServer.unlock();
}

int MySerialServer::getClientFD() {
    int clientFD;
    mutexSerialServer.lock();
    clientFD = clientsSocketQueue.front();
    mutexSerialServer.unlock();
    return clientFD;
}

void MySerialServer::acceptingClientThread(MySerialServer *server) {
    server->runningAcceptClientThread();
}

void MySerialServer::runningAcceptClientThread() {
    while (isRunning) {
        int result = acceptClient();
        if (result < 0) {
            break;
        }
        clientHandler->handleClient(getClientFD(), &isRunning);
        popClientFromQueue();
        usleep(5000);

    }
}
