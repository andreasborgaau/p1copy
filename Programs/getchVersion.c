#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <termios.h>
#include <time.h>

#define ASCII_newline 10
#define ASCII_one 49
#define ASCII_two 50
#define ASCII_three 51
#define ASCII_four 52
#define ASCII_five 53
#define ASCII_six 54
#define ASCII_seven 55

#define ANSI_UNDERLINED_PRE  "\033[4m"
#define ANSI_UNDERLINED_POST "\033[0m"


static struct termios old, current;

/* Function prototype declaration */
int mainMenu(int*);
int modelMenu(int*);
int finishMenu(int*);
void manual(void);
void newProcess(int*);
void initTermios(void);
void resetTermios(void);
char getch(void); 

int main(void) {
    int amount_of_processes = 0;

    mainMenu(&amount_of_processes);
    return EXIT_SUCCESS;
}

int mainMenu(int *amount_of_processes) {
    int mainSelector=0;
    /* Menu selector */

    do{
        system("clear");
        printf(ANSI_UNDERLINED_PRE "Main Menu" ANSI_UNDERLINED_POST "\n\n");
        printf("1. Model system \n"
               "2. Manual\n"
               "3. Quit program\n");

        mainSelector = getch();

        
        }while(mainSelector < ASCII_one || mainSelector > ASCII_three);

    /* mainMenu switch case */
    switch(mainSelector) {
        case ASCII_one:
            /* Model system */
            modelMenu(amount_of_processes);
            break;
        case ASCII_two:
            /* Manual */
            system("clear");
            manual();
            printf("\n1. Return to Main Menu");
            
            do{
                mainSelector = getch();
                if(mainSelector == ASCII_one)
                    return mainMenu(amount_of_processes);
            } while (mainSelector != ASCII_one);
            break;
        case ASCII_three:
            /* Quit */
            system("clear");
            printf("The program has shut down.\n");
            exit(EXIT_SUCCESS);
            break;
    }
    return EXIT_SUCCESS;
}

int modelMenu(int *amount_of_processes) {
    int modelSelector = 0;

     do{
        system("clear");
        printf(ANSI_UNDERLINED_PRE "Model Menu" ANSI_UNDERLINED_POST "\n\n");
        printf("1. Model manufacturing system\n");
        printf("2. Finish model\n");
        printf("3. Go back\n");
        printf("4. Quit program\n");

        modelSelector = getch();
        

        }while(modelSelector < ASCII_one || modelSelector > ASCII_four);

    /* modelMenu switch case */
    switch(modelSelector) {
        case ASCII_one:
            /* New process */
            system("clear");
            newProcess(amount_of_processes);
            
            do{
                modelSelector = getch();
                if(modelSelector == ASCII_newline)
                    modelSelector = getch();
                if(modelSelector == ASCII_one)
                    return modelMenu(amount_of_processes);
            } while(modelSelector != ASCII_one);
            break;
        case ASCII_two:
            /* Finish model */
            finishMenu(amount_of_processes);
            break;
        case ASCII_three:
            /* Go back */
            return mainMenu(amount_of_processes);
            break;
        case ASCII_four:
            /* Quit */
            system("clear");
            printf("The program has shut down.\n");
            exit(EXIT_SUCCESS);
            break;
    }
    
    return EXIT_SUCCESS;
}

int finishMenu(int *amount_of_processes) {
    int finishSelector;

        do{
            system("clear");
            printf(ANSI_UNDERLINED_PRE "Finish Menu" ANSI_UNDERLINED_POST "\n\n");
            printf("amount of processes: %d\n", *amount_of_processes);
            printf("1. Total count\n");
            printf("2. Ideal cycle time\n");
            printf("3. Data for defect products\n");
            printf("4. Data for unplanned stop\n");
            printf("5. Run simulation\n");
            printf("6. Go back\n");
            printf("7. Quit program\n");

            finishSelector = getch();

            }while(finishSelector < ASCII_one || finishSelector > ASCII_seven);
    /* finish model switch case */
    switch(finishSelector) {
        case ASCII_one:
            /* Total count */

            break;
        case ASCII_two:
            /* Ideal cycle time */
            break;
        case ASCII_three:
            /* Defect products */
            break;
        case ASCII_four:
            /* Unplanned stop */
            break;
        case ASCII_five:
            /* Run simulation */
            break;
        case ASCII_six:
            /* Go back */
            return modelMenu(amount_of_processes);
            break;
        case ASCII_seven:
            /* Quit */
            system("clear");
            printf("The program has shut down.\n");
            exit(EXIT_SUCCESS);
            break;
    }

    return EXIT_SUCCESS;
}

/* This function prints the manual on the screen. */
void manual(void) {
    FILE *filePointer;
    char c; 
  
    /* Open file */
    filePointer = fopen("Manual", "r"); 
    if (filePointer == NULL) { 
        printf("Can not open file \n"); 
        exit(EXIT_FAILURE);
    } 
  
    c = fgetc(filePointer);
    /* Read contents from file */
    while (c != EOF) { 
        printf ("%c", c);
        c = fgetc(filePointer);
    } 

    fclose(filePointer); 
}

void newProcess(int *amount_of_processes)
{
    int i;

    printf("Enter the amount of processes: ");
    scanf(" %d", amount_of_processes);
    printf("\n");

    for(i = 1; i <= *amount_of_processes; i++)
    {
    printf("* * * * *\n");
    printf("*       *\n");
    printf("*%4d   *\n", i);
    printf("*       *\n");
    printf("* * * * *\n");

    if(i != *amount_of_processes)
        printf("    |\n");
    }

    printf("1. Return to model menu\n");

}

void initTermios(void) 
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  current = old; /* make new settings same as old settings */
  current.c_lflag &= ~ICANON; /* disable buffered i/o */
  tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch(void) 
{
  char ch;
  initTermios();
  ch = getchar();
  resetTermios();
  return ch;
}
