//
// Created by yekaterina on 10/01/2020.
//

#ifndef MILESTONE_2_SEARCHABLE_H
#define MILESTONE_2_SEARCHABLE_H

#include <vector>
#include "State.h"

class Searchable {


public:
    virtual State* getInitialState() = 0;

    virtual State getGoalState() = 0;

    virtual vector<State*> getAllPossibleStates(State *s) = 0;

    virtual double getCostToGetToNode(State *s) = 0;

};

#endif //MILESTONE_2_SEARCHABLE_H
