/*
    Author: Lionel Jamaigne
    Creation Date: 26/02/2016
    Last Modified: 27/04/2016
    Last Modification:
    Known Issues:
    Version: 1.0
*/

#include "stack.h"

static int nbMaxElems = 0;
static int nbCurElems = 0;

static T** tab = NULL;

T**
createStack(const int nbElems)
{
    /*
        Input:
        Core:
        Output:
    */

    nbMaxElems = nbElems;
    tab = (T**)malloc(sizeof(T*)*nbElems);

    if( tab )
    {
        for(int i=0;i<nbElems;i++)
        {
            tab[i] = NULL;
        }
        //DEBUG("je viens de creer une stack sans soucis\n");
    }

    else
    {
        MYERROR("malloc error in createStack");
    }



    return tab;
}

/******************************************************************************/
void
pushStack(T* elem)
{
    /*
        Input:
        Core:
        Output:
    */

    if( !isFullStack() )
    {
        tab[nbCurElems] = elem;
        nbCurElems++;
        //DEBUG("push OK pile non pleine\n");
    }

    else
        MYERROR("The stack is currently full");
}

/******************************************************************************/
T*
popStack(void)
{
    /*
        Input:
        Core:
        Output:
    */

    if( !isEmptyStack() )
    {
        T* temp = tab[nbCurElems-1];
        tab[--nbCurElems] = NULL;
        //DEBUG("pop OK je vais retourner l'annif");
        return temp;
    }

    else
        MYERROR("The stack is currently empty");

    return NULL;
}

/******************************************************************************/
void
freeStack(void)
{
    /*
        Input:
        Core:
        Output:
    */

    nbCurElems = nbMaxElems = 0;
    free(tab);
    tab = NULL;
}

/******************************************************************************/
T*
getLastElemStack(void)
{
    /*
        Input:
        Core:
        Output:
    */

    return tab[nbCurElems-1];
}

/******************************************************************************/
BOOL
isEmptyStack(void)
{
    /*
        Input:
        Core:
        Output:
    */

    return tab[0] ? false : true;
}

/******************************************************************************/
BOOL
isFullStack(void)
{
    /*
        Input:
        Core:
        Output:
    */

    return tab[nbMaxElems-1] ? true : false;

}

/******************************************************************************/
void
setTemplate(const char* string)
{
    /*
        Input:
        Core:
        Output:
    */

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
        //DEBUG("je set le template d'annifs\n");
    }

    else
        MYERROR("wrong template in setTemplate");
}
