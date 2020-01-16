//
// Created by yekaterina on 10/01/2020.
//

#ifndef MILESTONE_2_STATE_H
#define MILESTONE_2_STATE_H

#include <string>
#include <cstring>
#include <cmath>

using namespace std;

class State {
private:
    string stateDescription;
    double cost = INFINITY;
    State *cameFrom;

public:
    State() { cameFrom = nullptr; }

    void init(string state) {
        stateDescription = state;
    }

    State(const State &s) {//copy
        stateDescription = s.getDescription();

        cost = s.getCurrentCost();
        cameFrom = s.cameFrom;
    }


    State(string state, State *camefrom) {
        stateDescription = state;
        this->cameFrom = camefrom;
    }

    void setCameFrom(State *s) { cameFrom = s; }

    State *getFather() {
        return cameFrom;
    }


    string getDescription() const {
        return stateDescription;
    }


    double getCurrentCost() const { return cost; }

    void setCost(double c) { this->cost = c; }

    friend bool operator>(const State &s1, const State &s2) {
        return s1.cost > s2.cost;
    }

    friend bool operator>=(const State &s1, const State &s2) {
        return s1.cost >= s2.cost;
    }

    friend bool operator<(const State &s1, const State &s2) {
        return s1.cost < s2.cost;
    }

    friend bool operator<=(const State &s1, const State &s2) {
        return s1.cost <= s2.cost;
    }

    friend bool operator==(const State &s1, const State &s2) {
        return s1.getDescription() == s2.getDescription();
    }

    friend bool operator!=(const State &s1, const State &s2) {
        return s1.getDescription() != s2.getDescription();
    }

};


#endif //MILESTONE_2_STATE_H
