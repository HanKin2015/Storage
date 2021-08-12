::
:: 文 件 名: 删除SVN信息.bat
:: 文件描述: 解决桌面图标左下角问号图标问题
:: 作    者: HanKin
:: 创建日期: 2021.08.11
:: 修改日期：2021.08.11
:: 
:: Copyright (c) 2021 HanKin. All rights reserved.
::

for /r . %%a in (.) do @if exist "%%a\.svn" rd /s /q "%%a\.svn"


