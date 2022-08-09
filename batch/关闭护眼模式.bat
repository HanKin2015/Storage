::
:: 文 件 名: 关闭护眼模式.bat
:: 文件描述: 关闭护眼模式
:: 作    者: HanKin
:: 创建日期: 2022.05.19
:: 修改日期：2022.05.19
:: 
:: Copyright (c) 2022 HanKin. All rights reserved.
::

reg add "HKCU\Control Panel\Colors" /v Window /t REG_SZ /d "255 255 255" /f 