
#ifndef SUDOKUCONTROLLER_H
#define SUDOKUCONTROLLER_H




class SudokuController
{
public:
    SudokuController();
    void generatePuzzle(int);
    void resetGrid();
    int getValue(int, int);
    void setValue(int, int, int);
    bool isCorrect();

private:
    int grid[9][9] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    int firstMatrix[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    int secondMatrix[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    int thirdMatrix[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
};

#endif // SUDOKUCONTROLLER_H
