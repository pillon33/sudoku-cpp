
#ifndef NUMBERBUTTON_H
#define NUMBERBUTTON_H

#include <QPushButton>



class NumberButton : public QPushButton
{
    Q_OBJECT

private:
    int number;
public:
    NumberButton(int);
    int getNumber();
};

#endif // NUMBERBUTTON_H
