
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

private:
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
    int firstMatrix[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    int secondMatrix[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    int thirdMatrix[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    BacktrackingSolver *solver;
};

#endif // SUDOKUCONTROLLER_H
