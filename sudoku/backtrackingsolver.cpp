
#include "backtrackingsolver.h"
#include <QDebug>

BacktrackingSolver::BacktrackingSolver()
{

}

/**
 * @brief BacktrackingSolver::solve finds solution to given puzzle
 */
void BacktrackingSolver::solve()
{
    qDebug() << "solving\n";
}

int BacktrackingSolver::getIdx(int row, int col)
{
    return 9*row + col;
}

int BacktrackingSolver::getFieldValue(int row, int col)
{
    return this->board[getIdx(row, col)];
}

void BacktrackingSolver::setFieldValue(int row, int col, int value)
{
    this->board[getIdx(row, col)] = value;
}

void BacktrackingSolver::setBoard(int b[81])
{
//    for(int row = 0; row < 9; row++){
//        for(int col = 0; col < 9; col++){
//            qDebug() << b[row][col] << "\t";
//            this->board[row][col] = b[row][col];
//            this->solution[row][col] = b[row][col];
//            qDebug() << board[row][col] << "\t";
//        }
//        qDebug() << "\n";
//    }
    for(int i = 0; i < 81; i++){
        this->board[i] = b[i];
        this->solution[i] = b[i];
    }
}

