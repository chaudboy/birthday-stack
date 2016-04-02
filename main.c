/*
    Author: Lionel Jamaigne
    Creation Date: ?
    Last Modified: 15/03/2016
    Last Modification:
    Known Issues:
    Version: 1.0
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "chaudboy.h"
#include "birthday.h"
#include "stack.h"

int
main(int argc, const char *argv[])
{
    BIRTHDAY *ajout;
    int choice = 0;
    char temp[3] = "";
    char test[] = "1";

    if( argc > 1 && strcmp(argv[1], "-l") == 0 ) loadBirthdays();

    pressKeyToContinue();
    pressEnterToContinue();

    do
    {
        printf("\t\n1. Encoder une nouvelle date");
        printf("\t\n2. Afficher les anniversaires");
        printf("\t\n3. charger les anniversaires");
        printf("\t\n4. sauvegarder les anniversaires");
        printf("\t\n5. Quitter");
        printf("\t\n\nVotre choix: ");

        fgets(temp, sizeof(temp), stdin);
        choice = atoi(temp);

        cleanString(temp);

        switch(choice)
        {
            case 1: setBirthday(ajout);
                break;

            case 2: printBirthdays();
                break;

            case 3: loadBirthdays();
                break;

            case 4: saveBirthdays();
                break;

            default:
                break;
        }

    }while( choice != 5 );

    cleanBirthdays();

    return EXIT_SUCCESS;
}
