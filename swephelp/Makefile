# Swephelp makefile

CC = gcc
CFLAGS += -g -O9 -Wall -std=gnu99
# path to swisseph
INCS = -I. -I./libswe

SWHOBJ = swhdatetime.o swhformat.o swhgeo.o swhmisc.o swhraman.o swhsearch.o swhutil.o

.c.o:
	$(CC) -c $(CFLAGS) $(INCS) $<

all: libswephelp.a

libswephelp.a: $(SWHOBJ)
	ar rcs libswephelp.a $(SWHOBJ)

clean:
	rm -f *.o libswephelp.a

# vi: set fenc=utf-8 ff=unix et sw=4 ts=4 sts=4 :
