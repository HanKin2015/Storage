# 1、写在前面
- 分支gitbook是项目原始文件，并且会编译生成_book文件夹
- 分支master是渲染的网页框架文件

因此主体操作是在gitbook分支上进行平时的源文件md编辑，间隔一段时间之后进行gitbook编译生成_book文件夹，然后将生成的html文件布置到分支master上面。

会创建 README.md 和 SUMMARY.md 这两个文件，README.md 应该不陌生，就是说明文档,书籍的介绍写在这个文件里。而 SUMMARY.md 其实就是书的章节目录，书籍的目录结构在这里配置。

网页地址：https://hankin2015.github.io/GitBook/
由于已经搭建好，使用gitbook build即可编译成功。

# 2、目录
- ACM
- Books
- C++
- Checklist
- Database
- Emtertainment
- Golang
- Linux
- ML
- node_modules（nodejs库）
- Others
- Project
- Python
- QT
- Scripts
- Shell-vim
- Source（图标）
- StudyNotes
- Styles（网页格式）
- todo
- Tools
- USBDevice
- Web
- Windows

# 3、日常维护操作
详细教程参考：https://zhuanlan.zhihu.com/p/34946169

## 3-1、git上库更新
git add .
git commit -m"20230220"
git push origin

## 3-2、使用脚本生成SUMMARY.md文件
python generate_summary.py
否则需要自己一个一个手动添加。

## 3-3、注意事项
- md文件不能以中文命名。
- md文件不能包含#符号
- gitbook build报错，book.json中的插件出现问题（当前发现summary插件出现问题，已过滤掉，自动生成SUMMARY.md文件插件）
- SUMMARY.md文件一定要是UTF-8格式
- md文件内容不能出现连续两个大括号\{\{ \}\}，否则gitbook编译不通过，必须要使用反斜杠转义

## 3-4、gitbook编译
在Gitbook文件夹里使用：
- gitbook init   （会根据生成的SUMMARY.md文件进行初始化检测操作，不存在的文件会自动创建）
- gitbook build . ../master     （创建时间会非常长3001.9s，可以通过打开生成目录查看html文件的生成过程）
- gitbook serve [--port xxxx]    # 编译后并在本地可使用地址查看，默认 4000 端口
- gitbook pdf ./ ./bookname.pdf
- gitbook epub ./ ./bookname.epub
- gitbook mobi ./ ./bookname.mobi

## 老式维护方式
然后将生成的_book文件夹里的动态替换到Github/GitBook/文件夹里：
>git add .
git commit -m"[UPDATE]20201230"
git push origin master

## 新式维护方式
https://blog.csdn.net/guoshenglong11/article/details/22306721/

github上面默认在仓库根目录下调用index.html文件，是不是可以跳转到_book文件夹呢?答案是不能。

删除分支gitbook，只保留master分支，然后通过自己单独编写的index.html文件来处理跳转问题。

但是出现一个很奇怪的问题，重新上库后整个目录没有任何变化。
忘记之前出现什么问题了，反正总之失败了，还是采用老式维护方式。

# 4、给gitbook的目录添加数字 添加章节序号
默认情况下，GitBook的目录是没有序号的，若想为目录编号，

需要在GitBook项目的根目录下创建一个book.json文件，在其中输入如下内容：
```
{
    "pluginsConfig": {
        "theme-default": {
             "showLevel": true
        }
    }
}
```

# 5、文件
book.json：文件配置
README.md：图书简介
SUMMARY.md：目录
GLOSSARY.md：要注释的术语列表
generate_summary.py：生成SUMMARY.md文件

# 6、gitbook build文章到非_book默认目录
在使用gitbook创建文章时。有时候我们不希望自己写的文章在_book目录下又不想手动去拷贝一遍，那么，我们可以在build指令后传入参数

参数一，书籍所在的目录，如果执行build指令时位于当前项目目录，输入./
参数二，输出的目录，相对于当前目录

