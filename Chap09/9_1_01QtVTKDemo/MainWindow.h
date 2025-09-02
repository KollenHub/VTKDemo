
#pragma once
#include "ui_MainWindow.h"
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow* ui;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};
