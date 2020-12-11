#include "inv_tran_sampling.h"

#include <stdio.h>

double good_count(int totalCount, int amount_of_processes, process processes[]){
    int i, j;
    double defects_total = 0, defects_mean;

    for (i = 0; i < amount_of_processes; i++){
        for (j = 0; j < NUM_SIM; j++)
            defects_total += processes[i].defectsArr[j];
    }
    
    defects_mean = defects_total / NUM_SIM * amount_of_processes;

    return (double)totalCount - defects_mean;
}

double calculateAvailability(double runTime, double plannedProductionTime){
    return runTime / plannedProductionTime;
}

double calculatePerformance(double idealCycleTime, double totalCount, double runTime){
    return (idealCycleTime * totalCount) / runTime;
}

double calculateQuality(double goodCount, double totalCount){
    return goodCount / totalCount;
}

double calculateOEE1(double availability, double performace, double quality){
    return availability * performace * quality;
}

double calculateOEE2(double idealCycleTime, double goodCount, double plannedProductionTime){
    return (idealCycleTime * goodCount) / plannedProductionTime;
}