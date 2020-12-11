#include "constants.h"
#include "model_system.h"
#include "calculate_functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <termios.h>
#include <time.h>



int mainMenu(int*);
int modelMenu(int*);
int finishMenu(int*);
void manual(void);
void initTermios(void);
void resetTermios(void);
char getch(void);

int main(void){
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
    } while(modelSelector < ASCII_one || modelSelector > ASCII_four);

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

int finishMenu (int *amount_of_processes){
    int i, distribution_selector = 0;

    process *processes;
    processes = malloc(*amount_of_processes * sizeof(int));

    printf("Total amount of processes: %d\n", *amount_of_processes);

    for(i = 0; i < *amount_of_processes; i++) {
        processes[i].mean_defects = -1;
        processes[i].lambda_defects = -1;
        processes[i].mean_US = -1;
        processes[i].lambda_US = -1;

        system("clear");

        printf("Current process: %d \n\n", i+1);

        printf("Enter total count: ");
        scanf(" %d", &processes[i].total_count);

        printf("Enter ideal cycle time: ");
        scanf(" %d", &processes[i].ideal_cycle_time);

        printf("\nChoose type of probability distribution for defects:\n"
               "1. Normal distribution\n"
               "2. Exponential distribution\n");

        distribution_selector = getch();
        if(distribution_selector == ASCII_newline)
            distribution_selector = getch();

        if(distribution_selector == ASCII_one){
            printf("\n\nEnter mean value: ");
            scanf(" %lf", &processes[i].mean_defects);

            printf("Enter standard deviation: ");
            scanf(" %lf", &processes[i].std_deviation_defects);
        }

        if(distribution_selector == ASCII_two){
            printf("Enter Lambda value: ");
            scanf(" %lf", &processes[i].lambda_defects);
        }

        printf("\nChoose type of probability distribution for unplanned stops:\n"
               "1. Normal distribution\n"
               "2. Exponential distribution\n");

        distribution_selector = getch();
        if(distribution_selector == ASCII_newline)
            distribution_selector = getch();


        if(distribution_selector == ASCII_one){
            printf("\nEnter mean value: ");
            scanf(" %lf", &processes[i].mean_US);

            printf("Enter standard deviation: ");
            scanf(" %lf", &processes[i].std_deviation_US);
        }

        if(distribution_selector == ASCII_two){
            printf("\nEnter Lambda value: ");
            scanf(" %lf", &processes[i].lambda_US);
        }
    }
    return EXIT_SUCCESS;
}
 

/*int finishMenu(int *amount_of_processes) {
    int finishSelector, *total_count, *ideal_cycle_time;

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
    } while(finishSelector < ASCII_one || finishSelector > ASCII_seven);

    switch(finishSelector) {
        case ASCII_one:
           
            system("clear");
            printf("Enter the total count: ");
            scanf(" %d", total_count);
            
            break;
        case ASCII_two:
  
            system("clear");
            printf("Enter ideal cycle time: ");
            scanf(" %d", ideal_cycle_time);

            break;
        case ASCII_three:
            
            system("clear");
            printf("");
            break;
        case ASCII_four:
            
            break;
        case ASCII_five:
            
            break;
        case ASCII_six:
           
            return modelMenu(amount_of_processes);
            break;
        case ASCII_seven:
            
            system("clear");
            printf("The program has shut down.\n");
            exit(EXIT_SUCCESS);
            break;
    }
    return EXIT_SUCCESS;
}*/

/* This function prints the manual on the screen. */
void manual(void) {
    FILE *filePointer;
    char c; 

    printf(ANSI_UNDERLINED_PRE "Manual" ANSI_UNDERLINED_POST "\n\n");

    /* Open file */
    filePointer = fopen("manual.txt", "r"); 
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

void initTermios(void) {
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  current = old; /* make new settings same as old settings */
  current.c_lflag &= ~ICANON; /* disable buffered i/o */
  tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) {
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch(void) {
  char ch;
  initTermios();
  ch = getchar();
  resetTermios();
  return ch;
}