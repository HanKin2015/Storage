::
:: 文 件 名: 强制删除文件和文件夹.bat
:: 文件描述: 主要用于删除文件或者文件夹被占用
:: 作    者: HanKin
:: 创建日期: 2022.02.09
:: 修改日期：2022.02.09
:: 
:: Copyright (c) 2022 HanKin. All rights reserved.
::

DEL /F /A /Q \\?\%1

RD /S /Q \\?\%1