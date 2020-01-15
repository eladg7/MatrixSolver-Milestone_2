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
        string solution;
        StringUtils::eraseAllSubStr(key, "\r");
        if (cm->keyExist(key)) {
            char *str = cm->get(key);
            solution = str;
            solver->toString(solution);
        } else {
            solution = solver->toString(solver->solve(key));
            char *temp = new char[sizeof(solution)];
            strcpy(temp, solution.c_str());
//            cm->insert(key, temp);
            delete[]temp;
        }
        return solution;
    }

    virtual void handleClient(int clientFD, bool *isRunning) {
        string buffer;
        char tempBuffer[BUFFER_SIZE] = {0};
        int isRead = 0;
        string solution;

        while (*isRunning) {
            isRead = read(clientFD, tempBuffer, sizeof(tempBuffer));
            if (isRead <= 0) {//error getting info from client.
                cerr << "Couldn't read from client." << endl;
                break;
            }

            string tempStrBuffer = tempBuffer;
            buffer += tempStrBuffer;
            string copy = buffer;
            StringUtils::rtrim(copy);
            if (StringUtils::endsWith(copy, "end")) {
                copy.erase(copy.length() - 3);
                buffer = copy;
                solution = getSolutionFromKey(buffer);
                this->writeToClient(clientFD, solution);
                buffer.clear();
                break;
            }

            memset(tempBuffer, 0, sizeof tempBuffer);
        }
    }
};


#endif //MILESTONE_2_MYTESTCLIENTHANDLER_H
