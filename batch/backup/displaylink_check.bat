rem @echo off���������е����������ʾ
@echo off

rem ������ʱ��������
setlocal EnableDelayedExpansion

rem �ֱ��ʵĿ�͸�
set /a width=0
set /a height=0

rem ��ȡ�����ķֱ����б�
set resolution_getter=resolutionGather.exe

rem ϵͳ�Դ���DisplaySwitch���ߣ�����ʵ�ָ���������չ�����л�
set displaySwitch_extend=C:\Windows\System32\DisplaySwitch.exe /extend
set displaySwitch_clone=C:\Windows\System32\DisplaySwitch.exe /clone

rem ���÷ֱ��ʵĹ���
set display_modify=C:\nircmd\x64\nircmd.exe setdisplay    

rem �ȴ�5��
set wait=ping 127.0.0.1 -n 5 >nul

rem ������������зֱ���
%resolution_getter%

rem ��������Ϊ��չ��
%displaySwitch_extend%
%wait%

rem ѭ�����resoutions�����еķֱ���
for /f "delims=" %%a in (resolutions.txt) do (
	rem ��÷ֱ��ʵĿ�
	for /f "delims=* tokens=1" %%i in ("%%a") do (
		 set /a width=%%i
	)
	rem ��÷ֱ��ʵĸ�
	for /f "delims=* tokens=2" %%j in ("%%a") do (
		 set /a height=%%j
	)
	echo "���÷ֱ���Ϊ��!width! * !height!"
	rem �������������ķֱ���
	%display_modify% !width! !height! 32
	%wait%
)

rem ����Ϊ������
%displaySwitch_clone%

for /f "delims=" %%a in (resolutions.txt) do (
	rem ��÷ֱ��ʵĿ�
	for /f "delims=* tokens=1" %%i in ("%%a") do (
		 set /a width=%%i
	)
	rem ��÷ֱ��ʵĸ�
	for /f "delims=* tokens=2" %%j in ("%%a") do (
		 set /a height=%%j
	)
	echo "���÷ֱ���Ϊ��!width! * !height!"
	rem �������������ķֱ���
	%display_modify% !width! !height! 32
	%wait%
)

%ʹ������ͣ��������Ļ��������밴�������������%
pause
