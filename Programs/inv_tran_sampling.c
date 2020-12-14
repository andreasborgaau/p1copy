#include "constants.h"
#include "asa241.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct{
    int index;
    double availability;
    double performance;
    double quality;
    double OEE;
    double planned_production_time;
    double ideal_cycle_time;
    double defectsArr[NUM_SIM];
    double stopsArr[NUM_SIM];
    double mean_defects;
    double std_deviation_defects;
    double lambda_defects;
    double mean_US;
    double std_deviation_US;
    double lambda_US;
} process;

/*Performs inverse transform sampling of a single sample on an approximation of the inverse cdf of the standard normal distribution.
The result is scaled to any normal distribution.*/
double inv_cdf_normal(double mean, double std_deviation, double sample){
    return r8_normal_01_cdf_inverse(sample) * std_deviation + mean;
}
/*Performs inverse transform sampling of a single sample on the inverse cdf of the exponential distribution.*/
double inv_cdf_exponential(double lambda, double sample){
    return -(log(sample)) / lambda;
}

/*Generates a random sample in the interval [0,1].*/
double sample(void){
    return (double)rand() / (double)RAND_MAX;
}

/*Simulates all manufacturing processes by generating data for defects and unplanned stops that follows a probability distribution.*/
void simulate(process processes[], int amount_of_processes){
    int i, j;
    
    srand(time(NULL));

    for(i = 0; i < amount_of_processes; i++){
        if(processes[i].mean_defects != -1)
            for(j = 0; j < NUM_SIM; j++)
                processes[i].defectsArr[j] = inv_cdf_normal(processes[i].mean_defects, processes[i].std_deviation_defects, sample());
        if(processes[i].lambda_defects != -1)
            for(j = 0; j < NUM_SIM; j++)
                processes[i].defectsArr[j] = inv_cdf_exponential(processes[i].lambda_defects, sample());
    }

    for(i = 0; i < amount_of_processes; i++){
        if(processes[i].mean_US != -1)
            for(j = 0; j < NUM_SIM; j++)
                processes[i].stopsArr[j] = inv_cdf_normal(processes[i].mean_US, processes[i].std_deviation_US, sample());
        if(processes[i].lambda_US != -1)
            for(j = 0; j < NUM_SIM; j++)
                processes[i].stopsArr[j] = inv_cdf_exponential(processes[i].lambda_US, sample());
    }
}