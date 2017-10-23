#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>

/*
 * Terminal option to print help information.
 */
#define HELP_ARG "-h"

/*
 *   Improper or invalid arguments have been enetered. Will print a message to
 *   the console specifying proper next steps.
 */
#define improper_args() printf("Improper arguments. Correct usage: producer_jct <BUFFER SIZE> <NUM PRODUCERS> <NUM MESSAGES>\n");

/*
 *   Invlalid quantity of arguments was entered. Yell at the user!
 */
#define improper_num_arguments() improper_args()

void produce();
void print_help_info();
int check_args(char *, char *, char *);
void create_threads(int, int);
void setup_buffer(int);
