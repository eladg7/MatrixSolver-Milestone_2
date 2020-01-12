#ifndef MILESTONE_2_BREADTHFIRSTSEARCH_H
#define MILESTONE_2_BREADTHFIRSTSEARCH_H


#include <queue>
#include "AbstractQueueSearchers.h"

class BreadthFirstSearch : public AbstractQueueSearchers {

public:
    virtual vector<State*> search(Searchable *searchable);

};


#endif //MILESTONE_2_BREADTHFIRSTSEARCH_H
