#include "AbstractQueueSearchers.h"
#include "CustomPriorityQueue.h"


State *AbstractQueueSearchers::popFromQueue() {
    State *s = nullptr;
    for ( auto it = openQueue.begin(); it != openQueue.end(); ++it) {
        if ((*it)->getDescription() ==
        priorityQueue.top().getDescription()) {
            s = *it;
            openQueue.erase(it);

            break;
        }
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




