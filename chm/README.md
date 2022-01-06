# chm

## 1、简介（摘自百度百科）
CHM 文件格式是微软于 1998 年推出的基于 HTML 文件特性的帮助文件系统，以替代早先的 WinHelp 帮助系统。它在 Windows 98 中把 CHM 类型文件称作“编译的 HTML 帮助文件”（Compiled HTML Help file）。
被 IE 浏览器支持的JavaScript, VBScript, ActiveX, Java Applet, Flash, 常见图形文件(GIF、JPEG、PNG)、音频视频文件(MID、WAV、AVI)等等，CHM同样支持，并可以通过 URL 与 Internet 联系在一起。
CHM 文件因为使用方便，形式多样，也被采用作为电子书的格式。
中文名编译的 HTML 帮助文件外文名Compiled HTML Help file

## 2、制作工具简介
关于制作 CHM 文件的工具，我们可以使用微软的 HTML Help Workshop(以下简称HHW)或者“国华软件工作室”的 eTextWizard (电子文档处理器，以下简称EW)。HHW 在 VB、 VC 等开发工具的 CD 中都有，也可以到微软的站点去下载最新版本，互联网上也可以找到汉化的版本。EW 是国人开发的软件，使用上要方便一些。在此我们以 HHW 为例。

## 3、hhw.exe
hhw.exe是Microsoft HTML Help Workshop相关程序，用于制作帮助文档。

在我的笔记本使用everything搜索并没有搜索到hhw.exe，可能是因为没有安装vs的原因吧。

下次有机会再实践，试试ew是不是好用些：
使用 HHW 制作 CHM 文件
假设我们制作好的主页放在 C:\test 目录中，其中有一个 index.html，通过它可以链接到所有其他的文件。
打开 HTMLHelpWorkshop，单击“File→New”菜单(或者单击工具栏第一个按钮)，出现“New”对话框，选择其中的“Project”后，按“OK”，创建一个工程。
这一步的对话框提供了从 *.hlp 到 *.chm 文件的转换，在此我们不需要，直接按“下一步”。
这一步的对话框要求指定工程的位置。单击“Browse”，进入 C:\test 目录，并在文件名中键入“test”，这时文本框中应出现“C:\test\test.hlp”，然后按“下一步”。
这一步要求选择你已为工程创建的文件类型，在此我们选择第三个“HTML files(.htm)”。
需要添加我们制作好的 HTML 文件，按“Add”，选择“C:\test\index.html”，将它添加到列表框。说明一下，只要被 index.html 文件直接或间接链接到的文件，都会包含进去，因此不必将所有的文件添加进去！然后单击“完成”即可。
单击“File→Compile…”(或工具栏第三个按钮)，出现“Createacompiledfile”对话框，直接单击“Compile”。
测试：在资源管理器中双击生成的 C:\test\test.chm，在页面单击右键，在菜单中选择“属性”，在“属性”对话框中复制其中的“地址”(应该为mk: @MSITStore:C:\test\test.chm::/index.html)。将上面的地址粘贴到浏览器的地址栏中，如果正确，按回车可以在浏览器中看到正确的页面。

## 4、还原方法
可以利用 Windows 自带的 hh.exe 文件来进行文件格式转换，语法为：
HH.EXE -decompile <输出路径> <目标chm文件>

hh -decompile <输出路径> <目标chm文件>

以当前文件夹下restore/AHK_CN_V1.chm文件为例。
hh -decompile result AHK_CN_V1.chm

## 5、制作chm文件
工具有太多，根据知乎可以试试，建议使用myBase导出chm，在 Microsoft HTML Help Workshop 中选择hhp文件进行编译。