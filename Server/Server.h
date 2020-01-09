#ifndef MILESTONE_2_SERVER_H
#define MILESTONE_2_SERVER_H

#include "../ClientHandler/ClientHandler.h"

namespace server_side {
    template<typename P, typename S>
    class Server {
    protected:
        bool isRunning = false;

        ClientHandler<P, S> *clientHandler;

        int socketFD{};

        int port{};
    public:
        virtual bool open(int port, ClientHandler<P, S> *c) = 0;

        virtual void stop() = 0;

        virtual bool isServerRunning() {
            return this->isRunning;
        }

        virtual void start() = 0;

        ~Server() = default;
    };
}
#endif //MILESTONE_2_SERVER_H
