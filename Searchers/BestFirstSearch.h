#ifndef MILESTONE_2_BESTFIRSTSEARCH_H
#define MILESTONE_2_BESTFIRSTSEARCH_H

#include "CustomPriorityQueue.h"
#include "AbstractQueueSearchers.h"

using namespace std;

class BestFirstSearch : public AbstractQueueSearchers {

public:
    virtual vector<State *> search(Searchable *searchable);

    virtual string getTypeAsString() {
        return "BestFS_SEARCHER";
    }
};


#endif //MILESTONE_2_BESTFIRSTSEARCH_H
