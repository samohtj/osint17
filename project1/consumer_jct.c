/* 
 * Jonathan Thomas
 * CEG 4350 Fall 2017
 * Project 1: Producer / Consumer Problem
 * Creates producer processes that add messages to a buffer in shared memory space.
 */

#include "consumer_jct.h"

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
    case 3:
	if (check_args(argv[1], argv[2]) != 0) {
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

/*
 * Print basic help information to the console.
 */
void print_help_info() {
    printf("CONSUMER PROCESS\n");
    printf("To use: ");
    printf("\tconsumer_jct <NUM CONSUMERS> <NUM MESSAGES>\n");
    printf("\tNUM CONSUMERS: Number of consumer processes to create.\n");
    printf("\tNUM MESSAGES : Maximum number of messages to read from the buffer.\n");
}

/*
 * Check the validity of the arguments entered. They should all be integers.
 * TODO Fill this out!
 * @param a,b Strings parsed from the command line arguments.
 * @return 0 if arguments are valid, 1 otherwise.
 */
int check_args(char * a, char * b) {
   return 0; 
}
