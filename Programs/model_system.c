#include <stdlib.h>
#include <stdio.h>

void newProcess(int *amount_of_processes) {
    int i;

    printf("Enter the amount of processes: ");
    scanf(" %d", amount_of_processes);
    printf("\n");

    for(i = 1; i <= *amount_of_processes; i++) {
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