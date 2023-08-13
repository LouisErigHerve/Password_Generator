/*
 ============================================================================
 Name        : main.c
 Author      : Louis-Erig HERVE
 Version     : 1.0
 Date        : 2021 - September - 18
 Copyright   : None
 Description : Password generator main program source
 ============================================================================
 */


/* Include ------------------------------------------------------------------*/
#include "main.h"


/* Define -------------------------------------------------------------------*/
#define UNUSED_VARIABLE(x) (x = x)

#define DEFAULT_PASSWORD_LEN   32  /* 32 characters length by default */
#define MAX_PASSWORD_LEN      512  /* 512 characters length maximum */

#define DEFAULT_PASSWORD_NUM    4  /* Generate 4 passwords by default */
#define MAX_PASSWORD_NUM      512  /* 512 passwords maximum to generate */

#define DEFAULT_USE_DECIMAL_CHARACTERS                0
#define DEFAULT_USE_HEXADECIMAL_CHARACTERS            1  /* Use Hex by default */
#define DEFAULT_USE_UPPERCASE_LETTERS                 0
#define DEFAULT_USE_LOWERCASE_LETTERS                 0
#define DEFAULT_USE_SPECIAL_CHARACTERS                0
#define DEFAULT_USE_CUSTOM_LIST                       0

#define EXTENDED_BUFFER_SIZE    0x100000  /* 1 MByte buffer */


/* Global variables ---------------------------------------------------------*/

const uint8_t SpecialCharacterList[] =
{
  '<', '>', '?', ',', '.', ';', ':', '|',
  '!', '%', '&', '#', '{', '}', '(', ')',
  '[', ']', '-', '_', '@', '+', '='
};

const uint8_t ExcludeSimilarCharacterList[] =
{
  'i', 'l', '1', 'L', 'o', 'O', '0', 'Q',
  'I', '|'
};


/* Functions ----------------------------------------------------------------*/


/*
 * @brief : Main program of "Password_Generator" application
 *
 * @param argc : Number of arguments in the call command line
 *
 * @param argv : Pointer to call command line arguments
 *
 * @return 0 Execution correct
 *         Others = Execution error
 *
 */
