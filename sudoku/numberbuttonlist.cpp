
#include "numberbuttonlist.h"

NumberButtonList::NumberButtonList()
{

}

void NumberButtonList::addButton(NumberButton *b){
    this->buttons.push_back(b);
}
