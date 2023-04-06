
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "numberbutton.h"


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

void MainWindow::createButtons(){
    for (int i = 1; i < 10; ++i) {
        NumberButton *b = new NumberButton(i);
        ui->numberList->addWidget(b);
    }
}
