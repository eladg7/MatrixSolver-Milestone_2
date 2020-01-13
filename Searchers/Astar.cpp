#include "Astar.h"

vector<State *> Astar::search(Searchable *searchable) {
    // The set of discovered nodes that may need to be (re-)expanded.
    // Initially, only the start node is known.
    State *initialState = searchable->getInitialState();
    initialState->setCost(searchable->getCostToGetToNode(initialState));
    State goalState = searchable->getGoalState();
    map<State *, double> openSet;
    openSet[initialState] = 0;

    // For node n, cameFrom[n] is the node immediately preceding
    // it on the cheapest path from start to n currently known.
    map<State *, State *> cameFrom;

    // For node n, gScore[n] is the cost of the cheapest path from start to n currently known.
    map<State *, double> gScore;

    //  set cost of state s to infinity
    gScore[initialState] = initialState->getCurrentCost();

    // For node n, fScore[n] := gScore[n] + h(n).
    map<State *, double> fScore;
    fScore[initialState] = searchable->getCostToGetToNode(initialState);

    State *current = nullptr;
    double tentative_gScore = 0;
    while (!openSet.empty()) {
        current = openSet.begin()->first;
        ++this->numberOfNodesEvaluated;
        if (*current == goalState) {
            return backTrace(current);
        }

        openSet.erase(current);

        for (auto neighbor : searchable->getAllPossibleStates(current)) {
            // d(current,neighbor) is the weight of the edge from current to neighbor
            // tentative_gScore is the distance from start to the neighbor through current
            if (gScore.find(neighbor) == gScore.end()) {
                gScore[neighbor] = numeric_limits<double>::infinity();
            }

            tentative_gScore = gScore[current] + searchable->getCostToGetToNode(neighbor);

            if (tentative_gScore < gScore[neighbor]) {
                // This path to neighbor is better than any previous one. Record it!
                neighbor->setCameFrom(current);
                gScore[neighbor] = tentative_gScore;
                neighbor->setCost(tentative_gScore);
                fScore[neighbor] = gScore[neighbor] + searchable->getCostToGetToNode(neighbor);
                if (openSet.find(neighbor) == openSet.end()) {
                    openSet[neighbor] = fScore[neighbor];
                }
            }
        }
    }

    // Open set is empty but goal was never reached
    return {};
}

int Astar::getNumberOfNodesEvaluated() {
    return this->numberOfNodesEvaluated;
}