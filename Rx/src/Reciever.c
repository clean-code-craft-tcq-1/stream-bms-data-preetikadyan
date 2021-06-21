#include "Reciever.h"
#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include "ListReader.h"

//testdouble
int (*print)(const char * format, ...) = &printf;

const char *BatteryParameterToString[BatteryParameter_TotalNumber] = {
    "Temparature","StateOfCharge"
};

typedef struct {
    Status_t RxStatus;
}RecieveDataStateSpecific_t;

RecieveDataStateSpecific_t ReadParamStateSpecificData;

void Execute_RecieveData(statemachine_t *sm)
{
    sm->param++;
    if(sm->param >= BatteryParameter_TotalNumber)
    {
        sm->param = BatteryParameter_Temparature;
    }
    ReadParamStateSpecificData.RxStatus = GetBatteryParamValueFromList(&sm->parambuff[sm->param]);
}

void updateState_RecieveData(statemachine_t *sm)
{
    if(ReadParamStateSpecificData.RxStatus == Status_OK)
    {
        sm->state = sm->listOfStates[State_CalculateMax];
    }
    else{
        sm->state = sm->listOfStates[State_ExitProgram];
    }
    return;    
}


typedef struct {
    int maxvalue[BatteryParameter_TotalNumber];
}CalculateMaxStateSpecific_t;

CalculateMaxStateSpecific_t CalculateMaxStateSpecificData = {{-1,-1 }};

void Execute_CalculateMax(statemachine_t *sm)
{
    BatteryParameter_t param = sm ->param;
    if(CalculateMaxStateSpecificData.maxvalue[param] < sm->parambuff[param])
    {
        CalculateMaxStateSpecificData.maxvalue[param] = sm->parambuff[param];
    }
    print("%s max value in the stream of data  is %d\n", BatteryParameterToString[param], CalculateMaxStateSpecificData.maxvalue[param]);
    
}

void updateState_CalculateMax(statemachine_t *sm)
{
    sm->state = sm->listOfStates[State_CalculateMin];
}


typedef struct {
    int minvalue[BatteryParameter_TotalNumber];
}CalculateMinStateSpecific_t;

CalculateMinStateSpecific_t CalculateMinStateSpecificData = {{INT_MAX,INT_MAX }};

void Execute_CalculateMin(statemachine_t *sm)
{
    BatteryParameter_t param = sm ->param;
    if(CalculateMinStateSpecificData.minvalue[param] > sm->parambuff[param])
    {
        CalculateMinStateSpecificData.minvalue[param] = sm->parambuff[param];
    }
    print("%s min value in the stream of data  is %d\n", BatteryParameterToString[param], CalculateMinStateSpecificData.minvalue[param]);
    
}

void updateState_CalculateMin(statemachine_t *sm)
{
    sm->state = sm->listOfStates[State_CalculateMovingAverage];
}


typedef struct {
    int NumberofSamplesCollected;
    int SumOfSamples;
    float MovingAverage;
    int MaxNumOfSamplesForMovingAverage;
}CalculateMovingAvergaeStateSpecific_t;

static CalculateMovingAvergaeStateSpecific_t CalculateMovingAvergaeStateSpecific[BatteryParameter_TotalNumber] = {
    {
        0,0,0.0,5
    },
    {
        0,0,0.0,5
    }
};

void Execute_CalculateMovingAverage(statemachine_t *sm)
{
    assert(CalculateMovingAvergaeStateSpecific[sm->param].MaxNumOfSamplesForMovingAverage !=0 );
    CalculateMovingAvergaeStateSpecific[sm->param].SumOfSamples += sm->parambuff[sm->param];
    CalculateMovingAvergaeStateSpecific[sm->param].NumberofSamplesCollected++;
    if(CalculateMovingAvergaeStateSpecific[sm->param].NumberofSamplesCollected == 
        CalculateMovingAvergaeStateSpecific[sm->param].MaxNumOfSamplesForMovingAverage )
    {
        CalculateMovingAvergaeStateSpecific[sm->param].MovingAverage = 
                                (((float)CalculateMovingAvergaeStateSpecific[sm->param].SumOfSamples)/CalculateMovingAvergaeStateSpecific[sm->param].MaxNumOfSamplesForMovingAverage);
        CalculateMovingAvergaeStateSpecific[sm->param].NumberofSamplesCollected = 0;
        CalculateMovingAvergaeStateSpecific[sm->param].SumOfSamples = 0;
        print("%f is the moving average for %s\n",CalculateMovingAvergaeStateSpecific[sm->param].MovingAverage,BatteryParameterToString[sm->param]);
    }
}

void updateState_CalculateMovingAverage(statemachine_t *sm)
{
    sm->state = sm->listOfStates[State_ExitProgram];
}


void Execute_Exit(statemachine_t *sm)
{
    sm->IsRxTerminationRequested = (IsListReadingAllowed() == 0);    
}

void updateState_Exit(statemachine_t *sm)
{
    if(sm->IsRxTerminationRequested == 0)
    {
        sm->state = sm->listOfStates[State_RecieveData];
    }
}

void Execute_RecieverDataStatemachine(statemachine_t *this)
{
    while(this->IsRxTerminationRequested == 0)
    {
        assert(this->state->Execute!=0 && "state method is pointing to NULL");
        this->state->Execute(this);
        assert(this->state->updateState!=0 && "state method is pointing to NULL");
        this->state->updateState(this);
    }
}


state_t RecieveData ={ &Execute_RecieveData, &updateState_RecieveData };
state_t CalculateMaxValue = { &Execute_CalculateMax , &updateState_CalculateMax};
state_t CalculateMinValue = { &Execute_CalculateMin , &updateState_CalculateMin};
state_t CalculateMovingAverage ={ &Execute_CalculateMovingAverage, &updateState_CalculateMovingAverage };
state_t Exit = {&Execute_Exit,&updateState_Exit};

statemachine_t Reciever_sm = {
    0,
    {0,0},
    BatteryParameter_TotalNumber,
    {&RecieveData , &CalculateMaxValue, &CalculateMinValue, &CalculateMovingAverage ,&Exit},   /// listOfStates
    &RecieveData,                                                                               /// Starting default state
    &Execute_RecieverDataStatemachine
};

void Reciever_Main(void)
{
   ListReaderInit();
    Reciever_sm.Execute(&Reciever_sm);
}

#ifdef MAIN
int main()
{
    Reciever_Main();
    return 0;
}
#endif