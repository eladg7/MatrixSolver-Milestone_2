#include <map>
#include "BestFirstSearch.h"


vector<State*> BestFirstSearch::search(Searchable *searchable) {
    State *initial = searchable->getInitialState();
    initial->setCost(searchable->getCostToGetToNode(initial));
    addToQueue(initial);
    map<string, State*> closed;
    State goalState = searchable->getGoalState();
    while (!openStateList.empty()) {
        State* n = popFromQueue();
        this->numberOfNodes++;

        if (*n == goalState) {
            return Searcher::backTrace(n);
        }
        vector<State*> succerssors = searchable->getAllPossibleStates(n);
        for (State *s:succerssors) {
            if (closed.find(s->getDescription()) == closed.end()
                && !openStateList.contains(s)) { //not in closed and not in open
                //update came from in all in getAllPossible.
                addToQueue(s);
            } else if (s->getCurrentCost() >
                    n->getCurrentCost() + searchable->getCostToGetToNode(s)) {
                if (closed.find(s->getDescription()) != closed.end()) {
                    closed.erase(closed.find(s->getDescription()));
                } else {// in open
                    removeFromQueue(s);
                }
                s->setCost(n->getCurrentCost() + searchable->getCostToGetToNode(s));
                addToQueue(s);
            }
        }

    }
}


