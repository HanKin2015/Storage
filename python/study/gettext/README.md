# gettext实现中英文切换
https://pythonjishu.com/dlhmkgpbxyzrxms/

## 1、简介
gettext 是 Python 中的一个国际化（i18n）和本地化（l10n）库。它提供了一种在程序中实现多语言支持的方式。

gettext 库的主要功能是提供一个翻译函数 gettext()，它可以根据当前的语言环境将文本翻译成对应的目标语言。为了使用 gettext，你需要先创建一个翻译文件（通常是 .po 或 .mo 格式），其中包含了源语言和目标语言之间的翻译映射。然后，你可以在程序中使用 gettext() 函数来获取翻译后的文本。

## 2、gettext工具的使用
gettext 工具是一个命令行工具，用于提取源代码中的文本，并生成 .po 文件，以便进行翻译。下面是使用 gettext 工具创建翻译文件的一般步骤：

在源代码中标记需要翻译的文本：在你的源代码中，使用 gettext 提供的 _() 函数来标记需要翻译的文本。例如：
```python
print(_('Hello, world!'))
```

提取文本并生成 .pot 文件：使用 xgettext 命令来提取源代码中的文本，并生成一个 .pot 文件。.pot 文件包含了所有需要翻译的文本，但是还没有进行翻译。例如：
```bash
xgettext --output=messages.pot myapp.py
```
上面的命令将会提取 myapp.py 文件中使用 _() 函数标记的所有文本，并将其保存到 messages.pot 文件中。

创建 .po 文件：将 .pot 文件复制一份，并将其重命名为 .po 文件。例如：
```bash
cp messages.pot messages.po
```
编辑 .po 文件：使用任何文本编辑器打开 .po 文件，并为每个需要翻译的文本提供翻译。例如：
```
msgid "Hello, world!"
msgstr "Bonjour le monde!"
```
在上面的示例中，msgid 表示源语言的文本，msgstr 表示目标语言的翻译文本。

编译 .po 文件：使用 msgfmt 命令将 .po 文件编译成 .mo 文件。.mo 文件包含了翻译后的文本，可以在程序中使用。例如：
```bash
msgfmt messages.po -o messages.mo
```
上面的命令将会将 messages.po 文件编译成 messages.mo 文件。

这些是使用 gettext 工具创建翻译文件的基本步骤。你可以根据自己的需求和项目的规模来进行更复杂的国际化和本地化处理。

## 3、实战
必须要有这样的路径结构：locale\en_US\LC_MESSAGES

可以在网上下载一个gettext工具：gettext0.21-iconv1.16-static-64.exe
https://github.com/autotools-mirror/gettext
```
xgettext.exe -d <domain> -o <output_file>.po <source_file>.py
msgfmt -o <output_file>.mo <input_file>.po
```

代码见：D:\Github\Storage\python\study\gettext\main.py

## 4、再次实战（python）
项目：D:\Github\Storage\python\study\gettext\practice

- 编写程序文件main.py
- 编写翻译文件translator.py（注意有中文记得在首行# -*- coding: utf-8 -*-，另外文件字符编码得是UTF-8否则在转义成po文件时乱码）
- 安装gettext0.21-iconv1.16-static-64.exe软件，主要需要用到xgettext.exe和msgfmt.exe两个命令
- xgettext.exe -d practice -o practice.po translation.py
- 编辑practice.po文件，手动翻译内容
- msgfmt -o practice.mo practice.po
- 创建gettext要求的目录结构locale/en_US/LC_MESSAGES和locale/zh_CN/LC_MESSAGES
在实际开发中，使用到mo文件，中英文的mo文件是不一样的，是因为前面的字段算是一个键，键是一样的，但是对应的值分别对应中文和英文。所以一般只需要写一个英文版的翻译mo文件即可，不需要再去写一个中文版的翻译mo文件。
```
lang = gettext.translation('practice_en_US', localedir=localedir, languages=['en_CN'])
lang.install('practice_zh_CN')
```
install中参数随便写，没任何影响，有影响的有practice_en_US必须和mo文件名称一样，另外languages中可以是en_US、en、zh、zh_CN都可以，但是需要和前面的域名要相对应。

最后，本来想实现通过运行py文件时写入参数动态调整翻译语言，然而并不能成功，因为加载翻译文件是在入参之前。但是，我又想到一个方法，只要思想不滑坡，办法总比困难多。
最终成功了，但是代码不优雅，不推荐：D:\Github\Storage\python\study\gettext\practice\ultimate
通过修改配置文件传递参数较优雅些，但还是不完美。
感觉当前架构有问题，不应该分成两个文件写，写在一个文件岂不是可以，在调用中文的时候_("嗨世界")不就可以了。（但是这种架构不适合提供给翻译团队翻译文案，还是应该写成两个文件方便些，另外一个好处就是多处使用同一个字符串时，这样只需要改一处，而写在一个文件则需要修改多处）

又双叒叕一个想法：D:\Github\Storage\python\study\gettext\practice\perfect\main.py
最终还是达到了我的预期，这才是完美！

## 5、gettext还支持shell脚本翻译
资料：https://blog.csdn.net/monarch91/article/details/132323704
demo: D:\Github\Storage\python\study\gettext\shell

### 5-1、简介
在编写shell脚本时，我们可能需要shell脚本在运行时，根据用户操作系统的语言环境，自动选择对应语言的字符串进行输出。这个时候，就需要用到gettext和消息数据库。

与消息数据库相关的是三种语言文件：pot，po，mo。当mo文件存放在规定路径的文件夹中时，这个文件夹就可以称之为一个消息数据库。

