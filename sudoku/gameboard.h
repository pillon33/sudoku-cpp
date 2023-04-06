
#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "numberbuttonlist.h"
/**
 * @brief The GameBoard class representing game board.
 * @details This class is implemented as Singleton and Observer design patterns.
 */
class GameBoard
{
private:
    int selectedNumber=0;
    static GameBoard* instance_;
    NumberButtonList buttons;
public:
    GameBoard();
    ~GameBoard();
    void selectNumber(int);
    static GameBoard* getInstance();
    void setButtonsList(NumberButtonList);
    int getSelectedNumber();
    void setSelectedNumber(int);
};

#endif // GAMEBOARD_H
