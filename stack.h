/*
    Author: Lionel Jamaigne
    Creation Date: 10/03/2016
    Last Modified: 27/04/2016
    Last Modification:
    Known Issues:
    Version: 1.0
*/

#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "birthday.h"
#include "chaudboy.h"

typedef T;

T** createStack(const int nbElems);
T* popStack(void);
T* getLastElemStack(void);

void pushStack(T* elem);
void setTemplate(const char* string);
void freeStack(void);

static BOOL isFullStack(void);
static BOOL isEmptyStack(void);

#endif
