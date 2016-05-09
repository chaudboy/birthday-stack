/*
    Author: Lionel Jamaigne
    Creation Date: 05/05/2016
    Last Modified: 06/05/2016
    Last Modification:
    Known Issues:
    Version: 1.0
*/

#include "licence.h"

char*
generate_licence(void)
{
    /*
        Input:
        Core:
        Output:
    */



} /* char* generate_licence(void) */

/******************************************************************************/
char*
get_last_licence(void)
{
    /*
        Input:
        Core:
        Output:
    */

    return licence;

} /* char* get_last_licence(void) */

/******************************************************************************/
void
encode_licence(void)
{
    /*
        Input:
        Core:
        Output:
    */

    set_input_string("\n\tEntrez la licence: ", licence, MAX_CHARS);

} /* void encode_licence(void) */

/******************************************************************************/
void
to_hexa(const int number, char* toHexa)
{
    /*
        Input:
        Core:
        Output:
    */

    int size = sizeof(toHexa) / sizeof(char);

    if( number <= 255 && size >= 2 )
    {
        int temp = 0;
        int i = 1;
        int quotient = number;

        while( quotient != 0 )
        {
            temp = quotient % 16;

            if( temp < 10)
                temp = temp + 48;
            else
                temp = temp + 55;

            quotient = quotient / 16;

            if( size == 2 )
                *(toHexa+(--i)) = temp;
            else
                *(toHexa+(i--)) = temp;
      }

    }

    else
        set_errno("Not enough memory space for hexadecimal value");

} /* void to_hexa(const int number, char* toHexa) */


/******************************************************************************/
BOOL
verify_licence(const char* licence)
{
    /*
        Input:
        Core:
        Output:
    */

} /* BOOL verify_licence(const char* licence) */
