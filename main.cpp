#include <iostream>
#include "Server/MySerialServer.h"
#include "ClientHandler/MyTestClientHandler.h"

int main() {
    MySerialServer s;
    MyTestClientHandler<string, string> handler;
    if (s.open(5600, &handler)) {
        s.start();
        s.joinThreads();
    }
    return 0;
}
