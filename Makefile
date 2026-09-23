CC ?= cc
CFLAGS ?= -std=c99 -Wall -Wextra -O2

2048: 2048.c
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: run clean

run: 2048
	./2048

clean:
	rm -f 2048
