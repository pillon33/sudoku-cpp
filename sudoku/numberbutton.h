
#ifndef NUMBERBUTTON_H
#define NUMBERBUTTON_H

#include <QPushButton>



class NumberButton : public QPushButton
{
private:
    int number;
public:
    NumberButton(int);
};

#endif // NUMBERBUTTON_H
