/*
 ============================================================================
 Name        : password_lib.c
 Author      : Louis-Erig HERVE
 Version     : 1.0
 Date        : 2021 - September - 19
 Copyright   : None
 Description : Password generator library source
 ============================================================================
 */


/* Include ------------------------------------------------------------------*/
#include "password_lib.h"


/* Define -------------------------------------------------------------------*/


/* Global variables ---------------------------------------------------------*/


/* Functions ----------------------------------------------------------------*/


/*
 * @brief : Initialize the current password library
 *
 * @param None
 *
 * @return None
 *
 */
void InitPasswordLib(void)
{
  uint64_t i;
  uint64_t NbLoop;
  time_t   rawtime;
  struct   tm * timeinfo = NULL;
  struct   timeval tv;

  /* Initialize random seed with the current time */
  srand(time(NULL));

  /* Get the current time */
  time(&rawtime);
  timeinfo = localtime(&rawtime);
  gettimeofday (&tv, NULL);

  /* Compute the number of loop to process */
  NbLoop  = (uint32_t)(timeinfo->tm_yday * 24 * 3600);
  NbLoop += (uint32_t)(timeinfo->tm_hour * 3600);
  NbLoop += (uint32_t)(timeinfo->tm_min * 60);
  NbLoop += (uint32_t)(timeinfo->tm_sec);
  NbLoop += (uint32_t)(tv.tv_usec);

  /* Generate random numbers */
  for(i = 0; i < NbLoop; i++)
  {
    rand();
  }
} /* End InitPasswordLib() */


/*
 * @brief : This function generate a random password
 *
 * @param PasswordLen : The length of the password to generate (in characters)
 *
 * @param CharacterList : A list of ASCII characters to be used to generate password
 *
 * @param CharacterListSize : The size of the ASCII character list used to generate the password
 *
 * @param OutputPassword : A buffer where the output password will be stored
 *
 * @return None
 *
 */
void GeneratePassword(uint32_t  PasswordLen,
                      uint8_t * CharacterList,
                      uint32_t  CharacterListSize,
                      uint8_t * OutputPassword)
{
  uint64_t i = 0;
  uint64_t NbLoop = 0;
  uint64_t RandomXor = 0;
  time_t   rawtime;
  struct   tm * timeinfo = NULL;
  struct   timeval tv;
  uint32_t RandomIndex;

  /* Step 1 : Get the current time */
  time(&rawtime);
  timeinfo = localtime(&rawtime);
  gettimeofday (&tv, NULL);

  /* Step 2 : Compute the number of loop to process */
  NbLoop  = (uint32_t)(timeinfo->tm_yday * 24 * 3600);
  NbLoop += (uint32_t)(timeinfo->tm_hour * 3600);
  NbLoop += (uint32_t)(timeinfo->tm_min * 60);
  NbLoop += (uint32_t)(timeinfo->tm_sec);
  NbLoop += (uint32_t)(tv.tv_usec);

  /* Step 3 : Generate random numbers */
  for(i = 0; i < NbLoop; i++)
  {
    rand();
  }

  /* Step 4 : Generate a 64 bits random number based on the current time */
  RandomXor = Generate64BitsRandomNumber();

  /* Step 5 : Generates a random password */
  for(i = 0; i < PasswordLen; i++)
  {
    RandomIndex = (uint32_t)((rand() ^ RandomXor) % CharacterListSize);
    OutputPassword[i] = CharacterList[RandomIndex];

    /* Re-generate the 64 bits random number */
    RandomXor = Generate64BitsRandomNumber();
  }

} /* End GeneratePassword() */


/*
 * @brief : This function generate a random 64 bits number
 *          based on the current microsecond time machine
 *          value.
 *
 * @param None
 *
 * @return A 64 bits random number
 *
 */
uint64_t Generate64BitsRandomNumber(void)
{
  uint64_t Random64bitsNum = 0;
  uint32_t i;
  struct   timeval tv;

  /* For a 64 bits number there are 16 loop */
  for(i = 0; i < (sizeof(Random64bitsNum) / 4); i++)
  {
    /* Get the current time */
    gettimeofday (&tv, NULL);

    /* Get 4 MSBits of the microsecond time value as a part
     * of the 64 bits random number */
    Random64bitsNum = (Random64bitsNum << 4) | (uint64_t)(tv.tv_usec & 0x0F);

    /* Wait for a random delay (this ensure the
     * microsecond counter value will change randomly on
     * next call of the current function) */
    Password_delay((tv.tv_usec & 0xF) + 10);

    /* Call rand() to be sure to change
     * the random system value */
    rand();
  }

  return Random64bitsNum;
}


/*
 * @brief : This function generate a delay, it replace the "usleep" function not
 *          available on Windows machines.
 *          This function is not precise and must not be used for real
 *          time applications.
 *
 * @param None
 *
 * @return None
 *
 */
void Password_delay(uint64_t Delay)
{
  volatile uint64_t i = 0;
  for(i = 0; i < (Delay * 100); i++)
  {
    /* Call rand() to be sure to change
     * the random system value */
    rand();
  }
} /* End Password_delay() */


/* End of file */
