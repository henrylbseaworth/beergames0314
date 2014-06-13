FLAGS=-Wall -pedantic -ansi -Werror

ifndef DEBUG
	$(FLAGS)+= -g2
else
	$(FLAGS)+= -O99
endif

all:	barley-wine.c trippel.c
	gcc $(FLAGS) -o barley-wine barley-wine.c
	gcc $(FLAGS) -o trippel trippel.c

clean:
	rm *.trace
