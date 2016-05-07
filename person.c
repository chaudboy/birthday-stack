/*
    Author: Lionel Jamaigne
    Creation Date: 26/02/2016
    Last Modified: 06/05/2016
    Last Modification:
    Known Issues:
    Version: 1.0
*/

#include "person.h"

int nbCurBirthdays = 0;
int lastDayCheckForSoonBirthdays = 0;

BOOL checkForSoonBirthdayToday = FALSE;

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

    if( first->birthdate.month < second->birthdate.month )
        return TRUE;

    if( first->birthdate.month == second->birthdate.month )
        if( first->birthdate.day < second->birthdate.day || first->birthdate.day == second->birthdate.day )
            return TRUE;

    return FALSE;

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

    if( indexBirthday[(addedBirthday->birthdate.month)-1] == NULL )
        indexBirthday[(addedBirthday->birthdate.month)-1] = addedBirthday;

    else
    {
        if( comp_birthdays(addedBirthday, indexBirthday[(addedBirthday->birthdate.month)]) )
            indexBirthday[(addedBirthday->birthdate.month)-1] = addedBirthday;
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
static
void
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
        //memcpy(newBirthdayZone, birthdayToAdd, sizeof(PERSON));
        copy_birthday(newBirthdayZone, birthdayToAdd, FALSE);

        PERSON* temp = first;

        BOOL flag = FALSE;
        int i = 0;

        set_template("birthday");
        create_stack(nbCurBirthdays);
        //printf("je viens de creer une pile de %d elements", nbCurBirthdays);

        for(i=0 ; i<nbCurBirthdays && flag != TRUE ; i++ ) // i scan the Dynamic Data Structure until i should be inserted before a PERSON struct or unless it's the end
        {
            if( comp_birthdays(temp, newBirthdayZone) )
            {
                push_stack(temp);

                if( temp->psuiv != NULL )
                    temp = temp->psuiv;
            }

            else
                flag = TRUE;
        }

        if( flag == TRUE ) // i ran into a PERSON struct before which i should be inserted
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
        SET_ERRNO("malloc error in sortBirthdays");

} /* void sortBirthdays(const PERSON* birthdayToAdd) */

/******************************************************************************/
BOOL
is_empty_birthday_list(void)
{
    /*
        Input:  none
        Core:   says wheter there is at least 1 struct in memory
        Output: a BOOL variable that is TRUE if it's empty
    */

    return first ? FALSE : TRUE;

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
    BOOL ret = FALSE;

    ajout = (PERSON*)malloc(sizeof(PERSON));

    set_input_string("\t\nEntrez un nom: ", temp, 18);
    strcpy(ajout->nom, temp);
    clear_string(temp);

    set_input_string("\t\nEntrez un prenom: ", temp, 18);
    strcpy(ajout->prenom, temp);
    clear_string(temp);

    do
    {
        printf("\t\nEntrez le jour (au format xx): ");
        fgets(temp, 4, stdin);
        clean_string(temp);
        entier = atoi(temp);
        ret = check_int_bondaries(entier, 1, 31);

        if( ret == TRUE )
            ajout->birthdate.day = entier;

    }while( ret != TRUE );

    clear_string(temp);

    do
    {
        printf("\t\nEntrez le mois (au format xx): ");
        fgets(temp, 4, stdin);
        entier = atoi(temp);
        ret = check_int_bondaries(entier, 1, 12);

        if( ret == TRUE )
            ajout->birthdate.month = entier;

        clean_string(temp);

    }while( ret != TRUE );

    clear_string(temp);

    do
    {
        printf("\t\nEntrez l'annee (au format xxxx): ");
        fgets(temp, 6, stdin);
        clean_string(temp);
        entier = atoi(temp);
        ret = check_int_bondaries(entier, 1950, get_current_year());

        if( ret == TRUE )
            ajout->birthdate.year = entier;

    }while( ret != TRUE );

} /* void setBirthday(PERSON* ajout) */

/******************************************************************************/
void
add_birthday(PERSON *ajout)
{
    /*
        Input:  the address of a PERSON struct
        Core:   adds a PERSON struct into the dynamic data structure from the beginning ("first" pointer)
        Output: none
    */

    if( is_empty_birthday_list() )
    {
        DEBUG("je passe par add_birthday()\n");
        first = (PERSON*)malloc(sizeof(PERSON));

        if( first )
        {
            DEBUG("avant de copier\n");
            //memcpy(first, ajout, sizeof(PERSON));
            copy_birthday(first, ajout, FALSE);
            DEBUG("j'ai fini de copier\n");
            first->psuiv = NULL;

            add_birthday_to_index(first);
            DEBUG("apres le add_birthday_to_index\n");

            printf("\nAnniversaire ajoute");
        }

        else
            SET_ERRNO("malloc error in addBirthday");


        DEBUG("hello");
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
            printf("%s %s est ne le %d/%d/%d et a %d an%c \n",temp->prenom,
                                                              temp->nom,
                                                              temp->birthdate.day,
                                                              temp->birthdate.month,
                                                              temp->birthdate.year,
                                                              get_age(temp),
                                                              get_age(temp) > 1 ? 's' : ' ');

            temp = temp->psuiv;
        }
    }

    else
        SET_ERRNO("no birthdays to print\n");

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

    printf("%s %s est ne le %d/%d/%d et a %d an%c \n",temp->prenom,
                                                      temp->nom,
                                                      temp->birthdate.day,
                                                      temp->birthdate.month,
                                                      temp->birthdate.year,
                                                      get_age(temp),
                                                      get_age(temp) > 1 ? 's' : ' ');
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
        SET_ERRNO("no birthdays to delete\n");

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

                fread(&(temp->birthdate.day), sizeof(int), 1, file);
                fread(&(temp->birthdate.month), sizeof(int), 1, file);
                fread(&(temp->birthdate.year), sizeof(int), 1, file);

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

                fwrite(&(temp->birthdate.day), sizeof(int), 1, file);
                fwrite(&(temp->birthdate.month), sizeof(int), 1, file);
                fwrite(&(temp->birthdate.year), sizeof(int), 1, file);

                temp = temp->psuiv;

                i++;
            }

            fclose(file);
        }
    }

    else
        SET_ERRNO("no birthdays to save\n");

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

  	age = local->tm_year - person->birthdate.year ;

  	if( local->tm_mon < person->birthdate.month )
  	    age--;

  	else
  	{
  	    if( local->tm_year == person->birthdate.month )
  	        if( local->tm_mday < person->birthdate.day )
  	            age--;
  	}

  	return age;

} /* int tAge(const PERSON* person) */

