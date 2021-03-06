/* 
 * Jonathan Thomas
 * CEG 4350 Fall 2017
 * Project 1: Producer / Consumer Problem
 * Creates producer processes that add messages to a buffer in shared memory space.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <semaphore.h>
#include <errno.h>


/* Terminal option to print help information. */
#define HELP_ARG "-h"

/* Buffer is not allowed to hold more than 100 things. */
#define MAX_BUFF_SIZE 100
#define BUFF_NAME "JCT"

/* Mutex and semaphore name tags */
#define ACCESS_MTX "JCT_Access_mutex"
#define FULL_SEM "JCT_Full_semaphore"
#define EMPTY_SEM "JCT_Empty_semaphore"

typedef struct {
/* Command decision: Messages shall be no more than 20 chars long, and there shall
   be no more than 100 of them. Standard disclaimer: this is a hack. */
    char buffer[20*100];
    int head;
    int tail;
    int size;
} fifo_buffer;
