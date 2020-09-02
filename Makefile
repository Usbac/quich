CC=gcc
CFLAGS=-lm -std=c99 -pedantic -Wall -Wextra -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition
FILES=src/main.c src/helper.c src/parser.c src/lexer.c src/variable.c
PREFIX=/usr/local
ifndef NAME
    NAME=quich
endif

all: quich

quich: $(FILES)
	$(CC) -o $(NAME) $(FILES) $(CFLAGS)

install: quich
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp $< $(DESTDIR)$(PREFIX)/bin/$(NAME)

clean:
	rm $(NAME)
