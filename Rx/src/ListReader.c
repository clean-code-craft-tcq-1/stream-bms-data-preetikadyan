/*******************************************************************************************************************************************************************
 * This program recieves the data from the .py file
 * The python sender outputs the data in the list [python data structure] format.
 * The code below extracts the param values from the list.
 * the output looks as follows
 * 
 * -----------------------------------SENDER OUTPUT --------------------------------
 * [[['temperature 1', 81, 'check_limit'], ['ListReaderState_of_charge 1', 86, 'check_limit']], [['temperature 2', 46, 'check_limit'], ['ListReaderState_of_charge 2', 27, 'Limit OK']]]
 * -----------------------------------SENDER OUTPUT END -----------------------------
 * 
 * The output can be assumed as follows
 *      1) ... = unwanted characters
 *      2) _   = space
 *      3) number = number
 *      4) , = , 
 * 
 * ...,_number,_...,_...,_number,_...,_...,_number,_...,_...,_number,(and so on)
 * 
 * The sequence ends as soon as a new line is entered. We will just iterate through the
 * sequence until a new line (\n) is read.
 * Once the '-' is read then there end of hte data buffer is read.
 * 
 * 
 ********************************************************************************************************************************************************************/ 

#include <stdio.h>              /* for scanf() */
#include <assert.h>             /* for assert */
#include "ListReader.h"         /* Units header */

ListReader_t ListReaderState;

//Test double.
int (*scan)(const char *format, ...) = &scanf;

static char ReadCharFromStdin(void)
{
    char ch;
    scan("%c",&ch);    
    return ch;
}

static void Readthestreamuntil(char par_ch)
{
    char ch;
    while(1)
    {
        scan("%c",&ch);
        if(ch == par_ch)
        {
            break;
        }   
    }
    
}

static int IsCharInputANumber(char ch)
{
    int ret = 0;
    if((ch >= '0') && (ch <='9'))
    {
        ret= 1;
    }
    return ret;
}

static Status_t readparametervalue(int *buf)
{   

    char ch ;
    Status_t ParamReadStatus = Status_OK;
    int unit = 1;
    int number = 0;
    int loop = 1;
    ch = ReadCharFromStdin(); /* the extra space in the sequence */
    while(loop)
    {
        ch = ReadCharFromStdin();
        
        if(ch != ',')
        {
            if(IsCharInputANumber(ch))
            {
                number = number * unit + (ch -'0');
                unit = unit*10;
            }else
            {
                ParamReadStatus = Status_NotOk;
                loop = 0;
            }
        }
        else{
            loop = 0 ;
            *buf = number;
        }
    }
   return ParamReadStatus;
}

static int IsNextParameterPresent(void)
{
    int IsNextParamPresent = 1;
    char ch;
    int loop = 2;
    while(loop >0)
    {
        ch = ReadCharFromStdin();
        
        if(ch == ',')
        {
            loop --;
        }

        if(ch =='-')
        {
            IsNextParamPresent = 0;
            loop = 0;                
        }
        
    }
    return IsNextParamPresent;
}

static void ListReaderStateBasedOnNextParameter(void)
{
    if(IsNextParameterPresent() == 1)
    {
        ListReaderState = ListReader_ContainsData;
    }
    else 
    {
        ListReaderState = ListReader_NoData;
    }
}

Status_t GetBatteryParamValueFromList(int *buf)
{
    Status_t readstatus ;
    /* https://stackoverflow.com/questions/3692954/add-custom-messages-in-assert/3692961 */
    assert(IsListReadingAllowed() && "Reading is triggered even when it is not possible");
    assert((buf != 0)&&"parameter buf is NULL");

    readstatus =  readparametervalue(buf);
    if( readstatus == Status_OK)
    {
        ListReaderStateBasedOnNextParameter();
    }
    else{
        ListReaderState = ListReader_IllegalFormat;
    }
    return readstatus;
}

void ListReaderInit(void)
{
    Readthestreamuntil(',');
    ListReaderState = ListReader_ContainsData;
}


int IsListReadingAllowed(void)
{
    return (ListReaderState == ListReader_ContainsData);
}
