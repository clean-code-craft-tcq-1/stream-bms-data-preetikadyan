#include "../../src/ListReader.c"
#include "test_mocks.h"


void Environment_Initialization(void)
{
    scan = &scanf;
    ListReaderState = ListReader_Inactive;
    resetstubs();
}


void TC_TestingListReaderInit(void)
{
    char *string = "--------------------------------SENDER OUTPUT------------------------\n[[['temperature 1', 0, 'Limit OK'], ['state_of_charge 1', 52, 'Limit OK']], [['temperature 2', 44, 'Limit OK'], ['state_of_charge 2', 12, 'check_limit']]] \n";
    inputstring = string;
    scan = &scanf_mock;
    ListReaderInit();
    assert(string[call_scanf_mock] == ' ');
    assert(string[call_scanf_mock+1] == '0');
}

void TC_GetBatteryParamValueFromList(void)
{
    char *string = " 0, 'Limit OK'], ['state_of_charge 1', 52, 'Limit OK']], [['temperature 2', 44, 'Limit OK'], ['state_of_charge 2', 12, 'check_limit']]] \n";
    int number;
    Status_t status;
    ListReaderState = ListReader_ContainsData;
    scan = &scanf_mock;
    inputstring = string;
    status = GetBatteryParamValueFromList(&number);
    assert(ListReaderState == ListReader_ContainsData);
    assert(status == Status_OK);
    assert(string[call_scanf_mock] == ' ');
    assert(string[call_scanf_mock+1] == '5');
    assert(string[call_scanf_mock+2] == '2');
    assert(number == 0);
}

void TC_IllegalParamValueForASCIIcharbelow0(void)
{
    char *string = "./#$.......,";
    int number;
    Status_t status;
    ListReaderState = ListReader_ContainsData;
    scan = &scanf_mock;
    inputstring = string;
    status = GetBatteryParamValueFromList(&number);
    assert(ListReaderState == ListReader_IllegalFormat);
    assert(status == Status_NotOk);
    assert(IsListReadingAllowed() == 0);
}

void TC_IllegalParamValueForASCIIcharAbove9(void)
{
    char *string = ".:#$.......,";
    int number;
    Status_t status;
    ListReaderState = ListReader_ContainsData;
    scan = &scanf_mock;
    inputstring = string;
    status = GetBatteryParamValueFromList(&number);
    assert(ListReaderState == ListReader_IllegalFormat);
    assert(status == Status_NotOk);
    assert(IsListReadingAllowed() == 0);
}

void TC_GetBatteryParamValueFromListEndOfListReached(void)
{
    char *string = " 12, 'check_limit']]] \n-";
    int number;
    Status_t status;
    ListReaderState = ListReader_ContainsData;
    scan = &scanf_mock;
    inputstring = string;
    status = GetBatteryParamValueFromList(&number);
    assert(ListReaderState == ListReader_NoData);
    assert(number == 12);
    assert(status == Status_OK);
    assert(IsListReadingAllowed() == 0);
}



