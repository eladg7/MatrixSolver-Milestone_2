#include "AbstractQueueSearchers.h"
#include "CustomPriorityQueue.h"


State *AbstractQueueSearchers::popFromQueue() {
    State *s = nullptr;
    bool flag = false;
    for ( auto it = openQueue.begin(); it != openQueue.end(); ++it) {
        string si = (*it)->getDescription();
        State si1 = priorityQueue.top();
        string si2 = si1.getDescription();
        if (si == si2) {
            s = *it;
            openQueue.erase(it);
            flag = true;
            break;
        }
    }
    if (!flag) {
        int x = 2;
    }
    priorityQueue.pop();
    return s;
}

void AbstractQueueSearchers::eraseFromPointerQueue(State *s) {

    for ( auto it = openQueue.begin(); it != openQueue.end(); ++it) {
        if ((*it)->getDescription() ==
            s->getDescription()) {
            openQueue.erase(it);
            break;
        }
    }
}

void AbstractQueueSearchers::removeFromQueue(State *s) {
    eraseFromPointerQueue(s);
    CustomPriorityQueue<State, vector<State>, std::greater<>> newQueue;

    while (!priorityQueue.empty()) {
        State *removedState = popFromQueue();
        if (*s == *removedState) {
            continue;
        }
        newQueue.push(*removedState);
    }

    priorityQueue.swap(newQueue);
}

void AbstractQueueSearchers::addToQueue(State *s) {
    openQueue.push_back(s);
    priorityQueue.push(*s);
}




