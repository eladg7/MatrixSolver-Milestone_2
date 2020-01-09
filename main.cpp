#include <iostream>
#include "Server/MySerialServer.h"
#include "ClientHandler/MyTestClientHandler.h"

int main() {
    MySerialServer s;
    MyTestClientHandler<string, string> handler;
    s.open(4200, &handler);
    s.start();
    s.joinThreads();
    return 0;
}
