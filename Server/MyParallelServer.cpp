#include "MyParallelServer.h"

void MyParallelServer::start() {
    threadsOfServer.clear();
    thread acceptThread(acceptingClientThread, this);
    threadsOfServer.push_back(move(acceptThread));
}


void MyParallelServer::acceptingClientThread(MyParallelServer *server) {
    server->runningAcceptClientThread();
}

void MyParallelServer::runningAcceptClientThread() {
    vector<thread> parallelThreads{};
    while (isRunning) {
        int result = acceptClient();
        if (result < 0) {
            if (getSizeOfInProgress() == 0
                && getSizeOfQueue() == 0) {
                stop();
                break;
            }
        }

        if (getSizeOfInProgress() < MAX_CONNECTED
            && getSizeOfQueue() > 0) {
            int client = getClientFromQueue();
            decreseSizeOfQueue();
            thread handleOneClient(runningHandleOneClient, this, client);
            parallelThreads.push_back(move(handleOneClient));
        }

        usleep(5000);
    }

    std::for_each(parallelThreads.begin(), parallelThreads.end(),
                  std::mem_fn(&std::thread::join));
}

void MyParallelServer::runningHandleOneClient(
        MyParallelServer *server, int clientHandlerNumber) {
    ClientHandler *handler = server->getClientHandlerFromQueue(
            clientHandlerNumber);
    handler->handleClient(clientHandlerNumber);
    server->popClientFromQueue(clientHandlerNumber);
    server->closeClientSocket(clientHandlerNumber);
    cout << "Closed client socket, number: " << clientHandlerNumber << endl;
}


void MyParallelServer::popClientFromQueue(int numberClient) {
    mutexServer.lock();
    ClientHandler *c = clientsMap[numberClient];
    clientsMap.erase(numberClient);
    unusedHandlers.push_back(c);

    mutexServer.unlock();
}

int MyParallelServer::getSizeOfQueue() {
    mutexServer.lock();
    int size = sizeOfWaitingClients;
    mutexServer.unlock();
    return size;
}

int MyParallelServer::getSizeOfInProgress() {
    mutexServer.lock();
    int size = clientsMap.size();
    mutexServer.unlock();
    return size;
}


void MyParallelServer::increseSizeOfQueue() {
    mutexServer.lock();
    ++sizeOfWaitingClients;
    mutexServer.unlock();

}

void MyParallelServer::decreseSizeOfQueue() {
    mutexServer.lock();
    --sizeOfWaitingClients;
    mutexServer.unlock();
}

void MyParallelServer::pushToClientQueue(int clientSocket) {
    mutexServer.lock();
    ClientHandler *c = unusedHandlers.back();
    unusedHandlers.pop_back();
    clientsMap[clientSocket] = c;
    mutexServer.unlock();
}

int MyParallelServer::getClientFromQueue() {
    mutexServer.lock();
    int client = clientsMap.begin()->first;
    mutexServer.unlock();
    return client;
}

ClientHandler *MyParallelServer::getClientHandlerFromQueue(int client) {
    mutexServer.lock();
    ClientHandler *handler = clientsMap[client];
    mutexServer.unlock();
    return handler;
}



