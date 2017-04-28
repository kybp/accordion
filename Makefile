CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c89
LDFLAGS = -lcurses
COMPILE = gcc $(CFLAGS) -c
LINK = gcc
SRC = src

accordion:	util.o cards.o accordion.o
	$(LINK) $^ $(LDFLAGS) -o $@

accordion.o: $(SRC)/accordion.c
	$(COMPILE) $^

cards.o:	$(SRC)/cards.h $(SRC)/cards.c
	$(COMPILE) $(SRC)/cards.c

util.o:	$(SRC)/util.h $(SRC)/util.c
	$(COMPILE) $(SRC)/util.c

clean:
	rm -f accordion *.o
