# Swephelp makefile

CC = gcc
CFLAGS = -g -O9 -Wall -std=gnu99
# path to swisseph
INCS = -I. -I./src

SWHOBJ = swhdatetime.o swhformat.o swhgeo.o swhraman.o swhsearch.o swhutil.o

.c.o:
	$(CC) -c $(CFLAGS) $(INCS) $<

all: libswephelp.a

libswephelp.a: $(SWHOBJ)
	ar rcs libswephelp.a $(SWHOBJ)

clean:
	rm -f *.o libswephelp.a test

