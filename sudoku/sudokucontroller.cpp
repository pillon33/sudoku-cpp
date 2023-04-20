
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
void SudokuController::generatePuzzle(int numbersToRemove)
{
    //Correct puzzle can't have less than 17 clues (visible numbers at start)
    if (numbersToRemove + 17 > 81){
        return;
    }

    //backtracking generator
//    this->fillWithRandomNumbers();

//    if(this->solver){
//        this->solver->setBoard(grid);
//        this->solver->solve();
//        getSolution();
//    }

    //shuffle generator
    this->shufflePattern();

    this->createMask(40, 0);
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
    this->solution[getIdx(row, col)] = value;
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

void SudokuController::fillWithRandomNumbers()
{
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
}

void SudokuController::createMask(int numbersToRemove, int trial)
{
    int idxs[81] = {
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

    int usedIdxs[81] = {
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

    int randomNumber = 0;

    int removedNumbers = 0;

    //creates random order to iterate through matrix
    for(int i = 0; i < 81; i++){
        randomNumber = rand()%81;

        //Check if idx wasn't used
        while(!usedIdxs[randomNumber]){
            randomNumber = rand()%81;
        }

        //add idx to random order
        idxs[i] = randomNumber;

        //mark idx as used
        usedIdxs[randomNumber] = 0;
    }

    //remove numbers from random positions
    for(int i = 0; i < 81; i++){
        //get random idx
        int idx = idxs[i];

        //remove number
        this->grid[idx] = 0;

        //check if has only one solution
        if(this->solver->isPuzzle(this->grid)){
            removedNumbers++;
            this->mask[idx] = 0;
            if(removedNumbers == numbersToRemove){
                return;
            }
        }else{
            this->grid[idx] = this->solution[idx];
        }
    }

    if(numbersToRemove - removedNumbers > 10){
        if(trial++ < 100){
            this->createMask(numbersToRemove, trial);
        }
    }
}

/**
 * @brief SudokuController::shufflePattern makes random changes to default pattern that don't affect rules of sudoku
 * in this case each grid is in fact the same grid but it is impossible for user to see that
 * this method has really low complexity as it doesn't need to use backtracking solver and
 * it has huge ammount of combinations as results.
 */
void SudokuController::shufflePattern()
{
    //shuffle digits and replace them in all cells
    int newDigits[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int usedDigits[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int randomNumber = rand()%9;

    for (int number = 0; number < 9; number++){
        while(usedDigits[randomNumber]){
            randomNumber = rand()%9;
        }

        newDigits[number] = randomNumber;
        usedDigits[randomNumber] = 1;
    }

    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            int number = this->pattern[getIdx(row, col)];
            setFieldValue(row, col, newDigits[number - 1] + 1);
        }
    }
    /////////////////////////////////////////////////////


    //randomly rearange groups of rows (1, 2, 3), (4, 5, 6), (7, 8, 9) within themselves
    for(int i = 0; i < 3; i++){
        int firstRandomNumber = rand() % 3;
        int secondRandomNumber = rand() % 3;

        while(firstRandomNumber == secondRandomNumber){
            firstRandomNumber = rand() % 3;
        }

        //rearanges rows (1, 2, 3)
        this->swapRows(firstRandomNumber, secondRandomNumber);

        firstRandomNumber = rand() % 3;
        secondRandomNumber = rand() % 3;

        while(firstRandomNumber == secondRandomNumber){
            firstRandomNumber = rand() % 3;
        }

        //rearanges rows (4, 5, 6)
        this->swapRows(firstRandomNumber + 3, secondRandomNumber + 3);

        firstRandomNumber = rand() % 3;
        secondRandomNumber = rand() % 3;

        while(firstRandomNumber == secondRandomNumber){
            firstRandomNumber = rand() % 3;
        }

        //rearanges rows (7, 8, 9)
        this->swapRows(firstRandomNumber + 6, secondRandomNumber + 6);
    }
    //////////////////////////////////////////////////////////////////////////////


    //randomly rearange groups of columns (1, 2, 3), (4, 5, 6), (7, 8, 9) within themselves
    for(int i = 0; i < 3; i++){
        int firstRandomNumber = rand() % 3;
        int secondRandomNumber = rand() % 3;

        while(firstRandomNumber == secondRandomNumber){
            firstRandomNumber = rand() % 3;
        }

        //rearanges rows (1, 2, 3)
        this->swapColumns(firstRandomNumber, secondRandomNumber);

        firstRandomNumber = rand() % 3;
        secondRandomNumber = rand() % 3;

        while(firstRandomNumber == secondRandomNumber){
            firstRandomNumber = rand() % 3;
        }

        //rearanges rows (4, 5, 6)
        this->swapColumns(firstRandomNumber + 3, secondRandomNumber + 3);

        firstRandomNumber = rand() % 3;
        secondRandomNumber = rand() % 3;

        while(firstRandomNumber == secondRandomNumber){
            firstRandomNumber = rand() % 3;
        }

        //rearanges rows (7, 8, 9)
        this->swapColumns(firstRandomNumber + 6, secondRandomNumber + 6);
    }
    /////////////////////////////////////////////////////////////////////////



    //randomly rearange 3 rows of subsquares
    for(int i = 0; i < 3; i++){
        int firstRandomNumber = rand() % 3;
        int secondRandomNumber = rand() % 3;

        while(firstRandomNumber == secondRandomNumber){
            firstRandomNumber = rand() % 3;
        }

        this->swapRows(firstRandomNumber*3, secondRandomNumber*3);
        this->swapRows(firstRandomNumber*3 + 1, secondRandomNumber*3 + 1);
        this->swapRows(firstRandomNumber*3 + 2, secondRandomNumber*3 + 2);
    }
    /////////////////////////////////////////////////////////////////////////


    //randomly rearange 3 columns of subsquares
    for(int i = 0; i < 3; i++){
        int firstRandomNumber = rand() % 3;
        int secondRandomNumber = rand() % 3;

        while(firstRandomNumber == secondRandomNumber){
            firstRandomNumber = rand() % 3;
        }

        this->swapColumns(firstRandomNumber*3, secondRandomNumber*3);
        this->swapColumns(firstRandomNumber*3 + 1, secondRandomNumber*3 + 1);
        this->swapColumns(firstRandomNumber*3 + 2, secondRandomNumber*3 + 2);
    }
}

void SudokuController::swapRows(int first, int second)
{
    for (int i = 0; i < 9; i++) {
        //get idxs
        int firstIdx = getIdx(first, i);
        int secondIdx = getIdx(second, i);

        //swap numbers
        int tmp = this->grid[firstIdx];
        this->grid[firstIdx] = this->grid[secondIdx];
        this->grid[secondIdx] = tmp;
    }
}

void SudokuController::swapColumns(int first, int second)
{
    for (int i = 0; i < 9; i++) {
        //get idxs
        int firstIdx = getIdx(i, first);
        int secondIdx = getIdx(i, second);

        //swap numbers
        int tmp = this->grid[firstIdx];
        this->grid[firstIdx] = this->grid[secondIdx];
        this->grid[secondIdx] = tmp;
    }
}

void SudokuController::rotate(int)
{

}

void SudokuController::mirror(int)
{

}

