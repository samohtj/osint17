/* 
 * Jonathan Thomas
 * CEG 4350 Fall 2017
 * Project 1: Producer / Consumer Problem
 * Creates producer processes that add messages to a buffer in shared memory space.
 */

#include "producer_jct.h"

/*
 * Main entry point. Parses terminal arguments to determine what action to take.
 */
int main(int argc, char** argv) {
    switch(argc) {
    case 2:
        if (strcmp(argv[1], HELP_ARG) != 0) {
	    improper_args();
	    return 1;
	} else {
	    /* User asks for help! */
	    print_help_info();
	    return 0;
	}
    case 5:
	if (check_args(argv[1], argv[2], argv[3]) != 0) {
	    /* Invalid arguments. Yell at user! */
	    improper_args();
	    return 1;
	} else {
	    /* Actually run the program */
	    return 0;
	}
    case 1:
		/* Run the program with default arguments. */
	return 0;
    default:
		/* Improper number of arguments. Print proper useage to screen*/
		improper_num_arguments();
		return 1;
    }
}

void produce() {



}

/*
 * Print basic help information to the console.
 */
void print_help_info() {
    printf("PRODUCER PROCESS\n");
    printf("To use: ");
    printf("\tproducer_jct <BUFFER SIZE> <NUM PRODUCERS> <NUM MESSAGES>\n");
	printf("\tBUFFER SIZE: ")
}

/*
 * Check the validity of the arguments entered. They should all be integers.
 *
 * @param a, b, c Strings parsed from the command line arguments.
 * @return 0 if arguments are valid, 1 otherwise.
 */
int check_args(char * a, char * b, char * c) {
   return 0; 
}
