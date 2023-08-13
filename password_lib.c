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
  time_t   rawtime;
  struct   tm * timeinfo = NULL;
  struct   timeval tv;
  uint32_t RandomIndex;
  uint8_t  OldByte1 = 0;
  uint8_t  OldByte2 = 0;
  uint8_t  OldByte3 = 0;
  uint8_t  OldByte4 = 0;
  uint32_t RepeatLoop = 0;

  /* Step 1 : Init the pseudo random generator */
  srand(time(NULL));

  /* Step 2 : Get the current time */
  time(&rawtime);
  timeinfo = localtime(&rawtime);
  gettimeofday (&tv, NULL);

  /* Step 3 : Compute the number of loop to process */
  NbLoop  = (uint32_t)(timeinfo->tm_yday * 24 * 3600);
  NbLoop += (uint32_t)(timeinfo->tm_hour * 3600);
  NbLoop += (uint32_t)(timeinfo->tm_min * 60);
  NbLoop += (uint32_t)(timeinfo->tm_sec);
  NbLoop += (uint32_t)(tv.tv_usec);

  /* Step 3 : Generate several random numbers */
  for(i = 0; i < NbLoop; i++)
  {
    rand();
  }

  /* Step 4 : Generates a random password */
  for(i = 0; i < PasswordLen; i++)
  {
    RandomIndex = (uint32_t)(rand() % CharacterListSize);

    /* Check that the current random byte selected is different from the previous */
    if(((OldByte1 & 0xFF) == (CharacterList[RandomIndex] & 0xFF)) ||
       ((OldByte2 & 0xFF) == (CharacterList[RandomIndex] & 0xFF)) ||
       ((OldByte3 & 0xFF) == (CharacterList[RandomIndex] & 0xFF)) ||
       ((OldByte4 & 0xFF) == (CharacterList[RandomIndex] & 0xFF)))
    {
      RepeatLoop = 0;

      /* Force exit after up to 1000 loop */
      while(RepeatLoop < 1000)
      {
        /* Generate a new random index */
        RandomIndex = (uint32_t)(rand() % CharacterListSize);
        RepeatLoop++;

        /* Exit the "while" loop only when a new byte different from the
         * 4 previous one has been found */
        if(((OldByte1 & 0xFF) != (CharacterList[RandomIndex] & 0xFF)) &&
           ((OldByte2 & 0xFF) != (CharacterList[RandomIndex] & 0xFF)) &&
           ((OldByte3 & 0xFF) != (CharacterList[RandomIndex] & 0xFF)) &&
           ((OldByte4 & 0xFF) != (CharacterList[RandomIndex] & 0xFF)))
        {
          break;
        }
      }
    }

    /* Store the random byte as a character of the password */
    OutputPassword[i] = CharacterList[RandomIndex];

    /* Shift all previous bytes */
    OldByte4 = OldByte3;
    OldByte3 = OldByte2;
    OldByte2 = OldByte1;
    OldByte1 = CharacterList[RandomIndex];
  }

} /* End GeneratePassword() */


/* End of file */
