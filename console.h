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

void console_init();
void console_color(int color);
int   console_printc(FILE* out, int color, const char* format, ...) __CHECK_PRINTF__(3, 4);
void console_error(const char* format, ...) __CHECK_PRINTF__(1,2);
void console_warn(const char* format, ...) __CHECK_PRINTF__(1,2);
void console_info  (const char* format, ...) __CHECK_PRINTF__(1,2);

#ifdef CONSOLE_IMPLEMENTATION
#include <stdarg.h>
#include <stdlib.h>

#ifdef _WIN32
#include <io.h>
#define isatty _isatty
#else
#include <unistd.h>
#endif

int* __PIPEDORNOT__ = NULL;
int  __INITED_OR_NOT__ = 0;

void console_init() {
    __PIPEDORNOT__ = ((int*) malloc(sizeof(int)));
    *__PIPEDORNOT__ = (isatty(STDOUT_FILENO)) || (isatty(STDERR_FILENO));
    __INITED_OR_NOT__ = 1;
}

void console_color(int color) {
    switch (color) {
        case RESET:
            (void) printf("\033[0m");
        break;
        case CLEAR:
            (void) printf("\033[2J");
        break;
        case FBLACK:
            (void) printf("\033[30m");
        break;
        case FRED:
            (void) printf("\033[31m");
        break;
        case FGREEN:
            (void) printf("\033[32m");
        break;
        case FYELLOW:
            (void) printf("\033[33m");
        break;
        case FBLUE:
            (void) printf("\033[34m");
        break;
        case FMAGENTA:
            (void) printf("\033[35m");
        break;
        case FCYAN:
            (void) printf("\033[36m");
        break;
        case FWHITE:
            (void) printf("\033[37m");
        break;
        case FGRAY:
            (void) printf("\033[30m");
        break;
        case FLRED:
            (void) printf("\033[90m");
        break;
        case FLGREEN:
            (void) printf("\033[91m");
        break;
        case FLYELLOW:
            (void) printf("\033[92m");
        break;
        case FLBLUE:
            (void) printf("\033[93m");
        break;
        case FLMAGENTA:
            (void) printf("\033[94m");
        break;
        case FLCYAN:
            (void) printf("\033[96m");
        break;
        case FLWHITE:
            (void) printf("\033[97m");
        break;
        case BBLACK:
            (void) printf("\033[40m");
        break;
        case BRED:
            (void) printf("\033[41m");
        break;
        case BGREEN:
            (void) printf("\033[42m");
        break;
        case BYELLOW:
            (void) printf("\033[43m");
        break;
        case BBLUE:
            (void) printf("\033[44m");
        break;
        case BMAGENTA:
            (void) printf("\033[45m");
        break;
        case BCYAN:
            (void) printf("\033[46m");
        break;
        case BWHITE:
            (void) printf("\033[47m");
        break;
        case BGRAY:
            (void) printf("\033[100m");
        break;
        case BLRED:
            (void) printf("\033[101m");
        break;
        case BLGREEN:
            (void) printf("\033[102m");
        break;
        case BLYELLOW:
            (void) printf("\033[103m");
        break;
        case BLBLUE:
            (void) printf("\033[104m");
        break;
        case BLMAGENTA:
            (void) printf("\033[105m");
        break;
        case BLCYAN:
            (void) printf("\033[106m");
        break;
        case BOLD:
            (void) printf("\033[1m");
        break;
        case ITALIC:
            (void) printf("\033[3m");
        break;
        case UNDERLINE:
            (void) printf("\033[4m");
        break;
        case STRIKE:
            (void) printf("\033[9m");
        break;
    }
}

int console_printc(FILE* out, int color, const char* format, ...) {
    va_list args;
    va_start(args, format);

    int r;

    if (__INITED_OR_NOT__ == 1 && *__PIPEDORNOT__) {
        console_color(color);
        r = vfprintf(out,format,args);
        console_color(RESET);
    } else {
        r = vfprintf(out,format,args);
    }
    va_end(args);
    return r;
}

void console_error(const char* format, ...) {va_list args; va_start(args,format); console_printc(stdout,FLRED, "[ERROR] "); vprintf(format, args);}
void console_warn(const char* format, ...) {va_list args; va_start(args,format); console_printc(stdout,FYELLOW, "[WARN] "); vprintf(format, args);}
void console_info  (const char* format, ...) {va_list args; va_start(args,format); console_printc(stdout,FBLUE, "[INFO] "); vprintf(format, args);}
#endif // CONSOLE_IMPLEMENTATION

// Copyright 2022 datawater <datawater1@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
