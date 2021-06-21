
#include "testcases.h"
#include <stdio.h>
int main()
{
Environment_Initialization(); 
TC_EvaluateTheOrderOfParametersRecieved(); 
Environment_Initialization(); 
TC_EvaluateIfloopingbnTheseTwoParameters(); 
Environment_Initialization(); 
TC_VeryFirstValueOfMax(); 
Environment_Initialization(); 
TC_MaxValueChangesIfstreamMaxChanges(); 
Environment_Initialization(); 
TC_MaxValueDoesntChangeIfstreamMaxDoesntChange(); 
Environment_Initialization(); 
TC_VeryFirstValueOfMin(); 
Environment_Initialization(); 
TC_MinValueDeosnotChangesIfstreamMinDoesntChange(); 
Environment_Initialization(); 
TC_MinChangesIfstreamMinChanges(); 
Environment_Initialization(); 
TC_RetainingOlderMovingAverage(); 
Environment_Initialization(); 
TC_VeryFirstMovingAverage(); 
Environment_Initialization(); 
TC_CalculateMovingAverage(); 
Environment_Initialization(); 
TC_CalculatingNewMovingAverage(); 
Environment_Initialization(); 
TC_VerifyIfFloatingIsTrimmedInMovingAverage(); 
Environment_Initialization(); 
TC_RecieverExitIfListReadingNotAllowed(); 
Environment_Initialization(); 
TC_RecieverExitsDuringIllegalFormat(); 
Environment_Initialization(); 
TC_StringToEnumConverter(); 
Environment_Initialization(); 
TC_EvaluatePrintfParametersInCalculateMax(); 
Environment_Initialization(); 
TC_EvaluatePrintfParametersInCalculateMin(); 
Environment_Initialization(); 
TC_EvaluatePrintfParametersInMovingAverage(); 
Environment_Initialization(); 
TC_EvaluateIfListReaderInitCalledBeforeRecieverStatemachine();
printf("End Of TestCase Execution \n");
return 0;
}
