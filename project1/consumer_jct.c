/* 
 * Jonathan Thomas
 * CEG 4350 Fall 2017
 * Project 1: Producer / Consumer Problem
 * Creates producer processes that add messages to a buffer in shared memory space.
 */

#include "consumer_jct.h"

fifo_buffer* buff_ptr;
sem_t* access_mtx;
sem_t* full_sem;
sem_t* empty_sem;
int num_messages = 100;
int nm_original = 100;
int buff_size = 10;

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
	        num_messages = nm_original = atoi(argv[1]);
	        if (create_shared_mem() == 1) {
	            return 1;
	        }
	        create_consumers(atoi(argv[1]));
	        cleanup();
	        return 0;
	    }
    case 1:
	    /* Run the program with default arguments. */
	    if (create_shared_mem() == 1) {
	        return 1;
	    }
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
    pthread_t this_id = pthread_self();
    int i = 0;
    while(num_messages > 0) {
        /* Start of critical section */
        
        /* Obtain access to the buffer */
        if (sem_wait(access_mtx) != 0) {
            printf("Error accessing shared memory.\n");
            continue;
        }
        
        
        /* If there are no full spots, there is nothing to consume. Release the buffer and give the producer a chance. */
        int fullval;
        sem_getvalue(full_sem, &fullval);
        if (fullval <= 0) {
            sem_post(access_mtx);
            continue;
        }
        
        sem_wait(full_sem);
        
        char message[20];
        buffer_pop(buff_ptr, message);
        num_messages--;
        
        /* Release semaphores */
        sem_post(empty_sem);
        sem_post(access_mtx);
        
        /* End of critical section */
        printf("Consumer %d consumed item %s (%d/%d)\n",
            (unsigned int) this_id,
            message,
            nm_original - num_messages,
            nm_original);
        
    }
    
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

/*
 * Creates a shared memory buffer with the name JCT that the
 * producer and consumer processes can use to pass data back
 * and forth.
 * @param size: number of message pointers that the buffer can hold
 */
int create_shared_mem() {
    /* Create semaphores */
    /* Access mutex */
    
    if ((access_mtx = sem_open(ACCESS_MTX, 0)) == SEM_FAILED) {
        printf("Error creating semaphore %s\n", ACCESS_MTX);
        if (errno == ENOENT) {
            printf("Please run the producer before running the consumer.\n");
        }
        return 1;
    }
    
    int shm_filedesc;
    shm_filedesc = shm_open(BUFF_NAME, O_CREAT | O_RDWR, 0666);
    buff_ptr = mmap(0, MAX_BUFF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_filedesc, 0);
    if (buff_ptr == MAP_FAILED) {
        printf("Failed to map shared memory buffer!\n");
        return 1;
    }
    
    buff_size = buff_ptr->size;
    
    
    
    /* Full counter semaphore */
    
    if ((full_sem = sem_open(FULL_SEM, O_CREAT, 0666, 0)) == SEM_FAILED) {
        printf("Error creating semaphore %s\n", FULL_SEM);
        return 1;
    }
    
    /* Empty counter semaphore */
    
    if ((empty_sem = sem_open(EMPTY_SEM, O_CREAT, 0666, buff_size)) == SEM_FAILED) {
        printf("Error creating semaphore %s\n", EMPTY_SEM);
        return 1;
    }
    return 0;
}

void cleanup() {
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

void buffer_pop(fifo_buffer * buff, char* data) {
    if (buff->head == buff->tail) {
        return;
    }
    int next = (buff->tail + 1) % buff_size;
    strcpy(data, buff->buffer + (buff->tail * 20));
    buff->tail = next;
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
