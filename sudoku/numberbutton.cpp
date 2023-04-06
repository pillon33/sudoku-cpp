
#include "numberbutton.h"

NumberButton::NumberButton(int n)
{
    this->number = n;
    this->setFixedSize(QSize(40, 50));
    this->setText(QString(QString::fromStdString(std::to_string(n))));
    this->setCheckable(true);
    this->gameBoard = GameBoard::getInstance();
}

int NumberButton::clicked(){

}
