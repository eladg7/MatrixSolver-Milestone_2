
#ifndef MILESTONE_2_MYTESTCLIENTHANDLER_H
#define MILESTONE_2_MYTESTCLIENTHANDLER_H


#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"
template<typename  T>
class MyTestClientHandler : public ClientHandler {

private:
    Solver solver;
    CacheManager <T>cm;
public:

};


#endif //MILESTONE_2_MYTESTCLIENTHANDLER_H
