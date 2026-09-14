HOST_TAG ?= linux-x86_64
ARCH ?= arm
API ?= 21
TRIPLE := armv7a-linux-androideabi
TOOLCHAIN := /home/hejian/hj/NDK/android-ndk-r25c/toolchains/llvm/prebuilt/$(HOST_TAG)/bin
CC := $(TOOLCHAIN)/\((TRIPLE)\)(API)-clang
CXX := \((TOOLCHAIN)/\)(TRIPLE)\((API)-clang++
CFLAGS := -O2 -fPIE
LDFLAGS := -pie
SRC := *.c
TARGET := get_usb_descriptor

all:\)(TARGET)
    \((TARGET):\)(SRC)
    $(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

clean:
    rm -rf $(TARGET)

.PHONY:all clean
