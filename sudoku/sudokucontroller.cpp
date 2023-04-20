
#include "sudokucontroller.h"
#include <stdlib.h>
#include <time.h>
#include <QDebug>

SudokuController::SudokuController()
{
    srand(time(NULL));
    this->solver = new BacktrackingSolver();
}

/**
 * @brief SudokuController::generatePuzzle generates random puzzle
 * @param numberOfClues - number of visible fields (>17)
 */
void SudokuController::generatePuzzle(int numberOfClues)
{
    //Correct puzzle can't have less than 17 clues (visible numbers at start)
    if (numberOfClues < 17){
        return;
    }

    int randomNumber = 0;

    for (int i = 0; i < 9; i++) {
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
            setFieldValue(i, j, randomNumber);

            randomNumber = rand() % 9 + 1;

            while(this->secondMatrix[randomNumber - 1] == 0){
                randomNumber = rand() % 9 + 1;
            }

            this->secondMatrix[randomNumber - 1] = 0;

            //middle square
            setFieldValue(i + 3, j + 3, randomNumber);

            randomNumber = rand() % 9 + 1;

            while(this->thirdMatrix[randomNumber - 1] == 0){
                randomNumber = rand() % 9 + 1;
            }

            this->thirdMatrix[randomNumber - 1] = 0;

            //right bottom square
            setFieldValue(i + 6, j + 6, randomNumber);
        }
    }

    if(this->solver){
        this->solver->setBoard(grid);
        this->solver->solve();
        getSolution();
    }
}

/**
 * @brief SudokuController::resetGrid fills grid with 0
 */
void SudokuController::resetGrid()
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            setFieldValue(i, j, 0);
        }
    }
}

/**
 * @brief SudokuController::getValue returns value of field with given coordinates
 * @param row
 * @param col
 * @return value of field
 */
int SudokuController::getValue(int row, int col)
{
    if( (row < 0 || row > 8) || (col < 0 || col > 8) ){
        return 0;
    }

    return getFieldValue(row, col);
}

void SudokuController::setValue(int row, int col, int value)
{
    if( (row < 0 || row > 8) || (col < 0 || col > 8) ){
        return;
    }

    setFieldValue(row, col, value);
}

/**
 * @brief SudokuController::isCorrect checks if grid is filled correctly
 * @return
 */
bool SudokuController::isCorrect()
{
    //iterates through big squares
    for (int mainRow = 0; mainRow < 3; mainRow++) {
        for (int mainCol = 0; mainCol < 3; mainCol++) {
            //numbers in current square
            int numbers[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            //iterate through all fields in small square
            for (int row = 0; row < 3; row++) {
                for (int col = 0; col < 3; col++) {
                    int number = getFieldValue(row + mainRow*3, col + mainCol*3);
                    numbers[number]++;
                    if( (number) && (numbers[number] > 1) ){
                        return false;
                    }
                }
            }
        }
    }

    //iterates through all rows
    for (int row = 0; row < 9; row++) {
        int numbers[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        for (int col = 0; col < 9; col++) {
            int number = getFieldValue(row, col);
            numbers[number]++;
            if( (number) && (numbers[number] > 1) ){
                return false;
            }
        }
    }

    //iterates through all rows
    for (int col = 0; col < 9; col++) {
        int numbers[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        for (int row = 0; row < 9; row++) {
            int number = getFieldValue(row, col);
            numbers[number]++;
            if( (number) && (numbers[number] > 1) ){
                return false;
            }
        }
    }

    return true;
}

/**
 * @brief SudokuController::optimisedIsCorrect checks if last change is correct
 * @param row
 * @param col
 * @return
 * Checks only given row, column and appropriate sub-square
 */
bool SudokuController::optimisedIsCorrect(int posRow, int posCol)
{
    //finds coordinates of sub-square
    int mainRow = posRow/3;
    int mainCol = posCol/3;

    int number = getFieldValue(posRow, posCol);
    if(!number){
        return true;
    }

    int numbers[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    //iterate through all fields in sub-square
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            int number = getFieldValue(row + mainRow*3, col + mainCol*3);
            numbers[number]++;
        }
    }

    if (numbers[number] > 1){
        return false;
    }

    //reset counter table
    for (int i = 0; i < 10; i++) {
        numbers[i] = 0;
    }

    //checks given row
    for (int col = 0; col < 9; col++) {
        int number = getFieldValue(posRow, col);
        numbers[number]++;
    }

    if (numbers[number] > 1){
        return false;
    }

    //reset counter table
    for (int i = 0; i < 10; i++) {
        numbers[i] = 0;
    }

    //checks given column
    for (int row = 0; row < 9; row++) {
        int number = getFieldValue(row, posCol);
        numbers[number]++;
    }

    if (numbers[number] > 1){
        return false;
    }

    return true;
}

int SudokuController::getIdx(int row, int col)
{
    return 9*row + col;
}

int SudokuController::getFieldValue(int row, int col)
{
    return this->grid[getIdx(row, col)];
}

void SudokuController::setFieldValue(int row, int col, int value)
{
    this->grid[getIdx(row, col)] = value;
}

/**
 * @brief SudokuController::getSolution copies solution from solver to grid table
 */
void SudokuController::getSolution()
{
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            int number = this->solver->getFieldValue(row, col);
            setFieldValue(row, col, number);
        }
    }
}

