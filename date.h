/*
    Author: Lionel Jamaigne
    Creation Date: 08/04/2016
    Last Modified: 04/05/2016
    Last Modification:
    Known issues:
    Version: 1.0
*/

#ifndef DATE_H
#define DATE_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "chaudboy.h"

typedef struct Date
{
    int day;
    int month;
    int year;
} MY_DATE;

int daysThisYear;
int daysPerMonth[12];



BOOL is_year_bissextile(int year);
void set_days_bissextile(void);

int month_to_number(const char* mois);
int get_current_year(void);

MY_DATE get_date(void);

#endif
