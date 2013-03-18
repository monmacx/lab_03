CFLAGS=-c -Wall
CROSS_COMPILE=
CC=$(CROSS_COMPILE)gcc

all:
	make server
	make client

server:
	$(CROSS_COMPILE)$(CC) server.c -o server

client:
	$(CROSS_COMPILE)$(CC) client.c -o client

rebuild:
	make clean
	make

clean: 
	rm -rf *o server client