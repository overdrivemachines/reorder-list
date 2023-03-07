
# Variables to control Makefile operation

CC = g++
CFLAGS = -Wall -g

reorder-list: reorder-list.o
	$(CC) $(CFLAGS) -o reorder-list reorder-list.o

reorder-list.o: reorder-list.cpp
	$(CC) $(CFLAGS) -c reorder-list.cpp

clean:
	rm -rf reorder-list reorder-list.o
