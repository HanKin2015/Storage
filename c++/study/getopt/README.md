# getopt()函数详解

## 1、函数原型
```
#include <unistd.h>
int getopt(int argc, char * const argv[], const char *optstring);

#include <getopt.h>
int getopt_long(int argc, char * const argv[],
          const char *optstring,
          const struct option *longopts, int *longindex);
int getopt_long_only(int argc, char * const argv[],
          const char *optstring,
          const struct option *longopts, int *longindex);
```

## 2、参数
| 参数      | 含义                                                         |
| --------- | ------------------------------------------------------------ |
| argc      | 命令参数选项个数。执行命令时调用main函数，并从main函数传入   |
| argv      | 命令行参数选项内容                                           |
| optstring | 命令所支持的**选项字符的集合**，通常为一个字符串 例如：命令ls -la，参数为la，optstring可以为“la”， 后面会详细讲述optstring格式与含义 |

## 3、返回值
备注1：该函数调用时需要在循环中进行调用，故每循环调用一次都会有一个返回值。
备注2：返回值为int类型，因为每个字符其实本身也是对应一个int值的，故虽然为int型，返回值可以是一个字符。
| 返回值       | 含义                                                         |
| ------------ | ------------------------------------------------------------ |
| -1           | 当返回-1表示argv中的参数已经全部解析完成。（即：命令传入的参数） |
| 参数选项字符 | 解析出命令的【参数选项字符】，若该选项带有参数，则全局变量optarg会指向该参数。 |
| ？           | 表示传入的参数不合法。即：不是optstring字符串中指定的【选项字符】 |
| ：           |                                                              |

## 4、ptstring参数详解
形参含义：
**optstring表示命令参数选项的集合，用字符串表示，字符串中的每一个字符表示一个合法选项。**
```c
例如：某个命令cmd支持选项-a -b -c -d -e -f -g，则形参optstring可以是:
"abcdefg"
12
```

**一个完整的optstring字符串由【字符】、【冒号】、【双冒号】组成，其中冒号和双冒号非必定出现。**
```c
例如，下面形参optstring都是合法的：
"abcdefg"
"ab:cd::efg"
"a:bcde::fg::"
1234
```

**【冒号】or【双冒号】是跟随在选项字符后面的，表示该选项是否带有参数。具体含义见下表格**
| 字符后面是否有冒号 | 具体含义                                           |
| ------------------ | -------------------------------------------------- |
| 无冒号             | 该选项不带参数，直接使用即可，格式为 cmd [-option] |
| 单冒号             | 该选项后必须带有参数，格式为 cmd [-option] [para]  |
| 双冒号             | 该选项后可以有参数，也可以无参数                   |

```
例如：
    当optstring为 "a:bde::f" 时，
表示：
    命令有abdefg几个选项，
其中：
    a 后有一个单冒号，所以必须跟有参数，不跟参数会报错。使用格式为  cmd -a para 或 cmd -apara（注意：选项跟参数之间可以有空格，可以没有空格，这点一定要跟双冒号区分开）
    bdf 后没有冒号，所以无参数，直接使用即可，格式为  cmd -b -d -f 或 cmd -bdf（可以连在一起写）
    e 后面有双冒号，表示选项e后面参数可有可无。使用格式为  cmd -e 或 cmd -epara（注意：当有参数时参数跟选项之间必须保持相连，没有空格！否则会报错）
```
注意选项都是单个字符。

## 5、4个全局变量
库中定义了4个全局变量跟该函数息息相关（**这些全局变量我们可以直接使用**）：
```c
extern char *optarg;
extern int optind, opterr, optopt;
12
```

当调用该函数的时候，会根据不同的结果对下面四个全局变量进行对应置位：

| 变量名 | 含义                      | 置位场景                                                     |
| ------ | ------------------------- | ------------------------------------------------------------ |
| optarg | 指向当前选项对应的参数    | 例如命令：cmd -a apara 当解析到参数-a时，则optarg指向字符串"apara" |
| optind | 用于记录下一次调用getopt()或getopt_long()函数时应该从哪个命令行参数开始解析 |  初始值为1，表示从第一个命令行参数开始解析。       |
| opterr | 是否将错误log打印到stderr | 该变量默认值为1，即：默认会将错误日志打印到stderr。 当我们不想看到终端上打印错误日志，可以将该变量赋值为0 |
| optopt | 保存无法识别的选项        | 当解析命令选项时，发现某个选项不能识别，则保存该选项到optopt中，并将错误信息打印到opterr中。 |

## 6、getopt()和getopt_long()区别
getopt()和getopt_long()都是用于解析命令行参数的函数，但它们有以下区别：
- 参数形式不同：getopt()只能处理短选项（如-a），而getopt_long()可以处理短选项和长选项（如--all）。
- 参数个数不同：getopt()只能处理单个字符的短选项，而getopt_long()可以处理任意长度的短选项和长选项。
- 错误处理不同：getopt()在遇到无效选项时会返回'?'，而getopt_long()可以通过设置错误处理回调函数来自定义错误处理方式。
- 使用方式不同：getopt()使用起来比较简单，但对于复杂的命令行参数解析，getopt_long()更加灵活和方便。
综上所述，如果需要处理复杂的命令行参数，建议使用getopt_long()函数。如果只需要处理简单的短选项，可以使用getopt()函数。

## 7、getopt_long()和getopt_long_only()区别
getopt_long()和getopt_long_only()都是用于解析命令行参数的函数，它们有以下区别：
- 处理方式不同：getopt_long()可以处理短选项和长选项，而getopt_long_only()只能处理长选项。
- 参数形式不同：getopt_long()使用的长选项形式为--option，而getopt_long_only()可以接受两种形式的长选项，即--option和-option。
- 错误处理不同：getopt_long()在遇到无效选项时会返回'?'，而getopt_long_only()在遇到无效选项时会返回'?'或'-'，具体取决于选项的形式。
综上所述，如果需要处理短选项和长选项，建议使用getopt_long()函数。如果只需要处理长选项，并且希望接受两种形式的长选项，可以使用getopt_long_only()函数。

## 8、实战
代码见：D:\Github\Storage\c++\study\getopt\getopt_long_example.c

注意：长选项一定需要--两个横线，因为短选项可以合并成一个类似长选项，导致区分不出来。



