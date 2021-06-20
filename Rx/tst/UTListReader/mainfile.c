
#include "testcases.h"
int main()
{
Environment_Initialization(); 
TC_TestingListReaderInit(); 
Environment_Initialization(); 
TC_GetBatteryParamValueFromList(); 
Environment_Initialization(); 
TC_IllegalParamValueForASCIIcharbelow0(); 
Environment_Initialization(); 
TC_IllegalParamValueForASCIIcharAbove9(); 
Environment_Initialization(); 
TC_GetBatteryParamValueFromListEndOfListReached();
return 0;
}
