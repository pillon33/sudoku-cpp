
#include "sudokucontroller.h"
#include <stdlib.h>
#include <time.h>
#include <QDebug>

SudokuController::SudokuController()
{
    srand(time(NULL));
}

void SudokuController::generatePuzzle(int numberOfClues)
{
    //Correct puzzle can't have less than 17 clues (visible numbers at start)
    if (numberOfClues < 17){
        return;
    }

    int randomNumber = 0;

    for (int i = 0; i < 10; ++i) {
        this->firstMatrix[i] = 1;
        this->secondMatrix[i] = 1;
        this->thirdMatrix[i] = 1;
    }

    //randomly fill squares on diagonal
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            randomNumber = rand() % 9 + 1;

            while(this->firstMatrix[randomNumber - 1] == 0){
                randomNumber = rand() % 9 + 1;
            }

            this->firstMatrix[randomNumber - 1] = 0;

            //left top square
            this->grid[i][j] = randomNumber;

            while(this->secondMatrix[randomNumber - 1] == 0){
                randomNumber = rand() % 9 + 1;
            }

            this->secondMatrix[randomNumber - 1] = 0;

            //middle square
            this->grid[i + 3][j + 3] = randomNumber;

            while(this->thirdMatrix[randomNumber - 1] == 0){
                randomNumber = rand() % 9 + 1;
            }

            this->thirdMatrix[randomNumber - 1] = 0;

            //right bottom square
            this->grid[i + 6][j + 6] = randomNumber;
        }
    }
}

void SudokuController::resetGrid()
{
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            this->grid[i][j] = 0;
        }
    }
}

int SudokuController::getValue(int row, int col)
{
    if( (row < 0 || row > 8) || (col < 0 || col > 8) ){
        return 0;
    }

    return this->grid[row][col];
}

