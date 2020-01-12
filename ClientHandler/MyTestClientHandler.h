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
    MyTestClientHandler(Solver<P, S> *s, CacheManager<S> *cache) {
        solver = s;
        cm = cache;
    }

    vector<string> getSolutionFromKey(string &key) {
        vector<string> solution;
        if (cm->keyExist(key)) {
            solution.push_back(solver->toString(cm->get(key)));
        } else {
//            StringUtils::eraseAllSubStr(key, "\r");
            solution.push_back(solver->toString(
                    solver->solve(solver->createProblemFromString(key))));

        }
        return solution;
    }

    virtual void handleClient(int clientFD, bool *isRunning) {
        char buffer[4 * BUFFER_SIZE] = {0};
        char tempBuffer[BUFFER_SIZE] = {0};
        int isRead = 0;
        vector<string> solution;

        while (*isRunning) {
            isRead = read(clientFD, tempBuffer, sizeof(buffer));
            if (isRead <= 0) {//error getting info from client.
                cerr << "Couldn't read from client." << endl;
                break;
            }
            ClientHandler::rnInTheEnd(tempBuffer);
            string tempStrBuffer = tempBuffer;
            if (StringUtils::endsWith(tempStrBuffer, "end")) {
                string key = buffer +
                             tempStrBuffer.substr(
                                     0, tempStrBuffer.length() - 5);//\r\nend
                solution = getSolutionFromKey(key);
                this->writeToClient(clientFD, solution);
                memset(buffer, 0, sizeof buffer);
                break;
            }

            strcat(buffer, tempBuffer);
            strcat(buffer, "/n");
            memset(tempBuffer, 0, sizeof tempBuffer);
        }
    }
};


#endif //MILESTONE_2_MYTESTCLIENTHANDLER_H
