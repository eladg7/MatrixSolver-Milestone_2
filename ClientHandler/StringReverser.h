#ifndef MILESTONE_2_STRINGREVERSER_H
#define MILESTONE_2_STRINGREVERSER_H
#include "Solver.h"
#include <string>
#include <algorithm>

using namespace std;

class StringReverser : public Solver<string, string> {
public:
    virtual string createProblemFromString(const string &str){
        cout<< "inCreateProblem"<<endl;
        return "";
    }

    virtual string toString(string solution){
        cout<< "inToString"<<endl;
        return "";
    }

    virtual string solve(string str) {
        string copy = str;
        reverse(copy.begin(), copy.end());
        return copy;
    }
};

#endif //MILESTONE_2_STRINGREVERSER_H
