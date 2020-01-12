#ifndef MILESTONE_2_CLIENTHANDLER_H
#define MILESTONE_2_CLIENTHANDLER_H

#include <iostream>
#include <sys/socket.h>
#include "../Solvers/Solver.h"
#include "CacheManager.h"

using namespace std;

class ClientHandler {
protected:

    static void rnInTheEnd(char *buffer) { //make sure there is /r/n in the end
        if (buffer[strlen(buffer) - 2] == '\r') {
            buffer[strlen(buffer) - 2] = '\0';
        } else if (buffer[strlen(buffer) - 1] == '\n') {
            buffer[strlen(buffer) - 1] = '\0';
        }
    }

    static int writeToClient(int clientFD, string messages) {
        const char *message = messages.c_str();

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
