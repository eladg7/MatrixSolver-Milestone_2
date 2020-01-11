#ifndef MILESTONE_2_ABSTRACTQUEUESEARCHERS_H
#define MILESTONE_2_ABSTRACTQUEUESEARCHERS_H

#include "Searcher.h"
#include "CustomPriorityQueue.h"

using namespace std;

class AbstractQueueSearchers : public Searcher {
protected:
    CustomPriorityQueue<State*> openStateList{};
    int numberOfNodes = 0;

    State* popFromQueue();

    void addToQueue(State *s);

    void removeFromQueue(State *s);

public:
    virtual int getNumberOfNodesEvaluated() {
        return numberOfNodes;
    }


};

#endif //MILESTONE_2_ABSTRACTQUEUESEARCHERS_H
