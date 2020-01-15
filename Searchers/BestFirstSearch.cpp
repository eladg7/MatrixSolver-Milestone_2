#include <map>
#include "BestFirstSearch.h"


vector<State *> BestFirstSearch::search(Searchable *searchable) {
    this->numberOfNodes = 0;
    State *initial = searchable->getInitialState();
    initial->setCost(searchable->getCostToGetToNode(initial));
    addToQueue(initial);
    map<string, State*> closed;
    State goalState = searchable->getGoalState();
    while (!priorityQueue.empty()) {
        State *n = popFromQueue();
        closed[n->getDescription()] = n;
        this->numberOfNodes++;

        if (*n == goalState) {
            return Searcher::backTrace(n);
        }
        vector<State *> succerssors = searchable->getAllPossibleStates(n);
        for (State *s:succerssors) {
            if (closed.find(s->getDescription()) == closed.end()
                && !priorityQueue.contains(*s)) { //not in closed and not in open
                s->setCameFrom(n);
                s->setCost(n->getCurrentCost() + searchable->getCostToGetToNode(s));
                addToQueue(s);
            } else if (s->getCurrentCost() >
                       n->getCurrentCost() + searchable->getCostToGetToNode(s)) {
                if (closed.find(s->getDescription()) != closed.end()) {// in closed
                    closed.erase(closed.find(s->getDescription()));
                } else {// in open
                    removeFromQueue(s);
                }
                s->setCost(n->getCurrentCost() + searchable->getCostToGetToNode(s));
                s->setCameFrom(n);
                addToQueue(s);
            }
        }

    }
}


