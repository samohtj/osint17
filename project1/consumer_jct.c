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
	        create_shared_mem();
	        create_consumers(atoi(argv[1]));
	        cleanup();
	        return 0;
	    }
    case 1:
	    /* Run the program with default arguments. */
	    create_shared_mem();
	    create_consumers(5);
	    cleanup();
	    return 0;
    default:
	    /* Improper number of arguments. Print proper useage to screen*/
	    improper_num_arguments();
	    return 1;
    }
}

void* consume(void* arg) {
    printf("Consumer created!\n");
    pthread_exit(0);
}

void create_consumers(int num_consumers) {
	/* Thread creating code goes here. */
    /* TODO Pass it in its thread id, so it can prepend it to the message */
    
    pthread_t thread_ids[num_consumers];
    /* Create N threads */
    for (int i = 0; i < num_consumers; i++) {
        pthread_attr_t attributes;
        pthread_attr_init(&attributes);
        pthread_create(&thread_ids[i], &attributes, consume, NULL);
    }

    /* Wait for threads to finish */
    for (int i = 0; i < num_consumers; i++) {
        pthread_join(thread_ids[i], NULL);
    }
}

void create_shared_mem() {
    printf("Creating shared memory space!\n");
}

void cleanup() {
    printf("Cleaning up shared memory space!\n");
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
    printf("\tAll arguments must be positive integers between 1 and 100 (inclusive).\n");
}

/*
 * Check the validity of the arguments entered. They should all be integers.
 * @param a,b: Strings parsed from the command line arguments.
 * @return   : 0 if arguments are valid, 1 otherwise.
 */
int check_args(char * a, char * b) {
    int first = atoi(a);
    int second = atoi(b);
    return (first <= 0 || first > 100 
        || second <= 0 || second > 100)? 1:0;  
}
