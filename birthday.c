/*
    Author: Lionel Jamaigne
    Creation Date: 26/02/2016
    Last Modified: 08/04/2016
    Last Modification:
    Known Issues:
    Version: 1.0
*/

#include "birthday.h"
#include "stack.h"

int nbCurBirthdays = 0;

BIRTHDAY *first = NULL;
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
sortBirthdays(const BIRTHDAY* birthdayToAdd)
{
    /*
        Input:
        Core:
        Output:
    */

    BIRTHDAY* temp = first;
    BIRTHDAY* newBirthdayZone = NULL;
    bool flag = false;
    int i = 0;

    setTemplate("birthday");
    createStack(nbCurBirthdays);

    newBirthdayZone = (BIRTHDAY*)malloc(sizeof(BIRTHDAY));
    memcpy(newBirthdayZone, birthdayToAdd, sizeof(BIRTHDAY));

    for(i=0 ; i<nbCurBirthdays && flag != true ; i++ ) // i scan the Dynamic Data Structure until i should be inserted before a BIRTHDAY struct or unless it's the end
    {
        if( compBirthdays(temp, newBirthdayZone) )
        {
            pushStack(temp);

            if( temp->psuiv != NULL )
                temp = temp->psuiv;
        }

        else
            flag = true;
    }

    if( flag == true ) // i ran into a BIRTHDAY struct before which i should be inserted
    {

        if( --i == 0 ) // i have to be inserted before the first BIRTHDAY struct -> no need to popStack()
        {
            newBirthdayZone->psuiv = first;
            first = newBirthdayZone;
        }

        else
        {
            BIRTHDAY* lastStackElem = popStack();
            lastStackElem->psuiv = newBirthdayZone;
            newBirthdayZone->psuiv = temp;
        }
    }

    else
    {
        temp->psuiv = newBirthdayZone;
        newBirthdayZone->psuiv = NULL;
    }

    freeStack();
}

