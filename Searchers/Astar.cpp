#include <algorithm>
#include "Astar.h"

vector<State *> Astar::search(Searchable *searchable) {
    this->numberOfNodesEvaluated = 0;
    // The set of discovered nodes that may need to be (re-)expanded.
    // Initially, only the start node is known.
    State *initialState = searchable->getInitialState();
    initialState->setCost(searchable->getCostToGetToNode(initialState));
    State goalState = searchable->getGoalState();
    CustomPriorityQueue<State, vector<State>, greater<>> openSet;
    initialState->setCost(searchable->getCostToGetToNode(initialState));
    vector<State *> currentStates = {initialState};
    openSet.push(*currentStates.at(0));

    // For node n, cameFrom[n] is the node immediately preceding
    // it on the cheapest path from start to n currently known.
    map<State *, State *> cameFrom;

    // For node n, gScore[n] is the cost of the cheapest path from start to n currently known.
    map<State *, double> gScore;

    //  set cost of state s to infinity
    gScore[initialState] = initialState->getCurrentCost();

    // For node n, fScore[n] := gScore[n] + h(n).
    map<State *, double> fScore;
    fScore[initialState] = gScore[initialState] + searchable->getHeuristic(initialState);

    State current;
    double tentative_gScore = 0;
    State *currentStatePointer = nullptr;
    while (!openSet.empty()) {
        current = openSet.top();
        currentStatePointer = findState(currentStates, current);
        ++this->numberOfNodesEvaluated;
        if (current == goalState) {
            return backTrace(currentStatePointer);
        }

        openSet.pop();
        currentStates.erase(remove(currentStates.begin(), currentStates.end(),
                                   currentStatePointer), currentStates.end());

        for (auto neighbor : searchable->getAllPossibleStates(currentStatePointer)) {
            // d(current,neighbor) is the weight of the edge from current to neighbor
            // tentative_gScore is the distance from start to the neighbor through current
            if (gScore.find(neighbor) == gScore.end()) {
                gScore[neighbor] = numeric_limits<double>::infinity();
            }

            tentative_gScore = gScore[currentStatePointer] + searchable->getCostToGetToNode(neighbor);

            if (tentative_gScore < gScore[neighbor]) {
                // This path to neighbor is better than any previous one. Record it!
                neighbor->setCameFrom(currentStatePointer);
                gScore[neighbor] = tentative_gScore;
                fScore[neighbor] = gScore[neighbor] + searchable->getHeuristic(neighbor);
                neighbor->setCost(gScore[neighbor]);
                if (!openSet.contains(*neighbor)) {
                    openSet.push(*neighbor);
                    currentStates.push_back(neighbor);
                }
            }
        }
    }

    // Open set is empty but goal was never reached
    return {};
}

State *Astar::findState(const vector<State *> &allStates, const State &stateToFind) {
    for (auto s : allStates) {
        if (s->getDescription() == stateToFind.getDescription()) {
            return s;
        }
    }

    return nullptr;
}

int Astar::getNumberOfNodesEvaluated() {
    return this->numberOfNodesEvaluated;
}