/*
    Author: Lionel Jamaigne
    Creation Date: 26/02/2016
    Last Modified: 09/04/2016
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
    tab = (T**)malloc(sizeof(T*)*nbElems);

    if( tab )
    {
        for(int i=0;i<nbElems;i++)
        {
            tab[i] = NULL;
        }
    }

    else
    {
        MYERROR("malloc error in createStack");
    }



    return tab;
}

void
pushStack(T* elem)
{
    if( !isFullStack() )
    {
        tab[nbCurElems] = elem;
        nbCurElems++;
    }

    else
        MYERROR("The stack is currently full");
}

T*
popStack(void)
{
    if( !isEmptyStack() )
    {
        T* temp = tab[nbCurElems-1];
        tab[--nbCurElems] = NULL;
        return temp;
    }

    MYERROR("The stack is currently empty");
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
