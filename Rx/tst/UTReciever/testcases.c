#include "../../src/Reciever.c"
#include "test_mocks.h"
#include <assert.h>
#include <string.h>


/**
 * assert()'s are not tested.
 */ 

void Environment_Initialization(void)
{
    
    print = &printf;
    ReadParamStateSpecificData.RxStatus = 0;

    CalculateMaxStateSpecificData.maxvalue[BatteryParameter_Temparature] = -1 ;
    CalculateMaxStateSpecificData.maxvalue[BatteryParameter_StateOfCharge] = -1 ;
    
    CalculateMinStateSpecificData.minvalue[BatteryParameter_Temparature] = INT_MAX ;
    CalculateMinStateSpecificData.minvalue[BatteryParameter_StateOfCharge] = INT_MAX ;

    CalculateMovingAvergaeStateSpecific[BatteryParameter_Temparature].MaxNumOfSamplesForMovingAverage = 5;
    CalculateMovingAvergaeStateSpecific[BatteryParameter_Temparature].MovingAverage = 0.0;
    CalculateMovingAvergaeStateSpecific[BatteryParameter_Temparature].NumberofSamplesCollected = 0;
    CalculateMovingAvergaeStateSpecific[BatteryParameter_Temparature].SumOfSamples = 0;

    CalculateMovingAvergaeStateSpecific[BatteryParameter_StateOfCharge].MaxNumOfSamplesForMovingAverage = 5;
    CalculateMovingAvergaeStateSpecific[BatteryParameter_StateOfCharge].MovingAverage = 0.0;
    CalculateMovingAvergaeStateSpecific[BatteryParameter_StateOfCharge].NumberofSamplesCollected = 0;
    CalculateMovingAvergaeStateSpecific[BatteryParameter_StateOfCharge].SumOfSamples = 0;

    Reciever_sm.IsRxTerminationRequested = 0;
    Reciever_sm.param = BatteryParameter_TotalNumber;
    Reciever_sm.parambuff[BatteryParameter_Temparature] = 0;
    Reciever_sm.parambuff[BatteryParameter_StateOfCharge] =0;
    Reciever_sm.state = &RecieveData;

    ResetStubs();
}

/**
 * The data that is recieved from list reader will be as follows
 * Temparature , StateOfCharge , Temparature , StateOfCharge ......
 * 
 * Lets run the Reciever for two times and check if the first value is treated as temparture 
 * and second value is treated as StateOfCharge.
 * 
 */

void TC_EvaluateTheOrderOfParametersRecieved(void)
{
    GetBatteryParamValueFromList_value = 10;
    MaxCall_IsListReadingAllowed = 2;
    GenerateValuesForBatteryParam = &GenerateIncrementalValues;
    Reciever_Main();
    assert(Reciever_sm.parambuff[BatteryParameter_Temparature] == 11);
    assert(Reciever_sm.parambuff[BatteryParameter_StateOfCharge] == 12);
}

/**
 * The data that is recieved from list reader will be as follows
 * Temparature , StateOfCharge , Temparature , StateOfCharge ......
 * 
 * Lets run the Reciever for three times and check if the third value is stored is temparature.
 * This test ensure that we are looping over these two parameters 
 */

void TC_EvaluateIfloopingbnTheseTwoParameters(void)
{
    GetBatteryParamValueFromList_value = 10;
    MaxCall_IsListReadingAllowed = 3;
    GenerateValuesForBatteryParam = &GenerateIncrementalValues;
    Reciever_Main();
    assert(Reciever_sm.parambuff[BatteryParameter_Temparature] == 13);
}

/**
 * Calculating Max:
 * The very first value of Max = Very First Value Recieved
 */

void TC_VeryFirstValueOfMax(void)
{
    GetBatteryParamValueFromList_value = 10;
    MaxCall_IsListReadingAllowed = 2;
    GenerateValuesForBatteryParam = &GenerateIncrementalValues;
    Reciever_Main();
    assert(CalculateMaxStateSpecificData.maxvalue[BatteryParameter_Temparature] == 11) ;
    assert(CalculateMaxStateSpecificData.maxvalue[BatteryParameter_StateOfCharge] == 12);
}

