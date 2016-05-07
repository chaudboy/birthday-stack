/*
    Author: Lionel Jamaigne
    Creation Date: ?
    Last Modified: 03/05/2016
    Last Modification:
    Known Issues:
    Version: 1.0
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//#include "chaudboy.h"
//#include "person.h"
//#include "stack.h"
//#include "date.h"
//#include "aes256.h"
#include "licence.h"

int
main(int argc, char* argv[])
{
    char valHexa[3] = "0";

    to_hexa(89, valHexa);

    printf("valeur decimale: %d", 89);
    printf("valHexa %c %c\n", *valHexa, *(valHexa+1));
    printf("valHexa %s", valHexa);
}
