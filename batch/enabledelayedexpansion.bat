::
:: 文 件 名: enabledelayedexpansion.bat
:: 文件描述: 启用延迟变量扩展，并且将其作用域限制在脚本或脚本的一部分中
:: 备    注: 启用延迟变量扩展后，你可以通过使用 ! 而不是 % 来引用变量（例如 !variable!），这样就可以获取到变量在代码块执行过程中的实时值
:: 作    者: HanKin
:: 创建日期: 2024.08.28
:: 修改日期：2024.08.28
:: 
:: Copyright (c) 2024 HanKin. All rights reserved.
::

@echo off
setlocal enabledelayedexpansion

set "count=0"

:: 不管有没有enabledelayedexpansion限制符%cout%都是输出0，而!count!则会随之是否生效
for /l %%i in (1,1,5) do (
    set /a count+=1
    echo Without delayed expansion: %count%
    echo With delayed expansion: !count!
)

endlocal
pause