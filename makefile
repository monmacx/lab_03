CFLAGS=-c -Wall
CROSS_COMPILE=
CC=$(CROSS_COMPILE)gcc

all:
	make server
	make client

server:
	$(CROSS_COMPILE)$(CC) -lpthread file_sender.c file_read.c server.c -o server

client:
	$(CROSS_COMPILE)$(CC) client.c -o client

rebuild:
	make clean
	make

clean: 
	rm -rf *o server client