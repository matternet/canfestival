
/* File generated by gen_cfile.py. Should not be modified. */

#ifndef CANOPENSHELLMASTEROD_H
#define CANOPENSHELLMASTEROD_H

#include "data.h"

/* Prototypes of function provided by object dictionnary */
UNS32 CANOpenShellMasterOD_valueRangeTest (UNS8 typeValue, void * value);
const indextable * CANOpenShellMasterOD_scanIndexOD (CO_Data *d, UNS16 wIndex, UNS32 * errorCode);

/* Master node data struct */
extern CO_Data CANOpenShellMasterOD_Data;

#endif // CANOPENSHELLMASTEROD_H