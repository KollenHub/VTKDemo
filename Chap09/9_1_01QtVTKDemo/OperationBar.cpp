#include "OperationBar.h"

OperationBar::OperationBar(QWidget *parent):QWidget(parent), ui(new Ui::OperationBar)
{
    ui->setupUi(this);
}

OperationBar::~OperationBar()
{

}
