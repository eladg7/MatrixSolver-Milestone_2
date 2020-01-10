//
// Created by yekaterina on 10/01/2020.
//

#ifndef MILESTONE_2_STATE_H
#define MILESTONE_2_STATE_H

#include <string>
#include <cstring>
#include <cmath>

using namespace std;

enum color {
    Unvisited, Visited, Examined
};

class State {
private:
    string stateDescription;
    double cost=INFINITY;
    State *cameFrom;
    color colorNode = Unvisited;

public:
    State(string state) {
        stateDescription = state;
        cameFrom = nullptr;
    }


    State(string state, State *camefrom) {
        stateDescription = state;
        this->cameFrom = camefrom;
    }

    State *getFather() {
        return cameFrom;
    }

    color getColor() { return colorNode; }

    void setVisited() {
        colorNode = Visited;
    }

    void setExamined() {
        colorNode = Examined;
    }

    string getDescription() { return stateDescription; }

    double getCost() { return cost; }

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
        return s1.stateDescription == s2.stateDescription;
    }

};


#endif //MILESTONE_2_STATE_H
