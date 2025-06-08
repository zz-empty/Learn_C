# 将每个.c文件都生成一个对应的可执行文件，放在./bin目录里
CC := gcc
srcs := $(wildcard *.c)
exe := $(addprefix bin/, $(basename $(srcs)))

all: $(exe)

# 生成规则（添加目录依赖）
bin/%: %.c | bin
	$(CC) $< -o $@

# 创建 bin 目录（order-only 依赖）
bin:
	@mkdir -p bin

.PHONY: clean rebuild

clean:
	$(RM) $(exe)

rebuild: clean all
