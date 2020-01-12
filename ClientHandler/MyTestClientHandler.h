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

    string getSolutionFromKey(string &key) {
        string solution;
        if (cm->keyExist(key)) {
            solution = solver->toString(cm->get(key));
        } else {
            StringUtils::eraseAllSubStr(key, "\r");
            solution = solver->toString(solver->solve(key));
            // todo cm->insert(solution); dont know how to represent matrix in key.
        }
        return solution;
    }

    virtual void handleClient(int clientFD, bool *isRunning) {
        char buffer[8 * BUFFER_SIZE] = {0};
        char tempBuffer[BUFFER_SIZE] = {0};
        int isRead = 0;
        string solution;

        while (*isRunning) {
            isRead = read(clientFD, tempBuffer, sizeof(buffer));
            if (isRead <= 0) {//error getting info from client.
                cerr << "Couldn't read from client." << endl;
                break;
            }
            ClientHandler::rnInTheEnd(tempBuffer);
            string tempStrBuffer = tempBuffer;
            if (StringUtils::endsWith(tempStrBuffer, "end")) {
                string key = (buffer + tempStrBuffer+"\r");//added /r tp erase this specific
                StringUtils::eraseAllSubStr(key, "\nend\r");

                solution = getSolutionFromKey(key);
                this->writeToClient(clientFD, solution);
                memset(buffer, 0, sizeof buffer);
                break;
            }

            strcat(buffer, tempBuffer);
            strcat(buffer, "\n");
            memset(tempBuffer, 0, sizeof tempBuffer);


        }
    }
};


#endif //MILESTONE_2_MYTESTCLIENTHANDLER_H
