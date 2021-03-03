CC = gcc
CFLAGS = -Iinclude -Wall

SOURCEFILES = $(wildcard src/*.c)
OBJECTFILES = $(patsubst src/%.c, obj/%.o, $(SOURCEFILES))
HEADERFILES = $(patsubst src/%.c, include/%.h, $(SOURCEFILES))

6502: $(OBJECTFILES)
	$(CC) $^ -o bin/6502 $(CFLAGS)

headers: $(HEADERFILES)

include/%.h:
	touch $@

obj/%.o: src/%.c
	$(CC) $< -c -o $@ $(CFLAGS)

clean:
	rm obj/*
	rm bin/*.exe

cleanlogs:
	rm logs/test/*_test/*.log
	rm logs/test/*.log
	rm logs/*.log 

count: $(SOURCEFILES)
	test/counter.exe $^

counter:
	$(CC) test/main.c -o test/counter.exe
