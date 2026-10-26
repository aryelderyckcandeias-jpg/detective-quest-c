CC     ?= gcc
CFLAGS ?= -std=c11 -Wall -Wextra -g

.PHONY: all run clean

all: detective_quest

detective_quest: src/detective_quest.c
	$(CC) $(CFLAGS) -o $@ $^

run: detective_quest
	./detective_quest

clean:
	rm -f detective_quest detective_quest.exe
