#ifndef MILESTONE_2_ASTAR_H
#define MILESTONE_2_ASTAR_H

#include <map>
#include <set>
#include <limits>
#include "Searcher.h"
#include "CustomPriorityQueue.h"

using namespace std;

struct statesFScoreComperator {
    map<State *, double> fScore;

    explicit statesFScoreComperator(map<State *, double> &fScore) {
        this->fScore = fScore;
    }

    inline bool operator()(State *state1, State *state2) {
        return fScore.at(state1) < fScore.at(state2);
    }
};

class Astar : public Searcher {
private:
    static void initScore(map<State *, double> *gScore);

    static vector<State *> reconstruct_path(map<State *, State *> cameFrom, State *current);

public:
    virtual vector<State *> search(Searchable *searchable);

    virtual int getNumberOfNodesEvaluated();
};

#endif //MILESTONE_2_ASTAR_H
