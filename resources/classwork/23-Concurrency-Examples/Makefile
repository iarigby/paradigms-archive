SOURCES := $(shell find $(SOURCEDIR) -name '*.c')
BINARIES := $(SOURCES:%.c=%)
CC := gcc
CFLAGS := -g

all: $(BINARIES)
%: %.c
	$(CC) $(CFLAGS) -lpthread $< -o $@

clean:
	rm $(BINARIES)

.PHONY: clean
