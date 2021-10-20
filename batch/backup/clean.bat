if not "%1"=="" do (
    cd %1
    call :del_files
    cd ..
) else call :del_files
pause 
goto :eof

:del_files
del /S *.h 
del /S *.c
del /S *.cpp
del /S *.plg
del /S *.dsp
del /S *.dsw
del /S *.json
del /S *.xml
del /S *.bin
del /S *.mml
del /S *.mpj
del /S *.mpx
del /S *.ncb
del /S *.opt
del /S *.positions
del /S *.mk
del /S *.html
goto :eof
