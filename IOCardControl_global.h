#ifndef IOCARDCONTROL_GLOBAL_H
#define IOCARDCONTROL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(IOCARDCONTROL_LIBRARY)
#  define IOCARDCONTROL_EXPORT Q_DECL_EXPORT
#else
#  define IOCARDCONTROL_EXPORT Q_DECL_IMPORT
#endif

#endif // IOCARDCONTROL_GLOBAL_H
