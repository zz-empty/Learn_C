CC:=gcc
srcs:=$(wildcard *.c)
exe:=$(patsubst %.c, %, $(srcs))

all:$(exe)
%:%.c
	$(CC) $^ -o $@

.PHONY: all clean rebuild
clean:
	$(RM) $(exe)
rebuild:clean all
