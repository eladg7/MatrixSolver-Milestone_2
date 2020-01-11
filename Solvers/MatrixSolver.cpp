#include "MatrixSolver.h"

string MatrixSolver::createProblemFromString(const string &str) {

    vector<string> matrix = StringUtils::split(str, '\n');
    State goal;
    goal.init(matrix.back());
    matrix.pop_back();
    State initial;
    initial.init(matrix.back());
    matrix.pop_back();
    unsigned M = (matrix.at(0).size());
    unsigned N = matrix.size();
    double mat[N][M];
    for (int i = 0; i < N; i++) {
        vector<string> nodes = StringUtils::split(matrix.front(), ',');
        matrix.erase(matrix.begin());
        for (int j = 0; j < M; j++) {
            string doub = nodes.front();
            mat[i][j] = stod(doub);
            nodes.erase(nodes.begin());
        }
    }


    searchable = new MatrixMaze(mat, M, N);
}