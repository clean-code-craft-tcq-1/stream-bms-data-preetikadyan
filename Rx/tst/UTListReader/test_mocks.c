#include <string.h>
#include <assert.h>

char inputchar;
char fmtstring[30];
char *inputstring;
int call_scanf_mock;
int scanf_mock(char *fmt, char *buf)
{
    assert(inputstring !=0 && "No input string provided to scanf_mock");
    //strcpy(fmtstring,fmt);
    *buf = inputstring[call_scanf_mock]; 
    call_scanf_mock++;
    return 1;
}


void resetstubs(void)
{
    memset(fmtstring,0,30);
    inputchar = 0;
    call_scanf_mock = 0; 
    inputstring = NULL;
}