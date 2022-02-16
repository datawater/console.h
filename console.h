#ifndef CONSOLE_H

#define CONSOLE_H

#ifdef _WIN32
#include <windows.h>

void clear_win();
static WORD win_default_attributes(HANDLE hConsole);
static void win_set_attributes(int fg, int bg);
void reset_win();
void red_win();
void green_win();
void yellow_win();
void blue_win();
void magenta_win();
void cyan_win();

#else
#include <unistd.h>

#define ANSII_COLOR_RESET "\033[0m"
#define ANSII_COLOR_RED "\033[31m"
#define ANSII_COLOR_GREEN "\033[32m"
#define ANSII_COLOR_YELLOW "\033[33m"
#define ANSII_COLOR_BLUE "\033[34m"
#define ANSII_COLOR_MAGENTA "\033[35m"
#define ANSII_COLOR_CYAN "\033[36m"
#define ANSII_CLEAR "\033[2J"

static void _reset();
static void _red();
static void _green();
static void _yellow();
static void _blue();
static void _magenta();
static void _cyan();
static void _clear();

#endif

#ifdef CONSOLE_IMPLEMENTATION

#ifdef _WIN32

void clear_win() {
    COORD topLeft  = { 0, 0 };
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(
        console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    FillConsoleOutputAttribute(
        console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    SetConsoleCursorPosition(console, topLeft);
}

static WORD win_default_attributes(HANDLE hConsole) {
	static WORD defaultAttributes = 0;
	CONSOLE_SCREEN_BUFFER_INFO info;

    if (!defaultAttributes && GetConsoleScreenBufferInfo(hConsole, &info)) {
		defaultAttributes = info.wAttributes;
	}

	return defaultAttributes;
}

static void win_set_attributes(int fg, int bg) {
    WORD defaultAttributes;
    CONSOLE_SCREEN_BUFFER_INFO info;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    defaultAttributes = win_default_attributes(hConsole);

    if (fg == -1 && bg == -1) {
        SetConsoleTextAttribute(hConsole, defaultAttributes);
        return;
    }

    if (!GetConsoleScreenBufferInfo(hConsole, &info)) {
        return;
    }

    if (fg != -1) {
        info.wAttributes &= ~(info.wAttributes & 0x0F);
        info.wAttributes |= (WORD)fg;
    }

    if (bg != -1) {
        info.wAttributes &= ~(info.wAttributes & 0xF0);
        info.wAttributes |= (WORD)bg;
    }

    SetConsoleTextAttribute(hConsole, info.wAttributes);
}

void reset_win() {win_set_attributes(-1, -1);}
void red_win() {win_set_attributes(FOREGROUND_RED, -1);}
void green_win() {win_set_attributes(FOREGROUND_GREEN, -1);}
void yellow_win() {win_set_attributes(FOREGROUND_RED | FOREGROUND_GREEN, -1);}
void blue_win() {win_set_attributes(FOREGROUND_BLUE, -1);}
void magenta_win() {win_set_attributes(FOREGROUND_RED | FOREGROUND_BLUE, -1);}
void cyan_win() {win_set_attributes(FOREGROUND_GREEN | FOREGROUND_BLUE, -1);}

#else

void _reset() {printf("%s", ANSII_COLOR_RESET);}
void _red() {printf("%s", ANSII_COLOR_RED);}
void _green() {printf("%s", ANSII_COLOR_GREEN);}
void _yellow() {printf("%s", ANSII_COLOR_YELLOW);}
void _blue() {printf("%s", ANSII_COLOR_BLUE);}
void _blue() {printf("%s", ANSII_COLOR_CYAN);}
void _magenta() {printf("%s", ANSII_COLOR_MAGENTA);}
void _clear() {printf("%s", ANSII_CLEAR);}

#endif
#endif

#define RED 1
#define GREEN 2
#define YELLOW 3
#define BLUE 4
#define MAGENTA 5
#define CYAN 6
#define RESET 7
#define CLEAR 8

extern void console(int c) {
	switch (c) {
		case RED:
			#ifdef _WIN32
				red_win();
			#else
				_red();
			#endif
		break;
		case GREEN:
			#ifdef _WIN32
				green_win();
			#else
				_green();
			#endif
		break;
		case YELLOW:
			#ifdef _WIN32
				yellow_win();
			#else
				_yellow();
			#endif
		break;
		case BLUE:
			#ifdef _WIN32
				blue_win();
			#else
				_blue();
			#endif
		break;
		case MAGENTA:
			#ifdef _WIN32
				magenta_win();
			#else
				_magenta();
			#endif
		break;
		case CYAN:
			#ifdef _WIN32
				cyan_win();
			#else
				_cyan();
			#endif
		break;

		case RESET:
			#ifdef _WIN32
				reset_win();
			#else
				_reset();
			#endif
		break;
		case CLEAR:
			#ifdef _WIN32
				clear_win();
			#else
				_clear();
			#endif
		break;
		default:
			printf("NON EXISTANT COLOR");
			exit(1);
		break;
	}
}

#endif
