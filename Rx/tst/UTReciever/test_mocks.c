#include <string.h>
#include <assert.h>
#include "test_mocks.h"



int call_ListReaderInit;
int call_IsListReadingAllowed;
int MaxCall_IsListReadingAllowed;
Status_t ret_getbatparamvauluefromlist;
int call_GetBatteryParamValueFromList;
int GetBatteryParamValueFromList_value;

void ListReaderInit(void)
{
    call_ListReaderInit++;
}

int IsListReadingAllowed(void)
{
    int retval = 1;
    call_IsListReadingAllowed++;
    if (call_IsListReadingAllowed ==  MaxCall_IsListReadingAllowed)
    {
        retval = 0;
    }
    if(ret_getbatparamvauluefromlist == Status_NotOk)
    {
        retval = 0;
    }
    return retval;
}

void GenerateIncrementalValues(void)
{
    GetBatteryParamValueFromList_value++;
}

void GenerateDecrementalValues(void)
{
    GetBatteryParamValueFromList_value--;
}
void (*GenerateValuesForBatteryParam)(void);

Status_t GetBatteryParamValueFromList(int *buf)
{
    call_GetBatteryParamValueFromList++;
    assert(GenerateValuesForBatteryParam!=0);
    GenerateValuesForBatteryParam();
    *buf = GetBatteryParamValueFromList_value;
    return ret_getbatparamvauluefromlist;
}

char fmt[150];
char paramname[20];
int value;
float MovingAverage;
char mvavg_Parname[20];

int printfmockforMaxandMin(char *par_fmt, char *par_paramname, int par_value)
{
    strcpy(fmt,par_fmt);
    strcpy(paramname,par_paramname);
    value = par_value;
    return 0;
}

int printfmockforMovingAverage(char *par_fmt, double par_MovingAverage, char *par_paramname)
{
    strcpy(fmt,par_fmt);
    MovingAverage = par_MovingAverage;
    strcpy(paramname,par_paramname);
    return 0;
}


void ResetStubs (void)
{
    call_ListReaderInit = 0;
    call_IsListReadingAllowed = 0;
    MaxCall_IsListReadingAllowed = 0;
    ret_getbatparamvauluefromlist = 0;
    call_GetBatteryParamValueFromList = 0;
    GetBatteryParamValueFromList_value = 0;
    GenerateValuesForBatteryParam = 0;
    
    memset(fmt,0,150);
    memset(paramname,0,20);
    value = 0;
}
