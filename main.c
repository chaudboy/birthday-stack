/*
    Author: Lionel Jamaigne
    Creation Date: ?
    Last Modified: 03/05/2016
    Last Modification: 06/05/2016
    Known Issues:
    Version: 1.0
*/
/* hello */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "chaudboy.h"
#include "person.h"
#include "stack.h"
#include "date.h"
#include "aes256.h"

#define USERSFILE "usersFile.dat"

void check_argument(const int argc, const char *argv[]);

int
main(const int argc, const char *argv[])
{
    PERSON *ajout = NULL;
    int choice = 0;
    char temp[3] = "";

    clear_screen();

    create_users_file(USERSFILE);

    set_index_birthdays();

    check_argument(argc, argv);

    do
    {
        printf("\t\n1. Encoder un nouvel anniversaire");
        printf("\t\n2. Afficher les anniversaires");
        printf("\t\n3. Charger un fichier d'anniversaires");
        printf("\t\n4. Sauvegarder les anniversaires sur fich ier");
        printf("\t\n5. Afficher le prochain anniversaire");
        printf("\t\n6. Supprimer les anniversaires en cours");
        printf("\t\n7. Supprimer un anniversaire");
        printf("\t\n8. Quitter");
        printf("\t\n\nVotre choix: ");

        fgets(temp, sizeof(temp), stdin);
        choice = atoi(temp);

        clean_string(temp);

        switch(choice)
        {
            case 1: set_birthday(&ajout);
                    add_birthday(ajout);
                    free(ajout);
                    ajout = NULL;
                break;

            case 2: print_birthdays();
                break;

            case 3: load_birthdays();
                break;

            case 4: save_birthdays();
                break;

            case 5: print_next_birthday();
                break;

            case 6: clean_birthdays();
                break;

            case 7: delete_birthday();
                break;

            default:
                break;
        }

        if( choice != 8 )
        {
            press_enter_to_continue();
            clear_screen();
        }

    }while( choice != 8 );

    clean_birthdays();

    clean_errno();

    return EXIT_SUCCESS;
}

/******************************************************************************/
void
check_argument(const int argc, const char *argv[])
{
    /*
        Input:
        Core:
        Output:
    */

    if( argc > 1 )
    {
        int i = 0;

        do
        {
            if( strcmp(argv[i+1], "-lb") == 0 )
                load_birthdays();


            else if( strcmp(argv[i+1], "-login") == 0 )
                load_login(USERSFILE);

            i++;

        }while( i+1 < argc );
    }

} /* void checkArgument(const int argc, const char *argv[]) */
