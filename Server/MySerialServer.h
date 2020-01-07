#ifndef MILESTONE_2_MYSERIALSERVER_H
#define MILESTONE_2_MYSERIALSERVER_H

#include "Server.h"

using namespace server_side;

class MySerialServer : public Server {
public:
    bool open(int port, ClientHandler c) override;
};

#endif //MILESTONE_2_MYSERIALSERVER_H
