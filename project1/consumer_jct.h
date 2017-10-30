/* 
 * Jonathan Thomas
 * CEG 4350 Fall 2017
 * Project 1: Producer / Consumer Problem
 * Creates producer processes that add messages to a buffer in shared memory space.
 */


#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "comm.h"

/*
 *   Improper or invalid arguments have been enetered. Will print a message to
 *   the console specifying proper next steps.
 */
#define improper_args() printf("Improper arguments.\n"); print_help_info();

/*
 *   Invlalid quantity of arguments was entered. Yell at the user!
 */
#define improper_num_arguments() improper_args()

void print_help_info();
int check_args(char *, char *);
void create_consumers(int);
void* consume(void*);
void create_shared_mem(void);
void cleanup(void);
