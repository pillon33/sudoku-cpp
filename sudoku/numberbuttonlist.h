
#ifndef NUMBERBUTTONLIST_H
#define NUMBERBUTTONLIST_H

#include "numberbutton.h"

/**
 * @brief The NumberButtonList class stores number buttons.
 */
class NumberButtonList
{
private:
    std::vector<NumberButton*> buttons;
public:
    NumberButtonList();
    ~NumberButtonList();
    /**
     * @brief addButton function adds button into specified position;
     */
    void addButton(NumberButton*);
};

#endif // NUMBERBUTTONLIST_H
