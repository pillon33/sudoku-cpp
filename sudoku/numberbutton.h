
#ifndef NUMBERBUTTON_H
#define NUMBERBUTTON_H

#include <QPushButton>



class NumberButton : public QPushButton
{
    Q_OBJECT

private:
    int number;
    int occurances;
public:
    NumberButton(int, int);
    int getNumber();
    int getOccurances() const;
    void setOccurances(int newOccurances);
    void incOccurances();
    void decOccurances();
};

#endif // NUMBERBUTTON_H
