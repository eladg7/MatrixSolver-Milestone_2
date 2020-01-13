#ifndef MILESTONE_2_SEARCHER_H
#define MILESTONE_2_SEARCHER_H

#include "../Searchables/Searchable.h"

class Searcher {
public:
    virtual vector<State *> search(Searchable *searchable) = 0;

    virtual int getNumberOfNodesEvaluated() = 0;

    vector<State *> backTrace(State *goal) {
        vector<State *> backtrace;
        while (goal->getFather() != nullptr) {
            backtrace.insert(backtrace.begin(), goal);
            goal = (*goal).getFather();
        }
        backtrace.insert(backtrace.begin(), goal);// first node
        return backtrace;
    }

    vector<State *> backTraceAndUpdateCost(State *s, Searchable *searchable) {
        vector<State *> route = Searcher::backTrace(s);
        auto it = route.begin();
        double cost = 0;
        for (; it < route.end(); it++) {
            cost += searchable->getCostToGetToNode(*it);
            (*it)->setCost(cost);
        }
        return route;

    }

};

#endif //MILESTONE_2_SEARCHER_H
