/*
    Author: Lionel Jamaigne
    Creation Date: 26/02/2016
    Last Modified: 15/03/2016
    Last Modification:
    Known Issues:
    Version: 1.0
*/

#include "birthday.h"
#include "stack.h"

int nbCurBirthdays = 0;

BIRTHDAY *first = NULL;
BIRTHDAY *last = NULL;
BIRTHDAY *prec = NULL;

BIRTHDAY* indexBirthdayTab[12];


bool
compBirthdays(const BIRTHDAY* first, const BIRTHDAY* second)
{
    /*
        Input:
        Core:
        Output:
    */

    if( first->mois < second->mois ) return true;
    if( first->mois == second->mois )
    {
        if( first->jours < second->jours || first->jours == second->jours ) return true;
    }

    return false;
}

void
alterIndex(BIRTHDAY* new)
{
    /*
        Input:
        Core:
        Output:
    */

    indexBirthdayTab[(new->mois)++] = new;
}

void
sortBirthdays(const BIRTHDAY* new)
{
    /*
        Input:
        Core:
        Output:
    */

    BIRTHDAY* temp = first;
    BIRTHDAY* temp2 = NULL;
    bool flag = false;
    int i = 0;

    setTemplate("birthday");
    BIRTHDAY** tab = createStack(nbCurBirthdays);
    printf("JE CREE UNE PILE DE %d ELEMENTS", nbCurBirthdays);
    for(i=0 ; i<nbCurBirthdays && flag != true ; i++ ) // i scan the Dynamic Data Structure until i should be inserted before a BIRTHDAY struct or unless it's the end
    {
        if( compBirthdays(temp, new) )
        {
            pushStack(temp);
            if( temp->psuiv != NULL ) temp = temp->psuiv;
        }

        else flag = true;
    }

    temp2 = (BIRTHDAY*)malloc(sizeof(BIRTHDAY)); // if there is something before or not i need the malloc to create the new birtday
    memcpy(temp2, new, sizeof(BIRTHDAY));

    if( flag == true ) // i ran into a BIRTHDAY struct before which i should be inserted
    {
        if( !isEmptyStack() ) // if there is at least 1 thing in the stack i know i have to get this element & make it point to my new zone
        {
            DEBUG("PILE PAS VIDE\n");
            BIRTHDAY* beforeNew = popStack();
            beforeNew->psuiv = temp2;
            DEBUG("FIN PILE PAS VIDE\n");
        }

        else
        {
            first = temp2;
            temp2->psuiv = temp;
        }
    }

    else temp->psuiv = temp2;

    freeStack();
}

bool
isEmpty(void)
{
    /*
        Input:  none
        Core:   says wheter there is at least 1 struct in memory
        Output: a bool variable that is true if it's empty
    */

    return first ? false : true;
}

void
setBirthday(BIRTHDAY* ajout)
{
    /*
        Input:  the address of a BIRTHDAY struct
        Core:   completes a BIRTHDAY struct
        Output: none
    */

    char temp[20] = "";
    int entier = 0;
    bool ret = false;

    ajout = (BIRTHDAY*)malloc(sizeof(BIRTHDAY));

    printf("\t\nEntrez un nom: ");
    fgets(temp, 12, stdin);
    cleanString(temp);
    strcpy(ajout->nom, temp);

    printf("\t\nEntrez un prenom: ");
    fgets(temp, 12, stdin);
    cleanString(temp);
    strcpy(ajout->prenom, temp);

    do
    {
        printf("\t\nEntrez le jour (au format xx): ");
        fgets(temp, 4, stdin);
        entier = atoi(temp);
        ret = checkIntBondaries(entier, 1, 31);

        if( ret == true )
            ajout->jours = entier;

        cleanString(temp);

    }while( ret != true );

    do
    {
        printf("\t\nEntrez le mois (au format xx): ");
        fgets(temp, 4, stdin);
        entier = atoi(temp);
        ret = checkIntBondaries(entier, 1, 12);

        if( ret == true )
            ajout->mois = entier;

        cleanString(temp);

    }while( ret != true );

    do
    {
        printf("\t\nEntrez l'annee (au format xxxx): ");
        fgets(temp, 6, stdin);
        entier = atoi(temp);
        ret = checkIntBondaries(entier, 1950, getCurrentYear());

        if( ret == true )
            ajout->annee = entier;

        cleanString(temp);

    }while( ret != true );

    addBirthday(ajout);
}

