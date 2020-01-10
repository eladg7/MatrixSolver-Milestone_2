#ifndef MILESTONE_2_CLIENTHANDLER_H
#define MILESTONE_2_CLIENTHANDLER_H

#include <iostream>
#include <sys/socket.h>
#include "Solver.h"
#include "CacheManager.h"

using namespace std;

class ClientHandler {
protected:
    static int writeToClient(int clientFD, const char *message) {
        char copy[strlen(message) + 2];
        strcpy(copy, message);
        if (message[strlen(message) - 1] != '\n') {
            strcat(copy, "\r\n");
        }

        send(clientFD, copy, strlen(copy), 0);
        cout << "Message sent" << endl;
        return 0;
    };

public:
    virtual void handleClient(int clientFD, bool *isRunning) = 0;
};

#endif //MILESTONE_2_CLIENTHANDLER_H
