#include "producer_jct.h"

/*
    Boilerplate identifiying comment goes here

*/
int main(int argc, char** argv) {
    switch(argc) {
    case 2:
        if (strcmp(argv[1], HELP_ARG) != 0) {
	    improper_args(1);
	    return 1;
	} else {
	    /* User asks for help! */
	    print_help_info();
	    return 0;
	}
    case 5:
	if (check_args(argv[1], argv[2], argv[3]) != 0) {
	    /* Invalid arguments. Yell at user! */
	    improper_args(3);
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
 *   Improper or invalid arguments have been enetered Will print a message to
 *   the console specifying proper next steps.
 *
 *   @param count The number of arguments being passed. Valied values are 1 (help
 *	argument) or 3 (normal run). Helps discern what the user was tyring to do.
 */
void improper_args(int count) {
    if (count == 1) {
	printf("Unknown argument. Run with %s for help\n", HELP_ARG);	
    } else if (count == 3) {
	printf("Improper arguments. Correct usage: producer_jct <BUFFER SIZE> <NUM PRODUCERS> <NUM MESSAGES>\n");
    }

}

/*
 *   Invlalid quantity of arguments was entered. Yell at the user!
 */
void improper_num_arguments() {
    improper_args(3);
}

/*
 * Print basic help information to the console.
 */
void print_help_info() {
    printf("PRODUCER PROCESS\n");
    printf("To use: ");
    printf("\tproducer_jct <BUFFER SIZE> <NUM PRODUCERS> <NUM MESSAGES>\n");
}

/*
 * Check the validity of the arguments entered. They should all be integers.
 *
 * @param a, b, c Strings parsed from the command line arguments.
 * @return 0 if arguments are valid, false otherwise.
 */
int check_args(char * a, char * b, char * c) {
   return 0; 
}
