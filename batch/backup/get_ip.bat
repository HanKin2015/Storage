@echo off
setlocal EnableDelayedExpansion

call :get_ip_addr

:finish_setup_address
goto :EOF

:get_ip_addr
setlocal
	for /f %%i in ( ' genhid ' ) do ( set "dtphid=%%i" )
	for /f %%i in ( ' ipconfig /all ^| sed -e "s/-//g" ^| grep "%dtphid%" -A4 ^| grep "IPv4" ^| sed  "s/.*:.\([0-9.]*\).*/\1/g"' ) do ( echo %%i )
	for /f %%i in ( ' ipconfig /all ^| sed -e "s/-//g" ^| grep "%dtphid%" -A4 ^| grep "IP Address" ^| sed  "s/.*:.\([0-9.]*\).*/\1/g"' ) do ( echo %%i )
endlocal & goto :EOF
