#ifndef MILESTONE_2_SEARCHER_H
#define MILESTONE_2_SEARCHER_H

#include "../Searchables/Searchable.h"

class Searcher{
public:
   virtual vector<State*> search(Searchable *searchable) = 0;
    virtual int getNumberOfNodesEvaluated()=0;

    vector<State*> backTrace(State *s) {
        vector<State*> backtrace;
        while (s->getFather()!= nullptr) {
            backtrace.insert(backtrace.begin(), s);
            s = (*s).getFather();
        }
        return backtrace;
    }

};

#endif //MILESTONE_2_SEARCHER_H
