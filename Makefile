CC = gcc
CFLAGS += -O2 -Wall -Wextra -Werror -pipe -ggdb3 -std=gnu99 -march=native
CPPFLAGS += -D_GNU_SOURCE=1

all: p001 p002

clean:
	rm -f *.o p001 p002

.PHONY: clean all