void
addBirthday(BIRTHDAY *ajout)
{
    /*
        Input:  the address of a BIRTHDAY struct
        Core:   adds a BIRTHDAY struct into the dynamic data structure from the beginning ("first" pointer)
        Output: none
    */

    if( isEmpty() )
    {
        first = (BIRTHDAY*)malloc(sizeof(BIRTHDAY));
        memcpy(first, ajout, sizeof(BIRTHDAY));
        first->psuiv = NULL;
    }

    else
    {
        sortBirthdays(ajout);
    }

    nbCurBirthdays++;

}

void
printBirthdays(void)
{
    /*
        Input:  none
        Core:   prints all BIRTHDAY structures attached from the "first" pointer to "last" pointer
        Output: none
    */

    BIRTHDAY* temp = first;

    if( !isEmpty() )
    {
        while( temp != NULL )
        {
            printf("%s %s est n%c le %d/%d/%d et a %d an(s) \n",temp->prenom, temp->nom, '\x8a',temp->jours, temp->mois, temp->annee, getAge(temp));
            temp = temp->psuiv;
        }
    }

    else
        MYERROR(ANSI_COLOR_YELLOW "NO BIRTHDAYS TO PRINT" ANSI_COLOR_RESET);
}

void
printBirthday(const BIRTHDAY* temp)
{
    /*
        Input:  a BIRTHDAY structure address
        Core:   prints a BIRTHDAY structure given in parameter
        Output: none
    */

    printf("%s %s est n%c le %d/%d/%d et a %d an(s) \n",temp->prenom, temp->nom, '\xe9',temp->jours, temp->mois, temp->annee, getAge(temp));
}

void
cleanBirthdays(void)
{
    /*
        Input:  none
        Core:   processes to free all the BIRTHDAY structur's data allocated from the upper malloc. From "first" to "last"
        Output: none
    */

    if( !isEmpty() )
    {
        BIRTHDAY *temp = first;

        while( temp )
        {
          first = temp;
          temp = first->psuiv;

          free(first);
        }
    }
}

void
loadBirthdays(void)
{
    /*
        Input:  none
        Core:   loads every BIRTHDAY structures stored in the file into memory
        Output: none
    */

    FILE* file = NULL;

    file = fopen("birthdays.dat", "rb");

    if(file)
    {
        fseek(file, 0, SEEK_SET);
        DEBUG("je passe dans loadbirthdays");
        BIRTHDAY* temp = (BIRTHDAY*)malloc(sizeof(BIRTHDAY));

        while( fread(temp, sizeof(BIRTHDAY), 1, file) == 1 )
        {
            DEBUG("1 + ");
            addBirthday(temp);
            BIRTHDAY* temp = (BIRTHDAY*)malloc(sizeof(BIRTHDAY));
        }

        fclose(file);
    }

    else
    {
        perror("Error in loadBirthdays ");
    }

}

void
saveBirthdays(void)
{
    /*
        Input:  none
        Core:   stores every BIRTHDAY structures on a file
        Output: none
    */

    if( !isEmpty() )
    {
        FILE* file = NULL;
        DEBUG("je passe par saveBirthdays");
        file = fopen("birthdays.dat", "w+b");

        if(file)
        {
            fseek(file, 0, SEEK_SET);

            BIRTHDAY* temp = first;

            while( fwrite(temp, sizeof(BIRTHDAY), 1, file) == 1 );
            {
                temp = temp->psuiv;
            }

            fclose(file);
        }
    }

    else
    {
        MYERROR( ANSI_COLOR_YELLOW "NO BIRTHDAYS TO SAVE" ANSI_COLOR_RESET );
    }
}

int
getAge(const BIRTHDAY* person)
{
    /*
        Input:  the address of a BIRTHDAY structure
        Core:   gets the age of a person with the current year
        Output: the year
    */

    int age = 0;

    time_t now = time(0);
  	struct tm* local = localtime(&now);

  	local->tm_year += 1900;

  	age = local->tm_year - person->annee ;

  	if( local->tm_mon < person->mois )
  	    age--;

  	else
  	{
  	    if( local->tm_year == person->mois )
  	        if( local->tm_mday < person->jours )
  	            age--;
  	}

  	return age;
}
