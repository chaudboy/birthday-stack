/*
    Author: Lionel Jamaigne
    Creation Date: 08/04/2016
    Last Modified: 13/04/2016
    Last Modification:
    Known issues:
    Version: 1.0
*/

#include "date.h"

bool
isYearBissextile(int year)
{
    /*
        Input:
        Core:
        Output:
    */

    return true == ( ( year % 4 == 0 && year % 100 != 0 ) || year % 100 == 0 );
}

void
setBissextile(void)
{
    /*
        Input:
        Core:
        Output:
    */

    struct tm* today = getDate();

    daysPerMonth[0] = 31;
    daysPerMonth[2] = 31;
    daysPerMonth[3] = 30;
    daysPerMonth[4] = 31;
    daysPerMonth[5] = 30;
    daysPerMonth[6] = 31;
    daysPerMonth[7] = 31;
    daysPerMonth[8] = 30;
    daysPerMonth[9] = 31;
    daysPerMonth[10] = 30;
    daysPerMonth[11] = 31;

    if( isYearBissextile(today->tm_year) )
    {
        daysPerMonth[1] = 29;
        daysThisYear = 366;
    }

    else
    {
        daysPerMonth[1] = 28;
        daysThisYear = 365;
    }
}

struct tm*
getDate(void)
{
    /*
        Input:
        Core:
        Output:
    */

    time_t now = time(0);
  	struct tm* local = localtime(&now);

  	local->tm_year += 1900;
    local->tm_mon += 1;

    return local;
}

int
monthToNumber(const char* mois)
{
    /*
        Input:  the address of a day of the week
        Core:   sends back the number relative to the good month passed as a const char*
        Output: the month's number
    */

    int ret = 0;

    if( strcmp("Janvier", mois) == 0 ) // ceci est un commentaire
        ret = 1;

    else if( strcmp("Fevrier", mois) == 0 )
        ret = 2;

     else if( strcmp("Mars", mois) == 0 )
        ret = 3;

    else if( strcmp("Avril", mois) == 0 )
        ret = 4;

    else if( strcmp("Mai", mois) == 0 )
        ret = 5;

    else if( strcmp("Juin", mois) == 0 )
        ret = 6;

    else if( strcmp("Juillet", mois) == 0 )
        ret = 7;

    else if( strcmp("Aout", mois) == 0 )
        ret = 8;

    else if( strcmp("Septembre", mois) == 0 )
        ret = 9;

    else if( strcmp("Octobre", mois) == 0 )
        ret = 10;

    else if( strcmp("Novembre", mois) == 0 )
        ret = 11;

    else if( strcmp("Decembre", mois) == 0 )
        ret = 12;

    return ret;
}

int
getCurrentYear(void)
{
    /*
        Input:
        Core:
        Output:
    */

    time_t now = time(0);
	struct tm* local = localtime(&now);

	local->tm_year += 1900;

	return local->tm_year;
}