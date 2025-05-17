CC := gcc
SRCS := $(wildcard *.c)
EXE  := $(addprefix bin/, $(basename $(SRCS)))
OBJS := $(addprefix objs/, $(SRCS:.c=.o))

all: create_dirs $(EXE)

# 创建输出目录（order-only 依赖，目录存在即不重复创建）
create_dirs:
	@mkdir -p bin objs

# 生成可执行文件：从 objs/xxx.o 生成 bin/xxx
bin/%: objs/%.o | create_dirs
	$(CC) $< -o $@

# 生成目标文件：从 xxx.c 生成 objs/xxx.o
objs/%.o: %.c | create_dirs
	$(CC) -c $< -o $@

.PHONY: all clean rebuild create_dirs

clean:
	rm -rf bin objs

rebuild: clean all
