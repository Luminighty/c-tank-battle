IDIR=./include
TARGET=bin/main

CC=gcc
CFLAGS=-I$(IDIR)
LDFLAGS=-Llibs -lraylib -lGL -lpthread -ldl -lm -lX11


DEPS=$(wildcard $(IDIR)/**/*.h)
SRCS := $(shell find src -name '*.c')
OBJS=$(patsubst src/%.c, build/%.o, $(SRCS))


.PHONY: debug release clean

debug: CFLAGS += -g -O0 -Wall -Wextra
debug: $(TARGET)

release: CFLAGS += -O2 -DNDEBUG
release: $(TARGET)


build/%.o: src/%.c $(DEPS)
	mkdir -p $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS)


$(TARGET): $(OBJS)
	mkdir -p bin
	cp -r assets bin/
	$(CC) -o $@ $^ $(LDFLAGS) $(CFLAGS)


clean:
	rm -rf build bin

