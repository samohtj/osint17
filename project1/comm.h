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


// Terminal option to print help information.
#define HELP_ARG "-h"

// Buffer is not allowed to hold more than 100 things.
#define MAX_BUFF_SIZE 100
#define BUFF_NAME "JCT"