/**
 * Calculating Max:
 * The max value is the value which is the maximum in the stream. 
 * So here values will be incremented and see if the Maximum is chaning.
 */

void TC_MaxValueChangesIfstreamMaxChanges(void)
{
    GetBatteryParamValueFromList_value = 10;
    MaxCall_IsListReadingAllowed = 4;
    GenerateValuesForBatteryParam = &GenerateIncrementalValues;
    Reciever_Main();
    assert(CalculateMaxStateSpecificData.maxvalue[BatteryParameter_Temparature] == 13) ;
    assert(CalculateMaxStateSpecificData.maxvalue[BatteryParameter_StateOfCharge] == 14);
}


/**
 * Calculating Max:
 * The max value is the value which is the maximum in the stream. 
 * So here stream values will be decremented and see if the Maximum is chaning.
 * Maximum value should not change
 */

void TC_MaxValueDoesntChangeIfstreamMaxDoesntChange(void)
{
    GetBatteryParamValueFromList_value = 20;
    MaxCall_IsListReadingAllowed = 4;
    GenerateValuesForBatteryParam = &GenerateDecrementalValues;
    Reciever_Main();
    assert(CalculateMaxStateSpecificData.maxvalue[BatteryParameter_Temparature] == 19) ;
    assert(CalculateMaxStateSpecificData.maxvalue[BatteryParameter_StateOfCharge] == 18);
    assert(GetBatteryParamValueFromList_value == 16);
}


/**
 * Calculating Min:
 * The very first value of Min = Very First Value Recieved
 */

void TC_VeryFirstValueOfMin(void)
{
    GetBatteryParamValueFromList_value = 10;
    MaxCall_IsListReadingAllowed = 2;
    GenerateValuesForBatteryParam = &GenerateIncrementalValues;
    Reciever_Main();
    assert(CalculateMinStateSpecificData.minvalue[BatteryParameter_Temparature] == 11) ;
    assert(CalculateMinStateSpecificData.minvalue[BatteryParameter_StateOfCharge] == 12);
}

/**
 * Calculating Min:
 * The Min value is the value which is the Minimum in the stream. 
 * So here values will be incremented and see if the Minimum is chaning.
 */

void TC_MinValueDeosnotChangesIfstreamMinDoesntChange(void)
{
    GetBatteryParamValueFromList_value = 10;
    MaxCall_IsListReadingAllowed = 4;
    GenerateValuesForBatteryParam = &GenerateIncrementalValues;
    Reciever_Main();
    assert(CalculateMinStateSpecificData.minvalue[BatteryParameter_Temparature] == 11) ;
    assert(CalculateMinStateSpecificData.minvalue[BatteryParameter_StateOfCharge] == 12);
}


/**
 * Calculating Max:
 * The max value is the value which is the maximum in the stream. 
 * So here stream values will be decremented and see if the Maximum is chaning.
 */

void TC_MinChangesIfstreamMinChanges(void)
{
    GetBatteryParamValueFromList_value = 20;
    MaxCall_IsListReadingAllowed = 4;
    GenerateValuesForBatteryParam = &GenerateDecrementalValues;
    Reciever_Main();
    assert(CalculateMinStateSpecificData.minvalue[BatteryParameter_Temparature] == 17);
    assert(CalculateMinStateSpecificData.minvalue[BatteryParameter_StateOfCharge] == 16);
}

/**
 * Calculating Moving Average:
 * older Moving average is retained until 5 new samples are read for a parameter
 */ 

void TC_RetainingOlderMovingAverage(void)
{
    GetBatteryParamValueFromList_value = 20;
    MaxCall_IsListReadingAllowed = 8;
    GenerateValuesForBatteryParam = &GenerateIncrementalValues;
    CalculateMovingAvergaeStateSpecific[BatteryParameter_Temparature].MovingAverage = 12.0;
    CalculateMovingAvergaeStateSpecific[BatteryParameter_StateOfCharge].MovingAverage = 12.0;
    Reciever_Main();
    assert(CalculateMovingAvergaeStateSpecific[BatteryParameter_Temparature].MovingAverage == 12.0);
    assert(CalculateMovingAvergaeStateSpecific[BatteryParameter_StateOfCharge].MovingAverage == 12.0);
}

