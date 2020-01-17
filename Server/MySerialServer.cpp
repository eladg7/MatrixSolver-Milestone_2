
#include "MySerialServer.h"

void MySerialServer::start() {
    threadsOfServer.clear();
    thread acceptThread(acceptingClientThread, this);
    threadsOfServer.push_back(move(acceptThread));
}


void MySerialServer::acceptingClientThread(MySerialServer *server) {
    server->runningAcceptClientThread();
}

void MySerialServer::runningAcceptClientThread() {

    while (isRunning) {
        int result = acceptClient();
        if (result < 0) {
            stop();
            break;
        }
        int clientSocket = getClientFromQueue();
        clientHandler->handleClient(clientSocket);

        closeClientSocket(clientSocket);
        cout << "Closed client socket." << endl;
        popClientFromQueue(clientSocket);
        usleep(5000);
    }
}

void MySerialServer::popClientFromQueue(int numberClient) {
    mutexServer.lock();
    clientsSocketQueue.pop();
    mutexServer.unlock();
}


void MySerialServer::pushToClientQueue(int clientSocket) {
    mutexServer.lock();
    this->clientsSocketQueue.push(clientSocket);
    mutexServer.unlock();
}


int MySerialServer::getClientFromQueue() {
    int clientFD;
    mutexServer.lock();
    clientFD = clientsSocketQueue.front();
    mutexServer.unlock();
    return clientFD;
}

int MySerialServer::getSizeOfQueue() {
    return clientsSocketQueue.size();
}

