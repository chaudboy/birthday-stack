/*
    Author: Lionel Jamaigne
    Creation Date: 08/04/2016
    Last Modified: 13/04/2016
    Last Modification:
    Known issues:
    Version: 1.0
*/

#ifndef DATE_H
#define DATE_H

#include <time.h>
#include "chaudboy.h"

int daysThisYear;
int daysPerMonth[12];

BOOL isYearBissextile(int year);
void setBissextile(void);

int monthToNumber(const char* mois);
int getCurrentYear(void);

struct tm* getDate(void);

#endif
