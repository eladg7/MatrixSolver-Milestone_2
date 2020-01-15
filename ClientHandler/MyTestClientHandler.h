#ifndef MILESTONE_2_MYTESTCLIENTHANDLER_H
#define MILESTONE_2_MYTESTCLIENTHANDLER_H


#include "ClientHandler.h"
#include "../StringUtils.h"

#define BUFFER_SIZE 1024

template<typename P, typename S, typename T>
class MyTestClientHandler : public ClientHandler {
private:
    Solver<P, S> *solver;
    CacheManager<T> *cm;

public:
    MyTestClientHandler(Solver<P, S> *s, CacheManager<T> *cache) {
        solver = s;
        cm = cache;
    }

    string getSolutionFromKey(string &key) {
        S solution;
        string strSolution;
        StringUtils::eraseAllSubStr(key, "\r");
        if (cm->keyExist(key)) {
            strSolution = cm->get(key);
        } else {
            solution = solver->solve(key);
            strSolution = solver->toString(solution);
            //casting to char*, to avoid const
            cm->insert(key, (char *) strSolution.c_str(), strSolution.length());//no +1 bytes number
        }

        return strSolution;
    }

    virtual void handleClient(int clientFD, bool *isRunning) {
        string buffer;
        char tempBuffer[BUFFER_SIZE] = {0};
        int isRead = 0;
        string solution;

        while (*isRunning) {
            isRead = read(clientFD, tempBuffer, BUFFER_SIZE);
            if (isRead <= 0) {//error getting info from client.
                cerr << "Couldn't read from client." << endl;
                break;
            }

            string tempStrBuffer = tempBuffer;
            buffer += tempStrBuffer;
            string copy = buffer;
            StringUtils::rtrim(copy);
            if (StringUtils::endsWith(copy, "end")) {
                buffer = copy.substr(0, copy.length() - 3);
                solution = getSolutionFromKey(buffer);
                this->writeToClient(clientFD, solution);
                buffer.clear();
                break;
            }

            memset(tempBuffer, 0,  BUFFER_SIZE);
        }
    }
};


#endif //MILESTONE_2_MYTESTCLIENTHANDLER_H
