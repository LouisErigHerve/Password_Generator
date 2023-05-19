# sudo apt-get update
# sudo apt-get install make gcc
#
# Call this script with the following syntax:
# Standard GCC
# make all clean
#
# Compiling with MinGW32 GCC (by using Cygwin on Windows)
# make SPECIFIC_CC=i686-w64-mingw32-gcc specific_gcc clean
#
# Compiling with MinGW64 GCC (by using Cygwin on Windows)
# make SPECIFIC_CC=x86_64-w64-mingw32-gcc specific_gcc clean
#

CC = gcc
#CC = x86_64-w64-mingw32-gcc
#CC = i686-w64-mingw32-gcc

CFLAGS = -O3 -Wall -c -fmessage-length=0 -std=c99 -o

all:
	$(CC) $(CFLAGS) main.o main.c
	$(CC) $(CFLAGS) password_lib.o password_lib.c
	$(CC) $(CFLAGS) getopt.o getopt.c
	$(CC) -o Password_Generator password_lib.o getopt.o main.o

specific_gcc:
	$(SPECIFIC_CC) $(CFLAGS) main.o main.c
	$(SPECIFIC_CC) $(CFLAGS) password_lib.o password_lib.c
	$(SPECIFIC_CC) $(CFLAGS) getopt.o getopt.c
	$(SPECIFIC_CC) -o Password_Generator password_lib.o getopt.o main.o

clean:
	rm -rf *.o
