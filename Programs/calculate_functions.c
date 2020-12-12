#include "inv_tran_sampling.h"

#include <stdio.h>

double defects(process process, int amount_of_processes){
    int i;
    double defects_total;

    for (i = 0; i < NUM_SIM; i++)
        defects_total += process.defectsArr[i];

    return defects_total / NUM_SIM;
}

double stops(process process, int amount_of_processes) {
    int i;
    double US_total = 0;

    for (i = 0; i < NUM_SIM; i++)
        US_total += process.stopsArr[i];
    
    return US_total / NUM_SIM;
}

double calculateAvailability(double run_time, manufacturing_system manu_system){
    return run_time / manu_system.planned_production_time;
}

double calculatePerformance(double run_time, process process, manufacturing_system manu_system){
    return (process.ideal_cycle_time * manu_system.total_count) / run_time;
}

double calculateQuality(double good_count, manufacturing_system manu_system){
    return good_count / manu_system.total_count;
}

double calculateOEE1(double availability, double performace, double quality){
    return availability * performace * quality;
}