pot是Portable Object Template的缩写。由英文名称可知，这是一类模板文件。
po是Portable Object的缩写，可由pot文件生成，可以看做是pot文件的子类，因为pot文件和po文件从语法上来看是一致的，只不过填充了翻译的内容。
mo指Machine Object的缩写，由po文件生成，是一个二进制数据文件，是Linux实现国际化时，实际使用的文件。

pot和po格式的文件都是文本文件，可以直接在文本编辑器中编写，也可以通过特定软件生成。mo文件不可以直接阅读，但可以反编译为po文件后再阅读。

所用到的软件是gettext，该软件为程序员、翻译人员甚至用户提供了一套集成良好的工具和文档。gettext旨在最大限度地减少国际化对程序源的影响。

具体来说，gettext提供了以下功能：
- 在程序源代码中添加gettext的相关声明信息及本地化运行环境检测代码;
- 为需要翻译的交互语句设置标记;
- 使用gettext工具提取源代码中的交互语句，生成pot文件;
- 使用msginit工具将pot文件转化成一个特定语言版本的po文件; 或者使用msgmerge将更新了的pot文件与旧的po文件合并生成新的po文件;
- 编辑po文件，将交互语句逐条翻译;
- 使用msgfmt工具将po文件转化成mo文件。

gettext的在线帮助文档为：https://www.gnu.org/software/gettext/manual/html_node/

### 5-2、准备shell脚本
demo见：D:\Github\Storage\python\study\gettext\shell\test.sh

linux支持c语言printf函数:
```
[root@ubuntu0006:~] #printf "I am %s, my age is %d\n" das 23
I am das, my age is 23
[root@ubuntu0006:~] #gettext --help
用法：gettext [选项] [[文本域] MSGID]
或：  gettext [选项] -s [MSGID]...

显示某原文消息的本地语言翻译。

  -d, --domain=文本域       由<文本域>读取翻译后的消息
  -e                        允许展开某些转义字符
  -E                        (为了兼容性存在的选项，不会造成任何影响)
  -h, --help                显示此段说明消息并退出
  -n                        禁用尾随的换行符
  -V, --version             显示版本信息并退出
  [文本域] MSGID            由<文本域>读取相应于 MSGID 的翻译消息
```

### 5-3、准备翻译文件
生成pot文件：
```
xgettext test.sh  -o msg.pot \
        --language=shell \
        --keyword=printf_loc \
        --add-comments --add-location  --no-wrap \
        --copyright-holder="laowang" \
        --package-name="test" \
        --package-version="V1.0"\
        --msgid-bugs-address="test@csdn.com" 
```

编辑pot：生成的pot有时候需要修改，主要是处理误生成的冗余文本。如下图所示20,21,22行就需要删除。这可能算是一个bug，即使在指定了keyword的情况下，生成pot时，还是会扫描到gettext那一行。
不过，在写shell脚本时，可以把自定义的方法放在另一个shell脚本中，通过source读取后再调用。这样生成的pot文件，就不会有额外的内容。

生成po：po通过pot文件生成，示例命令如下，其中-i参数设置pot路径，-l参数设置语言，-o参数设置po文件的输出路径。
```
# 生成中文po
msginit -i msg.pot -l zh_CN.UTF-8 -o zh_CN.po
# 生成英语po
msginit -i msg.pot -l en_US.UTF-8 -o en_US.po
```

编辑po文件进行手动翻译。

生成mo文件：mo文件由po文件生成，mo文件也可以反编译为po文件。
```
#po转为mo   
msgfmt  xxxx.po -o xxxx.mo

#mo转为po
msgunfmt xxxx.mo -o xxxx.po
```

创建gettext要求的目录结构：
```
[root@ubuntu0006:~/cmake/hj] #tree locale/
locale/
├── en_US
│   └── LC_MESSAGES
│       └── laowangtest.mo
└── zh_CN
    └── LC_MESSAGES
        ├── laowangtest.mo
        └── zh_CN.mo

4 directories, 3 files
```

需要说明的是，不建议将mo文件直接生成在当前文件夹，而应该生成在locale/${语言代号}/LC_MASSAGES这样一个目录层级中。因为这个目录结构是gettext要求的，这样的locale文件夹就是一个上文提到的“消息数据库”。
默认的l消息数据库的路径是/usr/share/locale，如下图所示，该文件夹存储了操作系统和各个软件提供的本地化文件。

### 5-4、实现国际化
消息数据库的使用需要注意三个全局变量。
```
LC_MESSAGES： 指定语言环境，如果提供，则会覆盖消息的 LANG。
TEXTDOMAIN： 指定文本域名，它与不带有 .mo 后缀的消息目标文件名相同。
TEXTDOMAINDIR： 指定消息数据库的路径名。如果提供，则会替换 /usr/lib/locale。
```
另外，我们既可以通过TEXTDOMAINDIR指定消息数据库的路径，也可以将我们创建的消息数据库复制到默认消息数据库的路径/usr/lib/locale，这样的话，测试脚本中的export TEXTDOMAINDIR="./locale"就可以删除。
同时，文本域名还可以通过gettext的-d参数指定，所以测试脚本中的export TEXTDOMAIN="laowangtest"这一行可以删除，只需要将gettext -e -s "$1"改成gettext -e -s -d "laowangtest" "$1"。

```
[root@ubuntu0006:~/cmake/hj] #export LANGUAGE=en_US.UTF-8
[root@ubuntu0006:~/cmake/hj] #./test.sh
Hello,Welcome to the world of Linux.
My name is Laowang , aged 32.
[root@ubuntu0006:~/cmake/hj] #export LANGUAGE=zh_CN.UTF-8
[root@ubuntu0006:~/cmake/hj] #./test.sh
您好，欢迎来到Linux的世界。
我的名字是Laowang，年龄是32岁。
```
我的是xubuntu，虽然也有LANG字段，但是修改不生效，修改LANGUAGE生效。