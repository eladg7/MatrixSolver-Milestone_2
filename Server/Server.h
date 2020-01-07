#ifndef MILESTONE_2_SERVER_H
#define MILESTONE_2_SERVER_H

#include "../ClientHandler/ClientHandler.h"

namespace server_side {
    class Server {
    protected:
        bool isRunning = false;
    public:
        virtual bool open(int port, ClientHandler c) = 0;

        virtual void stop() {
            this->isRunning = false;
        };

        ~Server() = default;
    };
}
#endif //MILESTONE_2_SERVER_H
