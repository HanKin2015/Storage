rem @echo off作用是所有的命令均不显示
@echo off

rem 开启延时环境变量
setlocal EnableDelayedExpansion

rem 分辨率的宽和高
set /a width=0
set /a height=0

rem 获取主屏的分辨率列表
set resolution_getter=resolutionGather.exe

rem 系统自带的DisplaySwitch工具，可以实现复制屏和扩展屏的切换
set displaySwitch_extend=C:\Windows\System32\DisplaySwitch.exe /extend
set displaySwitch_clone=C:\Windows\System32\DisplaySwitch.exe /clone

rem 设置分辨率的工具
set display_modify=C:\nircmd\x64\nircmd.exe setdisplay    

rem 等待5秒
set wait=ping 127.0.0.1 -n 5 >nul

rem 获得主屏的所有分辨率
%resolution_getter%

rem 首先设置为扩展屏
%displaySwitch_extend%
%wait%

rem 循环获得resoutions中所有的分辨率
for /f "delims=" %%a in (resolutions.txt) do (
	rem 获得分辨率的宽
	for /f "delims=* tokens=1" %%i in ("%%a") do (
		 set /a width=%%i
	)
	rem 获得分辨率的高
	for /f "delims=* tokens=2" %%j in ("%%a") do (
		 set /a height=%%j
	)
	echo "设置分辨率为：!width! * !height!"
	rem 依次设置主屏的分辨率
	%display_modify% !width! !height! 32
	%wait%
)

rem 设置为复制屏
%displaySwitch_clone%

for /f "delims=" %%a in (resolutions.txt) do (
	rem 获得分辨率的宽
	for /f "delims=* tokens=1" %%i in ("%%a") do (
		 set /a width=%%i
	)
	rem 获得分辨率的高
	for /f "delims=* tokens=2" %%j in ("%%a") do (
		 set /a height=%%j
	)
	echo "设置分辨率为：!width! * !height!"
	rem 依次设置主屏的分辨率
	%display_modify% !width! !height! 32
	%wait%
)

%使程序暂停，即在屏幕上输出“请按任意键继续…”%
pause
