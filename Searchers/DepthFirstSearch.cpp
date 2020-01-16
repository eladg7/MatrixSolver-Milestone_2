#include "DepthFirstSearch.h"

void DepthFirstSearch::addToStack(State *s) {
    openStack.push(s);
}

State *DepthFirstSearch::popFromStack() {
    State *s = openStack.top();
    openStack.pop();
    return s;
}

void DepthFirstSearch::removeFromStack(State *s) {
    stack<State *> newStack;
    stack<State *> temp;
    while (!openStack.empty()) {
        State *tempState = popFromStack();
        if (tempState == s) {
            continue;
        }
        temp.push(tempState);
    }
    while (!temp.empty()) {
        State *tempState = popFromStack();
        newStack.push(tempState);
    }
    openStack.swap(newStack);
}


vector<State *> DepthFirstSearch::search(Searchable *searchable) {
    this->numberOfNodes = 0;
    State *initial = searchable->getInitialState();
    initial->setCost(searchable->getCostToGetToNode(initial));
    addToStack(initial);
    State goalState = searchable->getGoalState();
    while (!openStack.empty()) {
        State *n = popFromStack();
        this->numberOfNodes++;

        if (*n == goalState) {
            return backTraceAndUpdateCost(n, searchable);
        }
        vector<State *> succerssors = searchable->getAllPossibleStates(n);
        for (State *s:succerssors) {
            if (s->getCurrentCost() == INFINITY) {
                s->setCost(0); //has been visited
                s->setCameFrom(n);
                addToStack(s);
            }
        }
    }

    return {};
}