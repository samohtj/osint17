/* 
 * Jonathan Thomas
 * CEG 4350 Fall 2017
 * Project 1: Producer / Consumer Problem
 * Creates producer processes that add messages to a buffer in shared memory space.
 */

#include "producer_jct.h"

int num_messages = 100;

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
        create_shared_mem();
        num_messages = atoi(argv[3]);
        create_threads(atoi(argv[2]));
        cleanup();
	    return 0;
	}
    case 1:
		/* Run the program with default arguments. */
        create_shared_mem();
        create_threads(5);
        cleanup();
	    return 0;
    default:
		/* Improper number of arguments. Print proper useage to screen*/
		improper_num_arguments();
		return 1;
    }
}

/*
 * Create messages and put them on the buffer.
 * (This is what you pass to pthread_create)
 */
void* produce(void* arg) {
    printf("Producer created!\n");
    pthread_t this_id = pthread_self();
    int i = 0;
    while (num_messages > 0) {
        /* START OF CRITICAL SECTION */
        // Create message
        // Add to buffer
        char* buf;
        snprintf(buf, 20, "%d_mes%d", (unsigned int) this_id, i);
        printf("Message created by producer %d!\n", (unsigned int) this_id);
        i++;
        num_messages--;
        /* END OF CRITICAL SECTION */
    }
    pthread_exit(0);
}

/*
 * Create producer threads.
 * @param num_producers: Number of producer threads to create.
 * @param num_messages : Total number of messages for all threads to create.
 */
void create_threads(int num_producers) {
	/* Thread creating code goes here. */
    /* TODO Pass it in its thread id, so it can prepend it to the message */
    
    pthread_t thread_ids[num_producers];
    /* Create N threads */
    for (int i = 0; i < num_producers; i++) {
        pthread_attr_t attributes;
        pthread_attr_init(&attributes);
        pthread_create(&thread_ids[i], &attributes, produce, NULL);
    }

    /* Wait for threads to finish */
    for (int i = 0; i < num_producers; i++) {
        pthread_join(thread_ids[i], NULL);
    }
}

void create_shared_mem() {
    printf("Creating shared memory.\n");
}

/*
 * Print basic help information to the console.
 */
void print_help_info() {
    printf("PRODUCER PROCESS\n");
    printf("To use: ");
    printf("\tproducer_jct <BUFFER SIZE> <NUM PRODUCERS> <NUM MESSAGES>\n");
    printf("\tBUFFER SIZE  : Number of message objects that can be held in the buffer at once.\n");
    printf("\tNUM PRODUCERS: Number of producer processes to create.\n");
    printf("\tNUM MESSAGES : Total number of messages to place on the buffer.\n");
    printf("\tAll arguments must be positive integers between 1 and 100 (inclusive).\n");
}

/*
 * Check the validity of the arguments entered. They should all be 
 * integers, and should all be positive.
 * @param a, b, c: Strings parsed from the command line arguments.
 * @return       : 0 if arguments are valid, 1 otherwise.
 */
int check_args(char * a, char * b, char * c) {
    int first = atoi(a);
    int second = atoi(b);
    int third = atoi(c);
    return (first <= 0 || first > 100 
        || second <= 0 || second > 100 
        || third <= 0 || third > 100)? 1:0; 
}

/*
 * Set up the shared memory buffer that messages are added to.
 */
void setup_buffer(int buffer_size) {
	const int size = buffer_size;
	const char *buffer_name = "JCT";
	int shared_buffer = shm_open(buffer_name, O_CREAT | O_RDWR, 0666);
	ftruncate(shared_buffer, size);
	void * buffer_pointer;
	buffer_pointer = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, shared_buffer, 0);
	if (buffer_pointer == MAP_FAILED) {
		printf("Could not map shared buffer to memory.");
	}// TODO This is not correct in any fashion.

}

void cleanup() {
    printf("Running cleanup.\n");
}
