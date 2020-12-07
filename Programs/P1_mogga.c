#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_POS_FINISH 7
#define MAX_POS_MODEL 5
#define MAX_POSITION 3
#define MIN_POSITION 1
#define ARROW_DOWN 80
#define ARROW_UP 72
#define ESC_KEY 27
#define ENTER_KEY 13

/* Function prototype declaration */
int mainMenu(void);
int modelMenu(void);
int finishMenu(void);
int readInput(int, int, int, int);
void printArrow(int, int);
void manual(void);
void newProcess(int*);
void deleteProcess();
double calculateRunTime();
double calculateAvailability();
double calculatePerformance();
double calculateQuality();
void calculateOee();

int main(void) {
    mainMenu();
    return EXIT_SUCCESS;
}

/* Funktionsliste */
int mainMenu(void) {
    int mainSelector=0, position=1;
    /* Menu selector */
    while(mainSelector != ENTER_KEY) {
        system("cls");
        printArrow(1, position); printf("Model system\n");
        printArrow(2, position); printf("Manual\n");
        printArrow(3, position); printf("Quit program\n");

        mainSelector = getch();
        position = readInput(mainSelector, position, MIN_POSITION, MAX_POSITION);
    }

    /* mainMenu switch case */
    switch(position) {
        case 1:
            /* Model system */
            modelMenu();
            break;
        case 2:
            /* Manual */
            system("cls");
            manual();
            printf("If you want to return to main menu, then press escape.");
            mainSelector = getch();
            if(mainSelector == ESC_KEY)
                return mainMenu();
            break;
        case 3:
            /* Quit */
            system("cls");
            printf("The program has shut down.\n");
            exit(EXIT_SUCCESS);
            break;
    }
}

int modelMenu(void) {
    int modelSelector, position=MIN_POSITION, count=0, sumCount=0;
    while(modelSelector != ENTER_KEY) {
        system("cls");
        printArrow(1, position); printf("New process\n");
        printArrow(2, position); printf("Delete process\n");
        printArrow(3, position); printf("Finish model\n");
        printArrow(4, position); printf("Go back\n");
        printArrow(5, position); printf("Quit program\n");

        modelSelector = getch();
        position = readInput(modelSelector, position, MIN_POSITION, MAX_POS_MODEL);
    }
    /* modelMenu switch case */
    switch(position) {
        case 1:
            /* New process */
            system("cls");
            do{
                count = 0;
                printf("\n");
                newProcess(&count);
                sumCount += count;
                printf("Amount of circles = %d", sumCount);
            } while(getch() != ESC_KEY);
            return modelMenu();
            break;
        case 2:
            /* Delete process */
            printf("Delete process");
            break;
        case 3:
            /* Finish model */
            finishMenu();
            break;
        case 4:
            /* Back to mainMenu */
            return mainMenu();
            break;
        case 5:
            /* Quit */
            system("cls");
            printf("The program has shut down.\n");
            exit(EXIT_SUCCESS);
            break;
    }
}

int finishMenu(void) {
    int finishSelector, position=1;
    while(finishSelector != ENTER_KEY){
        system("cls");
                                 printf("You have chosen to finish model\n");
        printArrow(1, position); printf("Total count\n");
        printArrow(2, position); printf("Ideal cycle time\n");
        printArrow(3, position); printf("Data for defect products\n");
        printArrow(4, position); printf("Data for unplanned stop\n");
        printArrow(5, position); printf("Run simulation\n");
        printArrow(6, position); printf("Go back\n");
        printArrow(7, position); printf("Quit program\n");

        finishSelector = getch();
        position = readInput(finishSelector, position, MIN_POSITION, MAX_POS_FINISH);
    }
    /* finish model switch case */
    switch(position) {
        case 1:
            /* Total count */
            break;
        case 2:
            /* Ideal cycle time */
            break;
        case 3:
            /* Defect products */
            break;
        case 4:
            /* Unplanned stop */
            break;
        case 5:
            /* Run simulation */
            break;
        case 6:
            /* Go back to model system */
            return modelMenu();
            break;
        case 7:
            /* Quit */
            system("cls");
            printf("The program has shut down.\n");
            exit(EXIT_SUCCESS);
            break;
    }
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

/* This function increments or decrements the position of the arrow in the arrow menu. */
int readInput(int keyPressed, int position, int minPosition, int maxPosition) {
    if(keyPressed == ARROW_DOWN && position != maxPosition)
        position++;
    else if(keyPressed == ARROW_UP && position != minPosition)
        position--;
    else
        position = position;
    
    return position;
}
/* This function checks that if the position from readInput is 
   the same as a position on the menu, then it print a ">" */
void printArrow (int realPosition, int arrowPosition) {
    if(realPosition == arrowPosition)
        printf(">    ");
    else
        printf("  ");
}

void newProcess(int *count) {
    int radius = 4;
    int i,j;
    for (i=0; i<=2*radius; i++) {
        for (j=0; j<=2*radius; j++) {
            double distance = sqrt((double)(i-radius)*(i-radius) + (j-radius)*(j-radius));
            if (distance>radius-0.5 && distance<radius+0.5)
                printf("*");
            else 
                printf(" ");
        }
        printf("\n");
    }
    printf("    |\n"
           "    |\n");
    *count += 1;
}

void deleteProcess() {

}

double calculateRunTime(int plannedProdTime, int stopTime) {
    int runTime;
    runTime = plannedProdTime - stopTime;
    return runTime;
}

double calculateAvailability(double runtime, double plannedProdTime) {
    double availability;
    availability = runtime / plannedProdTime;
    return availability;
}

double calculatePerformance(int runTime, int goodCount, int idealcycletime) {
    double performance;
    performance = (idealcycletime * goodCount) / runTime;
    return performance;
}

double calculateQuality(int goodCount, int totalCount) {
    double Quality;
    Quality = goodCount / totalCount;
    return Quality;
}

void calculateOee() {

}
