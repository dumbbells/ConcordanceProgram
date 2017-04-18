CC = gcc
CFFLAGS = -g
RM = rm -f
default: all

all: concordance

concordance: proj2.c
	$(CC) $(CFLAGS) -w -o proj2 proj2.c
