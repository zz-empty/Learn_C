# 生成一个可执行文件
CC := gcc
srcs := $(wildcard *.c)
exe := main


# 生成规则（添加目录依赖）
bin/$(exe):$(srcs) | bin
	$(CC) $^ -o $@

# 创建 bin 目录（order-only 依赖）
bin:
	@mkdir -p bin

.PHONY: clean rebuild
clean:
	$(RM) $(exe)
rebuild: clean all
