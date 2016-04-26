/*
    Author: Lionel Jamaigne
    Creation Date: ?
    Last Modified: 13/04/2016
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
#include "aes256.h"

#define USERSFILE "usersFile.dat"

#define DUMP(s, i, buf, sz)  {printf(s);                   \
                              for (i = 0; i < (sz);i++)    \
                                  printf("%c", buf[i]); \
                              printf("\n");}

void checkArgument(const int argc, const char *argv[]);

int
main(int argc, char *argv[])
{
    BIRTHDAY *ajout;
    int choice = 0;
    char temp[3] = "";

    printf("bloc de test aes256");
    {
        aes256_context ctx;
        uint8_t key[32];
        uint8_t buf[16], i;

        for (i = 0; i < sizeof(key);i++) key[i] = i;

        strcpy(buf, "plaintexttoencrypt");

        DUMP("txt: ", i, buf, sizeof(buf));
        DUMP("key: ", i, key, sizeof(key));


        aes256_encrypt_ecb(&ctx, buf);
        aes256_decrypt_ecb(&ctx, buf);
        DUMP("dec: ", i, buf, sizeof(buf));

        aes256_done(&ctx);

    }


    //clearScreen();

    createUsersFile(USERSFILE);

    setIndexBirthdays();

    checkArgument(argc, argv);

    do
    {
        checkIfBirthdaySoon();

        printf("\t\n1. Encoder un nouvel anniversaire");
        printf("\t\n2. Afficher les anniversaires");
        printf("\t\n3. Charger un fichier d'anniversaires");
        printf("\t\n4. Sauvegarder les anniversaires sur fichier");
        printf("\t\n5. Afficher le prochain anniversaire");
        printf("\t\n6. Supprimer les anniversaires en cours");
        printf("\t\n7. Supprimer un anniversaire");
        printf("\t\n8. Quitter");
        printf("\t\n\nVotre choix: ");

        fgets(temp, sizeof(temp), stdin);
        choice = atoi(temp);

        cleanString(temp);

        switch(choice)
        {
            case 1: setBirthday(ajout);
                    checkIfBirthdaySoon();
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

            case 7: deleteBirthday();
                break;

            default:
                break;
        }

        if( choice != 8 )
        {
            pressEnterToContinue();
            clearScreen();
        }

    }while( choice != 8 );

    cleanBirthdays();

    return EXIT_SUCCESS;
}

void
checkArgument(const int argc, const char *argv[])
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
                loadBirthdays();


            else if( strcmp(argv[i+1], "-login") == 0 )
                loadLogin(USERSFILE);

            i++;

        }while( i+1 < argc );
    }
}
