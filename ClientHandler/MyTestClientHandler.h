
#ifndef MILESTONE_2_MYTESTCLIENTHANDLER_H
#define MILESTONE_2_MYTESTCLIENTHANDLER_H


#include "ClientHandler.h"

template<typename P,typename S>
class MyTestClientHandler : public ClientHandler<P,S> {
private:
    Solver<P,S> solver;
    CacheManager <S>cm;
public:
    virtual void handleClient(istream &is,ostream &os){
        string str;


    }

};


#endif //MILESTONE_2_MYTESTCLIENTHANDLER_H
