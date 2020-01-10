#ifndef MILESTONE_2_SEARCHER_H
#define MILESTONE_2_SEARCHER_H

#include "../Searchables/Searchable.h"


class Searcher {
public:
   virtual vector<State> search(Searchable *searchable) = 0;

};

#endif //MILESTONE_2_SEARCHER_H
