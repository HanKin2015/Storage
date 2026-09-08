#include <stdio.h>
#include <dlfcn.h>
extern int g_counter;
// 声明外部函数（来自静态库和共享库）
extern void increment_static ();
// 实际上，如果共享库里有 increment_shared，这里应该通过 dlopen 获取，但为了演示简化
int main () {
printf ("[Main] Initial Counter: % d (addr: % p)\n", g_counter, (void*)&g_counter);
// 调用静态链接版本的函数
increment_static ();
// 假设我们通过 dlopen 加载了一个共享库，里面调用了 increment_shared
void* handle = dlopen ("./libtest_shared.so", RTLD_NOW);
if (!handle) {
fprintf (stderr, "dlopen failed: % s\n", dlerror ());
return 1;
}
void (*shared_func)() = dlsym (handle, "increment_shared");
if (shared_func) {
shared_func (); // 调用共享库里的函数
}
// 再次检查主程序的 counter
printf ("[Main] Final Counter: % d (addr: % p)\n", g_counter, (void*)&g_counter);
dlclose (handle);
return 0;
}