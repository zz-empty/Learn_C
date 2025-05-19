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
