# json库

## 1、有效的 JSON 格式文件
- 所有的键（key）都必须用双引号包围。
- 键值对之间用冒号分隔，多个键值对之间用逗号分隔。
- 数组的开头和结尾必须用方括号 [] 包围，数组中的元素用逗号分隔。

在标准的 JSON 格式中，不支持注释。JSON（JavaScript Object Notation）是一种轻量级的数据交换格式，旨在简洁和易于解析，因此不允许在数据中包含注释。

数组中的元素必须是有效的 JSON 数据类型（如对象、数组、字符串、数字、布尔值或 null）。

## 2、json.dumps方法
json.dumps() 方法是将 Python 对象序列化为 JSON 字符串的方法。它有以下几个参数：
- obj：要序列化为 JSON 的 Python 对象。
- skipkeys：如果设置为 True，则在序列化过程中跳过非字符串类型的键值对。默认为 False。
- ensure_ascii：如果设置为 True，则将所有非 ASCII 字符转义为 Unicode 转义序列。默认为 True。
- check_circular：如果设置为 True，则检查是否存在循环引用。默认为 True。
- allow_nan：如果设置为 True，则允许序列化 NaN、Infinity 和 -Infinity。默认为 True。
- cls：用于自定义序列化器的类。默认为 None。
- indent：用于指定 JSON 对象在序列化为字符串时的缩进量。默认为 None。
- separators：用于指定 JSON 对象在序列化为字符串时的分隔符。默认为 (', ', ': ')。
- default：用于指定无法序列化的对象的转换函数。默认为 None。
其中，obj 参数是必须的，其他参数都是可选的。如果需要使用可选参数，可以通过关键字参数的方式传递。

## 3、json.dump方法
json.dump() 方法用于将 Python 对象序列化为 JSON 并将其写入文件。它与 json.dumps() 方法类似，但是多了一个文件对象参数和一些其他参数。以下是 json.dump() 方法的参数列表：
- obj：要序列化为 JSON 的 Python 对象。
- fp：文件对象，用于写入 JSON 数据。
- skipkeys：如果设置为 True，则在序列化过程中跳过非字符串类型的键值对。默认为 False。
- ensure_ascii：如果设置为 True，则将所有非 ASCII 字符转义为 Unicode 转义序列。默认为 True。
- check_circular：如果设置为 True，则检查是否存在循环引用。默认为 True。
- allow_nan：如果设置为 True，则允许序列化 NaN、Infinity 和 -Infinity。默认为 True。
- cls：用于自定义序列化器的类。默认为 None。
- indent：用于指定 JSON 对象在序列化为字符串时的缩进量。默认为 None。
- separators：用于指定 JSON 对象在序列化为字符串时的分隔符。默认为 (', ', ': ')。
- default：用于指定无法序列化的对象的转换函数。默认为 None。
其中，obj 和 fp 参数是必须的，其他参数都是可选的。如果需要使用可选参数，可以通过关键字参数的方式传递。

## 4、ensure_ascii参数
在json.dump和json.dumps方法中，ensure_ascii参数用于控制是否将非ASCII字符转义为ASCII字符序列。

当ensure_ascii设置为True时（默认值），所有非ASCII字符将被转义为类似\uXXXX的ASCII字符序列。这样做的目的是确保生成的JSON数据是ASCII编码的，以便在传输或存储时不会出现编码问题。

当ensure_ascii设置为False时，非ASCII字符将保留原样，不进行转义。这意味着生成的JSON数据可能包含非ASCII字符，但它们将按照其原始编码进行处理。

通常情况下，如果你需要生成的JSON数据是纯ASCII编码的，可以保持ensure_ascii参数为默认值True。如果你希望保留非ASCII字符的原始形式，可以将ensure_ascii设置为False。

代码见：D:\Github\Storage\python\study\dict\json_example.py

## 5、indent参数
json.dump()和json.dumps()方法中的 indent 参数是用于指定 JSON 对象在序列化为字符串时的缩进量。它是一个可选参数，可以是一个整数或者是一个字符串。

当 indent 参数是一个整数时，它表示每个级别的缩进量，通常是空格的数量。例如，如果将 indent 参数设置为 4，则每个级别的缩进量为 4 个空格。如果将 indent 参数设置为 None，则表示不使用缩进，输出的 JSON 字符串将是一行。

当 indent 参数是一个字符串时，它表示每个级别的缩进字符串。例如，如果将 indent 参数设置为 "\t"，则每个级别的缩进量为一个制表符。

代码见：D:\Github\Storage\python\study\dict\json_example.py

## 6、UnicodeEncodeError: 'gbk' codec can't encode character '\u0409' in position 1: illegal multibyte sequenc
注意在open函数写入文件内容时，需要添加encoding参数，否则会报上面的错误。

代码见：D:\Github\Storage\python\study\dict\json_example.py

## 7、json.load和json.loads的区别
son.load和json.loads都是Python中用于解析JSON数据的函数，但它们之间有一些区别。

json.load是用于从文件中读取JSON数据并将其解析为Python对象。它接受一个文件对象作为参数，并返回解析后的JSON数据。例如：
```
import json

with open('data.json', 'r') as file:
    data = json.load(file)
```
在上面的例子中，data.json是包含JSON数据的文件。json.load函数将文件对象作为参数传递给它，并返回解析后的JSON数据。

json.loads是用于将JSON字符串解析为Python对象。它接受一个JSON字符串作为参数，并返回解析后的JSON数据。例如：
```
import json

json_string = '{"name": "John", "age": 30}'
data = json.loads(json_string)
```
在上面的例子中，json_string是一个包含JSON数据的字符串。json.loads函数将该字符串作为参数传递给它，并返回解析后的JSON数据。

因此，json.load用于解析JSON文件，而json.loads用于解析JSON字符串。

## 8、json文件内容不仅仅只有大括号开始和结尾
当需要一些并列对象存入json文件时，可以直接使用中括号列表来存储，并不需要再加一层键包裹。
如:
```
{
    "toolbox": [
        {
            "name": "",
            "desc": ""
        }, {
            "name": "",
            "desc": ""
        }]
}

可以直接这样：
[
    {
        "name": "",
        "desc": ""
    }, {
        "name": "",
        "desc": ""
    }
]
```

使用python脚本测试发现：
```
(base) D:\Users\User\Desktop>python k.py
<class 'list'>
<class 'dict'>
<class 'dict'>
```


