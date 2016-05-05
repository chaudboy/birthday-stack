/*
    Author: Lionel Jamaigne
    Creation Date: 14/03/2016
    Last Modified: 04/05/2016
    Last Modification:
    Known Issues:
    Version: 1.0
*/

#include "chaudboy.h"

BOOL
check_int_bondaries(const int number, const int min, const int max)
{
    /*
        Input:
        Core:
        Output:
    */

    BOOL ret;

    if( number < min || number > max )
        ret = FALSE;

    else
        ret = TRUE;

    return ret;

} /* BOOL checkIntBondaries(const int number, const int min, const int max) */

/******************************************************************************/
void
print_char_value(const char* string)
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

} /* void printCharValue(const char* string) */

/******************************************************************************/
void
clean_string(char* temp)
{
    /*
        Input:  the address of the string from wich to remove the "new line" character
        Core:   removes the "new line" character
        Output: none
    */

    if( temp[strlen(temp)-1] = '\n' )
        temp[strlen(temp)-1] = '\0';

} /* void cleanString(char* temp) */

/******************************************************************************/
void
clear_string(char* temp)
{
    /*
        Input:
        Core:
        Output:
    */

    strcpy(temp, "\0");

} /* void clear_string(char* temp) */

/******************************************************************************/
void
press_key_to_continue(void)
{
    /*
        Input:
        Core:
        Output:
    */

    //struct  termios argin, argout;
    unsigned char   ch = 0;

    printf("Press a key to continue ..");

    /*
    tcgetattr(0,&argin);
    argout = argin;
    argout.c_lflag &= ~(ICANON);
    argout.c_iflag &= ~(ICRNL);
    argout.c_oflag &= ~(OPOST);
    argout.c_cc[VMIN] = 1;
    argout.c_cc[VTIME] = 0;
    tcsetattr(0,TCSADRAIN,&argout);
    read(0, &ch, 1);
    tcsetattr(0,TCSADRAIN,&argin);*/

} /* void pressKeyToContinue(void) */

/******************************************************************************/
void
press_enter_to_continue(void)
{
    /*
        Input:
        Core:
        Output:
    */

    int temp = 0;

    printf("\nPress enter to continue ..");

    while( (temp = getchar()) != '\n' );

} /* void pressEnterToContinue(void) */

/******************************************************************************/
void
print_all_ansi_colors(void)
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

} /* void printAllANSIColors(void) */

/******************************************************************************/
void
clear_screen(void)
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

} /* void clearScreen(void) */

/******************************************************************************/
void
set_input_string(const char* message, char* string, const int maxChar)
{
    /*
        Input:
        Core:
        Output:
    */

    printf("%s", message);

    fgets(string, maxChar+2, stdin);
    clean_string(string);

} /* void setInputString(const char* message, char* string, const int maxChar) */

/******************************************************************************/
void
set_input_number(const char* message, int* number, const int maxChar, const int min, const int max)
{
    /*
        Input:
        Core:
        Output:
    */

    int flag = FALSE;
    char temp[30] = "";

    do
    {
        printf("%s", message);

        fgets(temp, maxChar+2, stdin);

        if( check_int_bondaries(atoi(temp), min, max) == FALSE )
            flag = TRUE;

        else
            *number = atoi(temp);

    }while( flag == TRUE );

    clean_string(temp);

} /* void setInputNumber(const char* message, int* number, const int maxChar, const int min, const int max) */

/******************************************************************************/
void
set_input_password(const char* message, char* string, const int maxChar, const char charToDisplay)
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
        retour = getch_unix();
        input[i] = retour;
        printf("%c", charToDisplay);

        i++;
    }

    clean_string(input);
    strcpy(string, input);

} /* void setInputPassword(const char* message, char* string, const int maxChar, const char charToDisplay) */

/******************************************************************************/
void
print_all_ascii_chars(void)
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

} /* void printAllASCIIChars(void) */

/******************************************************************************/
void
load_login(const char* fileName)
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

    set_input_string("\n\tLogin: ", login, 8);
    set_input_password("\n\tPassword: ", password, 8, '*');

    FILE* usersFile = NULL;

    if( usersFile = fopen(fileName, "rb") )
    {
        rewind(usersFile);

        fread(loginFile, sizeof(char)*10, 1, usersFile);
        fread(passwordFile, sizeof(char)*10, 1, usersFile);

        if( strcmp(loginFile, login) != 0 && strcmp(loginFile, password) != 0 )
        {
            SET_ERRNO("wrong login or password");
        }

        else
            clear_screen();
    }

} /* void loadLogin(const char* fileName) */

/******************************************************************************/
void
create_users_file(const char* fileName)
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

} /* void createUsersFile(const char* fileName) */

/******************************************************************************/
char
getch_unix(void)
{
    /*
        Input:
        Core:
        Output:
    */

    /*char buf=0;
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

    return buf;*/

} /* char getchUnix(void) */
