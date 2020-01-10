#include "BestFirstSearch.h"

vector<State> BestFirstSearch::backTrace(State s) {
    vector<State> backtrace;
    while (s.getFather()) {
        backtrace.insert(backtrace.begin(), s);
        s = *(s.getFather());
    }
    return backtrace;
}


State BestFirstSearch::popFromOpenQueue() {
    State s = openStateList.top();
    openStateList.pop();
    return s;
}

void BestFirstSearch::addToOpenQueue(State s) {
    openStateList.push(s);
}

vector<State> BestFirstSearch::search(Searchable *searchable) {
    addToOpenQueue(searchable->getInitialState());
    State goalState = searchable->getGoalState();
    while (openStateList.size() > 0) {
        State n = popFromOpenQueue();
        if (n == goalState) {
            return backTrace(n);
        }
        vector<State> succerssors = searchable->getAllPossibleStates(n);
        for (State s:succerssors) {
            if (s.getColor() == Unvisited) {
                s.markAsVisited();
                addToOpenQueue(s);
            }
        }
        n.markAsExamined();

    }
}
