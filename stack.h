/*
    Author: Lionel Jamaigne
    Creation Date: 10/03/2016
    Last Modified: 06/05/2016
    Last Modification:
    Known Issues:
    Version: 1.0
*/

#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "person.h"
#include "chaudboy.h"

typedef int T;

T** create_stack(const int nbElems);
T* pop_stack(void);
T* get_last_elem_from_stack(void);

void push_stack(T* elem);
void set_template(const char* string);
void free_stack(void);

BOOL is_full_stack(void);
BOOL is_empty_stack(void);

#endif
