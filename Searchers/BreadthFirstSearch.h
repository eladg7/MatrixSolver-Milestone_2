#ifndef MILESTONE_2_BREADTHFIRSTSEARCH_H
#define MILESTONE_2_BREADTHFIRSTSEARCH_H


#include <queue>
#include "AbstractQueueSearchers.h"

class BreadthFirstSearch : public Searcher {
    queue<State *> openStateList{};
    int numberOfNodes = 0;


public:
    virtual vector<State *> search(Searchable *searchable);

    State *popFromQueue();

    void addToQueue(State *s);

    void removeFromQueue(State *s);

    virtual int getNumberOfNodesEvaluated() {
        return numberOfNodes;
    }

    virtual string getTypeAsString() {
        return "BreadthFS_SEARCHER";
    }


    virtual ~BreadthFirstSearch() = default;
};


#endif //MILESTONE_2_BREADTHFIRSTSEARCH_H
