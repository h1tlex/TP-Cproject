CC=gcc
CFLAGS=-Werror -Wall

all: testpoly

testpoly: testpolygone.o polygone.o svg.o 
	$(CC) $(CFLAGS) testpolygone.o polygone.o svg.o -o testpoly

testpolygone.o: testpolygone.c polygone.h svg.h
	$(CC) $(CFLAGS) -c testpolygone.c

polygone.o: polygone.c polygone.h svg.h
	$(CC) $(CFLAGS) -c polygone.c

svg.o: svg.c svg.h
	$(CC) $(CFLAGS) -c svg.c

clean:
	rm -f *.o testpoly