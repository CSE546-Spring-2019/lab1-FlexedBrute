#makefile for lab1.c

CC=gcc
CGLAGS = -g -Wall

all: count

count: lab1.c
	$(CC) $(CFLAGS) -o count lab1.c

clean:
	rm count