bool
isEmptyBirthdayList(void)
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

    if( isEmptyBirthdayList() )
    {
        first = (BIRTHDAY*)malloc(sizeof(BIRTHDAY));

        if( first )
        {
            memcpy(first, ajout, sizeof(BIRTHDAY));
            first->psuiv = NULL;
        }

        else
            MYERROR("malloc error in addBirthday");

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

    if( !isEmptyBirthdayList() )
    {
        BIRTHDAY* temp = first;

        while( temp )
        {
            printf("%s %s est n%c le %d/%d/%d et a %d an(s) \n",temp->prenom, temp->nom, '\xe9',temp->jours, temp->mois, temp->annee, getAge(temp));

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

    if( !isEmptyBirthdayList() )
    {
        BIRTHDAY *temp = first;

        /*do
        {
            if( current->psuiv )
                next = current->psuiv;

            current = NULL;
            free(current);


            if( next )
                current = next;

        }while( next );*/

        do
        {
            first = temp;

            if( first->psuiv )
            {
                first = first->psuiv;
                temp = first;
            }


            free(first);
            first = NULL;

        }while( temp->psuiv );
    }

    else
        MYERROR("no birthdays to delete");
}

void
loadBirthdays(void)
{
    /*
        Input:  none
        Core:   loads every BIRTHDAY structures stored in the file into memory
        Output: none
    */

    cleanBirthdays();

    FILE* file = NULL;

    file = fopen("birthdays.dat", "rb");

    if(file)
    {
        int nbBirthdays = 0;
        int i = 0;

        rewind(file);

        fread(&nbBirthdays, sizeof(int), 1, file);

        if( nbBirthdays > 0 )
        {
            nbCurBirthdays = nbBirthdays;

            while( nbBirthdays > i )
            {
                BIRTHDAY* temp = (BIRTHDAY*)malloc(sizeof(BIRTHDAY));

                fread(temp->prenom, sizeof(char)*15, 1, file);
                fread(temp->nom, sizeof(char)*15, 1, file);

                fread(&(temp->jours), sizeof(int), 1, file);
                fread(&(temp->mois), sizeof(int), 1, file);
                fread(&(temp->annee), sizeof(int), 1, file);

                addBirthday(temp);

                i++;
            }
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

    if( !isEmptyBirthdayList() )
    {
        FILE* file = NULL;

        file = fopen("birthdays.dat", "w+b"); DEBUG("ouverture du fichier\n");


        if(file)
        {
            int i = 0;

            rewind(file);

            BIRTHDAY* temp = first;

            fwrite(&nbCurBirthdays, sizeof(int), 1, file); DEBUG("entier ecrit\n");
            DEBUG("avant tour de boucle\n");
            while( i < nbCurBirthdays )
            {
                printf("i = %d & nbCur = %d", i, nbCurBirthdays);
                fwrite(temp->prenom, sizeof(char)*15, 1, file);
                fwrite(temp->nom, sizeof(char)*15, 1, file);

                fwrite(&(temp->jours), sizeof(int), 1, file);
                fwrite(&(temp->mois), sizeof(int), 1, file);
                fwrite(&(temp->annee), sizeof(int), 1, file);

                temp = temp->psuiv;

                i++;
            }

            fclose(file);
        }
    }

    else
    {
        MYERROR("NO BIRTHDAYS TO SAVE");
    }

    DEBUG("je me casse\n");
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

struct tm*
getDate(void)
{
    time_t now = time(0);
  	struct tm* local = localtime(&now);

  	local->tm_year += 1900;
    local->tm_mon += 1;

    return local;
}

BIRTHDAY*
getNextBirthday(void)
{
    int i = nbCurBirthdays;
    bool found = false;
    BIRTHDAY* temp = first;

    struct tm* today = getDate();

    while( !found && i<nbCurBirthdays )
    {
        if( temp->mois == today->tm_mon )
        {
            if( today->tm_mday < temp->jours )
                found = true;
        }

        if( !found && i < nbCurBirthdays )
            temp = temp->psuiv;
    }

    return temp;
}

void
printNextBirthday(void)
{
    if( first )
    {
        BIRTHDAY* nextBirthday = getNextBirthday();
        int age = getAge(nextBirthday);
        age++;

        printf("%s %s est n%c le %d/%d/%d et aura %d an(s) dans %d jours\n",nextBirthday->prenom,
                                                                            nextBirthday->nom,
                                                                            '\xe9',
                                                                            nextBirthday->jours,
                                                                            nextBirthday->mois,
                                                                            nextBirthday->annee,
                                                                            age,
                                                                            getDaysBeforeBirthday(nextBirthday));
    }

    else
        MYERROR("Il n'y a pas d'anniversaires en memoire");

}

int
getDaysBeforeBirthday(const BIRTHDAY* birthday)
{
    struct tm* today = getDate();
    int nbJours = 0;
    int i = 0;
    int diffMois = 0;

    setBissextile();

    if( today->tm_mon > birthday->mois || ( today->tm_mon == birthday->mois && today->tm_mday > birthday->jours ) )
    {
        diffMois = ((birthday->mois)+12) - today->tm_mon;
    }

    else if( today->tm_mon < birthday->mois )
    {
        diffMois = birthday->mois - today->tm_mon;
    }

    while( diffMois > 1 )
    {
        nbJours += daysPerMonth[(today->tm_mon)+i];

        if( (today->tm_mon)+i == 11 )
        {
            i = 1;
        }

        else
        {
            i++;
        }

        diffMois--;
    }

    if( diffMois == 1 )
    {
        nbJours += (daysPerMonth[(today->tm_mon)+i] - today->tm_mday);
        nbJours += (birthday->jours - 1);
    }

    else if( diffMois == 0 )
    {
        nbJours += (birthday->jours - today->tm_mday);
    }

    return nbJours;

}
