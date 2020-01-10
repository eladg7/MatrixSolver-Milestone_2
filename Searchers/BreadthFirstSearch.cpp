#include "BreadthFirstSearch.h"

vector<State> BreadthFirstSearch::search(Searchable *searchable) {
    State initial = searchable->getInitialState();
    initial.setCost(0);
    addToQueue(initial);
    State goalState = searchable->getGoalState();
    while (!openStateList.empty()) {
        State n = popFromQueue();
        this->numberOfNodes++;

        if (n == goalState) {
            return Searcher::backTrace(n);
        }
        vector<State> succerssors = searchable->getAllPossibleStates(n);
        for (State &s:succerssors) {
            if (s.getCost() >
                n.getCost() + searchable->getEdgeCost(s, n)) {
                removeFromQueue(s);
                s.setCost(n.getCost() + searchable->getEdgeCost(s, n));
                addToQueue(s);
            }
        }
    }
}