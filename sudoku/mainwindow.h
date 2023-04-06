
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

private:
    Ui::MainWindow *ui;
    std::vector<NumberButton*> numberButtons;
    int selectedNumber;
};

#endif // MAINWINDOW_H
