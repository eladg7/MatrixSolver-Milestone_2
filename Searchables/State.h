//
// Created by yekaterina on 10/01/2020.
//

#ifndef MILESTONE_2_STATE_H
#define MILESTONE_2_STATE_H

#include <string>
#include <cstring>

using namespace std;

class State {
private:
    string stateDesc;
    double cost;
    State *cameFrom;
public:
    State(string state) {
        stateDesc = state;
    }

    bool Equals(State s) {
        return s.stateDesc==this->stateDesc;
    }

};


#endif //MILESTONE_2_STATE_H
