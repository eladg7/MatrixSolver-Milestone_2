#ifndef MILESTONE_2_CLIENTHANDLER_H
#define MILESTONE_2_CLIENTHANDLER_H

#include <iostream>
#include <sys/socket.h>
#include "../Solvers/Solver.h"
#include "CacheManager.h"

using namespace std;

class ClientHandler {
protected:
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

    string searcherName{};
public:
    ClientHandler() = default;

    virtual void handleClient(int clientFD) = 0;

    virtual string getSearcherName() = 0;

    virtual ~ClientHandler() = default;
};

#endif //MILESTONE_2_CLIENTHANDLER_H
