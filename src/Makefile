# IPROPS - Input PROPerties System

TARGET = ../bin/libiprops.a

CFLAGS = -std=c99 -g -Wall -O2 -DDEBUG -I.

$(TARGET): iprops.o
	- mkdir ../bin
	ar r $@ $?

iprops.o: iprops.c iprops.h
	$(CC) -c $(CFLAGS) $*.c -o $*.o

.PHONY: clean
clean:
	rm -f $(TARGET)
	rm -f *.o
