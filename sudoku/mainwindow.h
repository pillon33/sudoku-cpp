
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "numberbutton.h"


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
//    void unselect();

    void on_grid_cellClicked(int row, int column);

private:
    Ui::MainWindow *ui;
    std::vector<NumberButton*> numberButtons;
    int selectedNumber;
    int selectedRow, selectedColumn;
    bool compare(int row, int column) const;
    void insertAction();
};

#endif // MAINWINDOW_H
