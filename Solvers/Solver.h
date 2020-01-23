#ifndef MILESTONE_2_SOLVER_H
#define MILESTONE_2_SOLVER_H

#include "../Searchables/Searchable.h"
#include "../Searchers/Searcher.h"

using namespace std;

template<typename P, typename S>
class Solver {
public:
    virtual void createProblemFromString(const string &str) = 0;

    virtual string toString(const S &solution) = 0;

    virtual S solve(const P &problem) = 0;

    virtual string getSearcherName() = 0;
};

#endif //MILESTONE_2_SOLVER_H
