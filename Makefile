CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c89
LDFLAGS = -lcurses
COMPILE = gcc $(CFLAGS) -c
LINK = gcc
SRC = src

solitaire:	main.o message.o cards.o accordion.o
	$(LINK) $^ $(LDFLAGS) -o $@

main.o:	$(SRC)/main.c
	$(COMPILE) $^

accordion.o: $(SRC)/accordion.c
	$(COMPILE) $^

cards.o:	$(SRC)/cards.h $(SRC)/cards.c
	$(COMPILE) $(SRC)/cards.c

message.o:	$(SRC)/message.h $(SRC)/message.c
	$(COMPILE) $(SRC)/message.c

clean:
	rm -f accordion *.o
