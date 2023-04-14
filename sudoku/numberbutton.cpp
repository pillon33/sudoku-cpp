
#include "numberbutton.h"

int NumberButton::getOccurances() const
{
    return occurances;
}


void NumberButton::setOccurances(int newOccurances)
{
    occurances = newOccurances;
}


void NumberButton::incOccurances()
{
    occurances++;
}


void NumberButton::decOccurances()
{
    occurances--;
}


NumberButton::NumberButton(int n, int oc)
{
    this->number = n;
    this->occurances = oc;
    this->setFixedSize(QSize(40, 50));
    this->setText(QString(QString::fromStdString(std::to_string(n))));
    this->setCheckable(true);
}


int NumberButton::getNumber(){
    return this->number;
}
