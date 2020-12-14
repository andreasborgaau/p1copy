#include "constants.h"
#include "model_system.h"
#include "results.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <termios.h>
#include <time.h>

static struct termios old, current;

int mainMenu(void);
int modelMenu(void);
int dataMenu(int);
int simulationMenu(process[], int, int);
void manual(void);
void initTermios(void);
void resetTermios(void);
char getch(void);
int quit(void);

/*Starts the program by initialising the main menu.*/
int main(void){
    mainMenu();

    return EXIT_SUCCESS;
}

/*The main menu, which allows for navigation to either the model menu or manual, or to quit the program.*/
int mainMenu(void){
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
        case ASCII_one:
            modelMenu();
            break;
        case ASCII_two:
            system("clear");
            manual();
            printf("\n\n1. Return to Main Menu");
            do{
                main_selector = getch();
                if(main_selector == ASCII_one)
                    return mainMenu();
            }while(main_selector != ASCII_one);
            break;
        case ASCII_nine:
            quit();
            break;
    }

    return EXIT_SUCCESS;
}

/*The model menu, which allows for modelling of a manufacturing system, going back, or quitting the program.*/
int modelMenu(void){
    int model_selector = 0, amount_of_processes;

    do{
        system("clear");
        printf(ANSI_UNDERLINED_PRE"Model Menu"ANSI_UNDERLINED_POST"\n\n");
        printf("1. Model manufacturing system\n\n");
        printf("8. Go back\n");
        printf("9. Quit program\n");

        model_selector = getch();
    }while(model_selector != ASCII_one && model_selector != ASCII_eight && model_selector != ASCII_nine);

    switch(model_selector){
        case ASCII_one:
            system("clear");
            newProcess(&amount_of_processes);
            do{
                model_selector = getch();
                if(model_selector == ASCII_newline)
                    model_selector = getch();
                if(model_selector == ASCII_one)
                    return modelMenu();
                if(model_selector == ASCII_two)
                    return dataMenu(amount_of_processes);
            }while(model_selector != ASCII_one && model_selector != ASCII_two);
            break;
        case ASCII_eight:
            return mainMenu();
            break;
        case ASCII_nine:
            quit();
            break;
    }

    return EXIT_SUCCESS;
}

/*The data menu, which allows for data input.*/
int dataMenu(int amount_of_processes){
    int i, distribution_selector = 0, total_count;

    process *processes;
    processes = malloc(amount_of_processes * sizeof(process));

    system("clear");

    printf(ANSI_UNDERLINED_PRE"Total amount of processes: %d"ANSI_UNDERLINED_POST"\n\n", amount_of_processes);

    printf("Enter total count: ");
    scanf(" %d", &total_count);

    for(i = 0; i < amount_of_processes; i++){
        processes[i].mean_defects = -1;
        processes[i].lambda_defects = -1;
        processes[i].mean_US = -1;
        processes[i].lambda_US = -1;
        processes[i].index = i;

        system("clear");

        printf(ANSI_UNDERLINED_PRE"Current process: %d / %d"ANSI_UNDERLINED_POST"\n\n", i+1, amount_of_processes);
        
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

    return simulationMenu(processes, amount_of_processes, total_count);
}

/*The simulation menu, which allows for running the simulation, going back, or quitting the program.*/
int simulationMenu(process processes[], int amount_of_processes, int total_count){
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
        case ASCII_one:   
            system("clear");
            simulate(processes, amount_of_processes);
            for(i = 0; i < amount_of_processes; i++)
                printHistogram(processes[i], i);
            printResult(amount_of_processes, processes, total_count);
            printSortedResult(amount_of_processes, processes, total_count);
            printOverallResult(amount_of_processes, processes, total_count);
            free(processes);
            break;           
        case ASCII_eight:
            return dataMenu(amount_of_processes);
            break;
        case ASCII_nine:
            quit();
            break;
    }

    return EXIT_SUCCESS;
}

/*Prints the manual on the screen.*/
void manual(void){
    int amount_of_processes = 1, total_count = 500;
    process manual_processes[1];
    FILE *file_pointer;
    char c;

    printf(ANSI_UNDERLINED_PRE"Manual"ANSI_UNDERLINED_POST"\n\n");

    file_pointer = fopen("manual.txt", "r"); 
    if(file_pointer == NULL){ 
        printf("Can not open file \n"); 
        exit(EXIT_FAILURE);
    }

    c = fgetc(file_pointer);

    while(c != EOF){ 
        printf ("%c", c);
        c = fgetc(file_pointer);
    }
    fclose(file_pointer);

    manual_processes[0].ideal_cycle_time = 0.8; 
    manual_processes[0].index = 1; 
    manual_processes[0].planned_production_time = 700; 
    manual_processes[0].lambda_defects = -1;
    manual_processes[0].lambda_US = -1; 
    manual_processes[0].mean_defects = 70; 
    manual_processes[0].std_deviation_defects = 10; 
    manual_processes[0].mean_US = 80; 
    manual_processes[0].std_deviation_US = 8; 

    simulate(manual_processes, amount_of_processes);

    printHistogram(manual_processes[0], 0);
    printResult(amount_of_processes, manual_processes, total_count);
    printOverallResult(amount_of_processes, manual_processes, total_count);
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

/*Quits the program*/
int quit(void){
    system("clear");
    printf("The program has shut down.\n");
    exit(EXIT_SUCCESS);
}