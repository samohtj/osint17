/* 
 * Jonathan Thomas
 * CEG 4350 Fall 2017
 * Project 1: Producer / Consumer Problem
 * Creates producer processes that add messages to a buffer in shared memory space.
 */

#include "producer_jct.h"

int num_messages = 100;
int buff_size = 10;
void* buff_ptr;
sem_t* access_mtx;
sem_t* full_sem;
sem_t* empty_sem;

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
        if (create_shared_mem(atoi(argv[1])) == 1) {
            return 1;
        }
        num_messages = atoi(argv[3]);
        create_threads(atoi(argv[2]));
        cleanup();
	    return 0;
	}
    case 1:
		/* Run the program with default arguments. */
        if (create_shared_mem(10 == 1)) {
            return 1;
        }
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
        /* Obtain access to the buffer */
        if (sem_wait(access_mtx) != 0) {
            printf("Error accessing shared memory.\n");
            continue;
        }
        
        sem_wait(empty_sem);
        
        // Create message
        
        char buf[20];
        snprintf(buf, sizeof buf, "%d_mes%d", (unsigned int) this_id, i);
        printf("Message created by producer %d! Message text: %s\n", 
            (unsigned int) this_id,
            buf);
        i++;
        // Add to buffer
        num_messages--;
        
        sem_post(full_sem);
        sem_post(access_mtx);
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

/*
 * Creates a shared memory buffer with the name JCT that the
 * producer and consumer processes can use to pass data back
 * and forth. Also creates semaphores to control access to the
 * shared buffer.
 * @param size: number of message pointers that the buffer can hold
 * @return    : 0 if succeeded, 1 if failed.
 */
int create_shared_mem(int size) {
    /* Create shared memory buffer */
    if (size > MAX_BUFF_SIZE) {
        size = MAX_BUFF_SIZE;
    } else if (size < 1) {
        size = 1;
    }
    printf("Creating shared memory.\n");
    int shm_filedesc;
    shm_filedesc = shm_open(BUFF_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_filedesc, MAX_BUFF_SIZE);
    buff_ptr = mmap(0, MAX_BUFF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_filedesc, 0);
    if (buff_ptr == MAP_FAILED) {
        printf("Failed to map shared memory buffer!\n");
        return 1;
    }
    
    /* Create semaphores */
    /* Access mutex */
    if (sem_unlink(ACCESS_MTX) == -1 && errno != ENOENT) {
        printf("Error removing semaphore %s\n", ACCESS_MTX);
        return 1; 
    }
    
    if ((access_mtx = sem_open(ACCESS_MTX, O_CREAT, 0666, 1)) == SEM_FAILED) {
        printf("Error creating semaphore %s\n", ACCESS_MTX);
        return 1;
    }
    
    /* Full counter semaphore */
    if (sem_unlink(FULL_SEM) == -1 && errno != ENOENT) {
        printf("Error removing semaphore %s\n", FULL_SEM);
        return 1;
    }
    
    if ((full_sem = sem_open(FULL_SEM, O_CREAT, 0666, 0)) == SEM_FAILED) {
        printf("Error creating semaphore %s\n", FULL_SEM);
        return 1;
    }
    
    /* Empty counter semaphore */
    if (sem_unlink(EMPTY_SEM) == -1 && errno != ENOENT) {
        printf("Error removing semaphore %s\n", EMPTY_SEM);
        return 1;
    }
    
    if ((empty_sem = sem_open(EMPTY_SEM, O_CREAT, 0666, size)) == SEM_FAILED) {
        printf("Error creating semaphore %s\n", EMPTY_SEM);
        return 1;
    }
    return 0;
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

void cleanup() {
    printf("Running cleanup.\n");
    /* Destroy all semaphores */
    /* Access mutex */
    if (sem_unlink(ACCESS_MTX) == -1) {
        printf("Error removing semaphore %s\n", ACCESS_MTX);
    }
    
    /* Full counter semaphore */
    if (sem_unlink(FULL_SEM) == -1) {
        printf("Error removing semaphore %s\n", FULL_SEM);
    }
    
    /* Empty counter semaphore */
    if (sem_unlink(EMPTY_SEM) == -1) {
        printf("Error removing semaphore %s\n", EMPTY_SEM);
    }
    
}
