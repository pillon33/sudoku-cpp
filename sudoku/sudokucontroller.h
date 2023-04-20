
#ifndef SUDOKUCONTROLLER_H
#define SUDOKUCONTROLLER_H

#include "backtrackingsolver.h"


class SudokuController
{
public:
    SudokuController();
    void generatePuzzle(int);
    void resetGrid();
    int getValue(int, int);
    void setValue(int, int, int);
    bool isCorrect();
    bool optimisedIsCorrect(int, int);
    int getIdx(int, int);
    int getFieldValue(int, int);
    void setFieldValue(int, int, int);
    void getSolution();
    void fillWithRandomNumbers();
    void createMask(int, int);

private:
    //contains current state of the grid
    int grid[81] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    //contains solution (whole board filled with numbers)
    int solution[81] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    //contains mask pattern 1 if this field is a clue 0 if it's invisible
    int mask[81] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1
    };
    int firstMatrix[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    int secondMatrix[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    int thirdMatrix[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    BacktrackingSolver *solver;
//    bool contains(int*, int, int = 81);
};

#endif // SUDOKUCONTROLLER_H
