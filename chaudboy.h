/*
    Author: Lionel Jamaigne
    Creation Date: 26/02/2016
    Last Modified: 15/03/2016
    Last Modification:
    Known Issues: none
    Version: 1.0w
*/

#ifndef CHAUDBOY_H
#define CHAUDBOY_H

#include <string.h>
#include <time.h>
#include <stdio.h>

#define USEDEBUG
#ifdef USEDEBUG
#define DEBUG(s) printf(s)
#endif

#define true 1
#define false 0

#define ANSI_COLOR_RED        "\x1b[31m" // UNIX
#define ANSI_COLOR_GREEN      "\x1b[32m" // UNIX
#define ANSI_COLOR_YELLOW     "\x1b[33m" // UNIX
#define ANSI_COLOR_BLUE       "\x1b[34m" // UNIX
#define ANSI_COLOR_MAGENTA    "\x1b[35m" // UNIX
#define ANSI_COLOR_CYAN       "\x1b[36m" // UNIX
#define ANSI_COLOR_GREY       "\E[37m" // UNIX
#define ANSI_COLOR_UNDERLINED "\E[4m" // UNIX
#define ANSI_COLOR_BACKGROUND "\E[7m" // UNIX
#define ANSI_COLOR_BOLD       "\033[1m" // UNIX
#define ANSI_COLOR_OPPOSITE       "\033[7m" // UNIX
#define ANSI_COLOR_RESET      "\x1b[0m" // UNIX
#define CLEAR_SCREEN       "\033[H\033[J" // UNIX // "\033[H\033[2J"


#define MYERROR(s) fputs(s, stderr)
#define clearScreen() printf(CLEAR_SCREEN)

typedef int bool;

void cleanString(char* temp);
void printCharValue(const char* string);
void wait(void);
void printAllANSIColors(void);

int monthToNumber(const char* mois);
int getCurrentYear(void);

bool checkIntBondaries(const int number, const int min, const int max);

#endif