/******************************************************************************/
PERSON*
get_birthday(const int rank)
{
    /*
        Input:
        Core:
        Output:
    */

    PERSON* ret = NULL;

    if( !is_empty_birthday_list() )
    {
        PERSON* temp = first;

        int i = 1;

        while( i<rank )
        {
            temp = temp->psuiv;
            i++;
        }

        ret = temp;
    }

    else
        SET_ERRNO("There isn't any birthday to get");

    return ret;

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
        PERSON* nextBirthday = get_birthday(1);
        int age = get_age(nextBirthday);
        age++;

        printf("%s %s est ne le %d/%d/%d et aura %d an(s) dans %d jours\n",nextBirthday->prenom,
                                                                           nextBirthday->nom,
                                                                           nextBirthday->birthdate.day,
                                                                           nextBirthday->birthdate.month,
                                                                           nextBirthday->birthdate.year,
                                                                           age,
                                                                           get_days_before_birthday(nextBirthday));
    }

    else
        SET_ERRNO("there is not any birthday in memory\n");

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

    MY_DATE today = get_date();
    int nbJours = 0;
    int i = 0;
    int diffMois = 0;

    set_days_bissextile();

    if( today.month > birthday->birthdate.month || ( today.month == birthday->birthdate.month && today.day > birthday->birthdate.day ) )
    {
        diffMois = ((birthday->birthdate.month)+12) - today.month;
    }

    else if( today.month < birthday->birthdate.month )
    {
        diffMois = birthday->birthdate.month - today.month;
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
        nbJours += (birthday->birthdate.day - 1);
    }

    else if( diffMois == 0 )
    {
        nbJours += (birthday->birthdate.day - today.day);
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
        BOOL found = FALSE;
        PERSON *input;

        set_birthday(input);

        PERSON* temp = first;

        set_template("birthday");
        create_stack(nbCurBirthdays);

        do
        {
            if( is_birthday_equal(temp, &input) )
                found = TRUE;

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
        SET_ERRNO("There is not any birthday in memory");

} /* PERSON* deleteBirthday(void) */

/******************************************************************************/
static
void
remove_birthday_from_index(const PERSON* birthday)
{
    /*
        Input:
        Core:
        Output:
    */

    if( is_birthday_equal(birthday, indexBirthday[birthday->birthdate.month]) )
        indexBirthday[birthday->birthdate.month] = NULL;

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

    return TRUE == ( b1->birthdate.day == b2->birthdate.day
                     && b1->birthdate.month == b2->birthdate.month
                     && b1->birthdate.year == b2->birthdate.year
                     && strcmp(b1->nom, b2->nom) == 0
                     && strcmp(b1->prenom, b2->prenom) == 0 );

} /*BOOL isBirthdayEqual(const PERSON* b1, const PERSON* b2) */

/******************************************************************************/
PERSON*
check_if_birthday_soon(void)
{
    /*
        Input:
        Core:
        Output:
    */

    if( !is_empty_birthday_list() )
    {
        MY_DATE today = get_date();
        PERSON *nextBirthdayEvent;

        if( !checkForSoonBirthdayToday && today.day != lastDayCheckForSoonBirthdays )
        {
            PERSON* nextBirthday = get_birthday(1);

            int nbJours = get_days_before_birthday(nextBirthday);

            if( nbJours <= 7 )
            {
                // TO COMPLETE
            }

            checkForSoonBirthdayToday = TRUE;
            lastDayCheckForSoonBirthdays = today.day;
        }

        else if( checkForSoonBirthdayToday && today.day != lastDayCheckForSoonBirthdays )
            checkForSoonBirthdayToday = FALSE;

        return nextBirthdayEvent;
    }

    else
        SET_ERRNO("there is no birthday to check for");

} /* PERSON* checkIfBirthdaySoon(void) */

/******************************************************************************/
static
void
copy_birthday(PERSON* dest, const PERSON* src, const BOOL copyNextFlag)
{
    /*
        Input:
        Core:
        Output:
    */

    strcpy(dest->prenom, src->prenom);
    strcpy(dest->nom, src->nom);
    dest->birthdate.day = src->birthdate.day;
    dest->birthdate.month = src->birthdate.month;
    dest->birthdate.year = src->birthdate.year;

    if( copyNextFlag )
        dest->psuiv = src->psuiv;

} /*  static void copy_birthday(PERSON* dest, const PERSON* src, const BOOL copyNextFlag) */
