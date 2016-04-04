CC = gcc
CFLAGS += -O2 -Wall -Wextra -Werror -pipe -ggdb3 -std=gnu99 -march=native
CPPFLAGS += -D_GNU_SOURCE=1
LDFLAGS += -lm

all: p001 p002 p003

clean:
	rm -f *.o p001 p002 p003

.PHONY: clean all
