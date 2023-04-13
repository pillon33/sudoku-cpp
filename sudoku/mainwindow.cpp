
#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->createButtons();
    this->selectedNumber = 0;
    this->selectedRow = -1;
    this->selectedColumn = -1;
//    connect(ui->grid, &QTableWidget::cellClicked, this, &MainWindow::unselect);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createButtons(){
    for (int i = 1; i < 10; ++i) {
        NumberButton *b = new NumberButton(i, 9);
        connect(b, &QPushButton::clicked, this, &MainWindow::selectNumber);

        ui->numberList->addWidget(b);
        this->numberButtons.push_back(b);
    }
}

void MainWindow::selectNumber(){
    //retrive information about sender
    NumberButton* buttonSender = qobject_cast<NumberButton*>(sender());
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
        this->insertAction();
    }else{
        this->selectedNumber = 0;
    }
//    ui->selectedNumberLabel->setText(
//        QString("Selected number: %1").arg(this->selectedNumber)
//    );
}

/**
 * @brief MainWindow::compare - function compares given coordinates with selected field.
 * @param row
 * @param column
 * @return result of comparison (True/False)
 */
bool MainWindow::compare(int row, int column) const{
    return ( (this->selectedRow == row) && (this->selectedColumn == column) );
}

void MainWindow::on_grid_cellClicked(int row, int column)
{
    bool areEqual = this->compare(row, column);

    if (areEqual){
        ui->grid->clearFocus();
        ui->grid->clearSelection();

        this->selectedRow = -1;
        this->selectedColumn = -1;
    }else{
        this->selectedRow = row;
        this->selectedColumn = column;
        this->insertAction();
    }
}

void MainWindow::insertAction(){
    //Check if any number selected
    if(this->selectedNumber == 0){
        return;
    }

    //Check if any field selected
    if( (this->selectedRow == -1) || (this->selectedColumn == -1) ){
        return;
    }

    NumberButton *b = this->numberButtons.at(this->selectedNumber - 1);
    ui->grid->item(this->selectedRow, this->selectedColumn)->
        setText("essa");
    b->decOccurances();

}
