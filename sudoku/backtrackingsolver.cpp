
#include "backtrackingsolver.h"
#include <QDebug>
#include <QProcess>
#include <QTime>
#include <QCoreApplication>
#include <vector>

BacktrackingSolver::BacktrackingSolver()
{

}

/**
 * @brief BacktrackingSolver::solve finds solution to given puzzle using backtracking algorithm
 */
void BacktrackingSolver::solve()
{
    int numberOfTries = 0;
    int row = 0;
    int col = 0;
    int idx = 0;
    int startidx = 0;
    std::vector<int> prevIdx;

    while(this->board[idx]){
        idx++;
        if(idx > 80){
            return;
        }
    }
    startidx = idx;

    while(idx < 81){
//        numberOfTries++;
//        if(numberOfTries >= 1){
//            this->debugSolution();
//            numberOfTries = 0;
//            this->delay();
//        }

        int number = this->board[idx];

        //if this field is a clue
        if (number){
            idx++;
            continue;
        }

        this->solution[idx]++;

        //no numbers match in this position
        if(this->solution[idx] > 9){
            //if it's first position then it can't find solution
            if(idx == startidx){
                return;
            }

            //reset this position
            this->solution[idx] = 0;

            //go to previous position
            idx = prevIdx.back();

            //remove this idx from history
            prevIdx.pop_back();

            if(idx >= 0){
                continue;
            }
            //couldn't find any solution
            return;
        }

        if(!this->isCorrect()){
            continue;
        }

        prevIdx.push_back(idx);
        idx++;
    }
}

int BacktrackingSolver::getIdx(int row, int col)
{
    return 9*row + col;
}

int BacktrackingSolver::getFieldValue(int row, int col)
{
    return this->solution[getIdx(row, col)];
}

void BacktrackingSolver::setFieldValue(int row, int col, int value)
{
    this->board[getIdx(row, col)] = value;
}

int *BacktrackingSolver::getSolution()
{
    return this->solution;
}

void BacktrackingSolver::setBoard(int b[81])
{
    for(int i = 0; i < 81; i++){
        this->board[i] = b[i];
        this->solution[i] = b[i];
    }
}

/**
 * @brief BacktrackingSolver::optimisedIsCorrect checks if last change is correct
 * @param row
 * @param col
 * @return
 * Checks only given row, column and appropriate sub-square
 */
bool BacktrackingSolver::optimisedIsCorrect(int posRow, int posCol)
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

void BacktrackingSolver::debugSolution()
{
    QProcess::execute("CLS");

    // Print debug info
    QString message;

    message += "\n\n\n";

    for (int row = 0; row < 9; row++) {
        message += QString::number(row) + ":\t";
        for (int col = 0; col < 9; col++) {
            int number = getFieldValue(row, col);
            message += QString::number(number) + "\t";
        }
        message += "\n";
    }

    qDebug().noquote().nospace() << message;
}

/**
 * @brief BacktrackingSolver::isCorrect checks if grid is filled correctly
 * @return
 */
bool BacktrackingSolver::isCorrect()
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

void BacktrackingSolver::delay()
{
    QTime dieTime= QTime::currentTime().addMSecs(500);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

/**
 * @brief BacktrackingSolver::isPuzzle checks if given puzzle has only one solution
 * @return
 */
bool BacktrackingSolver::isPuzzle(int *puzzle)
{
    int numberOfTries = 0;
    int row = 0;
    int col = 0;
    int idx = 0;
    int startidx = 0;
    int numberOfSolutions = 0;
    std::vector<int> prevIdx;

    this->setBoard(puzzle);

    while(this->board[idx]){
        idx++;
        if(idx > 80){
            return false;
        }
    }
    startidx = idx;

    while(idx < 81){
        //        numberOfTries++;
        //        if(numberOfTries >= 1){
        //            this->debugSolution();
        //            numberOfTries = 0;
        //            this->delay();
        //        }

        int number = this->board[idx];

        //if this field is a clue
        if (number){
            idx++;
            continue;
        }

        this->solution[idx]++;

        //no numbers match in this position
        if(this->solution[idx] > 9){
            //if it's first position then it can't find solution
            if(idx == startidx){
                break;
            }

            //reset this position
            this->solution[idx] = 0;

            //go to previous position
            idx = prevIdx.back();

            //remove this idx from history
            prevIdx.pop_back();

            if(idx >= 0){
                continue;
            }

            //couldn't find any solution
            break;
        }

        if(!this->isCorrect()){
            continue;
        }

        prevIdx.push_back(idx);
        idx++;
        if(idx > 80){
            numberOfSolutions++;
            idx--;
            if (numberOfSolutions > 1){
                return true;
            }
            continue;
        }
    }

    return numberOfSolutions == 1;
}
