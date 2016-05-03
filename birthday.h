/*
    Author: Lionel Jamaigne
    Creation Date: 10/03/2016
    Last Modified: 27/04/2016
    Last Modification:
    Known Issues:
    Version: 1.0
*/

#ifndef PERSON_H
#define PERSON_H

#include "chaudboy.h"
#include "date.h"
#include <time.h>

typedef struct Person
{
    char prenom[15];
    char nom[15];
    int jours;
    int mois;
    int annee;
    struct Person *psuiv;
} PERSON;

typedef struct Birthday
{
    PERSON* birthday;
    int ETA;
} BIRTHDAY;

static void addBirthdayToIndex(const PERSON* addedBirthday);
static void removeBirthdayFromIndex(const PERSON* birthday);
static void sortBirthdays(const PERSON* new);
static BOOL compBirthdays(const PERSON* first, const PERSON* second);

void printBirthdays(void);
void printBirthday(const PERSON* temp);
void setIndexBirthdays(void);
void loadBirthdays(void);
void saveBirthdays(void);
void setBirthday(PERSON* ajout);
void addBirthday(PERSON* ajout);
void cleanBirthdays(void);
void printNextBirthday(void);

int getAge(const PERSON* person);
int getDaysBeforeBirthday(const PERSON* birthday);

BOOL isEmptyBirthdayList(void);
BOOL isBirthdayEqual(const PERSON* b1, const PERSON* b2);

PERSON* getNextBirthday(void);
PERSON* deleteBirthday(void);

BIRTHDAY checkIfBirthdaySoon(void);

#endif
