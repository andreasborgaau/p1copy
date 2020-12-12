#include "inv_tran_sampling.h"

double defects(process, int);
double stops(process, int);
double calculateAvailability(double, manufacturing_system);
double calculatePerformance(double, process, manufacturing_system);
double calculateQuality(double, manufacturing_system);
double calculateOEE1(double, double, double);
double calculateOEE2(double, double, double);