/**
 * Calculating Moving Average
 * The very first moving sample until first 5 samples will be zero
 *  */ 

void TC_VeryFirstMovingAverage(void)
{
    GetBatteryParamValueFromList_value = 20;
    MaxCall_IsListReadingAllowed = 8;
    GenerateValuesForBatteryParam = &GenerateIncrementalValues;
    Reciever_Main();
    assert(CalculateMovingAvergaeStateSpecific[BatteryParameter_Temparature].MovingAverage == 0.0);
    assert(CalculateMovingAvergaeStateSpecific[BatteryParameter_StateOfCharge].MovingAverage == 0.0);
}




/**
 * Calculating Moving Average:
 * Moving average is Calculated after 5 new samples are read for a parameter
 */ 

void TC_CalculateMovingAverage(void)
{
    GetBatteryParamValueFromList_value = 0;
    MaxCall_IsListReadingAllowed = 10;
    GenerateValuesForBatteryParam = &GenerateIncrementalValues;
    CalculateMovingAvergaeStateSpecific[BatteryParameter_Temparature].MovingAverage = 12.0;
    CalculateMovingAvergaeStateSpecific[BatteryParameter_StateOfCharge].MovingAverage = 12.0;
    Reciever_Main();
    assert(CalculateMovingAvergaeStateSpecific[BatteryParameter_Temparature].MovingAverage == 5.0);
    assert(CalculateMovingAvergaeStateSpecific[BatteryParameter_StateOfCharge].MovingAverage == 6.0);
}

/**
 * Calculating Moving Average:
 * New Moving average is Calculated for every 5 new samples are read for a parameter
 */ 

void TC_CalculatingNewMovingAverage(void)
{
    GetBatteryParamValueFromList_value = 0;
    MaxCall_IsListReadingAllowed = 20;
    GenerateValuesForBatteryParam = &GenerateIncrementalValues;
    Reciever_Main();
    assert(CalculateMovingAvergaeStateSpecific[BatteryParameter_Temparature].MovingAverage == 15.0);
    assert(CalculateMovingAvergaeStateSpecific[BatteryParameter_StateOfCharge].MovingAverage == 16.0);
}


/**
 * Calculating Moving Average:
 * Check no floating value is being trimmed or lost during moving average calculation.
 * 
 * brief history behind this testcase:
 * When i designed the code first, naughty me introduced a bug.
 * i did    float = (int/int)   thinking this converts the into float.
 * again the same naughty me noticed this and changed into following
 *     float = (((float)int)/int)
 * 
 * Now, lucky me MISRA analysis is not being done here.
 */ 

void TC_VerifyIfFloatingIsTrimmedInMovingAverage(void)
{
    float movingAverage;
    CalculateMovingAvergaeStateSpecific[BatteryParameter_Temparature].NumberofSamplesCollected = 4;
    CalculateMovingAvergaeStateSpecific[BatteryParameter_Temparature].SumOfSamples = 26;
    Reciever_sm.param = BatteryParameter_Temparature;
    Execute_CalculateMovingAverage(&Reciever_sm);
    movingAverage = (((float)26)/5);
    assert(movingAverage ==  CalculateMovingAvergaeStateSpecific[BatteryParameter_Temparature].MovingAverage);
}




/**
 * Statemachine Exits if IsListReading is not Allowed.
 */ 

void TC_RecieverExitIfListReadingNotAllowed(void)
{
    GetBatteryParamValueFromList_value = 0;
    MaxCall_IsListReadingAllowed = 20;
    GenerateValuesForBatteryParam = &GenerateIncrementalValues;
    Reciever_Main();
    assert(Reciever_sm.state = &Exit);
    assert(call_IsListReadingAllowed == 20);
}

/**
 * Statemachine Exits if GetBatteryParamValueFromList() retuns NotOk
 * and Max , Min and MovingAverages are skipped
 */ 

