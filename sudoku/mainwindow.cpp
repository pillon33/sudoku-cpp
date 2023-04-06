
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "numberbutton.h"
#include "numberbuttonlist.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->createButtons();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::createButtons
 * Function creates 9 number buttons used to select number.
 * @see @link %NumberButton @endlink
 */
void MainWindow::createButtons(){
    NumberButtonList buttons;
    for (int i = 1; i < 10; ++i) {
        NumberButton *b = new NumberButton(i);
        buttons.addButton(b);
        ui->numberList->addWidget(b);
    }
    this->gameBoard = GameBoard::getInstance(buttons);
    this->gameBoard->setButtonsList(buttons);
}
