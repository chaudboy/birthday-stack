/*
    Author: Lionel Jamaigne
    Creation Date: 26/02/2016
    Last Modified: 03/05/2016
    Last Modification:
    Known Issues:
    Version: 1.0
*/

#include "stack.h"

static int nbMaxElems = 0;
static int nbCurElems = 0;

static T** tab = NULL;

T**
create_stack(const int nbElems)
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

} /* T** createStack(const int nbElems) */

/******************************************************************************/
void
push_stack(T* elem)
{
    /*
        Input:
        Core:
        Output:
    */

    if( !is_full_stack() )
        tab[nbCurElems++] = elem;

    else
        MYERROR("The stack is currently full");

} /* void pushStack(T* elem) */

/******************************************************************************/
T*
pop_stack(void)
{
    /*
        Input:
        Core:
        Output:
    */

    if( !is_empty_stack() )
    {
        T* temp = tab[nbCurElems-1];
        tab[--nbCurElems] = NULL;
        //DEBUG("pop OK je vais retourner l'annif");
        return temp;
    }

    else
        MYERROR("The stack is currently empty");

    return NULL;

} /* T* popStack(void) */

/******************************************************************************/
void
free_stack(void)
{
    /*
        Input:
        Core:
        Output:
    */

    nbCurElems = nbMaxElems = 0;
    free(tab);
    tab = NULL;

} /* void freeStack(void) */

/******************************************************************************/
T*
get_last_elem_from_stack(void)
{
    /*
        Input:
        Core:
        Output:
    */

    return tab[nbCurElems-1];

} /* T* getLastElemStack(void) */

/******************************************************************************/
BOOL
is_empty_stack(void)
{
    /*
        Input:
        Core:
        Output:
    */

    return tab[0] ? FALSE : TRUE;

} /* BOOL isEmptyStack(void) */

/******************************************************************************/
BOOL
is_full_stack(void)
{
    /*
        Input:
        Core:
        Output:
    */

    return tab[nbMaxElems-1] ? TRUE : FALSE;

} /* BOOL isFullStack(void) */

/******************************************************************************/
void
set_template(const char* string)
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

} /* void setTemplate(const char* string) */
