#ifndef MILESTONE_2_BOOT_H
#define MILESTONE_2_BOOT_H

#include "Server.h"
#include "MySerialServer.h"
#include "../Searchers/BestFirstSearch.h"
#include "../Solvers/MatrixSolver.h"
#include "../ClientHandler/FileCacheManager.h"
#include "../ClientHandler/MyTestClientHandler.h"
#include "../Solvers/StringReverser.h"

using namespace server_side;
namespace boot {
    class Main {
    public:
        Main() = default;

        static int main(unsigned int port);

        ~Main() = default;
    };

    class ParallelServerMain {
    public:
        ParallelServerMain() = default;

        static int main(unsigned int port);

        ~ParallelServerMain() = default;
    };

    class SerialServerMain {
    public:
        SerialServerMain() = default;

        static int main(unsigned int port);

        ~SerialServerMain() = default;
    };
}
#endif //MILESTONE_2_BOOT_H
