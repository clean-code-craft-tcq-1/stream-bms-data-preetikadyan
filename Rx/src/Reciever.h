#pragma once

/**
 * MISRA 18.1 All structure or union types shall be complete at the end of a translation unit.
 * A complete declaration of the structure or union shall be included within any translation
 *  unit that refers to that structure.
 */  

typedef enum {
    State_RecieveData = 0,
    State_CalculateMax,
    State_CalculateMin,
    State_CalculateMovingAverage,
    State_ExitProgram,
    State_TotalNumber
}States_t;

typedef enum{
    BatteryParameter_Temparature,
    BatteryParameter_StateOfCharge,
    BatteryParameter_TotalNumber
} BatteryParameter_t;

typedef struct sm statemachine_t;

typedef struct{
    void (*Execute)(statemachine_t *sm);
    void (*updateState)(statemachine_t *sm);
}state_t;


typedef struct sm
{
    int IsRxTerminationRequested;
    int parambuff[BatteryParameter_TotalNumber];
    BatteryParameter_t param;
    state_t* listOfStates[State_TotalNumber];
    state_t *state;
    void (*Execute)( statemachine_t *this);
}statemachine_t;


