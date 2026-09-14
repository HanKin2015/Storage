include <stdio.h>
int main ()
{
char str [100] = { 0 };
printf ("% c\n", str [0]);
if (str [0] == 0) {      // 等价于 str [0] == '\0'
printf ("str is null\n");
} else {
printf ("str is not null\n");
}
if (str == NULL) {
printf ("str is null\n");
} else {
printf ("str is not null\n");
}
char st [] = "00000";
printf ("% c\n", st [0]);
if (st [0] == 0) {
printf ("str is null\n");
} else {
printf ("str is not null\n");
}
return 0;
}
/*
10356856@hejian hj]$ ./a.out
str is null
str is not null
0
str is not null

在 C 语言里：

- `'\0'` 是**转义字符**，它的**ASCII 数值就是整数 0**。
- 字符本质就是小整数。

'\0'   // 字符，值 = 0
0      // 整数常量

所以 `str[0] == 0` 和 `str[0] == '\0'` 完全等价。
*/