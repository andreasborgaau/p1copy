#include "inv_tran_sampling.h"

#include <stdio.h>

/*Computes the mean of defects for a single manufacturing process.*/
double defects(process process){
    int i;
    double defects_total;

    for(i = 0; i < NUM_SIM; i++)
        defects_total += process.defectsArr[i];

    return defects_total / NUM_SIM;
}

/*Computes the mean of unplanned stops for a single manufacturing process.*/
double stops(process process){
    int i;
    double US_total = 0;

    for(i = 0; i < NUM_SIM; i++)
        US_total += process.stopsArr[i];
    
    return US_total / NUM_SIM;
}

/*Calculates the availability of a single manufacturing process.*/
double calculateAvailability(double run_time, process process){
    return run_time / process.planned_production_time;
}

/*Calculates the performance of a single manufacturing process.*/
double calculatePerformance(double run_time, process process, int total_count){
    return process.ideal_cycle_time * total_count / run_time;
}

/*Calculates the quality of a single manufacturing process.*/
double calculateQuality(double good_count, int total_count){
    return good_count / total_count;
}

/*Calculates the OEE of a single manufacturing process.*/
double calculateOEE(double availability, double performace, double quality){
    return availability * performace * quality;
}