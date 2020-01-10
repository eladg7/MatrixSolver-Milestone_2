//
// Created by yekaterina on 10/01/2020.
//

#ifndef MILESTONE_2_STATE_H
#define MILESTONE_2_STATE_H

#include <string>
#include <cstring>

using namespace std;
enum color {
    Unvisited, Visited, Examined
};

class State {
private:
    string stateDescription;
    double cost;
    State *cameFrom;
    color colorOfState = Unvisited;


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

    bool getColor() { return colorOfState; }

    void markAsVisited() { colorOfState = Visited; }

    void markAsExamined() { colorOfState = Examined; }

    bool operator>(const State &s1) {

        return cost > s1.cost;
    }

    bool operator>=(const State &s1) {

        return cost >= s1.cost;
    }

    bool operator<(const State &s1) {

        return cost < s1.cost;
    }

    bool operator<=(const State &s1) {

        return cost <= s1.cost;
    }

    bool operator==(const State &s1) {

        return stateDescription == s1.stateDescription;
    }

};


#endif //MILESTONE_2_STATE_H
