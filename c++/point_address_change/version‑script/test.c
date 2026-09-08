#include <stdio.h>
int g_counter = 0; // 全局变量
void increment_static () {
g_counter++;
printf ("[Static] Counter: % d (addr: % p)\n", g_counter, &g_counter);
}
void increment_shared () {
g_counter++;
printf ("[Shared] Counter: % d (addr: % p)\n", g_counter, &g_counter);
}