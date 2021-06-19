
#pragma once

#include "../../src/ListReader.h"


extern int call_ListReaderInit;
extern int call_IsListReadingAllowed;
extern int MaxCall_IsListReadingAllowed; 

extern void (*GenerateValuesForBatteryParam)(void);
extern void GenerateIncrementalValues(void);
extern void GenerateDecrementalValues(void);

extern Status_t ret_getbatparamvauluefromlist;
extern int call_GetBatteryParamValueFromList;
extern int GetBatteryParamValueFromList_value;
extern void ResetStubs (void);
