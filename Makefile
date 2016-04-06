CC = gcc
CFLAGS += -O2 -Wall -Wextra -Werror -pipe -ggdb3 -std=gnu99 -march=native
CPPFLAGS += -D_GNU_SOURCE=1
LDFLAGS += -lm

PROBLEMS = \
  p001 p002 p003 p004 p005 p006 p007 p008 p009 p010 \
  p011 p012 p013 p014 p015 p016 p017

all: $(PROBLEMS)

clean:
	rm -f *.o $(PROBLEMS)

.PHONY: clean all
