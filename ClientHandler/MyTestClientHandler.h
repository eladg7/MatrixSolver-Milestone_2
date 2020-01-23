#ifndef MILESTONE_2_MYTESTCLIENTHANDLER_H
#define MILESTONE_2_MYTESTCLIENTHANDLER_H


#include "ClientHandler.h"
#include "../StringUtils.h"

#define BUFFER_SIZE 4096

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

    virtual string getSearcherName() {
        return this->solver->getSearcherName();
    }

    string getSolutionFromKey(string &key) {
        S solution;
        string strSolution;
        StringUtils::eraseAllSubStr(key, "\r");
        string temp = getSearcherName() + "_" + key;
        if (cm->keyExist(temp)) {
            strSolution = cm->get(temp);
        } else {
            solution = solver->solve(key);
            strSolution = solver->toString(solution);
            char *copy = new char[strSolution.length() + 1];
            strcpy(copy, strSolution.c_str());
            //casting to char*, to avoid const
            cm->insert(temp, copy, strSolution.length()); //no +1 bytes number
        }

        return strSolution;
    }

    virtual void handleClient(int clientFD) {
        string buffer;
        char tempBuffer[BUFFER_SIZE] = {0};
        int isRead = 0;
        string solution;

        while (true) {
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
                copy.erase(copy.length() - 3);
                buffer = copy;
                solution = getSolutionFromKey(buffer);
                this->writeToClient(clientFD, solution);
                buffer.clear();
                break;
            }

            memset(tempBuffer, 0, BUFFER_SIZE);
            usleep(5000);
        }
    }

};


#endif //MILESTONE_2_MYTESTCLIENTHANDLER_H
