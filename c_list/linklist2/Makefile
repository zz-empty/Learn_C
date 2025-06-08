# 生成一个可执行文件
CC := gcc
srcs := $(wildcard *.c)
exe := main


# 生成规则（添加目录依赖）
$(exe):$(srcs)
	$(CC) $^ -o $@


.PHONY: clean rebuild
clean:
	$(RM) $(exe)
rebuild: clean all
