#ifndef SUPERCALC_H
#define SUPERCALC_H

#include <QMainWindow>
#include "supercalcplugin.h"
#include <vector>

namespace Ui {
class SuperCalc;
}

class SuperCalc : public QMainWindow
{
    Q_OBJECT

public:
    explicit SuperCalc(QWidget *parent = 0);
    ~SuperCalc();

signals:
    void calculate_needed();

public slots:
    void calculate();

private:
    Ui::SuperCalc *ui;

    std::vector<std::unique_ptr<SuperCalcPlugin>> plugins;

private:
    void do_connections();
    void reload();
    void load_builtin_operations();
    void load_plugins();
    void try_load_library(const QString &file);
    void clear_operations();
    void add_operation(std::unique_ptr<SuperCalcPlugin> plugin);
    void closeEvent(QCloseEvent *ce) override;
};

#endif // SUPERCALC_H
