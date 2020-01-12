#ifndef MILESTONE_2_STRINGREVERSER_H
#define MILESTONE_2_STRINGREVERSER_H

#include "Solver.h"
#include <string>
#include <algorithm>

using namespace std;

class StringReverser : public Solver<string, string> {
public:
    virtual void createProblemFromString(const string &str) {}

    virtual string toString(const string &solution) {
        return solution;
    }

    virtual string solve(const string& str) {
        vector<string> splittedProblems = StringUtils::split(str, '\n');
        string result{};
        if (!splittedProblems.empty()) {
            unsigned int problemsCount = splittedProblems.size();
            for (int i = 0; i < problemsCount; i++) {
                reverse(splittedProblems.at(i).begin(), splittedProblems.at(i).end());
                result.append(splittedProblems.at(i));
                //  add \r\n only if it's not the last word
                if (i != problemsCount - 1) {
                    result.append("\r\n");
                }
            }
        }

        return result;
    }
};

#endif //MILESTONE_2_STRINGREVERSER_H
