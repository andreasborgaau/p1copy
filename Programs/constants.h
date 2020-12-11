#define ASCII_newline 10
#define ASCII_one 49
#define ASCII_two 50
#define ASCII_three 51
#define ASCII_four 52
#define ASCII_five 53
#define ASCII_six 54
#define ASCII_seven 55

#define NUM_SIM 1000

#define ANSI_UNDERLINED_PRE  "\033[4m"
#define ANSI_UNDERLINED_POST "\033[0m"

static struct termios old, current;

typedef struct{
    int total_count;
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