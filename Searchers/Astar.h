#ifndef MILESTONE_2_ASTAR_H
#define MILESTONE_2_ASTAR_H

#include <map>
#include <set>
#include <limits>
#include "Searcher.h"
#include "CustomPriorityQueue.h"

using namespace std;

class Astar : public Searcher {
private:
    int numberOfNodesEvaluated = 0;

    static State *findState(const vector<State *> &allStates, const State &stateToFind);

public:
    virtual vector<State *> search(Searchable *searchable);

    virtual int getNumberOfNodesEvaluated();

    virtual string getTypeAsString() {
        return "Astar_SEARCHER";
    }
};

#endif //MILESTONE_2_ASTAR_H
