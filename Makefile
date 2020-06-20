CC=gcc
CFLAGS=-lm -std=c99 -pedantic -Wall -Wextra -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition
PREFIX=/usr/local
ifndef NAME
    NAME=quich
endif

all: quich

quich: src/main.c src/helper.c src/parser.c src/tokenizer.c
	$(CC) -o $(NAME) src/main.c src/helper.c src/parser.c src/tokenizer.c $(CFLAGS)

install: quich
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp $< $(DESTDIR)$(PREFIX)/bin/$(NAME)

clean:
	rm $(NAME)
