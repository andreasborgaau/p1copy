#include "constants.h"

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
}process;

double inv_cdf_normal(double, double, double);
double inv_cdf_exponential(double, double);
double sample(void);
void simulate(process[], int);