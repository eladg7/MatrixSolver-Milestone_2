#ifndef MILESTONE_2_SEARCHER_H
#define MILESTONE_2_SEARCHER_H

#include "../Searchables/Searchable.h"

template<typename P, typename S>
class Searcher {
public:
   virtual S search(Searchable searchable) = 0;

};

#endif //MILESTONE_2_SEARCHER_H
