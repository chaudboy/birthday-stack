/*
    Author: Lionel Jamaigne
    Creation Date: 26/02/2016
    Last Modified: 03/05/2016
    Last Modification:
    Known Issues:
    Version: 1.0
*/

#include "birthday.h"
#include "stack.h"

int nbCurBirthdays = 0;
int lastDayCheckForSoonBirthdays = 0;

BOOL checkForSoonBirthdayToday = false;

PERSON* first = NULL;
PERSON* indexBirthday[12];

/******************************************************************************/
static
BOOL
comp_birthdays(const PERSON* first, const PERSON* second)
{
    /*
        Input:
        Core:
        Output:
    */

    if( first->mois < second->mois )
        return true;

    if( first->mois == second->mois )
        if( first->jours < second->jours || first->jours == second->jours )
            return true;

    return false;

} /* BOOL compBirthdays(const PERSON* first, const PERSON* second) */

/******************************************************************************/
static
void
add_birthday_to_index(const PERSON* addedBirthday)
{
    /*
        Input:
        Core:
        Output:
    */

    if( indexBirthday[(addedBirthday->mois)-1] == NULL )
        indexBirthday[-(addedBirthday->mois)-1] = addedBirthday;

    else
    {
        if( comp_birthdays(addedBirthday, indexBirthday[(addedBirthday->mois)]) )
            indexBirthday[(addedBirthday->mois)-1] = addedBirthday;
    }

} /* void addBirthdayToIndex(const PERSON* addedBirthday) */

/******************************************************************************/
void
set_index_birthdays(void)
{
    /*
        Input:
        Core:
        Output:
    */

    for(int i=0 ; i<12 ; i++)
    {
        indexBirthday[i] = NULL;
    }

} /* void setIndexBirthdays(void) */

/******************************************************************************/
static void
sort_birthdays(const PERSON* birthdayToAdd)
{
    /*
        Input:
        Core:
        Output:
    */

    PERSON* newBirthdayZone = NULL;
    newBirthdayZone = (PERSON*)malloc(sizeof(PERSON));

    if( newBirthdayZone )
    {
        memcpy(newBirthdayZone, birthdayToAdd, sizeof(PERSON));

        PERSON* temp = first;

        BOOL flag = false;
        int i = 0;

        set_template("birthday");
        create_stack(nbCurBirthdays);
        //printf("je viens de creer une pile de %d elements", nbCurBirthdays);

        for(i=0 ; i<nbCurBirthdays && flag != true ; i++ ) // i scan the Dynamic Data Structure until i should be inserted before a PERSON struct or unless it's the end
        {
            if( comp_birthdays(temp, newBirthdayZone) )
            {
                push_stack(temp);

                if( temp->psuiv != NULL )
                    temp = temp->psuiv;
            }

            else
                flag = true;
        }

        if( flag == true ) // i ran into a PERSON struct before which i should be inserted
        {

            if( --i == 0 ) // i have to be inserted before the first PERSON struct -> no need to popStack()
            {
                newBirthdayZone->psuiv = first;
                first = newBirthdayZone;
            }

            else
            {
                PERSON* lastStackElem = pop_stack();
                lastStackElem->psuiv = newBirthdayZone;
                newBirthdayZone->psuiv = temp;
            }
        }

        else
        {
            temp->psuiv = newBirthdayZone;
            newBirthdayZone->psuiv = NULL;
        }

        add_birthday_to_index(newBirthdayZone);
        free_stack();
    }

    else
        MYERROR("malloc error in sortBirthdays");

} /* void sortBirthdays(const PERSON* birthdayToAdd) */

/******************************************************************************/
BOOL
is_empty_birthday_list(void)
{
    /*
        Input:  none
        Core:   says wheter there is at least 1 struct in memory
        Output: a BOOL variable that is true if it's empty
    */

    return first ? false : true;

} /* BOOL isEmptyBirthdayList(void) */

