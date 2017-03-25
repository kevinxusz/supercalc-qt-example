#include "supercalc.h"
#include "ui_supercalc.h"

SuperCalc::SuperCalc(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SuperCalc)
{
    ui->setupUi(this);
}

SuperCalc::~SuperCalc()
{
    delete ui;
}
