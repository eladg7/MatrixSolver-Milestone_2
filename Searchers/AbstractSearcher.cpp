#include "AbstractSearcher.h"
#include "CustomPriorityQueue.h"

vector<State> AbstractSearcher::backTrace(State s) {
    vector<State> backtrace;
    while (s.getFather()) {
        backtrace.insert(backtrace.begin(), s);
        s = *(s.getFather());
    }
    return backtrace;
}


State AbstractSearcher::popFromOpenQueue() {
    State s = openStateList.top();
    openStateList.pop();
    return s;
}

void AbstractSearcher::removeFromOpenQueue(State s) {
    CustomPriorityQueue <State> newQueue;
    auto it = openStateList.find(s);
    while (!openStateList.empty()) {
        State removedState = popFromOpenQueue();
        if (s == removedState) {
            continue;
        }
        newQueue.push(removedState);
    }
    openStateList = newQueue;
}

void AbstractSearcher::addToOpenQueue(State s) {
    openStateList.push(s);
}

