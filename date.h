/*
    Author: Lionel Jamaigne
    Creation Date: 08/04/2016
    Last Modified: 03/05/2016
    Last Modification:
    Known issues:
    Version: 1.0
*/

#ifndef DATE_H
#define DATE_H

typedef struct Date
{
    int day;
    int month;
    int year;
} DATE;

#include <time.h>
#include "chaudboy.h"

int daysThisYear;
int daysPerMonth[12];

BOOL is_year_bissextile(int year);
void set_days_bissextile(void);

int month_to_number(const char* mois);
int get_current_year(void);

DATE get_date(void);

#endif
