#include "inv_tran_sampling.h"

double defects(process);
double stops(process);
double calculateAvailability(double, process);
double calculatePerformance(double, process, manufacturing_system);
double calculateQuality(double, manufacturing_system);
double calculateOEE1(double, double, double);