/******************************************************************************/
void
set_birthday(PERSON* ajout)
{
    /*
        Input:  the address of a PERSON struct
        Core:   completes a PERSON struct
        Output:
    */

    char temp[20] = "";
    int entier = 0;
    BOOL ret = false;

    ajout = (PERSON*)malloc(sizeof(PERSON));

    printf("\t\nEntrez un nom: ");
    fgets(temp, 12, stdin);
    clean_string(temp);
    strcpy(ajout->nom, temp);

    printf("\t\nEntrez un prenom: ");
    fgets(temp, 12, stdin);
    clean_string(temp);
    strcpy(ajout->prenom, temp);

    do
    {
        printf("\t\nEntrez le jour (au format xx): ");
        fgets(temp, 4, stdin);
        entier = atoi(temp);
        ret = check_int_bondaries(entier, 1, 31);

        if( ret == true )
            ajout->jours = entier;

        clean_string(temp);

    }while( ret != true );

    do
    {
        printf("\t\nEntrez le mois (au format xx): ");
        fgets(temp, 4, stdin);
        entier = atoi(temp);
        ret = check_int_bondaries(entier, 1, 12);

        if( ret == true )
            ajout->mois = entier;

        clean_string(temp);

    }while( ret != true );

    do
    {
        printf("\t\nEntrez l'annee (au format xxxx): ");
        fgets(temp, 6, stdin);
        entier = atoi(temp);
        ret = check_int_bondaries(entier, 1950, get_current_year());

        if( ret == true )
            ajout->annee = entier;

        clean_string(temp);

    }while( ret != true );

} /* void setBirthday(PERSON* ajout) */

/******************************************************************************/
static void
add_birthday(PERSON *ajout)
{
    /*
        Input:  the address of a PERSON struct
        Core:   adds a PERSON struct into the dynamic data structure from the beginning ("first" pointer)
        Output: none
    */

    if( is_empty_birthday_list() )
    {
        first = (PERSON*)malloc(sizeof(PERSON));

        if( first )
        {
            memcpy(first, ajout, sizeof(PERSON));
            first->psuiv = NULL;

            add_birthday_to_index(first);
        }

        else
            MYERROR("malloc error in addBirthday");

        printf("\nAnniversaire ajoute");

    }

    else
    {
        sort_birthdays(ajout);
    }

    nbCurBirthdays++;

} /* void addBirthday(PERSON *ajout) */

/******************************************************************************/
void
print_birthdays(void)
{
    /*
        Input:  none
        Core:   prints all PERSON structures attached from the "first" pointer to "last" pointer
        Output: none
    */

    if( !is_empty_birthday_list() )
    {
        PERSON* temp = first;

        while( temp )
        {
            printf("%s %s est ne le %d/%d/%d et a %d an%c \n",temp->prenom, temp->nom, temp->jours, temp->mois, temp->annee, getAge(temp), getAge(temp) > 1 ? 's' : ' ');

            temp = temp->psuiv;
        }
    }

    else
        MYERROR("no birthdays to print\n");

} /* void printBirthdays(void) */

/******************************************************************************/
void
print_birthday(const PERSON* temp)
{
    /*
        Input:  a PERSON structure address
        Core:   prints a PERSON structure given in parameter
        Output: none
    */

    printf("%s %s est ne le %d/%d/%d et a %d an%c \n",temp->prenom, temp->nom, temp->jours, temp->mois, temp->annee, getAge(temp), getAge(temp) > 1 ? 's' : ' ');

} /* void printBirthday(const PERSON* temp) */

/******************************************************************************/
void
clean_birthdays(void)
{
    /*
        Input:  none
        Core:   processes to free all the PERSON structur's data allocated from the upper malloc. From "first" to "last"
        Output: none
    */

    if( !is_empty_birthday_list() )
    {
        PERSON *temp = first;

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

        printf("Anniversair%s supprim%ss", nbCurBirthdays > 1 ? "es" : "e", nbCurBirthdays > 1 ? "es" : "e");

        nbCurBirthdays = 0;
    }

    else
        MYERROR("no birthdays to delete\n");

} /* void cleanBirthdays(void) */

