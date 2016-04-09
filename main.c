/*
    Author: Lionel Jamaigne
    Creation Date: ?
    Last Modified: 09/04/2016
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
#include "date.h"

int
main(int argc, const char *argv[])
{
    BIRTHDAY *ajout;
    int choice = 0;
    char temp[3] = "";

    clearScreen();

    setIndexBirthdays();

    if( argc > 1 && strcmp(argv[1], "-l") == 0 )
        loadBirthdays();

    do
    {
        printf("\t\n1. Encoder un nouvel anniversaire");
        printf("\t\n2. Afficher les anniversaires");
        printf("\t\n3. Charger un fichier d'anniversaires");
        printf("\t\n4. Sauvegarder les anniversaires sur fichier");
        printf("\t\n5. Afficher le prochain anniversaire");
        printf("\t\n6. Supprimer les anniversaires en cours");
        printf("\t\n7. Quitter");
        printf("\t\n\nVotre choix: ");

        fgets(temp, sizeof(temp), stdin);
        choice = atoi(temp);

        //clearScreen();

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

            case 5: printNextBirthday();
                break;

            case 6: cleanBirthdays();
                break;

            default:
                break;
        }

        if( choice != 7 )
        {
            pressEnterToContinue();
            clearScreen();
        }

    }while( choice != 7 );

    cleanBirthdays();

    return EXIT_SUCCESS;
}
