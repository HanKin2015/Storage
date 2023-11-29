VERSION   = 1.00                            # 程序版本
CC        = gcc                             # 编译器选择
DEBUG     = -DUSE_DEBUG                     # 宏定义
CFLAGS    = -Wall                           # 编译选项
SOURCES   = $(wildcard ./source/*.c)        # 源文件
INCLUDES  = -I./include                     # 头文件
LIB_NAMES = -lfun_a -lfun_so                # 库文件名称
LIB_PATH  = -L./lib                         # 库文件路径
OBJ       = $(patsubst %.c, %.o, $(SOURCES))# 目标文件
TARGET    = app                             # 执行文件

# 链接
$(TARGET):$(OBJ)
		@mkdir -p output
		$(CC) $(OBJ) $(LIB_PATH) $(LIB_NAMES) -o output/$(TARGET)$(VERSION)
		@rm -rf $(OBJ)
 
# 编译
%.o: %.c
		$(CC) $(INCLUDES) $(DEBUG) -c $(CFLAGS) $< -o $@

# 清除编译信息
.PHONY:clean
clean:
		@echo "Remove linked and compiled files......"
		rm -rf $(OBJ) $(TARGET) output