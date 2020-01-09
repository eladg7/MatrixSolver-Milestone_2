#include <iostream>
#include "Server/MySerialServer.h"
#include "ClientHandler/MyTestClientHandler.h"

int main() {
    MySerialServer<string, string> s;
    MyTestClientHandler<string, string> handler;
    return 0;
}