void TC_RecieverExitsDuringIllegalFormat(void)
{
    GetBatteryParamValueFromList_value = 0;
    MaxCall_IsListReadingAllowed = 20;
    ret_getbatparamvauluefromlist = Status_NotOk;
    GenerateValuesForBatteryParam = &GenerateIncrementalValues;
    Reciever_Main();
    assert(Reciever_sm.state = &Exit);
    assert(call_IsListReadingAllowed == 1);
    assert(CalculateMovingAvergaeStateSpecific[BatteryParameter_Temparature].MovingAverage == 0.0);
    assert(CalculateMovingAvergaeStateSpecific[BatteryParameter_StateOfCharge].MovingAverage == 0.0);
    assert(CalculateMinStateSpecificData.minvalue[BatteryParameter_Temparature] == INT_MAX);
    assert(CalculateMinStateSpecificData.minvalue[BatteryParameter_StateOfCharge] == INT_MAX);
    assert(CalculateMaxStateSpecificData.maxvalue[BatteryParameter_Temparature] == -1) ;
    assert(CalculateMaxStateSpecificData.maxvalue[BatteryParameter_StateOfCharge] == -1);

}


void TC_StringToEnumConverter(void)
{
    assert(strcmp(BatteryParameterToString[BatteryParameter_Temparature] ,"Temparature") == 0);
    assert(strcmp(BatteryParameterToString[BatteryParameter_StateOfCharge] ,"StateOfCharge") == 0);
}

/**
 * This testcase evaluates the string printed for Max Value
 */ 

void TC_EvaluatePrintfParametersInCalculateMax(void)
{
    Reciever_sm.param = BatteryParameter_Temparature;
    CalculateMaxStateSpecificData.maxvalue[BatteryParameter_Temparature] = 10;
    print = &printfmockforMaxandMin;
    Execute_CalculateMax(&Reciever_sm);
    assert(strcmp(fmt,"%s max value in the stream of data  is %d\n")==0);
    assert(strcmp(paramname,"Temparature")==0);
    assert(value == CalculateMaxStateSpecificData.maxvalue[BatteryParameter_Temparature]);
}

/**
 * This testcase evaluates the string printed for Min Value
 */
void TC_EvaluatePrintfParametersInCalculateMin(void)
{
    Reciever_sm.param = BatteryParameter_Temparature;
    CalculateMinStateSpecificData.minvalue[BatteryParameter_Temparature] = 10;
    print = &printfmockforMaxandMin;
    Execute_CalculateMin(&Reciever_sm);
    assert(strcmp(fmt,"%s min value in the stream of data  is %d\n")==0);
    assert(strcmp(paramname,"Temparature")==0);
    assert(value ==  CalculateMinStateSpecificData.minvalue[BatteryParameter_Temparature]);
}


/**
 * This testcase evaluates the string printed for Moving Average
 */

void TC_EvaluatePrintfParametersInMovingAverage(void)
{
    CalculateMovingAvergaeStateSpecific[BatteryParameter_Temparature].NumberofSamplesCollected = 4;
    Reciever_sm.param = BatteryParameter_Temparature;
    print = &printfmockforMovingAverage;
    Execute_CalculateMovingAverage(&Reciever_sm);
    assert(strcmp(fmt,"%f is the moving average for %s\n")==0);
    assert(strcmp(paramname,"Temparature")==0);
    assert(MovingAverage ==  CalculateMovingAvergaeStateSpecific[BatteryParameter_Temparature].MovingAverage);
}

static void Execute_Fake(statemachine_t *this)
{
    if(call_ListReaderInit != 1)
    {
        call_ListReaderInit = 100;
    }
}

/**
 * This testcase verifies that ListReaderInit() is called before statemachine.
 */ 

void TC_EvaluateIfListReaderInitCalledBeforeRecieverStatemachine(void)
{
    GenerateValuesForBatteryParam = &GenerateIncrementalValues;
    MaxCall_IsListReadingAllowed = 1;
    Reciever_sm.Execute = &Execute_Fake; 
    Reciever_Main();
    assert(call_ListReaderInit == 1);
}
