//
// Created by elad on 07/01/2020.
//

#ifndef MILESTONE_2_CLIENTHANDLER_H
#define MILESTONE_2_CLIENTHANDLER_H

#include <iostream>
#include "Solver.h"
#include "CacheManager.h"

using namespace std;

template<typename P,typename S>
class ClientHandler {

public:
    virtual void handleClient(istream is,ostream os)=0;

};

#endif //MILESTONE_2_CLIENTHANDLER_H
