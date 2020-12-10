int mainMenu(int*);
int modelMenu(int*);
int finishMenu(int*);
void manual(void);
void newProcess(int*);
void initTermios(void);
void resetTermios(void);
char getch(void);

static struct termios old, current;