int main(int argc, char *argv[])
{
  uint32_t   i = 0;
  time_t     rawtime;
  struct     tm * timeinfo = NULL;
  uint32_t   PasswordOptionsSet       = 0;
  uint32_t   PasswordLengthOptionsSet = 0;
  uint32_t   PasswordNumberOptionsSet = 0;
  uint32_t   UseDecNumbers            = 0;
  uint32_t   UseHexNumbers            = 0;
  uint32_t   UseLettersUpperCase      = 0;
  uint32_t   UseLettersLowerCase      = 0;
  uint32_t   UseSpecialCharacters     = 0;
  uint32_t   UseCustomList            = 0;
  uint32_t   ExcludeSimilarCharacters = 0;
  uint32_t   PasswordLength           = 0;
  uint32_t   NbOfPasswordToGenerate   = 0;
  uint8_t    BufferCharactersList[512] = {0};  /* 512 bytes should be enough to store the entire character list, increase if necessary */
  uint32_t   BufferCharactersLen = 0;
  uint8_t    GeneratedPassword[MAX_PASSWORD_LEN + 1] = {0};
  uint8_t    CustomListBuffer[256 + 1] = {0};
  uint32_t   CustomListLen = 0;
  uint8_t  * BufferCharactersListExtended = NULL;  /* The pointer where EXTENDED_BUFFER_SIZE byte will be allocated */
  uint32_t   RandomIndex = 0;
  uint8_t    TempByte = 0;
  int Temp = 0;
  int c;

  /* Init the password library */
  InitPasswordLib();

  /* Get the current time */
  time(&rawtime);
  timeinfo = localtime(&rawtime);

  /* Print the current time */
  printf("[%04d-%02d-%02d %02d:%02d:%02d] ", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1,
         timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

  printf("Launching the program\n");
  fflush(stdout);

  while ((c = getopt (argc, argv, "hl:n:HDULSC:E")) != -1)
  {
    opterr = 0;
    switch (c)
    {
      /* -h : Help */
      case 'h':
      {
        usage();
        exit(0);
      }

      /* -l : Password length */
      case 'l':
      {
        /* Get the password length */
        Temp = 0;
        sscanf(optarg, "%i", &Temp);

        if((Temp > 0) && (Temp <= MAX_PASSWORD_LEN))
        {
          PasswordLength = Temp;
          PasswordLengthOptionsSet = 1;

          /* Print the current time */
          printf("[%04d-%02d-%02d %02d:%02d:%02d] ", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1,
                 timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

          printf("Password length = %u characters\n", PasswordLength);
          fflush(stdout);
        }
        else
        {
          /* Print the current time */
          printf("[%04d-%02d-%02d %02d:%02d:%02d] ", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1,
                 timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

          printf("The password length is incorrect (%s), use the default length : %u\n", optarg, DEFAULT_PASSWORD_LEN);
          fflush(stdout);
        }

        break;
      }

      /* -n : Number of password to generate */
      case 'n':
      {
        /* Get the password length */
        Temp = 0;
        sscanf(optarg, "%i", &Temp);

        if((Temp > 0) && (Temp <= MAX_PASSWORD_NUM))
        {
          NbOfPasswordToGenerate = Temp;
          PasswordNumberOptionsSet = 1;

          /* Print the current time */
          printf("[%04d-%02d-%02d %02d:%02d:%02d] ", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1,
                 timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

          printf("Number of password to generate = %u\n", NbOfPasswordToGenerate);
          fflush(stdout);
        }
        else
        {
          /* Print the current time */
          printf("[%04d-%02d-%02d %02d:%02d:%02d] ", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1,
                 timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

          printf("The number of password to generate is incorrect (%s), use the default length : %u\n", optarg, DEFAULT_PASSWORD_NUM);
          fflush(stdout);
        }

        break;
      }

      /* -H : Use Hexadecimal characters */
      case 'H':
      {
        UseHexNumbers = 1;
        PasswordOptionsSet = 1;

        /* Print the current time */
        printf("[%04d-%02d-%02d %02d:%02d:%02d] ", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1,
               timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

        printf("Use hexadecimal numbers [0..9][A..Z] to generate password(s)\n");
        fflush(stdout);
        break;
      }

      /* -D : Use Decimal characters */
      case 'D':
      {
        UseDecNumbers = 1;
        PasswordOptionsSet = 1;

        /* Print the current time */
        printf("[%04d-%02d-%02d %02d:%02d:%02d] ", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1,
               timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

        printf("Use decimal numbers [0..9] to generate password(s)\n");
        fflush(stdout);
        break;
      }

      /* -U : Use Uppercase letters */
      case 'U':
      {
        UseLettersUpperCase = 1;
        PasswordOptionsSet = 1;

        /* Print the current time */
        printf("[%04d-%02d-%02d %02d:%02d:%02d] ", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1,
               timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

        printf("Use uppercase letters [A..Z] to generate password(s)\n");
        fflush(stdout);
        break;
      }

      /* -L : Use Lowercase letters */
      case 'L':
      {
        UseLettersLowerCase = 1;
        PasswordOptionsSet = 1;

        /* Print the current time */
        printf("[%04d-%02d-%02d %02d:%02d:%02d] ", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1,
               timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

        printf("Use lowercase letters [a..z] to generate password(s)\n");
        fflush(stdout);
        break;
      }

      /* -S : Use Special letters */
      case 'S':
      {
        UseSpecialCharacters = 1;
        PasswordOptionsSet = 1;

        /* Print the current time */
        printf("[%04d-%02d-%02d %02d:%02d:%02d] ", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1,
               timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

        printf("Use special characters to generate password(s)\n");
        fflush(stdout);
        break;
      }

      /* -C : Use custom list */
      case 'C':
      {
        CustomListLen = strlen(optarg);
        if(CustomListLen > 0)
        {
          UseCustomList = 1;
          PasswordOptionsSet = 1;

          /* Prevent any overflow */
          if(CustomListLen >= (sizeof(CustomListBuffer) - 1))
          {
            /* Print the current time */
            printf("[%04d-%02d-%02d %02d:%02d:%02d] ", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1,
                   timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

            printf("Warning ! Custom list is too long (%u ASCII characters), use a truncated list with %lu ASCII characters\n", CustomListLen, (long unsigned int)sizeof(CustomListBuffer) - 1);

            /* Limit the length of the custom list */
            CustomListLen = sizeof(CustomListBuffer) - 1;
          }

          /* Copy the custom list */
          memset(CustomListBuffer, 0, sizeof(CustomListBuffer));
          memcpy(CustomListBuffer, optarg, CustomListLen);

          /* Print the current time */
          printf("[%04d-%02d-%02d %02d:%02d:%02d] ", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1,
                 timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

          printf("Use custom list to generate password(s) : \"%s\"\n", CustomListBuffer);
          fflush(stdout);
        }
        break;
      }

      /* -E : Exclude similar characters (i, l, 1, L, o, 0, O, Q, |) */
      case 'E':
      {

        ExcludeSimilarCharacters = 1;

        /* Print the current time */
        printf("[%04d-%02d-%02d %02d:%02d:%02d] ", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1,
               timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

        printf("Exclude similar characters : i, l, 1, L, o, 0, O, Q, I, |\n");
        fflush(stdout);

        break;
      }

      default:
      {
        usage();
        exit(0);
      }
    }
  }

  /* If no password length has been set, configure default value */
  if(PasswordLengthOptionsSet == 0)
  {
    /* Get the current time */
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    /* Print the current time */
    printf("[%04d-%02d-%02d %02d:%02d:%02d] ", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1,
           timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

    printf("No password length set, use default value : %u character(s)\n", DEFAULT_PASSWORD_LEN);
    fflush(stdout);

    /* Set default password length value */
    PasswordLength = DEFAULT_PASSWORD_LEN;
  }

  /* If no password number has been set, configure default value */
  if(PasswordNumberOptionsSet == 0)
  {
    /* Get the current time */
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    /* Print the current time */
    printf("[%04d-%02d-%02d %02d:%02d:%02d] ", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1,
           timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

    printf("No password number set, use default value : %u password(s) to generate\n", DEFAULT_PASSWORD_NUM);
    fflush(stdout);

    /* Set default number of password to generate */
    NbOfPasswordToGenerate = DEFAULT_PASSWORD_NUM;
  }

  /* If no password options has been set, configure default values */
  if(PasswordOptionsSet == 0)
  {
    /* Get the current time */
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    /* Print the current time */
    printf("[%04d-%02d-%02d %02d:%02d:%02d] ", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1,
           timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

    printf("No option set, use default options\n");
    fflush(stdout);

    /* Set default options */
    UseDecNumbers        = DEFAULT_USE_DECIMAL_CHARACTERS;
    UseHexNumbers        = DEFAULT_USE_HEXADECIMAL_CHARACTERS;
    UseLettersUpperCase  = DEFAULT_USE_UPPERCASE_LETTERS;
    UseLettersLowerCase  = DEFAULT_USE_LOWERCASE_LETTERS;
    UseSpecialCharacters = DEFAULT_USE_SPECIAL_CHARACTERS;
    UseCustomList        = DEFAULT_USE_CUSTOM_LIST;

    if(UseDecNumbers) printf("[%04d-%02d-%02d %02d:%02d:%02d] Use decimal characters [0..9]\n", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    if(UseHexNumbers) printf("[%04d-%02d-%02d %02d:%02d:%02d] Use hexadecimal characters [0..9][A..F]\n", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    if(UseLettersUpperCase) printf("[%04d-%02d-%02d %02d:%02d:%02d] Use uppercase letters [A..F]\n", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    if(UseLettersLowerCase) printf("[%04d-%02d-%02d %02d:%02d:%02d] Use lowercase letters [a..f]\n", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    if(UseSpecialCharacters) printf("[%04d-%02d-%02d %02d:%02d:%02d] Use special characters\n", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    if(UseCustomList) printf("[%04d-%02d-%02d %02d:%02d:%02d] Use custom list\n", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    fflush(stdout);
  }


  /* ----------------------------------------------------------------------- */
  /* ----------------------------------------------------------------------- */
  /* ----------------------------------------------------------------------- */
  /* ----------------------------------------------------------------------- */


  memset(BufferCharactersList, 0, sizeof(BufferCharactersList));
  BufferCharactersLen = 0;

  /* Fill the character buffer with decimal numbers */
  if(UseDecNumbers)
  {
    /* Fill '0' to '9' */
    for(i = 0; i < 10; i++)
    {
      if(ExcludeSimilarCharacters && IsCharacterExcluded(i + '0'))
      {
        /* Character excluded, nothing to do */
      }
      else
      {
        BufferCharactersList[BufferCharactersLen] = i + '0';

        /* Prevent any overflow */
        BufferCharactersLen = (BufferCharactersLen + 1) % sizeof(BufferCharactersList);
      }
    }
  }


  /* Fill the character buffer with hexadecimal characters */
  if(UseHexNumbers)
  {
    /* Fill '0' to '9' */
    for(i = 0; i < 10; i++)
    {
      if(ExcludeSimilarCharacters && IsCharacterExcluded(i + '0'))
      {
        /* Character excluded, nothing to do */
      }
      else
      {
        BufferCharactersList[BufferCharactersLen] = i + '0';

        /* Prevent any overflow */
        BufferCharactersLen = (BufferCharactersLen + 1) % sizeof(BufferCharactersList);
      }
    }

    /* Fill 'A' to 'F' */
    for(i = 0; i < 6; i++)
    {
      if(ExcludeSimilarCharacters && IsCharacterExcluded(i + 'A'))
      {
        /* Character excluded, nothing to do */
      }
      else
      {
        BufferCharactersList[BufferCharactersLen] = i + 'A';

        /* Prevent any overflow */
        BufferCharactersLen = (BufferCharactersLen + 1) % sizeof(BufferCharactersList);
      }
    }
  }


  /* Fill the character buffer with uppercase letters */
  if(UseLettersUpperCase)
  {
    /* Fill 'A' to 'Z' */
    for(i = 0; i < 26; i++)
    {
      if(ExcludeSimilarCharacters && IsCharacterExcluded(i + 'A'))
      {
        /* Character excluded, nothing to do */
      }
      else
      {
        BufferCharactersList[BufferCharactersLen] = i + 'A';

        /* Prevent any overflow */
        BufferCharactersLen = (BufferCharactersLen + 1) % sizeof(BufferCharactersList);
      }
    }
  }


  /* Fill the character buffer with uppercase letters */
  if(UseLettersLowerCase)
  {
    /* Fill 'a' to 'z' */
    for(i = 0; i < 26; i++)
    {
      if(ExcludeSimilarCharacters && IsCharacterExcluded(i + 'a'))
      {
        /* Character excluded, nothing to do */
      }
      else
      {
        BufferCharactersList[BufferCharactersLen] = i + 'a';

        /* Prevent any overflow */
        BufferCharactersLen = (BufferCharactersLen + 1) % sizeof(BufferCharactersList);
      }
    }
  }

  /* Fill the character buffer with special characters */
  if(UseSpecialCharacters)
  {
    for(i = 0; i < sizeof(SpecialCharacterList); i++)
    {
      if(ExcludeSimilarCharacters && IsCharacterExcluded(SpecialCharacterList[i]))
      {
        /* Character excluded, nothing to do */
      }
      else
      {
        BufferCharactersList[BufferCharactersLen] = SpecialCharacterList[i];

        /* Prevent any overflow */
        BufferCharactersLen = (BufferCharactersLen + 1) % sizeof(BufferCharactersList);
      }
    }
  }

  /* Fill the character buffer with custom list ASCII characters */
  if(UseCustomList)
  {
    for(i = 0; i < CustomListLen; i++)
    {
      if(ExcludeSimilarCharacters && IsCharacterExcluded(CustomListBuffer[i]))
      {
        /* Character excluded, nothing to do */
      }
      else
      {
        BufferCharactersList[BufferCharactersLen] = CustomListBuffer[i];

        /* Prevent any overflow */
        BufferCharactersLen = (BufferCharactersLen + 1) % sizeof(BufferCharactersList);
      }
    }
  }

  /* ----------------------------------------------------------------------- */
  /* ----------------------------------------------------------------------- */
  /* ----------------------------------------------------------------------- */
  /* ----------------------------------------------------------------------- */


  /* Allocate a new buffer with higher place */
  BufferCharactersListExtended = malloc(EXTENDED_BUFFER_SIZE * sizeof(uint8_t));

  /* Check the memory allocation result */
  if(BufferCharactersListExtended == NULL)
  {
    /* Get the current time */
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    /* Print the current time */
    printf("[%04d-%02d-%02d %02d:%02d:%02d] ", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1,
           timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

    printf("Error when allocating memory, exits the program\n");
    fflush(stdout);
    exit(0);
  }

  /* Fill the extended buffer */
  for(i = 0; i < EXTENDED_BUFFER_SIZE; i++)
  {
    BufferCharactersListExtended[i] = BufferCharactersList[i % BufferCharactersLen];
  }

  /* Init the pseudo random generator */
  srand(time(NULL));

  /* Make some permutations on the extended buffer */
  for(i = 0; i < EXTENDED_BUFFER_SIZE; i++)
  {
    /* Generate a random index */
    RandomIndex = rand() % EXTENDED_BUFFER_SIZE;

    /* Permute values */
    TempByte = BufferCharactersListExtended[RandomIndex];
    BufferCharactersListExtended[RandomIndex] = BufferCharactersListExtended[i];
    BufferCharactersListExtended[i] = TempByte;
  }


  /* ----------------------------------------------------------------------- */
  /* ----------------------------------------------------------------------- */
  /* ----------------------------------------------------------------------- */
  /* ----------------------------------------------------------------------- */


  /* Generate all passwords */
  for(i = 0; i < NbOfPasswordToGenerate; i++)
  {
    /* Generates a password */
    GeneratePassword(PasswordLength, BufferCharactersListExtended, EXTENDED_BUFFER_SIZE, GeneratedPassword);

    /* Get the current time */
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    /* Print the current time */
    printf("[%04d-%02d-%02d %02d:%02d:%02d] ", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1,
           timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

    printf("Password generated #%03u = %s\n", i + 1, GeneratedPassword);
    fflush(stdout);
  }


  /* ----------------------------------------------------------------------- */
  /* ----------------------------------------------------------------------- */
  /* ----------------------------------------------------------------------- */
  /* ----------------------------------------------------------------------- */

  /* Free memory */
  if(BufferCharactersListExtended) free(BufferCharactersListExtended);

  /* Get the current time */
  time(&rawtime);
  timeinfo = localtime(&rawtime);

  /* Print the current time */
  printf("[%04d-%02d-%02d %02d:%02d:%02d] ", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1,
         timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

  printf("Exiting the program\n");
  fflush(stdout);

  return EXIT_SUCCESS;
} /* End main() */


/*
 * @brief : Check if the character must be excluded
 *
 * @param Character : The byte/character to check
 *
 * @return 1 = Character must be excluded
 *         0 = Character is valid
 *
 */
uint32_t IsCharacterExcluded(uint8_t Character)
{
  uint32_t FlagCharExcluded = 0;
  uint32_t i;

  /* Parse all list of excluded characters */
  for(i = 0; i < sizeof(ExcludeSimilarCharacterList); i++)
  {
    if((ExcludeSimilarCharacterList[i] & 0xFF) == (Character & 0xFF))
    {
      FlagCharExcluded = 1;
      break;
    }
  }

  return FlagCharExcluded;
} /* End IsCharacterExcluded() */


/*
 * @brief : Displays all options / arguments of the current program
 *
 * @param None
 *
 * @return None
 *
 */
void usage(void)
{
  printf("Password_Generator [options] :\n");
  printf("-h          : Display help / argument list / usage\n");
  printf("-l <length> : Password Length (character number) [1..64] - Default = %u characters\n", DEFAULT_PASSWORD_LEN);
  printf("-n <number> : Number of password to generate [1..100] - Default = %u passwords\n", DEFAULT_PASSWORD_NUM);
  printf("-H          : Use hexadecimal characters [0..9][A..F] - Default\n");
  printf("-D          : Use decimal characters [0..9]\n");
  printf("-U          : Use uppercase letters characters [A..Z]\n");
  printf("-L          : Use lowercase letters characters [a..z]\n");
  printf("-S          : Use special letters characters \"<>?,.;:!%%&#{}()[]-_@+=|\"\n");
  printf("-C \"List\"   : Use a custom ASCII list of characters (up to 256 characters in the list)\n");
  printf("-E          : Exclude similar characters (i, l, 1, L, o, 0, O, Q, I, |)\n");
  printf("\n");
  fflush(stdout);
} /* End usage() */


/* End of file */

