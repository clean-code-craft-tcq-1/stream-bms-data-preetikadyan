#pragma once

typedef enum {
    ListReader_Inactive,
    ListReader_ContainsData,
    ListReader_NoData,
    ListReader_IllegalFormat,
    ListReader_TotalNumber
}ListReader_t;

typedef enum{
    Status_OK,
    Status_NotOk
}Status_t;

extern void ListReaderInit(void);
/**
 * @note: This API "must" always be used only if IsEndOfListReached() returns 0 
 *        if not PROGRAM MAY CRASH because of illegal format data or no data.
 * 
 * @brief 
 * Stores the parameter value which is read from the list into the buff address.
 * (The list is the output of the python program).
 * 
 * 
 * @param 
 * *buf - pointer to the bufffer
 *  buf should be Non NULL else PROGRAM CRASHES
 * 
 * @return
 *  Status_NotOK - If python outputted list data format is not recognizable.
 *  Status_OK    - In all other cases.
 *  
 */ 
extern Status_t GetBatteryParamValueFromList(int *buf);

/**
 * \brief Returns TRUE if End of List is reached or if List Format is illegal
 */ 
extern int IsListReadingAllowed(void);


