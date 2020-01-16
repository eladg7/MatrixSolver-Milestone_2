#include "BreadthFirstSearch.h"

vector<State *> BreadthFirstSearch::search(Searchable *searchable) {
    this->numberOfNodes = 0;
    State *initial = searchable->getInitialState();
    initial->setCost(searchable->getCostToGetToNode(initial));
    addToQueue(initial);
    State goalState = searchable->getGoalState();
    while (!openStateList.empty()) {
        State *n = popFromQueue();
        this->numberOfNodes++;

        if (*n == goalState) {
            return Searcher::backTraceAndUpdateCost(n, searchable);
        }
        vector<State *> succerssors = searchable->getAllPossibleStates(n);
        for (State *s:succerssors) {
            if (s->getCurrentCost() == INFINITY) {//not visited
                s->setCost(0);
                s->setCameFrom(n);
                addToQueue(s);
            }
        }
    }

    return {};
}

State *BreadthFirstSearch::popFromQueue() {
    State *s = openStateList.front();
    openStateList.pop();
    return s;
}

void BreadthFirstSearch::removeFromQueue(State *s) {
    queue<State *> newQueue;
    while (!openStateList.empty()) {
        State *removedState = popFromQueue();
        if (*s == *removedState) {
            continue;
        }
        newQueue.push(removedState);
    }
    openStateList.swap(newQueue);
}

void BreadthFirstSearch::addToQueue(State *s) {
    openStateList.push(s);
}