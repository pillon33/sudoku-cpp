
#ifndef NUMBERBUTTON_H
#define NUMBERBUTTON_H

#include <QPushButton>
#include "gameboard.h"


/**
 * @brief The NumberButton class - button used to select number.
 */
class NumberButton : public QPushButton
{
private:
    int number;
    GameBoard* gameBoard;
public:
    NumberButton(int);
};

#endif // NUMBERBUTTON_H
