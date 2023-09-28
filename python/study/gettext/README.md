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

## 3、实战失败了
必须要有这样的路径结构：locale\en_US\LC_MESSAGES

可以在网上下载一个gettext工具：gettext0.21-iconv1.16-static-64.exe
https://github.com/autotools-mirror/gettext
```
pygettext.py -d <domain> -o <output_file>.po <source_file>.py
msgfmt -o <output_file>.mo <input_file>.po
```