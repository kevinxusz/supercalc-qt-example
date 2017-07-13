#include <QApplication>
#include <QDirIterator>
#include <QMessageBox>
#include <QDebug>
#include <QLibrary>
#include <QWidget>
#include <QAction>
#include <QComboBox>
#include <QCloseEvent>
#include "supercalc.h"
#include "ui_supercalc.h"

class Addition : public SuperCalcPlugin
{
public:
    double operation(double op1, double op2) override { return op1 + op2; }
    std::string get_name() const override { return "addition (+)"; }
};

class Substraction : public SuperCalcPlugin
{
public:
    double operation(double op1, double op2) override { return op1 - op2; }
    std::string get_name() const override { return "soustraction (-)"; }
};

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

void SuperCalc::calculate()
{
    const double op1 = ui->spinbox_1st_arg->value();
    const double op2 = ui->spinbox_2nd_arg->value();

    const unsigned index = ui->combo_operation->currentIndex();

    if (index < plugins.size()) {
        SuperCalcPlugin *p = plugins[index].get();
        const double result = p->operation(op1, op2);
        ui->lcd_result->display(result);
    }
}

void SuperCalc::do_connections()
{
    connect(this, &SuperCalc::calculate_needed, this, &SuperCalc::calculate);
    connect(ui->spinbox_1st_arg, SIGNAL(valueChanged(double)), this, SIGNAL(calculate_needed()));
    connect(ui->spinbox_2nd_arg, SIGNAL(valueChanged(double)), this, SIGNAL(calculate_needed()));

    connect(ui->combo_operation, SIGNAL(currentIndexChanged(int)), this, SIGNAL(calculate_needed()));

    connect(ui->action_Quitter, &QAction::triggered, this, &QWidget::close);

    connect(ui->action_Recharger, &QAction::triggered, [this]{
        reload();
        emit calculate_needed();
    });
}

void SuperCalc::reload()
{
    clear_operations();

    qDebug() << "Chargement plugins...";

    load_builtin_operations();
    load_plugins();

    qDebug() << "Terminé\n";
}

void SuperCalc::load_builtin_operations()
{
    add_operation(std::make_unique<Addition>());
    add_operation(std::make_unique<Substraction>());
}

void SuperCalc::load_plugins()
{
    static const QDir::Filters exec = QDir::Files | QDir::Readable;

    QDirIterator it { QApplication::applicationDirPath(), exec };

    while (it.hasNext()) {
        try_load_library(it.next());
    }
}

void SuperCalc::try_load_library(const QString &file)
{
    qDebug() << file;
    QLibrary lib { file };

    auto factory = reinterpret_cast<decltype(SuperCalcPlugin_new) *>(lib.resolve("SuperCalcPlugin_new"));
    if (factory) {
        add_operation(factory());
    }
}

void SuperCalc::clear_operations()
{
    ui->combo_operation->clear();
    plugins.clear();
}

void SuperCalc::add_operation(std::unique_ptr<SuperCalcPlugin> plugin)
{
    ui->combo_operation->addItem(plugin->get_name().c_str());
    plugins.push_back(std::move(plugin));
}

void SuperCalc::closeEvent(QCloseEvent *ce)
{
    QMessageBox msg {};
    msg.setText("Quitter?");
    msg.setInformativeText("Voulez-vous vraiment quitter???");
    msg.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msg.setDefaultButton(QMessageBox::Ok);
    int ret = msg.exec();
    if (ret == QMessageBox::Ok)
        ce->accept();
    else
        ce->ignore();
}
