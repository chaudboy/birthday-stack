/*
    Author: Lionel Jamaigne
    Creation Date: 10/03/2016
    Last Modified: 27/04/2016
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

typedef struct BirthdayEvent
{
    BIRTHDAY* birthday;
    int ETA;
} BIRTHDAY_EVENT;

static void addBirthdayToIndex(const BIRTHDAY* addedBirthday);
static void removeBirthdayFromIndex(const BIRTHDAY* birthday);
static void sortBirthdays(const BIRTHDAY* new);
static BOOL compBirthdays(const BIRTHDAY* first, const BIRTHDAY* second);

void printBirthdays(void);
void printBirthday(const BIRTHDAY* temp);
void setIndexBirthdays(void);
void loadBirthdays(void);
void saveBirthdays(void);
void setBirthday(BIRTHDAY* ajout);
void addBirthday(BIRTHDAY* ajout);
void cleanBirthdays(void);
void printNextBirthday(void);

int getAge(const BIRTHDAY* person);
int getDaysBeforeBirthday(const BIRTHDAY* birthday);

BOOL isEmptyBirthdayList(void);
BOOL isBirthdayEqual(const BIRTHDAY* b1, const BIRTHDAY* b2);

BIRTHDAY* getNextBirthday(void);
BIRTHDAY* deleteBirthday(void);

BIRTHDAY_EVENT checkIfBirthdaySoon(void);

#endif
