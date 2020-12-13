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
               "2. Manual\n\n"
               "9. Quit program\n");

        main_selector = getch();
    }while(main_selector != ASCII_one && main_selector != ASCII_two && main_selector != ASCII_nine);

    switch(main_selector){
        /*Model system*/
        case ASCII_one:
            modelMenu(amount_of_processes);
            break;
        /*Manual*/
        case ASCII_two:
            system("clear");
            manual();
            printf("\n\n1. Return to Main Menu");
            do{
                main_selector = getch();
                if(main_selector == ASCII_one)
                    return mainMenu(amount_of_processes);
            }while(main_selector != ASCII_one);
            break;
        /*Quit*/
        case ASCII_nine:
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
        printf("1. Model manufacturing system\n\n");
        printf("8. Go back\n");
        printf("9. Quit program\n");

        model_selector = getch();
    }while(model_selector != ASCII_one && model_selector != ASCII_eight && model_selector != ASCII_nine);

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
                if(model_selector == ASCII_two)
                    return dataMenu(amount_of_processes);
            }while(model_selector != ASCII_one && model_selector != ASCII_two);
            break;
        /*Go back*/
        case ASCII_eight:
            return mainMenu(amount_of_processes);
            break;
        /*Quit*/
        case ASCII_nine:
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

    for(i = 0; i < *amount_of_processes; i++){
        processes[i].mean_defects = -1;
        processes[i].lambda_defects = -1;
        processes[i].mean_US = -1;
        processes[i].lambda_US = -1;

        system("clear");

        printf(ANSI_UNDERLINED_PRE"Current process: %d / %d"ANSI_UNDERLINED_POST"\n\n", i+1, *amount_of_processes);
        
        printf("Enter planned production time [min]: ");
        scanf(" %lf", &processes[i].planned_production_time);

        printf("Enter ideal cycle time [min]: ");
        scanf(" %lf", &processes[i].ideal_cycle_time);

        printf("\nChoose type of probability distribution for defects:\n"
               "1. Normal distribution\n"
               "2. Exponential distribution\n");
        
        do{
            distribution_selector = getch();
            if(distribution_selector == ASCII_newline)
                distribution_selector = getch();
        }while(distribution_selector != ASCII_one && distribution_selector != ASCII_two);

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

        do{
            distribution_selector = getch();
            if(distribution_selector == ASCII_newline)
                distribution_selector = getch();
        }while(distribution_selector != ASCII_one && distribution_selector != ASCII_two);


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
    int simulation_selector = 0, i;

    do{
        system("clear");
        printf(ANSI_UNDERLINED_PRE"Simulation"ANSI_UNDERLINED_POST"\n\n");
        printf("1. Run simulation\n\n");
        printf("8. Go back\n");
        printf("9. Quit program\n");

        simulation_selector = getch();
    }while(simulation_selector != ASCII_one && simulation_selector != ASCII_eight && simulation_selector != ASCII_nine);

    switch(simulation_selector){
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
        case ASCII_eight:
            return dataMenu(amount_of_processes);
            break;
        /*Quit program*/
        case ASCII_nine:
            quit();
            break;
    }
    return EXIT_SUCCESS;
}


/*This function prints the manual on the screen*/
void manual(void){
    FILE *file_pointer;
    char c; 

    printf(ANSI_UNDERLINED_PRE"Manual"ANSI_UNDERLINED_POST"\n\n");

    /*Open file*/
    file_pointer = fopen("manual.txt", "r"); 
    if(file_pointer == NULL){ 
        printf("Can not open file \n"); 
        exit(EXIT_FAILURE);
    }

    c = fgetc(file_pointer);
    /*Read contents from file*/
    while(c != EOF){ 
        printf ("%c", c);
        c = fgetc(file_pointer);
    }
    fclose(file_pointer); 
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