CFLAGS=-O3 -std=c99
CXXFLAGS=-O3
LDFLAGS=-O3
#CFLAGS=-g3 -std=c99
#LDFLAGS=-g3
EXES=hog piglets cow

.PHONY: clean

all: ${EXES}

hog: hog.o

piglets: LDFLAGS += -pthread
piglets: piglets.o

cow: cow.o
	$(CXX) $(LDFLAGS) -o $@ $^

clean:
	${RM} ${EXES} *.o
