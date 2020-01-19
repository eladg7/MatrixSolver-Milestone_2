#include <algorithm>
#include <iostream>
#include <iomanip>
#include "MatrixSolver.h"

#define POINTS_REGEX "^\\d+,\\d+$"

void MatrixSolver::createProblemFromString(const string &str) {
    vector<string> matrix = StringUtils::split(str, '\n');
    State goal;
    goal.init(matrix.back());
    matrix.pop_back();
    State initial;
    initial.init(matrix.back());
    matrix.pop_back();
    if (!StringUtils::matchRegex(initial.getDescription(), POINTS_REGEX)
        || !StringUtils::matchRegex(goal.getDescription(), POINTS_REGEX)) {
        throw "Could not parse initial or goal position";
    }

    int M = (StringUtils::split(matrix.front(), ',')).size();
    int N = matrix.size();

    if (!areInitialAndGoalValid(initial, goal, N, M)) {
        throw "Starting/end position invalid";
    }

    auto **mat = new double *[N];
    for (int i = 0; i < N; i++) {
        mat[i] = new double[M];
        vector<string> nodes = StringUtils::split(matrix.front(), ',');
        matrix.erase(matrix.begin());
        for (int j = 0; j < M; j++) {
            string doub = StringUtils::trim(nodes.front());
            mat[i][j] = stod(doub);
            auto it = nodes.begin();
            nodes.erase(it);
        }
    }

    searchable = new MatrixMaze(mat, N, M, initial, goal);
}

bool MatrixSolver::areInitialAndGoalValid(const State &initial, const State &goal, int N, int M) {
    bool valid = true;
    auto initialSplitted = StringUtils::split(initial.getDescription(), ',');
    auto goalSplitted = StringUtils::split(goal.getDescription(), ',');

    auto xInitial = stod(initialSplitted.at(0));
    auto yInitial = stod(initialSplitted.at(1));
    auto xGoal = stod(goalSplitted.at(0));
    auto yGoal = stod(goalSplitted.at(1));

    if (xInitial < 0 || yInitial < 0 || xGoal < 0 || yGoal < 0
        || xInitial >= N || yInitial >= M || xGoal >= N || yGoal >= M) {
        valid = false;
    }

    return valid;
}

string MatrixSolver::toString(const vector<State *> &backtrace) {
    if (!backtrace.empty()) {
        for (State *s:backtrace) {
            if (*s == *searchable->getInitialState()) {
                continue;
            }
            std::stringstream stream;
            stream << std::fixed << std::setprecision(2) << s->getCurrentCost();
            solution += searchable->getDirection(s) + " (" +
                        stream.str() + "), ";
        }
        solution = solution.substr(0, solution.length() - 2);
    } else {
        solution = NO_PATH_FOUND;
    }
    return solution;
}

vector<State *> MatrixSolver::solve(const string &problem) {
    solution.clear();
    try {
        createProblemFromString(problem);
    } catch (...) {
        cerr << "And error has occurred: Could not parse initial or goal position "
                "or the initial/goal position are invalid" << endl;
        return {};
    }

    vector<State *> backtrace = searcher->search(searchable);
    cout << getNumberOfNodesEvaluated() << endl;
    return backtrace;
}