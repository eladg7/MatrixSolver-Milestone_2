#ifndef MILESTONE_2_DEPTHFIRSTSEARCH_H
#define MILESTONE_2_DEPTHFIRSTSEARCH_H


#include <stack>
#include "AbstractQueueSearchers.h"

class DepthFirstSearch : public Searcher {
private:
    stack<State *> openStack{};
    int numberOfNodes = 0;

    State *popFromStack();

    void addToStack(State *s);

    void removeFromStack(State *s);

public:
    virtual vector<State *> search(Searchable *searchable);

    int getNumberOfNodesEvaluated() { return numberOfNodes; }

    virtual string getTypeAsString() {
        return "DFS_SEARCHER";
    }
};


#endif //MILESTONE_2_DEPTHFIRSTSEARCH_H
