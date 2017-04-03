#include "supercalc_plugin_mult.h"

double Supercalc_plugin_mult::operation(double op1, double op2)
{
    return op1 * op2;
}

std::string Supercalc_plugin_mult::get_name() const
{
    return "multiplication (*)";
}

extern "C" SUPERCALC_PLUGIN_MULTSHARED_EXPORT std::unique_ptr<SuperCalcPlugin> SuperCalcPlugin_new()
{
    return std::make_unique<Supercalc_plugin_mult>();
}
