
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "numberbutton.h"
#include "sudokucontroller.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void createButtons();

private slots:
    void selectNumber();
    void on_grid_cellClicked(int row, int column);
    void on_startGameButton_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<NumberButton*> numberButtons;
    int selectedNumber;
    int selectedRow, selectedColumn;
    SudokuController *sudokuController;
    bool compare(int row, int column) const;
    void insertAction();
    void initializeGrid();
    void resetButtons();
};

#endif // MAINWINDOW_H
