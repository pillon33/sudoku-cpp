
#include "gameboard.h"

GameBoard::GameBoard()
{

}

GameBoard::~GameBoard()
{

}

void GameBoard::selectNumber(int n){
    this->selectedNumber = n;
}

GameBoard* GameBoard::getInstance(){
    if(instance_ == nullptr){
        instance_ = new GameBoard();
    }
    return instance_;
}


void GameBoard::setButtonsList(NumberButtonList b){
    this->buttons = b;
}

int GameBoard::getSelectedNumber(){
    return this->selectedNumber;
}

void GameBoard::setSelectedNumber(int n){
    this->selectedNumber = n;
}
