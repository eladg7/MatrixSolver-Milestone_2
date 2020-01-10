#ifndef MILESTONE_2_BESTFIRSTSEARCH_H
#define MILESTONE_2_BESTFIRSTSEARCH_H

#include "Searcher.h"

class BestFirstSearch:public Searcher {


public:
    virtual string search(Searchable *searchable);
};


#endif //MILESTONE_2_BESTFIRSTSEARCH_H
