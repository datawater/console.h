#pragma once

#define RESET    -1
#define CLEAR    31

#define FBLACK    0
#define FGRAY     8
#define FGREY     8
#define FRED      1
#define FLRED     9
#define FGREEN    2
#define FLGREEN   10
#define FYELLOW   3
#define FLYELLOW  11
#define FBLUE     4
#define FLBLUE    12
#define FMAGENTA  5
#define FPINK     5
#define FLMAGENTA 13
#define FLPINK    13
#define FCYAN     6
#define FLCYAN    14
#define FWHITE    7
#define FLWHITE   15

#define BBLACK    1+15
#define BGRAY     9+15
#define BRED      2+15
#define BLRED     10+15
#define BGREEN    3+15
#define BLGREEN   11+15
#define BYELLOW   4+15
#define BLYELLOW  12+15
#define BBLUE     5+15
#define BLBLUE    13+15
#define BMAGENTA  6+15
#define BPINK     7+15
#define BLMAGENTA 14+15
#define BLPINK    14+15
#define BCYAN     7+15
#define BLCYAN    15+15
#define BWHITE    8+15
#define BLWHITe   16+15

#define BOLD      32
#define ITALIC    33
#define UNDERLINE 34
#define STRIKE    35

#if defined(__GNUC__) || defined(__clang__) || defined(__GNUG__)
#define __CHECK_PRINTF__(x, y) __attribute__((format(printf, x, y)))
#else
#define __CHECK_PRINTF__(x, y) 
#endif

#include <stdio.h>
#include <inttypes.h>

void console_init();
void console_color(int color);
int  console_printc(FILE* out, int color, const char* format, ...) __CHECK_PRINTF__(3, 4);
void console_error(const char* format, ...) __CHECK_PRINTF__(1,2);
void console_warn(const char* format, ...) __CHECK_PRINTF__(1,2);
void console_info(const char* format, ...) __CHECK_PRINTF__(1,2);