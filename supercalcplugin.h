#ifndef SUPERCALCPLUGIN_H
#define SUPERCALCPLUGIN_H

#include <string>
#include <memory>

class SuperCalcPlugin
{
public:
    virtual ~SuperCalcPlugin() {}

    virtual double operation(double op1, double op2) = 0;
    virtual std::string get_name() const = 0;
};

extern "C" std::unique_ptr<SuperCalcPlugin> SuperCalcPlugin_new();

#endif // SUPERCALCPLUGIN_H
