#include "constants.h"
#include "model_system.h"
#include "results.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <termios.h>
#include <time.h>

static struct termios old, current;

int mainMenu(int*);
int modelMenu(int*);
int dataMenu(int*);
int simulationMenu(process[], int*, manufacturing_system);
void manual(void);
void initTermios(void);
void resetTermios(void);
char getch(void);
int quit(void);

int main(void){
    int amount_of_processes = 0;

    mainMenu(&amount_of_processes);

    return EXIT_SUCCESS;
}

int mainMenu(int *amount_of_processes){
    int main_selector=0;

    do{
        system("clear");
        printf(ANSI_UNDERLINED_PRE"Main Menu"ANSI_UNDERLINED_POST"\n\n");
        printf("1. Model system \n"
               "2. Manual\n"
               "3. Quit program\n");

        main_selector = getch();
    }while(main_selector < ASCII_one || main_selector > ASCII_three);

    switch(main_selector){
        /*Model system*/
        case ASCII_one:
            modelMenu(amount_of_processes);
            break;
        /*Manual*/
        case ASCII_two:
            system("clear");
            manual();
            printf("\n1. Return to Main Menu");
            do{
                main_selector = getch();
                if(main_selector == ASCII_one)
                    return mainMenu(amount_of_processes);
            }while(main_selector != ASCII_one);
            break;
        /*Quit*/
        case ASCII_three:
            quit();
            break;
    }
    return EXIT_SUCCESS;
}

int modelMenu(int *amount_of_processes){
    int model_selector = 0;

    do{
        system("clear");
        printf(ANSI_UNDERLINED_PRE"Model Menu"ANSI_UNDERLINED_POST"\n\n");
        printf("1. Model manufacturing system\n");
        printf("2. Finish model\n");
        printf("3. Go back\n");
        printf("4. Quit program\n");

        model_selector = getch();
    }while(model_selector < ASCII_one || model_selector > ASCII_four);

    switch(model_selector){
        /*New process*/
        case ASCII_one:
            system("clear");
            newProcess(amount_of_processes);
            do{
                model_selector = getch();
                if(model_selector == ASCII_newline)
                    model_selector = getch();
                if(model_selector == ASCII_one)
                    return modelMenu(amount_of_processes);
            }while(model_selector != ASCII_one);
            break;
        /*Finish model*/
        case ASCII_two:
            dataMenu(amount_of_processes);
            break;
        /*Go back*/
        case ASCII_three:
            return mainMenu(amount_of_processes);
            break;
        /*Quit*/
        case ASCII_four:
            quit();
            break;
    }
    return EXIT_SUCCESS;
}

int dataMenu (int *amount_of_processes){
    int i, distribution_selector = 0;

    manufacturing_system manu_system;

    process *processes;
    processes = malloc(*amount_of_processes * sizeof(process));

    system("clear");

    printf(ANSI_UNDERLINED_PRE"Total amount of processes: %d"ANSI_UNDERLINED_POST"\n\n", *amount_of_processes);

    printf("Enter total count: ");
    scanf(" %d", &manu_system.total_count);

    printf("Enter planned production time in minutes: ");
    scanf(" %d", &manu_system.planned_production_time);

    for(i = 0; i < *amount_of_processes; i++){
        processes[i].mean_defects = -1;
        processes[i].lambda_defects = -1;
        processes[i].mean_US = -1;
        processes[i].lambda_US = -1;

        system("clear");

        printf(ANSI_UNDERLINED_PRE"Current process: %d / %d"ANSI_UNDERLINED_POST"\n\n", i+1, *amount_of_processes);

        printf("Enter ideal cycle time in minutes: ");
        scanf(" %lf", &processes[i].ideal_cycle_time);

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
            printf("\n\nEnter Lambda value: ");
            scanf(" %lf", &processes[i].lambda_defects);
        }

        printf("\nChoose type of probability distribution for unplanned stops:\n"
               "1. Normal distribution\n"
               "2. Exponential distribution\n");

        distribution_selector = getch();
        if(distribution_selector == ASCII_newline)
            distribution_selector = getch();

        if(distribution_selector == ASCII_one){
            printf("\n\nEnter mean value: ");
            scanf(" %lf", &processes[i].mean_US);

            printf("Enter standard deviation: ");
            scanf(" %lf", &processes[i].std_deviation_US);
        }

        if(distribution_selector == ASCII_two){
            printf("\n\nEnter Lambda value: ");
            scanf(" %lf", &processes[i].lambda_US);
        }
    }
    return simulationMenu(processes, amount_of_processes, manu_system);
}

int simulationMenu(process processes[], int *amount_of_processes, manufacturing_system manu_system){
    int simulationSelector = 0, i;

    do{
        system("clear");
        printf(ANSI_UNDERLINED_PRE"Simulation"ANSI_UNDERLINED_POST"\n\n");
        printf("1. Run simulation\n");
        printf("2. Go back\n");
        printf("3. Quit program\n");

        simulationSelector = getch();
    }while(simulationSelector < ASCII_one || simulationSelector > ASCII_three);

    switch(simulationSelector){
        /*Run simulation*/
        case ASCII_one:   
            system("clear");
            simulate(processes, amount_of_processes);
            for(i = 0; i < *amount_of_processes; i++)
                printHistogram(processes[i], i);
            printResult2(*amount_of_processes, processes, manu_system);
            printResult3(*amount_of_processes, processes, manu_system);
            free(processes);
            break;
        /*Go back*/            
        case ASCII_two:
            return dataMenu(amount_of_processes);
            break;
        /*Quit program*/
        case ASCII_three:
            quit();
            break;
    }
    return EXIT_SUCCESS;
}


/*This function prints the manual on the screen*/
void manual(void){
    FILE *filePointer;
    char c; 

    printf(ANSI_UNDERLINED_PRE"Manual"ANSI_UNDERLINED_POST"\n\n");

    /*Open file*/
    filePointer = fopen("manual.txt", "r"); 
    if(filePointer == NULL){ 
        printf("Can not open file \n"); 
        exit(EXIT_FAILURE);
    }

    c = fgetc(filePointer);
    /*Read contents from file*/
    while(c != EOF){ 
        printf ("%c", c);
        c = fgetc(filePointer);
    }
    fclose(filePointer); 
}

void initTermios(void){
  tcgetattr(0, &old); /*Grab old terminal i/o settings*/
  current = old; /*Make new settings same as old settings*/
  current.c_lflag &= ~ICANON; /*Disable buffered i/o*/
  tcsetattr(0, TCSANOW, &current); /*Use these new terminal i/o settings now*/
}

/*Restore old terminal i/o settings*/
void resetTermios(void){
  tcsetattr(0, TCSANOW, &old);
}

/*Read 1 character - echo defines echo mode*/
char getch(void){
  char ch;
  initTermios();
  ch = getchar();
  resetTermios();
  return ch;
}

/*This function quits the program*/
int quit(void){
    system("clear");
    printf("The program has shut down.\n");
    exit(EXIT_SUCCESS);
}