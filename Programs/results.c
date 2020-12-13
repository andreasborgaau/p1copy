#include "calculate_functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int comparator(const void *element1, const void *element2){
    return (*(double*)element1 - *(double*)element2);
}

void printHistogram(process processes, int index){
    int i, j, counter = 0;
    double min_defects = RAND_MAX, min_stops = RAND_MAX, max_defects = 0, max_stops = 0, prob_counter = 0;

    for(i = 0; i < NUM_SIM; i++){
        if (processes.defectsArr[i] < min_defects)
            min_defects = processes.defectsArr[i];
        if (processes.defectsArr[i] > max_defects)
            max_defects = processes.defectsArr[i];
        
        if (processes.stopsArr[i] < min_stops)
            min_stops = processes.stopsArr[i];
        if (processes.stopsArr[i] > max_stops)
            max_stops = processes.stopsArr[i];
    }

    printf(ANSI_UNDERLINED_PRE"Distribution of Defects for Process %d"ANSI_UNDERLINED_POST"\n\n", index + 1);
    for(i = 0; i < INTERVALS; i++){
                printf("[%2d][%8.2f,%8.2f]", i+1, (max_defects - min_defects) / INTERVALS * i + min_defects, (max_defects - min_defects) / INTERVALS * (i +1) + min_defects);
        for(j = 0; j < NUM_SIM; j++){
            if((max_defects - min_defects) / INTERVALS * i + min_defects < processes.defectsArr[j] && processes.defectsArr[j] < (max_defects - min_defects) / INTERVALS * (i + 1) + min_defects){
                counter++;
                prob_counter++;
                if(counter > 500){
                    counter = 0;
                    printf("x");
                }
            }
            if(j == NUM_SIM - 1){
                printf(" (%2.3f %%)", prob_counter / NUM_SIM * 100);
                prob_counter = 0;
                printf("\n");
            }
        }
    }

    printf("\n\n"ANSI_UNDERLINED_PRE"Distribution of Unplanned Stops for Process %d"ANSI_UNDERLINED_POST"\n\n", index + 1);
    for(i = 0; i < INTERVALS; i++){
                printf("[%2d][%8.2f,%8.2f]", i+1, (max_stops - min_stops) / INTERVALS * i + min_stops, (max_stops - min_stops) / INTERVALS * (i +1) + min_stops);
        for(j = 0; j < NUM_SIM; j++){
            if((max_stops - min_stops) / INTERVALS * i + min_stops < processes.stopsArr[j] && processes.stopsArr[j] < (max_stops - min_stops) / INTERVALS * (i + 1) + min_stops){
                counter++;
                prob_counter++;
                if(counter > 500){
                    counter = 0;
                    printf("x");
                }
            }
            if(j == NUM_SIM - 1){
                printf(" (%2.3f %%)", prob_counter / NUM_SIM * 100);
                prob_counter = 0;
                printf("\n");
            }
        }
    }
    printf("\n\n");
}

void printResult2(int amount_of_processes, process processes[], manufacturing_system manu_system){
    int i;
    double availability, performance, quality, OEE;

    printf("__________________________________________________________________\n");
    printf(ANSI_UNDERLINED_PRE "|                      OEE for Each Process                      |" ANSI_UNDERLINED_POST "\n");
    printf(ANSI_UNDERLINED_PRE "| Process |   OEE   |  Availability  |  Performance  |  Quality  |" ANSI_UNDERLINED_POST "\n");
    
    for(i = 0; i < amount_of_processes; i++){
        availability = calculateAvailability(processes[i].planned_production_time - stops(processes[i]), processes[i]);
        performance = calculatePerformance(processes[i].planned_production_time - stops(processes[i]), processes[i], manu_system);
        quality = calculateQuality(manu_system.total_count - defects(processes[i]), manu_system);
        OEE = calculateOEE1(availability, performance, quality);

        printf(ANSI_UNDERLINED_PRE "| %7d | %7.3f | %14.3f | %13.3f | %9.3f |" ANSI_UNDERLINED_POST "\n", i+1, OEE, availability, performance, quality);
    }
}

void printSortedResult(int amount_of_processes, process processes[], manufacturing_system manu_system){
    int i, j;
    double *indexArr;

    indexArr = malloc(sizeof(double) * amount_of_processes);

    for(i = 0; i < amount_of_processes; i++){
        processes[i].availability = calculateAvailability(processes[i].planned_production_time - stops(processes[i]), processes[i]);
        processes[i].performance = calculatePerformance(processes[i].planned_production_time - stops(processes[i]), processes[i], manu_system);
        processes[i].quality = calculateQuality(manu_system.total_count - defects(processes[i]), manu_system);
        processes[i].OEE = calculateOEE1(processes[i].availability, processes[i].performance, processes[i].quality);
        indexArr[i] = processes[i].OEE;
    }

    qsort(indexArr, amount_of_processes, sizeof(double), comparator);

    printf("__________________________________________________________________\n");
    printf(ANSI_UNDERLINED_PRE "|                      OEE for Each Process                      |" ANSI_UNDERLINED_POST "\n");
    printf(ANSI_UNDERLINED_PRE "| Process |   OEE   |  Availability  |  Performance  |  Quality  |" ANSI_UNDERLINED_POST "\n");

    for(i = 0; i < amount_of_processes; i++){
        for(j = 0; j < amount_of_processes; j++){
            if(indexArr[i] == processes[j].OEE)
                printf(ANSI_UNDERLINED_PRE "| %7d | %7.3f | %14.3f | %13.3f | %9.3f |" ANSI_UNDERLINED_POST "\n", i + 1, processes[j].OEE, processes[j].availability, processes[j].performance, processes[j].quality);
        }
    }
}

void printResult3(int amount_of_processes, process processes[], manufacturing_system manu_system){
    int i;
    double OEE, availability_total = 0, performance_total = 0, quality_total = 0, availability_mean, performance_mean, quality_mean;

    for(i = 0; i < amount_of_processes; i++){
        availability_total += calculateAvailability(processes[i].planned_production_time - stops(processes[i]), processes[i]);
        performance_total += calculatePerformance(processes[i].planned_production_time - stops(processes[i]), processes[i], manu_system);
        quality_total += calculateQuality(manu_system.total_count - defects(processes[i]), manu_system);
    }
    
    availability_mean = availability_total / amount_of_processes;
    performance_mean = performance_total / amount_of_processes;
    quality_mean = quality_total / amount_of_processes;
    
    OEE = calculateOEE1(availability_mean, performance_mean, quality_mean);

    printf("\n\n___________________________________\n");
    printf(ANSI_UNDERLINED_PRE "|            Total OEE            |" ANSI_UNDERLINED_POST "\n");
    printf(ANSI_UNDERLINED_PRE "| OEE            |  %12.3f  |" ANSI_UNDERLINED_POST "\n", OEE);
    printf(ANSI_UNDERLINED_PRE "| Availability   |  %12.3f  |" ANSI_UNDERLINED_POST "\n", availability_mean);
    printf(ANSI_UNDERLINED_PRE "| Performance    |  %12.3f  |" ANSI_UNDERLINED_POST "\n", performance_mean);
    printf(ANSI_UNDERLINED_PRE "| Quality        |  %12.3f  |" ANSI_UNDERLINED_POST "\n", quality_mean);
}