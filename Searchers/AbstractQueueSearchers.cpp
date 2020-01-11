#include "AbstractQueueSearchers.h"
#include "CustomPriorityQueue.h"


State* AbstractQueueSearchers::popFromQueue() {
    State *s = openStateList.top();
    openStateList.pop();
    return s;
}

void AbstractQueueSearchers::removeFromQueue(State* s) {
    CustomPriorityQueue<State*> newQueue;
    while (!openStateList.empty()) {
        State* removedState = popFromQueue();
        if (*s == *removedState) {
            continue;
        }
        newQueue.push(removedState);
    }
    openStateList.swap(newQueue);
}

void AbstractQueueSearchers::addToQueue(State* s) {
    openStateList.push(s);
}




