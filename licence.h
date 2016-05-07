/*
    Author: Lionel Jamaigne
    Creation Date: 05/05/2016
    Last Modified: 05/05/2016
    Last Modification:
    Known Issues:
    Version: 1.0
*/

#ifndef LICENCE_H
#define LICENCE_H

#include <string.h>
#include <stdio.h>
#include "chaudboy.h"

#define PARTS 3
#define NUMBER_PER_PART 4
#define MAX_CHARS PARTS*NUMBER_PER_PART

static char licence[MAX_CHARS+1];

char* generate_licence(void);
char* get_last_licence(void);
void encode_licence(void);
void to_hexa(const int number, char* toHexa);

BOOL verify_licence(const char* licence);

#endif
