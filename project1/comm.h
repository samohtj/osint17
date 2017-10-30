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

/*
 * Terminal option to print help information.
 */
#define HELP_ARG "-h"
