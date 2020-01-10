#ifndef MILESTONE_2_DEPTHFIRSTSEARCH_H
#define MILESTONE_2_DEPTHFIRSTSEARCH_H


#include <stack>
#include "AbstractQueueSearchers.h"

class DepthFirstSearch : public Searcher {
private:
    stack<State> openStateList{};
    int numberOfNodes = 0;

    State popFromStack();

    void addToStack(State s);

    void removeFromStack(State s);

    vector<State> backTrace(State s);

public:
    virtual vector<State> search(Searchable *searchable);
};


#endif //MILESTONE_2_DEPTHFIRSTSEARCH_H
