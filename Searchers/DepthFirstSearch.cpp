#include "DepthFirstSearch.h"

void DepthFirstSearch::addToStack(State s) {
    openStateList.push(s);
}

State DepthFirstSearch::popFromStack() {
    State s = openStateList.top();
    openStateList.pop();
    return s;
}

void DepthFirstSearch::removeFromStack(State s) {
    stack<State> newStack;
    stack<State> temp;
    while (!openStateList.empty()) {
        State tempState = popFromStack();
        if (tempState == s) {
            continue;
        }
        temp.push(tempState);
    }
    while (!temp.empty()) {
        State tempState = popFromStack();
        newStack.push(tempState);
    }
    openStateList.swap(newStack);
}

vector<State> DepthFirstSearch::search(Searchable *searchable) {
    State initial = searchable->getInitialState();
    initial.setCost(0);
    addToStack(initial);
    State goalState = searchable->getGoalState();
    while (!openStateList.empty()) {
        State n = popFromStack();
        this->numberOfNodes++;

        if (n == goalState) {
            return Searcher::backTrace(n);
        }
        vector<State> succerssors = searchable->getAllPossibleStates(n);
        for (State &s:succerssors) {
            if (s.getCost() >
                n.getCost() + searchable->getEdgeCost(s, n)) {
                removeFromStack(s);
                s.setCost(n.getCost() + searchable->getEdgeCost(s, n));
                addToStack(s);
            }
        }
    }
}