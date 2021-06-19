
#include "testcases.h"
int main()
{
Environment_Initialization(); 
TC_TestingListReaderInit(); 
Environment_Initialization(); 
TC_GetBatteryParamValueFromList(); 
Environment_Initialization(); 
TC_GetBatteryParamValueFromListIllegalFormat(); 
Environment_Initialization(); 
TC_GetBatteryParamValueFromListEndOfListReached();
return 0;
}
