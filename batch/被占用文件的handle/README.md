# 操作
先使用wps打开Eula.docx文件

# 执行handle.exe报错Unable to extract x64 image. Run Handle from a writeable directory.
```
D:\Github\Storage\batch\被占用文件的handle>handle.exe Eula.txt
Unable to extract x64 image. Run Handle from a writeable directory.
```

原因：exe文件是一个32位程序，需要使用64位程序。
```
D:\Github\Storage\batch\被占用文件的handle>handle64.exe Eula.txt

Nthandle v5.0 - Handle viewer
Copyright (C) 1997-2022 Mark Russinovich
Sysinternals - www.sysinternals.com

No matching handles found.
```

解决方法：更换64位程序。

# 使用skip跳过前几行
```
D:\Github\Storage\batch\被占用文件的handle>remove_handle.bat Eula.docx
Releasing \Github\Storage\batch\??????handle\Eula.docx

Nthandle v5.0 - Handle viewer
Copyright (C) 1997-2022 Mark Russinovich
Sysinternals - www.sysinternals.com

  D04: File  (R--)   D:\Github\Storage\batch\??????handle\Eula.docx

Handle closed.

D:\Github\Storage\batch\被占用文件的handle>handle64.exe Eula.docx

Nthandle v5.0 - Handle viewer
Copyright (C) 1997-2022 Mark Russinovich
Sysinternals - www.sysinternals.com

No matching handles found.
```

# 使用pause可以卡住
请任意键继续

# 遇到更强大的删除不掉的文件
增加了窗口的属性修改，使用handle64.exe软件以及任务管理器都没有找到句柄，但肯定是被占用了。只能祈祷重启电脑删除文件。
如果删除不掉，只能找始作俑者之人。Unlocker1.9.2.0



