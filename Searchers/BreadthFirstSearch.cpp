#include "BreadthFirstSearch.h"

vector<State*> BreadthFirstSearch::search(Searchable *searchable) {
    State *initial = searchable->getInitialState();
    initial->setCost(searchable->getCostToGetToNode(initial));
    addToQueue(initial);
    State goalState = searchable->getGoalState();
    while (!openStateList.empty()) {
        State* n = popFromQueue();
        this->numberOfNodes++;

        if (*n == goalState) {
            return Searcher::backTrace(n);
        }
        vector<State*> succerssors = searchable->getAllPossibleStates(n);
        for (State *s:succerssors) {
            if (s->getCurrentCost() >
                    n->getCurrentCost() + searchable->getCostToGetToNode(s)) {
                removeFromQueue(s);
                s->setCost(n->getCurrentCost() + searchable->getCostToGetToNode(s));
                s->setCameFrom(n);
                addToQueue(s);
            }
        }
    }
}