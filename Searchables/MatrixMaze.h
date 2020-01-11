//
// Created by yekaterina on 11/01/2020.
//

#ifndef MILESTONE_2_MATRIXMAZE_H
#define MILESTONE_2_MATRIXMAZE_H

#include "Searchable.h"
#include "../StringUtils.h"

class MatrixMaze : public Searchable {
private:
    double **matrix;
    int sizeCol;
    int sizeRow;
    State *initial;
    State goal;
    vector<State *> allStates;

public:
    MatrixMaze(double *mat[], int N, int M, State &ini, State g) {
        sizeCol = M;
        sizeRow = N;
        matrix = new double *[sizeRow];
        for (int i = 0; i < sizeRow; i++) {
            matrix[i] = new double[sizeCol];
            memcpy(matrix[i], mat[i], sizeof(double) * sizeCol);
        }
        initial = new State(ini);
        allStates.push_back(initial);
        goal = g;
    }

    virtual State *getInitialState() { return initial; }

    virtual State getGoalState() { return goal; }

    virtual vector<State *> getAllPossibleStates(State *s) {
        vector<State *> succesors;
        vector<int> place = getPlacementOfNodeInMatrix(s);
        int i = place.at(0);
        int j = place.at(1);

        if (matrix[i + 1][j] != INFINITY) {
            succesors.push_back(createSuccesorState(s, i + 1, j));
        }
        if (matrix[i - 1][j] != INFINITY) {
            succesors.push_back(createSuccesorState(s, i - 1, j));
        }
        if (matrix[i][j + 1] != INFINITY) {
            succesors.push_back(createSuccesorState(s, i, j + 1));
        }
        if (matrix[i][j - 1] != INFINITY) {
            succesors.push_back(createSuccesorState(s, i, j - 1));
        }
        return succesors;
    }

    State *createSuccesorState(State *s, int i, int j) {
        string place = to_string(i) + ',' + to_string(j);
        State *newState = new State(place, s);
        return newState;
    }

    virtual double getCostToGetToNode(State *s) {
        vector<int> placement = getPlacementOfNodeInMatrix(s);
        int r = placement.at(0);
        int c = placement.at(1);
        return matrix[r][c];
    }

    vector<int> getPlacementOfNodeInMatrix(State *s) {
        vector<string> place =
                StringUtils::splitByFirstChar((*s).getDescription(), ',');
        int r = atoi(place.at(0).c_str());
        int c = atoi(place.at(1).c_str());
        vector<int> placement;
        placement.push_back(r);
        placement.push_back(c);
        return placement;
    }


    ~MatrixMaze() {
        for (int i = 0; i < sizeRow; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;

        while (!allStates.empty()) {
            State *s = allStates.back();
            allStates.pop_back();
            delete s;
        }
    }
};

#endif //MILESTONE_2_MATRIXMAZE_H
