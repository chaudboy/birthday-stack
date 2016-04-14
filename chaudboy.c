/*
    Author: Lionel Jamaigne
    Creation Date: 14/03/2016
    Last Modified: 13/04/2016
    Last Modification:
    Known Issues:
    Version: 1.0
*/

hahapd
fgh
fg
hfg
hfg
h
fgh
h
f
gh
gfh
f
h
fg
hfg
h
fgh
fg
hgf
h
gfh
fg
hfg


#include "chaudboy.h"

bool
checkIntBondaries(const int number, const int min, const int max)
{
    /*
        Input:
        Core:
        Output:
    */

    bool ret;

    if( number < min || number > max )
        ret = false;

    else
        ret = true;

    return ret;g
}

void
printCharValue(const char* string)
{
    /*
        Input:
        Core:
        Output:
    */

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

    int temp = 0;

    printf("\nPress enter to continue ..");

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
        #include <windows.h>
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

void
setInputString(const char* message, char* string, const int maxChar)
{
    /*
        Input:
        Core:
        Output:
    */

    printf("%s", message);

    fgets(string, maxChar+2, stdin);
    cleanString(string);
}

void
setInputNumber(const char* message, int* number, const int maxChar, const int min, const int max)
{
    /*
        Input:
        Core:
        Output:
    */

    int flag = false;
    char temp[30] = "";

    do
    {
        printf("%s", message);

        fgets(temp, maxChar+2, stdin);

        if( checkIntBondaries(atoi(temp), min, max) == false )
            flag = true;

        else
            *number = atoi(temp);

    }while( flag == true );

    cleanString(temp);
}

void
setInputPassword(const char* message, char* string, const int maxChar, const char charToDisplay)
{
    /*
        Input:
        Core:
        Output:
    */

    char input[20] = "";
    char retour = 0;
    int i = 0;

    printf("%s", message);

    while( retour != '\n' && i < maxChar && i < 18 )
    {
        retour = getchUnix();
        input[i] = retour;
        printf("%c", charToDisplay);

        i++;
    }

    cleanString(input);
    strcpy(string, input);
}

void
printAllASCIIChars(void)
{
    /*
        Input:
        Core:
        Output:
    */

    for(int i=0 ; i<= 255 ; i++)
    {
        printf("Dec %d - Hexa %x - Char %c\n", i, i, i);
    }
}

void
loadLogin(const char* fileName)
{
    /*
        Input:
        Core:
        Output:
    */

    char login[10] = "";
    char password[10] = "";

    char loginFile[10] = "";
    char passwordFile[10] = "";

    setInputString("\n\tLogin: ", login, 8);
    setInputPassword("\n\tPassword: ", password, 8, '*');

    FILE* usersFile = NULL;

    if( usersFile = fopen(fileName, "rb") )
    {
        rewind(usersFile);

        fread(loginFile, sizeof(char)*10, 1, usersFile);
        fread(passwordFile, sizeof(char)*10, 1, usersFile);

        if( strcmp(loginFile, login) != 0 && strcmp(loginFile, password) != 0 )
        {
            MYERROR("wrong login or password");
        }

        else
            clearScreen();
    }
}

void
createUsersFile(const char* fileName)
{
    /*
        Input:
        Core:
        Output:
    */

    char login[10] = "root";
    char password[10] = "root";

    FILE* usersFile = NULL;

    if( usersFile = fopen(fileName, "wb") )
    {
        rewind(usersFile);

        fwrite(login, sizeof(char)*10, 1, usersFile);
        fwrite(password, sizeof(char)*10, 1, usersFile);
    }

    else
        perror("fopen() error in createUsersFile()");

    fclose(usersFile);
}

char
getchUnix(void)
{
    #include <unistd.h>   //_getch*/
    #include <termios.h>  //_getch*/

    char buf=0;
    struct termios old={0};
    fflush(stdout);
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    //printf("%c\n",buf);

    return buf;
}
