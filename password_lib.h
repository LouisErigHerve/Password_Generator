/*
 ============================================================================
 Name        : password_lib.h
 Author      : Louis-Erig HERVE
 Version     : 1.0
 Date        : 2021 - September - 19
 Copyright   : None
 Description : Password generator library source
 ============================================================================
 */


#ifndef PASSWORD_LIB_H_
#define PASSWORD_LIB_H_


/* Include ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>


/* Define -------------------------------------------------------------------*/


/* External variables -------------------------------------------------------*/


/* Typedef ------------------------------------------------------------------*/


/* Function prototypes ------------------------------------------------------*/
void InitPasswordLib(void);
void GeneratePassword(uint32_t  PassowrdLen,
                      uint8_t * CharacterList,
                      uint32_t  CharacterListSize,
                      uint8_t * OutputPassword);
uint64_t Generate64BitsRandomNumber(void);
void Password_delay(uint64_t);


#endif /* PASSWORD_LIB_H_ */

/* End of file */
