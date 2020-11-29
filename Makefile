CC=gcc
CFLAGS=-lm -std=c99 -pedantic -Wall -Wextra -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition
LDFLAGS=
FILES=src/helper.c src/parser.c src/lexer.c src/variable.c
PREFIX=/usr/local
ifndef NAME
    NAME=quich
endif

all: quich

quich: $(FILES)
	$(CC) -o $(NAME) $(FILES) src/quich.c $(CFLAGS) $(LDFLAGS)

install: quich
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp $(NAME) $(DESTDIR)$(PREFIX)/bin/$(NAME)

test:
	$(CC) -o quich_test $(FILES) tests/main.c -lm

clean:
	$(RM) $(NAME)
