#ifndef SUPERCALC_H
#define SUPERCALC_H

#include <QMainWindow>

namespace Ui {
class SuperCalc;
}

class SuperCalc : public QMainWindow
{
    Q_OBJECT

public:
    explicit SuperCalc(QWidget *parent = 0);
    ~SuperCalc();
private:
    Ui::SuperCalc *ui;
    void do_connections();
};

#endif // SUPERCALC_H
