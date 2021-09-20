/*
 ============================================================================
 Name        : main.h
 Author      : Louis-Erig HERVE
 Version     : 1.0
 Date        : 2021 - September - 18
 Copyright   : None
 Description : Password generator main program header
 ============================================================================
 */


#ifndef MAIN_H_
#define MAIN_H_


/* Include ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include "password_lib.h"


/* Define -------------------------------------------------------------------*/


/* External variables -------------------------------------------------------*/
extern int optind, opterr, optopt;


/* Typedef ------------------------------------------------------------------*/


/* Function prototypes ------------------------------------------------------*/
void usage(void);


#endif /* MAIN_H_ */

/* End of file */
