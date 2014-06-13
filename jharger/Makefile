CFLAGS=-O3 -march=native --std=c99
LDFLAGS=-O3 -march=native
EXES=hog

.PHONY: clean

all: ${EXES}

hog: hog.o

clean:
	${RM} ${EXES} *.o
