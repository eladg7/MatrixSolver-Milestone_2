#include <iostream>
#include "Server/MySerialServer.h"
#include "ClientHandler/MyTestClientHandler.h"
#include "ClientHandler/StringReverser.h"
#include "ClientHandler/FileCacheManager.h"

int main() {
    MySerialServer s;
    StringReverser *solver=new StringReverser();
    FileCacheManager<string> *cacheManager=new FileCacheManager<string>(5);
    MyTestClientHandler<string, string> handler(solver,cacheManager);
    if (s.open(5600, &handler)) {
        s.start();
        s.joinThreads();
    }
    s.stop();
    return 0;
}
