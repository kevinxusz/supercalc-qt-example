#include <QMessageBox>
#include <QWidget>
#include <QAction>
#include "supercalc.h"
#include "ui_supercalc.h"

SuperCalc::SuperCalc(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SuperCalc)
{
    ui->setupUi(this);
    do_connections();
}

SuperCalc::~SuperCalc()
{
    delete ui;
}

void SuperCalc::do_connections()
{
    connect(ui->spinbox_1st_arg, SIGNAL(valueChanged(double)), ui->lcd_result, SLOT(display(double)));
    connect(ui->action_Quitter, &QAction::triggered, this, &QWidget::close);
}
