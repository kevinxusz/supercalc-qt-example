#ifndef SUPERCALC_PLUGIN_MULT_GLOBAL_H
#define SUPERCALC_PLUGIN_MULT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SUPERCALC_PLUGIN_MULT_LIBRARY)
#  define SUPERCALC_PLUGIN_MULTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SUPERCALC_PLUGIN_MULTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SUPERCALC_PLUGIN_MULT_GLOBAL_H
