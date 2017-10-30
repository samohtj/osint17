/* 
 * Jonathan Thomas
 * CEG 4350 Fall 2017
 * Project 1: Producer / Consumer Problem
 * Creates producer processes that add messages to a buffer in shared memory space.
 */



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

void* produce(void*);
void print_help_info();
int check_args(char *, char *, char *);
void create_threads(int);
int create_shared_mem(int);
void cleanup(void);
void buffer_push(fifo_buffer *, char *);
