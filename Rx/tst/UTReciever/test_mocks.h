
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

extern char fmt[150];
extern char paramname[20];
extern int value;
extern float MovingAverage;
extern int printfmockforMaxandMin(char *par_fmt, char *par_paramname, int par_value);
extern int printfmockforMovingAverage(char *par_fmt, double par_MovingAverage, char *par_paramname);
extern void ResetStubs (void);
