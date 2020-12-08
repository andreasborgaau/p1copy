#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <termios.h>

#define ASCII_one 49
#define ASCII_two 50
#define ASCII_three 51
#define ASCII_four 52
#define ASCII_five 53
#define ASCII_six 54
#define ASCII_seven 55


static struct termios old, current;

/* Function prototype declaration */
int mainMenu(void);
int modelMenu(void);
int finishMenu(void);
void manual(void);
void newProcess(int*);
void initTermios(void);
void resetTermios(void);
char getch(void); 

int main(void) {
    mainMenu();
    return EXIT_SUCCESS;
}

int mainMenu(void) {
    int mainSelector=0;
    /* Menu selector */

    do{
        system("clear");
        printf("1. Model system \n"
               "2. Manual\n"
               "3. Luk program\n");

        mainSelector = getch();

        
        }while(mainSelector < ASCII_one || mainSelector > ASCII_three);

    /* mainMenu switch case */
    switch(mainSelector) {
        case ASCII_one:
            /* Model system */
            modelMenu();
            break;
        case ASCII_two:
            /* Manual */
            system("clear");
            manual();
            printf("\n\n1. Return to Main Menu\n");
            
            mainSelector = getch();

            if(mainSelector == ASCII_one)
                return mainMenu();
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

int modelMenu() {
    int modelSelector = 0;
    int amount_of_processes = 0, hej;

     do{
        system("clear");
        printf("1. New process\n");
        printf("2. Delete process\n");
        printf("3. Finish model\n");
        printf("4. Go back\n");
        printf("5. Quit program\n");

        modelSelector = getch();
        

        }while(modelSelector < ASCII_one || modelSelector > ASCII_five);

    /* modelMenu switch case */
    switch(modelSelector) {
        case ASCII_one:
            /* New process */
            system("clear");
            newProcess(&amount_of_processes);

            scanf(" %d", &modelSelector); /* Få getch() til at virke her. */
            printf("modelselector = %d", modelSelector);

            if(modelSelector == 1)
                    return modelMenu();
            break;
        case ASCII_two:
            /* Delete process */
            printf("Amount of processes = %d", amount_of_processes);
            break;
        case ASCII_three:
            /* Finish model */
            finishMenu();
            break;
        case ASCII_four:
            /* Back to mainMenu */
            return mainMenu();
            break;
        case ASCII_five:
            /* Quit */
            system("clear");
            printf("The program has shut down.\n");
            exit(EXIT_SUCCESS);
            break;
    }
    
    return EXIT_SUCCESS;
}

int finishMenu(void) {
    int finishSelector;

        do{
            system("clear");
            printf("You have chosen to finish model.\n\n");

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
            /* Go back to model system */
            return modelMenu();
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