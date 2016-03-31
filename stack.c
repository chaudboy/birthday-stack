/*
    Author: Lionel Jamaigne
    Creation Date: 26/02/2016
    Last Modified: 15/03/2016
    Last Modification:
    Known Issues:
    Version: 1.0
*/

#include "stack.h"

int nbMaxElems = 0;
int nbCurElems = 0;

T** tab = NULL;

T**
createStack(const int nbElems)
{
    nbMaxElems = nbElems;
    tab = (T**)malloc(sizeof(T)*nbElems);

    for(int i=0;i<nbElems;i++)
    {
        tab[i] = NULL;
    }

    return tab;
}

void
pushStack(T* elem)
{
    if( !isFullStack() )
    {
        tab[nbCurElems] = elem;
        printf("DANSLEPUSH valeurde nbCurElems = %d", nbCurElems);printBirthday(tab[nbCurElems]);
        nbCurElems++;
    }

    else
        MYERROR(ANSI_COLOR_YELLOW "The stack is currently full" ANSI_COLOR_RESET);
}

T*
popStack(void)
{
    if( !isEmptyStack() )
    {
        T* temp = tab[nbCurElems-1];
        printf("DANSLEPOP");printBirthday(temp);
        tab[--nbCurElems] = NULL;
        return temp;
    }

    MYERROR(ANSI_COLOR_YELLOW "The stack is currently empty" ANSI_COLOR_RESET);
    return NULL;
}

void freeStack(void)
{
    free(tab);
}

T*
getLastElemStack(void)
{
    return tab[nbCurElems-1];
}

bool
isEmptyStack(void)
{
    return tab[0] ? false : true;
}

bool
isFullStack(void)
{
    return tab[nbMaxElems-1] ? true : false;
}

void
setTemplate(const char* string)
{
    if( strcmp("int", string) == 0 )
    {
        typedef int T;
    }

    else if( strcmp("char", string) == 0 )
    {
        typedef char T;
    }

    else if( strcmp("float", string) == 0 )
    {
        typedef float T;
    }

    else if( strcmp("short", string) == 0 )
    {
        typedef short T;
    }

    else if( strcmp("birthday", string) == 0 )
    {
        typedef BIRTHDAY T;
    }
}
