#include "calculate_functions.h"
#include "inv_tran_sampling.h"

#include <stdio.h>
#include <stdlib.h>

void printResult1(int amount_of_processes, process processes[], manufacturing_system manu_system){
    int i;
    printf("\n_________________________________________________________________________\n");
    printf(ANSI_UNDERLINED_PRE "|                                   Table 1                             |" ANSI_UNDERLINED_POST "\n");

    printf(ANSI_UNDERLINED_PRE "| Process | Total count | Defects |  Good count  |  Run time  |  Unplanned stops  |" ANSI_UNDERLINED_POST "\n");

    for(i = 0; i < amount_of_processes; i++) {
        printf(ANSI_UNDERLINED_PRE "| %3d  | %-4s |  %-5d|  %-4d|  %-3d |" ANSI_UNDERLINED_POST "\n",i, manu_system.total_count, processes.,
                                                                                                            teams[i].goalScore, teams[i].goalAgainstTeam, 
                                                                                                            teams[i].goalScore - teams[i].goalAgainstTeam);
    } 
}




void printResult2(int amount_of_processes, process processes[], manufacturing_system manu_system){
    int i;
    printf("\n______________________________________________________________\n");
    printf(ANSI_UNDERLINED_PRE "|                            Table 2                         |" ANSI_UNDERLINED_POST "\n");

    printf(ANSI_UNDERLINED_PRE "| Process | OEE |  Availability  |  Performance  |  Quality  |" ANSI_UNDERLINED_POST "\n");
    
    for(i = 0; i < amount_of_processes; i++) {
        printf(ANSI_UNDERLINED_PRE "| %3d  | %-4s |  %-5d|  %-4d|  %-3d |" ANSI_UNDERLINED_POST "\n",i, teams[i].teamName, teams[i].points,
                                                                                                            teams[i].goalScore, teams[i].goalAgainstTeam, 
                                                                                                            teams[i].goalScore - teams[i].goalAgainstTeam);
    }
} 




void printResult3(int amount_of_processes, process processes[], manufacturing_system manu_system){
    printf("\n___________________________________\n");
    printf(ANSI_UNDERLINED_PRE "|             Table 3             |" ANSI_UNDERLINED_POST "\n");
    printf(ANSI_UNDERLINED_PRE "| OEE          |       %f%%        |" ANSI_UNDERLINED_POST "\n");
    printf(ANSI_UNDERLINED_PRE "| Availability |       %f%%        |" ANSI_UNDERLINED_POST "\n");
    printf(ANSI_UNDERLINED_PRE "| Performance  |       %f%%        |" ANSI_UNDERLINED_POST "\n");
    printf(ANSI_UNDERLINED_PRE "| Quality      |       %f%%        |" ANSI_UNDERLINED_POST "\n");
} 