# sudo apt-get update
# sudo apt-get install make gcc

CC = gcc
CFLAGS = -O3 -Wall -c -fmessage-length=0 -std=c99 -o

all:
	$(CC) $(CFLAGS) main.o main.c
	$(CC) $(CFLAGS) password_lib.o password_lib.c
	$(CC) -o Password_Generator password_lib.o main.o

clean:
	rm -rf *.o
