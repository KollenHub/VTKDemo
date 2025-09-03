#pragma once
#include "ui_OperationBar.h"
#include <QWidget>

class OperationBar : public QWidget
{
    Q_OBJECT
private:
    Ui::OperationBar *ui;
public:
    OperationBar(QWidget *parent = nullptr);
    ~OperationBar();
};
