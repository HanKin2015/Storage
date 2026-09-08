hejian@android-PowerEdge-R920:~/hj/point_addr_change/ndk/k\) /home/hejian/hj/NDK/android-ndk-r25c/ndk-build V=1 NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=./Android.mk

编译出来的文件运行结果是：console:/data # ./main_test
CANNOT LINK EXECUTABLE "./main_test": library "libtest_shared.so" not found
1|console:/data # export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
console:/data # ./main_test
[Main1] Initial Counter: 0 (addr: 0x85b35908)
[Static] Counter: 1 (addr: 0x85b35908)
[Shared] Counter: 1 (addr: 0xa6c306c4)
[Shared] After sleep: 1 (addr: 0xa6c306c4)
[Main] Final Counter: 1 (addr: 0x85b35908)