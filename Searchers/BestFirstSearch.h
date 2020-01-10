#ifndef MILESTONE_2_BESTFIRSTSEARCH_H
#define MILESTONE_2_BESTFIRSTSEARCH_H

#include "Searcher.h"
#include "CustomPriorityQueue.h"

using namespace std;
class BestFirstSearch : public Searcher {
    CustomPriorityQueue<State> openStateList;
    vector<State> backTrace(State s);
public:
    virtual vector<State> search(Searchable *searchable);

    State popFromOpenQueue();
    void addToOpenQueue(State s);
};


#endif //MILESTONE_2_BESTFIRSTSEARCH_H
