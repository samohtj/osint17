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
    case 4:
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

/*
 * Create a message and put in on the buffer.
 */
void produce() {



}

/*
 * Create producer threads.
 * @param num_producers Number of producer threads to create.
 * @param num_messages Number of messages for each thread to create.
 */
void create_threads(int num_producers, int num_messages) {
	/* Thread creating code goes here. */
}

/*
 * Print basic help information to the console.
 */
void print_help_info() {
    printf("PRODUCER PROCESS\n");
    printf("To use: ");
    printf("\tproducer_jct <BUFFER SIZE> <NUM PRODUCERS> <NUM MESSAGES>\n");
    printf("\tBUFFER SIZE: Number of message objects that can be held in the buffer at once.");
}

/*
 * Check the validity of the arguments entered. They should all be integers.
 * TODO Fill this out!
 * @param a, b, c Strings parsed from the command line arguments.
 * @return 0 if arguments are valid, 1 otherwise.
 */
int check_args(char * a, char * b, char * c) {
   return 0; 
}

void setup_buffer(int buffer_size) {
	const int size = buffer_size;
	const char *buffer_name = "JCT";
	int shared_buffer = shm_open(name, O_CREAT | O_RDWR, 0666);
	ftruncate(shared_buffer, size);
	void * buffer_pointer;
	buffer_pointer = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, shared_buffer, 0);
	if (buffer_pointer == MAP_FAILED) {
		printf("Could not map shared buffer to memory.");
	}// TODO This is not correct in any fashion.

}
