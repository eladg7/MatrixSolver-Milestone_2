#include <map>
#include "BestFirstSearch.h"



vector<State> BestFirstSearch::search(Searchable *searchable) {
    addToOpenQueue(searchable->getInitialState());
    map<string, State> closed;
    State goalState = searchable->getGoalState();
    while (!openStateList.empty()) {
        State n = popFromOpenQueue();
        if (n == goalState) {
            return backTrace(n);
        }
        vector<State> succerssors = searchable->getAllPossibleStates(n);
        for (State &s:succerssors) {
            if (closed.find(s.getDescription()) == closed.end()
                && !openStateList.contains(s)) { //not in closed and not in open
                //update came from in all in getAllPossible.
                addToOpenQueue(s);
            } else if (s.getCost() >
                       n.getCost() + searchable->getEdgeCost(s, n)) {
                if (closed.find(s.getDescription()) != closed.end()) {
                    closed.erase(closed.find(s.getDescription()));
                } else {// in open
                    removeFromOpenQueue(s);
                }
                s.setCost(n.getCost() + searchable->getEdgeCost(s, n));
                addToOpenQueue(s);
            }
        }

    }
}


