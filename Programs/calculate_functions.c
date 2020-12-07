/* Funktioner til beregning af Availability, Performance, Quality og OEE på 2 forskellige måder */

#include <stdio.h>

double calculateAvailability(double runTime, double plannedProductionTime){
    return runTime / plannedProductionTime;
}

double calculatePerformance(double idealCycleTime, double totalCount, double runTime){
    return (idealCycleTime * totalCount) / runTime;
}

double calculateQuality(double goodCount, double totalCount){
    return goodCount / totalCount;
}

double calculateOEE1(double avialability, double performace, double quality){
    return avialability * performace * quality;
}

double calculateOEE2(double idealCycleTime, double goodCount, double plannedProductionTime){
    return (idealCycleTime * goodCount) / plannedProductionTime;
}