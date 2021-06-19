
#pragma once

extern char inputchar;
extern char fmtstring[30];
extern char *inputstring;
extern int call_scanf_mock;
extern int scanf_mock(const char *fmt, char *buf);
extern void resetstubs(void);