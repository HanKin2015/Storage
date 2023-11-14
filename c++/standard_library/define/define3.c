/*******************************************************************************
* 文 件 名: define3.c
* 文件描述: 第一次见的写法，学习学习
* 作    者: HanKin
* 创建日期: 2023.11.10
* 修改日期：2023.11.10
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/

#include <stdio.h>

struct NAMEMAP {
    int value;
    const char *name;
};

#define MACRONAME(m) #m

#define FILE_DEVICE_MIDI_IN             0x0000000d
#define FILE_DEVICE_MIDI_OUT            0x0000000e
#define FILE_DEVICE_MOUSE               0x0000000f

#define GENNAMEMAP(m) {m, #m}

#if !defined(_countof)
#define _countof(_Array) (sizeof(_Array) / sizeof(_Array[0]))
#endif

struct NAMEMAP g_file_name[] =
{
	GENNAMEMAP(FILE_DEVICE_MIDI_IN),
	GENNAMEMAP(FILE_DEVICE_MIDI_OUT),
	GENNAMEMAP(FILE_DEVICE_MOUSE),
};

int main(int argc, char *argv[])
{
    for (int i = 0; i < _countof(g_file_name); i++) {
        printf("%08x: %s\n", g_file_name[i].value, g_file_name[i].name);
        printf("name: %s\n", MACRONAME(FILE_DEVICE_MIDI_IN));
    }
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
0000000d: FILE_DEVICE_MIDI_IN
name: FILE_DEVICE_MIDI_IN
0000000e: FILE_DEVICE_MIDI_OUT
name: FILE_DEVICE_MIDI_IN
0000000f: FILE_DEVICE_MOUSE
name: FILE_DEVICE_MIDI_IN
*/