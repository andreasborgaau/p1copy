#include "inv_tran_sampling.h"

#include <stdio.h>

double good_count(manufacturing_system manu_system, process processes[], int amount_of_processes){
    int i, j;
    double defects_total = 0, defects_mean;

    for (i = 0; i < amount_of_processes; i++){
        for (j = 0; j < NUM_SIM; j++)
            defects_total += processes[i].defectsArr[j];
    }
    
    defects_mean = defects_total / NUM_SIM * amount_of_processes;

    return (double)manu_system.total_count - defects_mean;
}

double run_time(manufacturing_system manu_system, process processes[], int amount_of_processes) {
    int i, j;
    double US_total = 0, US_mean;

    for (i = 0; i < amount_of_processes; i++){
        for (j = 0; j < NUM_SIM; j++)
            US_total += processes[i].stopsArr[j];
    }
    
    US_mean = US_total / NUM_SIM * amount_of_processes;

    return manu_system.planned_production_time - US_mean;
}

double calculateAvailability(double runTime, manufacturing_system manu_system){
    return runTime / manu_system.planned_production_time;
}

double calculatePerformance(process process, manufacturing_system manu_system, double runTime){
    return (process.ideal_cycle_time * manu_system.total_count) / runTime;
}

double calculateQuality(double goodCount, manufacturing_system manu_system){
    return goodCount / manu_system.total_count;
}

double calculateOEE1(double availability, double performace, double quality){
    return availability * performace * quality;
}

double calculateOEE2(double idealCycleTime, double goodCount, double plannedProductionTime){
    return (idealCycleTime * goodCount) / plannedProductionTime;
}