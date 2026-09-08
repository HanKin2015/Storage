
LOCAL_PATH := $(call my-dir)

# 1. 编译共享库 libtest.so (带 -Bsymbolic)

include $(CLEAR_VARS)
LOCAL_MODULE    := test_shared
LOCAL_SRC_FILES := test.c
LOCAL_CFLAGS    := -fPIC
LOCAL_CFLAGS    += -O2 -g

# 关键：强制共享库内部符号自包含

LOCAL_LDFLAGS   := -Wl,-Bsymbolic

# 如果上面不行，试试这个更强的隔离：

# LOCAL_LDFLAGS += -Wl,--version-script=$(LOCAL_PATH)/symbol.map

include $(BUILD_SHARED_LIBRARY)

# 2. 编译静态库 libtest.a

include $(CLEAR_VARS)
LOCAL_MODULE    := test_static
LOCAL_SRC_FILES := test.c

# 静态库不需要特殊标志

include $(BUILD_STATIC_LIBRARY)

# 3. 编译主程序 (同时链接静态和动态)

include $(CLEAR_VARS)
LOCAL_MODULE    := main_test
LOCAL_SRC_FILES := main.c
LOCAL_STATIC_LIBRARIES := test_static
LOCAL_SHARED_LIBRARIES := test_shared
LOCAL_LDLIBS    := -llog -ldl

# 关键：确保链接顺序是先动态后静态（虽然 ndk-build 会自动处理依赖，但我们可以强制）

# 如果需要精细控制，可以用 LOCAL_LDFLAGS 手动指定顺序，但通常上面的声明就够了

include \((BUILD_EXECUTABLE)