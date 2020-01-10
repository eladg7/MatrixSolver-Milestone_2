#ifndef MILESTONE_2_MYTESTCLIENTHANDLER_H
#define MILESTONE_2_MYTESTCLIENTHANDLER_H


#include "ClientHandler.h"
#include "../StringUtils.h"

#define BUFFER_SIZE 1024

template<typename P, typename S>
class MyTestClientHandler : public ClientHandler {
private:
    Solver<P, S> *solver;
    CacheManager<S> *cm;
public:
    MyTestClientHandler(Solver<P,S> *s,CacheManager<S> *cache){
        solver=s;
        cm=cache;
    }

    virtual void handleClient(int clientFD, bool *isRunning) {
        char buffer[BUFFER_SIZE] = {0};
        int isRead = 0;
        string solution;

        while (*isRunning) {
            isRead = read(clientFD, buffer, sizeof(buffer));
            if (isRead <= 0) {//error getting info from client.
                cerr << "Couldn't read for client." << endl;
                break;
            }
            buffer[strlen(buffer) - 2] = '\0';
            string key=buffer;
            if (key== "end") {
                break;
            }

            if (cm->keyExist(key)) {
                solution = solver->toString(cm->get(key));
            } else {
                vector<string> problems = StringUtils::split(key, '\n');
                for (string s :problems) {
                    solution = solver->toString(
                            solver->solve(solver->createProblemFromString(s)));
                }
            }

            this->writeToClient(clientFD, solution.c_str());
        }

    }

};


#endif //MILESTONE_2_MYTESTCLIENTHANDLER_H
