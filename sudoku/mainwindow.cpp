
#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->createButtons();
    this->selectedNumber = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createButtons(){
    for (int i = 1; i < 10; ++i) {
        NumberButton *b = new NumberButton(i);
        connect(b, &QPushButton::clicked, this, &MainWindow::selectNumber);

        ui->numberList->addWidget(b);
        this->numberButtons.push_back(b);
    }
}

void MainWindow::selectNumber(){
    NumberButton* buttonSender = qobject_cast<NumberButton*>(sender()); //retrive information about sender
    int n = buttonSender->getNumber();
    int prevN = this->selectedNumber;

    if(buttonSender->isChecked()){
        //uncheck previous button
        if(prevN){
            NumberButton* prevButton = this->numberButtons.at(prevN-1);
            prevButton->setChecked(false);
        }
        //change selectedNumber
        this->selectedNumber = n;
    }else{
        this->selectedNumber = 0;
    }
    ui->selectedNumberLabel->setText(
        QString("Selected number: %1").arg(this->selectedNumber)
    );
}