/******************************************************************************/
void
load_birthdays(void)
{
    /*
        Input:  none
        Core:   loads every PERSON structures stored in the file into memory
        Output: none
    */

    if( first )
        clean_birthdays();

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
                PERSON* temp = (PERSON*)malloc(sizeof(PERSON));

                fread(temp->prenom, sizeof(char)*15, 1, file);
                fread(temp->nom, sizeof(char)*15, 1, file);

                fread(&(temp->jours), sizeof(int), 1, file);
                fread(&(temp->mois), sizeof(int), 1, file);
                fread(&(temp->annee), sizeof(int), 1, file);

                add_birthday(temp);

                i++;
            }
        }

        fclose(file);

        printf("\nAnniversair%s sauvegard%s", nbCurBirthdays > 1 ? "es" :"e", nbCurBirthdays > 1 ? "es" : "e");

    }

    else
    {
        perror("Error in loadBirthdays");
    }

} /* void loadBirthdays(void) */

/******************************************************************************/
void
save_birthdays(void)
{
    /*
        Input:  none
        Core:   stores every PERSON structures on a file
        Output: none
    */

    if( !is_empty_birthday_list() )
    {
        FILE* file = NULL;

        file = fopen("birthdays.dat", "w+b");

        if(file)
        {
            int i = 0;

            rewind(file);

            PERSON* temp = first;

            fwrite(&nbCurBirthdays, sizeof(int), 1, file);

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
        MYERROR("no birthdays to save\n");

} /* saveBirthdays(void) */

/******************************************************************************/
int
get_age(const PERSON* person)
{
    /*
        Input:  the address of a PERSON structure
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

} /* int tAge(const PERSON* person) */

/******************************************************************************/
PERSON*
get_next_birthday(void)
{
    /*
        Input:
        Core:
        Output:
    */

    int i = nbCurBirthdays;
    BOOL found = false;
    PERSON* temp = first;

    struct tm* today = get_date();

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

} /* PERSON* getNextBirthday(void) */

/******************************************************************************/
void
print_next_birthday(void)
{
    /*
        Input:
        Core:
        Output:
    */

    if( first )
    {
        PERSON* nextBirthday = get_next_birthday();
        int age = get_age(nextBirthday);
        age++;

        printf("%s %s est ne le %d/%d/%d et aura %d an(s) dans %d jours\n",nextBirthday->prenom,
                                                                            nextBirthday->nom,
                                                                            nextBirthday->jours,
                                                                            nextBirthday->mois,
                                                                            nextBirthday->annee,
                                                                            age,
                                                                            get_days_before_birthday(nextBirthday));
    }

    else
        MYERROR("there is not any birthday in memory\n");

} /* void printNextBirthday(void) */

/******************************************************************************/
int
get_days_before_birthday(const PERSON* birthday)
{
    /*
        Input:
        Core:
        Output:
    */

    DATE today = get_date();
    int nbJours = 0;
    int i = 0;
    int diffMois = 0;

    check_if_bissextile();

    if( today.month > birthday.month || ( today.month == birthday->mois && today.day > birthday->jours ) )
    {
        diffMois = ((birthday->mois)+12) - today.month;
    }

    else if( today.month < birthday->mois )
    {
        diffMois = birthday->mois - today.month;
    }

    while( diffMois > 1 )
    {
        nbJours += daysPerMonth[(today.month)+i];

        if( (today.month)+i == 11 )
            i = 1;

        else
            i++;

        diffMois--;
    }

    if( diffMois == 1 )
    {
        nbJours += (daysPerMonth[(today.month)+i] - today.day);
        nbJours += (birthday->jours - 1);
    }

    else if( diffMois == 0 )
    {
        nbJours += (birthday->jours - today.day);
    }

    return nbJours;

} /* int getDaysBeforeBirthday(const PERSON* birthday) */

/******************************************************************************/
PERSON*
delete_birthday(void)
{
    /*
        Input:
        Core:
        Output:
    */

    if( !is_empty_birthday_list() )
    {
        BOOL found = false;
        PERSON input*;

        set_birthday(input);

        PERSON* temp = first;

        set_template("birthday");
        create_stack(nbCurBirthdays);

        do
        {
            if( is_birthday_equal(temp, &input) )
                found = true;

            else
            {
                push_stack(temp);
                temp = temp->psuiv;
            }


        }while( temp && !found );

        if( !temp & !found )
            printf("Cet anniversaire n'existe pas");

        else if( found )
        {
            if( !is_empty_stack() ) // stack not empty so what i found is at least 2nd
            {
                PERSON* previous = pop_stack();

                if( temp->psuiv ) // there is something after
                {
                    previous->psuiv = temp->psuiv;

                }

                else // only 2 birthdays
                    previous->psuiv = NULL;

                free(temp);
            }

            else // nothing is in the stack so what i found is 1st
            {
                if( temp->psuiv ) // something after
                {
                    first = temp->psuiv;
                    free(temp);
                }

                else // there was only 1 birthday so i initialize "first" & free the zone
                {
                    free(first);
                    first = NULL;
                }
            }

            remove_birthday_from_index(input);
            printf("Anniversaire supprime");
        }

        free(input);
        free_stack();
        nbCurBirthdays--;
    }

    else
        MYERROR("There is not any birthday in memory");

} /* PERSON* deleteBirthday(void) */

/******************************************************************************/
static void
remove_birthday_from_index(const PERSON* birthday)
{
    /*
        Input:
        Core:
        Output:
    */

    if( is_birthday_equal(birthday, indexBirthday[birthday->mois]) )
        indexBirthday[birthday->mois] = NULL;

} /* void removeBirthdayFromIndex(const PERSON* birthday) */

/******************************************************************************/
BOOL
is_birthday_equal(const PERSON* b1, const PERSON* b2)
{
    /*
        Input:
        Core:
        Output:
    */

    return true == ( b1->jours == b2->jours && b1->mois == b2->mois && b1->annee == b2->annee && strcmp(b1->nom, b2->nom) == 0 && strcmp(b1->prenom, b2->prenom) == 0 );

} /*BOOL isBirthdayEqual(const PERSON* b1, const PERSON* b2) */

/******************************************************************************/
BIRTHDAY*
check_ff_birthday_soon(void)
{
    /*
        Input:
        Core:
        Output:
    */

    if( !is_empty_birthday_list() )
    {
        DATE today = get_date();

        if( !checkForSoonBirthdayToday && today.day != lastDayCheckForSoonBirthdays )
        {
            PERSON* nextBirthday = get_next_birthday();

            int nbJours = get_days_before_birthday(nextBirthday);

            if( nbJours <= 7 )
            {
                BIRTHDAY nextBirthdayEvent;
                nextBirthdayEvent.birthday = nextBirthday;
                nextBirthdayEvent.ETA = nbJours;

                /*switch(nbJours)
                {
                    case 1: printf("Demain %s %s fetera son anniversaire & aura %d ans !", nextBirthday->prenom,
                                                                                         nextBirthday->nom,
                                                                                         getAge(nextBirthday)+1);
                        break;

                    case 2: printf("Apres demain %s %s fetera son anniversaire & aura %d ans !", nextBirthday->prenom,
                                                                                               nextBirthday->nom,
                                                                                               getAge(nextBirthday)+1);
                        break;

                    default: printf("Dans %d jours %s %s fetera son anniversaire & aura %d ans !", nbJours,
                                                                                                 nextBirthday->prenom,
                                                                                                 nextBirthday->nom,
                                                                                                 getAge(nextBirthday)+1);
                        break;
                }*/
            }

            checkForSoonBirthdayToday = true;
            lastDayCheckForSoonBirthdays = today.day;
        }

        else if( checkForSoonBirthdayToday && today.day != lastDayCheckForSoonBirthdays )
            checkForSoonBirthdayToday = false;

        return nextBirthdayEvent;
    }

} /* BIRTHDAY checkIfBirthdaySoon(void) */
