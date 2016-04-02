/*
    Author: Lionel Jamaigne
    Creation Date: 14/03/2016
    Last Modified: 02/04/2016
    Last Modification:
    Known Issues:
    Version: 1.0
*/

#include "chaudboy.h" // test du script de commit

int
monthToNumber(const char* mois)
{
    /*
        Input:  the address of a day of the week
        Core:   sends back the number relative to the good month passed as a const char*
        Output: the month's number
    */

    int ret = 0;

    if( strcmp("Janvier", mois) == 0 ) // ceci est un commentaire
        ret = 1;

    else if( strcmp("Fevrier", mois) == 0 )
        ret = 2;

     else if( strcmp("Mars", mois) == 0 )
        ret = 3;

    else if( strcmp("Avril", mois) == 0 )
        ret = 4;

    else if( strcmp("Mai", mois) == 0 )
        ret = 5;

    else if( strcmp("Juin", mois) == 0 )
        ret = 6;

    else if( strcmp("Juillet", mois) == 0 )
        ret = 7;

    else if( strcmp("Aout", mois) == 0 )
        ret = 8;

    else if( strcmp("Septembre", mois) == 0 )
        ret = 9;

    else if( strcmp("Octobre", mois) == 0 )
        ret = 10;

    else if( strcmp("Novembre", mois) == 0 )
        ret = 11;

    else if( strcmp("Decembre", mois) == 0 )
        ret = 12;

    return ret;
}

bool
checkIntBondaries(const int number, const int min, const int max)
{
    bool ret;

    if( number < min || number > max )
        ret = false;

    else
        ret = true;

    return ret;
}

int
getCurrentYear(void)
{
    time_t now = time(0);
	struct tm* local = localtime(&now);

	local->tm_year += 1900;

	return local->tm_year;
}

void
printCharValue(const char* string)
{
    for(int i=0;i<strlen(string);i++)
    {
        printf("%d %c ", string[i], string[i]);
    }

    //printf("\n");
}

void
cleanString(char* temp)
{
    /*
        Input:  the address of the string from wich to remove the "new line" character
        Core:   removes the "new line" character
        Output: none
    */

    if( temp[strlen(temp)-1] = '\n' )
        temp[strlen(temp)-1] = '\0';
}

void
pressKeyToContinue(void)
{
    /*
        Input:
        Core:
        Output:
    */

    printf("Press a key to continue ..");
    int temp = getchar();
}

void
pressEnterToContinue(void)
{
    /*
        Input:
        Core:
        Output:
    */

    printf("Press enter to continue ..");
    int temp = getchar();

    while( (temp = getchar()) != '\n' );
}

void
printAllANSIColors(void)
{
    /*
        Input:
        Core:
        Output:
    */

    printf(ANSI_COLOR_OPPOSITE);
    printf(ANSI_COLOR_RED "RED\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "GREEN\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "YELLOW\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_BLUE "BLUE\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA "MAGENTA\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "CYAN\n");
    printf(ANSI_COLOR_UNDERLINED "UNDERLINED\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN ANSI_COLOR_BACKGROUND "BACKGROUND\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREY "GREY" ANSI_COLOR_RESET);
}

void
clearScreen(void)
{
    /*
        Input:
        Core:
        Output:
    */

    #if defined(unix) || defined(__unix__) || defined(__APPLE__) || defined(__linux__)
        printf("\033[H\033[J");

    #elif defined(_WIN32) || defined(_WIN64)
        HANDLE                     hStdOut;
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        DWORD                      count;
        DWORD                      cellCount;
        COORD                      homeCoords = { 0, 0 };

        hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );

        if (hStdOut == INVALID_HANDLE_VALUE)
            return;

        /* Get the number of cells in the current buffer */
        if (!GetConsoleScreenBufferInfo( hStdOut, &csbi ))
            return;

        cellCount = csbi.dwSize.X *csbi.dwSize.Y;

        /* Fill the entire buffer with spaces */
        if (!FillConsoleOutputCharacter(hStdOut, (TCHAR) ' ', cellCount, homeCoords, &count))
            return;

        /* Fill the entire buffer with the current colors and attributes */
        if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count))
            return;

        /* Move the cursor home */
        SetConsoleCursorPosition( hStdOut, homeCoords );

    #endif
}

/* Test pour unix like systems & peut etre linux
void
clearScreen(void)
{
    /*
        Input:
        Core:
        Output:
    */

    if(!cur_term)
    {
        int result;
        setupterm(NULL, STDOUT_FILENO, &result);

        if(result<=0)
            return;
    }

    putp(tigetstr("clear")); // putp communique avec le terminal & tigetstr recoit la bonne séquence d'échappement à envoyer

}


*/
