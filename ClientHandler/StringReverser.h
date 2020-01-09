#ifndef MILESTONE_2_STRINGREVERSER_H
#define MILESTONE_2_STRINGREVERSER_H

#include <string>
#include "Solver.h"
#include <string>
#include <algorithm>

using namespace std;

class StringReverser : public Solver<string, string> {
public:
    string solve(string str) override {
        string copy = str;
        reverse(copy.begin(), copy.end());
        return copy;
    }
};

#endif //MILESTONE_2_STRINGREVERSER_H
