/*
    Author: Lionel Jamaigne
    Creation Date: 10/03/2016
    Last Modified: 08/04/2016
    Last Modification:
    Known Issues:
    Version: 1.0
*/

#ifndef BIRTHDAY_H
#define BIRTHDAY_H

#include "chaudboy.h"
#include "date.h"
#include <time.h>

typedef struct Birthday
{
    char prenom[15];
    char nom[15];
    int jours;
    int mois;
    int annee;
    struct Birthday *psuiv;
} BIRTHDAY;

void printBirthdays(void);
void printBirthday(const BIRTHDAY* temp);
void alterIndex(BIRTHDAY* new);
void sortBirthdays(const BIRTHDAY* new);
void loadBirthdays(void);
void saveBirthdays(void);
void setBirthday(BIRTHDAY* ajout);
void addBirthday(BIRTHDAY* ajout);
void cleanBirthdays(void);
void printNextBirthday(void);

int getAge(const BIRTHDAY* person);
int getDaysBeforeBirthday(const BIRTHDAY* birthday);

bool isEmptyBirthdayList(void);
bool compBirthdays(const BIRTHDAY* first, const BIRTHDAY* second);

BIRTHDAY* getNextBirthday(void);

#endif
