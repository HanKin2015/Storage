@echo off
::chcp 936 >nul 2>&1
::chcp 65001 >nul 2>&1
::chcp 936 >nul 2>&1

:: 切换到UTF-8代码页
chcp 65001 >nul 2>&1 && echo chcp succeeded

:: BAT脚本中，:: 注释必须在行首（或紧跟在标签后），绝不能跟在可执行命令后面！
chcp 65001 >nul 2>&1    :: 切换到UTF-8代码页(不生效)   
chcp 65001 >nul 2>&1 && echo chcp succeeded :: 验证方式  

:: UTF-8 vs GBK (ANSI) 的字节错位   
:: 在 UTF-8 中，汉字“秒”占用 3个字节 (0xE7 0xA7 0x92)   
:: 在 GBK 中，CMD 会尝试按 2个字节 一个汉字去解析   
:: 所以一个秒字会报错，但是两个秒字正常，或者在秒字后面加一个空格  
:: 上面的注释也会存在此问题，也需要在末尾添加空格解决
echo ==========================================
echo   ADB 自动循环连接脚本
echo   目标地址: %FULL_ADDRESS%
echo   重试间隔: %DELAY_SECONDS% 秒秒
echo   重试间隔: %DELAY_SECONDS% 秒  
echo   最大重试: %MAX_RETRIES% (0=无限)
echo   目标地址: %FULL_ADDRESS%
echo ==========================================
echo.

adb devices ::hejian

pause