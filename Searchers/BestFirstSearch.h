#ifndef MILESTONE_2_BESTFIRSTSEARCH_H
#define MILESTONE_2_BESTFIRSTSEARCH_H

#include "Searcher.h"

template <typename P,typename S>
class BestFirstSearch:public Searcher<P,S> {


public:
    virtual S search(Searchable searchable);
};


#endif //MILESTONE_2_BESTFIRSTSEARCH_H
