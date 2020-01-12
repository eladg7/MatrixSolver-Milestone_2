#include "MatrixSolver.h"

void MatrixSolver::createProblemFromString(const string &str) {

    vector<string> matrix = StringUtils::split(str, '\n');
    State goal;
    goal.init(matrix.back());
    matrix.pop_back();
    State initial;
    initial.init(matrix.back());
    matrix.pop_back();
    int M = (StringUtils::split(matrix.front(), ',')).size();
    int N = matrix.size();

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

    searchable = new MatrixMaze(mat, M, N, initial, goal);
}


string MatrixSolver::solve(const string &problem) {
    createProblemFromString(problem);
    vector<State *> backtrace = searcher->search(searchable);
    for (State *s:backtrace) {
        if (*s == *searchable->getInitialState()) {
            continue;
        }
        solution += searchable->getDirection(s) + " (" +
                    to_string(s->getCurrentCost()) + "), ";
    }
    solution = solution.substr(0, solution.length() - 2);
    return solution;
}