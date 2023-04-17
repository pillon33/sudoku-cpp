
#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->sudokuController = new SudokuController();
    this->sudokuController->resetGrid();
    this->createButtons();
    this->initializeGrid();
    this->selectedNumber = 0;
    this->selectedRow = -1;
    this->selectedColumn = -1;
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
    QTableWidgetItem *f =  ui->grid->item(this->selectedRow, this->selectedColumn);
    if(f){
        f->setText(QString(QString::fromStdString(std::to_string(this->selectedNumber))));
        b->decOccurances();
    }
}


void MainWindow::initializeGrid()
{
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            int number = this->sudokuController->getValue(i, j);

            QString val = QString(QString::fromStdString(std::to_string(number)));
            if(number == 0){
                val = QString("");
            }

            QTableWidgetItem *item  = new QTableWidgetItem("");
            item->setTextAlignment(Qt::AlignCenter);
            item->setText(val);
            ui->grid->setItem(i, j, item);
        }
    }
}


void MainWindow::resetButtons()
{
    for (int i = 0; i < 9; ++i) {
        NumberButton *b = this->numberButtons.at(i);
        b->setOccurances(9);
        b->setChecked(false);
    }
}


void MainWindow::on_startGameButton_clicked()
{
    this->sudokuController->resetGrid();
    this->sudokuController->generatePuzzle(40);

    this->initializeGrid();
    this->resetButtons();

    this->selectedNumber = 0;
    this->selectedRow = -1;
    this->selectedColumn = -1;

    ui->grid->clearFocus();
    ui->grid->clearSelection();
}

