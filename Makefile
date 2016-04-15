CC = gcc
CFLAGS += -O2 -Wall -Wextra -Werror -pipe -ggdb3 -std=gnu11 -march=native
CPPFLAGS += -D_GNU_SOURCE=1
LDFLAGS += -lm

SOURCES = $(wildcard src/*.c)
PROGRAMS = $(SOURCES:%.c=%)

all: $(PROGRAMS)

test: all
	./test/test.rb

clean:
	rm -f $(PROGRAMS)

.PHONY: all test clean
