#include "constants.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double inv_cdf_normal(double mean, double std_deviation, double sample){
    return sample + 2;
}

double inv_cdf_exponential(double lambda, double sample){
    return -ln(sample) / lambda;
}

double sample(void){
    return ((double)(rand() % 101))/(double)100;
}

double simulate(process processes[], int *amount_of_processes){
    int i, j;
    
    srand(time(NULL));

    for (i = 0; i < *amount_of_processes; i++){
        if(processes[i].mean_defects != -1)
            for (j = 0; j < NUM_SIM; j++){
                processes[i].defectsArr[j] = inv_cdf_normal(processes[i].mean_defects, processes[i].std_deviation_defects, sample());
            }
        if(processes[i].lambda_defects != -1)
            for (j = 0; j < NUM_SIM; j++){
                processes[i].defectsArr[j] = inv_cdf_exponential(processes[i].lambda_defects, sample());
            }
    }

    for (i = 0; i < *amount_of_processes; i++){
        if(processes[i].mean_US != -1)
            for (j = 0; j < NUM_SIM; j++){
                processes[i].stopsArr[j] = inv_cdf_normal(processes[i].mean_US, processes[i].std_deviation_US, sample());
            }
        if(processes[i].lambda_US != -1)
            for (j = 0; j < NUM_SIM; j++){
                processes[i].stopsArr[j] = inv_cdf_exponential(processes[i].lambda_US, sample());
            }
    }
}