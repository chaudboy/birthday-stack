/*
    Author: Lionel Jamaigne
    Creation Date: 10/03/2016
    Last Modified: 08/05/2016
    Last Modification:
    Known Issues:
    Version: 1.0
*/

#ifndef PERSON_H
#define PERSON_H

#include <string.h>
#include "stack.h"
#include "chaudboy.h"
#include "date.h"
#include <time.h>

typedef struct Person
{
    char prenom[15];
    char nom[15];
    MY_DATE birthdate;
    struct Person *psuiv;
} PERSON;

static void add_birthday_to_index(const PERSON* addedBirthday);
static void remove_birthday_from_index(const PERSON* birthday);
static void sort_birthdays(const PERSON* new);
static BOOL comp_birthdays(const PERSON* first, const PERSON* second);
static void copy_birthday(PERSON* dest, const PERSON* src, const BOOL copyNextFlag);

void print_birthdays(void);
void print_birthday(const PERSON* temp);
void set_index_birthdays(void);
void load_birthdays(void);
void save_birthdays(void);
void set_birthday(PERSON** ajout);
void add_birthday(PERSON* ajout);
void clean_birthdays(void);
void print_next_birthday(void);

int get_age(const PERSON* person);
int get_days_before_birthday(const PERSON* birthday);

BOOL is_empty_birthday_list(void);
BOOL is_birthday_equal(const PERSON* b1, const PERSON* b2);

PERSON* get_birthday(const int rank);
PERSON* delete_birthday(void);

PERSON* check_if_birthday_soon(void);

#endif
