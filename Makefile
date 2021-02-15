CFLAGS=-Wall -Wextra -Werror -pedantic -std=c11
OBJFILES = cs50.o program.o
TARGET=program

.PHONY: compile
compile:
	gcc $(CFLAGS) -c lib/cs50.c 
	gcc $(CFLAGS) -c program.c
	gcc $(CFLAGS) -o $(TARGET) $(OBJFILES) 
	rm $(OBJFILES)

.PHONY: clean
clean:
	rm $(TARGET)

default: all

.PHONY: all
all: clean compile
