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
    MatrixMaze(double **mat, int N, int M, State &ini, State g) {
        sizeCol = M;
        sizeRow = N;
        matrix = mat;
//        for (int i = 0; i < N; i++) {
//            matrix[i] = new double[M];
//            memcpy(matrix[i], mat[i], sizeof(double) * M);
//        }
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
        vector<int> dadsPlace;
        if(*s == *getInitialState()){//first node doesnt have a dad
            dadsPlace={0,0};
        }else{
            dadsPlace = getPlacementOfNodeInMatrix(s->getFather());

        }
        //check if he didnt go pass the border,
        // and through a wall, and if he is not coming from his dad.

        if (i < sizeRow - 1 && matrix[i + 1][j] != -1
            && i + 1 != dadsPlace.at(0)) {
            succesors.push_back(createSuccesorState(s, i + 1, j));
        }
        if (i > 0 && matrix[i - 1][j] != -1
            && i - 1 != dadsPlace.at(0)) {
            succesors.push_back(createSuccesorState(s, i - 1, j));
        }
        if (j < sizeCol - 1 && matrix[i][j + 1] != -1
            && j + 1 != dadsPlace.at(1)) {
            succesors.push_back(createSuccesorState(s, i, j + 1));
        }
        if (j > 0 && matrix[i][j - 1] != -1
            && j - 1 != dadsPlace.at(1)) {
            succesors.push_back(createSuccesorState(s, i, j - 1));
        }
        return succesors;
    }

    State *createSuccesorState(State *s, int i, int j) {
        string place = to_string(i) + ',' + to_string(j);
        State *newState = nullptr;
        for (State *state:allStates) {
            if (state->getDescription() == place) {
                newState = state;
                break;
            }
        }
        if (newState == nullptr) {
            newState = new State();
            newState->init(place);
            allStates.push_back(newState);
        }

        return newState;
    }

    string getDirection(State *s) {
        string direction;
        vector<int> place = getPlacementOfNodeInMatrix(s);
        vector<int> dadsPlace = getPlacementOfNodeInMatrix(s->getFather());
        if (place.at(0) == dadsPlace.at(0)) {//same row
            if (place.at(1) - 1 == dadsPlace.at(1)) {
                direction = "Right";
            } else {
                direction = "Left";
            }
        } else {//same col
            if (place.at(0) - 1 == dadsPlace.at(0)) {
                direction = "Down";
            } else {
                direction = "Up";
            }
        }
        return direction;
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
