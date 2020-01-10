#ifndef MILESTONE_2_ABSTRACTSEARCHER_H
#define MILESTONE_2_ABSTRACTSEARCHER_H

#include "Searcher.h"

class AbstractSearcher : public Searcher {
protected:
    CustomPriorityQueue<State> openStateList;
    vector<State> backTrace(State s);

public:
    State popFromOpenQueue();

    void addToOpenQueue(State s);

    void removeFromOpenQueue(State s);
};

#endif //MILESTONE_2_ABSTRACTSEARCHER_H
