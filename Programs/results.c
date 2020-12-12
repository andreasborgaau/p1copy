#include "calculate_functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void printResult1(int amount_of_processes, process processes[], manufacturing_system manu_system){
    int i, defect, good_count, run_time, unplanned_stops, temp_total_count = manu_system.total_count;

    printf("\n_________________________________________________________________________\n");
    printf(ANSI_UNDERLINED_PRE "|                                   Table 1                             |" ANSI_UNDERLINED_POST "\n");

    printf(ANSI_UNDERLINED_PRE "| Process | Total count | Defects |  Good count  |  Run time  |  Unplanned stops  |" ANSI_UNDERLINED_POST "\n");

    for(i = 0; i < amount_of_processes; i++) {
        if (i != 0)
            temp_total_count -= ceil(defects(processes[i-1], amount_of_processes));
        defect = ceil(defects(processes[i], amount_of_processes));
        good_count = temp_total_count - ceil(defects(processes[i], amount_of_processes));
        run_time = manu_system.planned_production_time - ceil(stops(processes[i], amount_of_processes));
        unplanned_stops = ceil(stops(processes[i], amount_of_processes));

        printf(ANSI_UNDERLINED_PRE "| %3d | %8d | %8d | %8d | %4d | %4d |" ANSI_UNDERLINED_POST "\n", i, temp_total_count, defect, good_count, run_time, unplanned_stops);
    }

    printf("\n\n");
}

void printResult2(int amount_of_processes, process processes[], manufacturing_system manu_system){
    int i;
    double availability, performance, quality, OEE;
    printf("\n______________________________________________________________\n");
    printf(ANSI_UNDERLINED_PRE "|                            Table 2                         |" ANSI_UNDERLINED_POST "\n");

    printf(ANSI_UNDERLINED_PRE "| Process | OEE |  Availability  |  Performance  |  Quality  |" ANSI_UNDERLINED_POST "\n");
    
    for(i = 0; i < amount_of_processes; i++) {
        availability = calculateAvailability(manu_system.planned_production_time - stops(processes[i], amount_of_processes), manu_system);
        performance = calculatePerformance(manu_system.planned_production_time - stops(processes[i], amount_of_processes), processes[i], manu_system);
        quality = calculateQuality(manu_system.total_count - defects(processes[i], amount_of_processes), manu_system);
        OEE = calculateOEE1(availability, performance, quality);

        printf(ANSI_UNDERLINED_PRE "| %3d | %3.3f | %3.3f | %3.3f | %3.3f |" ANSI_UNDERLINED_POST "\n", i, OEE, availability, performance, quality);
    }

    printf("\n\n");
} 




void printResult3(int amount_of_processes, process processes[], manufacturing_system manu_system){
    int i;
    double OEE, availability_total, performance_total, quality_total, availability_mean, performance_mean, quality_mean;

    for (i = 0; i < amount_of_processes; i++){
        availability_total += calculateAvailability(manu_system.planned_production_time - stops(processes[i], amount_of_processes), manu_system);
        performance_total += calculatePerformance(manu_system.planned_production_time - stops(processes[i], amount_of_processes), processes[i], manu_system);
        quality_total += calculateQuality(manu_system.total_count - defects(processes[i], amount_of_processes), manu_system);
    }
    
    availability_mean = availability_total / amount_of_processes;
    performance_mean = performance_total / amount_of_processes;
    quality_mean = quality_total / amount_of_processes;
    
    OEE = calculateOEE1(availability_mean, performance_mean, quality_mean);

    printf("\n___________________________________\n");
    printf(ANSI_UNDERLINED_PRE "|             Table 3             |" ANSI_UNDERLINED_POST "\n");
    printf(ANSI_UNDERLINED_PRE "| OEE          |  %3.3f  |" ANSI_UNDERLINED_POST "\n", OEE);
    printf(ANSI_UNDERLINED_PRE "| Availability |  %3.3f  |" ANSI_UNDERLINED_POST "\n", availability_mean);
    printf(ANSI_UNDERLINED_PRE "| Performance  |  %3.3f  |" ANSI_UNDERLINED_POST "\n", performance_mean);
    printf(ANSI_UNDERLINED_PRE "| Quality      |  %3.3f  |" ANSI_UNDERLINED_POST "\n", quality_mean);

    printf("\n\nIdeal cycle time: %d \nTotal count: %d \nRun time: %f ", processes[0].ideal_cycle_time, manu_system.total_count, manu_system.planned_production_time - stops(processes[0], amount_of_processes));
}