#ifndef MILESTONE_2_SERVER_H
#define MILESTONE_2_SERVER_H

#include "../ClientHandler/ClientHandler.h"

namespace server_side {
    class Server {
    protected:
        bool isRunning = false;

        ClientHandler*clientHandler;

        int socketFD{};

        int port{};
    public:
        virtual bool open(int port, ClientHandler *c) = 0;

        virtual void stop() = 0;

        virtual bool isServerRunning() {
            return this->isRunning;
        }

        virtual void start() = 0;

        ~Server() = default;
    };
}
#endif //MILESTONE_2_SERVER_H
