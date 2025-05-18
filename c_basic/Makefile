CC:=gcc
srcs:=$(wildcard *.c)
exe:=$(patsubst %.c, %, $(srcs))
obj:=$(patsubst %.c, %.o, $(srcs))

all: $(exe)

%:%.o
	$(CC) $< -o $@
%.o:%.c
	$(CC) -c $< -o $@

.PHONY:clean rebuild
clean:
	$(RM) $(exe) $(obj)
rebuild: clean all