推荐使用：gitbook build . ../master

# 7、在新电脑搭建维护环境
1. 安装nvm
[nvm-windows官网下载](https://github.com/coreybutler/nvm-windows/releases)
2. 配置镜像源
在你安装的目录下找到settings.txt文件，打开后加上 
node_mirror: https://npm.taobao.org/mirrors/node/ 
npm_mirror: https://npm.taobao.org/mirrors/npm/
3. 安装nodejs
nvm list available 显示可下载版本的部分列表
nvm install 版本号 安装指定的版本的nodejs
nvm use 版本号 使用指定版本的nodejs
注意: win7只能安装v12.16.2版本及更老的版本。
4. 安装gitbook
npm install gitbook-cli -g 
gitbook -V
5. 环境完成

# 8、20210125
- gitbook
- master

cd gitbook
gitbook build . ../master

它会删除原先的master文件夹，然后新建。这时候就不再是一个git仓库，需要重新添加remote等等。
发现SUMMARY.md也变回去了。
思考：是不是应该修改md文件名为中文名？？？

git remote add origin git@github.com:HanKin2015/GitBook.git
git push origin master报错如下面，原来是忘记git add了。
error: src refspec master does not match any

git push origin master --force强制替换

使用GitBook+GitHub pages建立在线电子书笔记。

# 网站地址
>https://hankin2015.github.io/GitBook/

master是解析的html文件，GitBook分支是源码。

# 日常维护
gitbook init（更新目录）

README.md 前言简介说明文档

SUMMARY.md 书的章节目录

gitbook serve（生成html）

_book 文件夹, 里面的内容即为生成的 html 文件

gitbook build（生成网页而不开启服务器）

book.json 存放配置信息

# 思考
有些东西需不需要单独建立文件夹呢？
如git.md都12000+了、golang教程一篇文章就够了？

文件夹数量需不需要限制？文章一篇需不需要限制行数？

姝shu：1.美好。2.美丽的女子。

# 更新记录

<details>

<summary>点击展开</summary>

## 2021.10.06
发现可以展开的功能。

## 2021.09.09
长长久久。

~~喝肥宅快乐水(\*´∀`)~~

</details>

程序员变量命名网站：https://unbug.github.io/codelf/

## 20220124
发现一个不错的网站，免费下载各种学习的pdf资料：https://www.bookstack.cn/

linux命令搜索大全：https://wangchujiang.com/linux-command/

## 20220509
- 建立ftp服务器，然后使用magictool进行快速拷贝
- 福利双色球
- 电视剧动漫表格编辑学习

## 问题一：关于gitbook 使用3.2.3版本，导致build编译后的自动生成的左侧目录无法跳转问题的解决办法
当前使用gitbook在写一些文档，但使用导出编译git build 后，生成的静态HTML页面，无法翻页到上下章节。 但放在服务器上线上就正常。于是乎是去查询相关资料。目前方法有二。

当前gitbook版本   3.2.3 
```
# gitbook --version
# CLI version: 2.3.2
# GitBook version: 3.2.3
```

方法一，使用 2.6.7 这个版本就可以。
```
git build  --gitbook=2.6.7
```

方法二，修改相关文件。
在导出的文件夹目录下找到gitbook->theme.js文件
找到下面的代码（搜索 if(m)for(n.handler&&）
将if(m)改成if(false)，问题完美解决，推荐使用方法二。

## 问题二：静态或者线上都无法单击展开
线上能双击展开，静态干脆不行，左侧的展开按钮简直就是一个摆设。

## Debugging
您可以使用选项 --log=debug 和 --debug 来获取更好的错误消息（使用堆栈跟踪）。例如：
```
$ gitbook build ./ --log=debug --debug
```

## VitePress搭建文档网站
https://www.cnblogs.com/Answer1215/p/18696254
https://blog.csdn.net/qq_44793507/article/details/142521250