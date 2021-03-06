//
// Created by yekaterina on 11/01/2020.
//

#ifndef MILESTONE_2_MATRIXSOLVER_H
#define MILESTONE_2_MATRIXSOLVER_H


#include "Solver.h"
#include "../Searchables/MatrixMaze.h"
#include "../StringUtils.h"

#define NO_PATH_FOUND  "Could not find path to solve this problem!"

class MatrixSolver : public Solver<string, vector<State *>> {

private:
    Searcher *searcher;
    MatrixMaze *searchable{};
    string solution = "";

    static bool areInitialAndGoalValid(const State &initial, const State &goal, int N, int M);

public:
    explicit MatrixSolver(Searcher *s) {
        searcher = s;
    }

    virtual void createProblemFromString(const string &str);

    virtual string toString(const vector<State *> &backtrace);

    virtual vector<State *> solve(const string &problem);

    virtual int getNumberOfNodesEvaluated() {
        return this->searcher->getNumberOfNodesEvaluated();
    }

    virtual string getSearcherName() {
        return this->searcher->getTypeAsString();
    }

    ~MatrixSolver() {
        delete searchable;
    }
};


#endif //MILESTONE_2_MATRIXSOLVER_H
