#include "constants.h"

typedef struct{
    int ideal_cycle_time;
    double defectsArr[NUM_SIM];
    double stopsArr[NUM_SIM];
    double mean_defects;
    double std_deviation_defects;
    double lambda_defects;
    double mean_US;
    double std_deviation_US;
    double lambda_US;
} process;

double inv_cdf_normal(double, double, double);
double inv_cdf_exponential(double, double);
double sample(void);
double simulate(process[], int*);