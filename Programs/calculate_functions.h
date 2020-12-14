#include "inv_tran_sampling.h"

double defects(process);
double stops(process);
double calculateAvailability(double, process);
double calculatePerformance(double, process, int);
double calculateQuality(double, int);
double calculateOEE(double, double, double);