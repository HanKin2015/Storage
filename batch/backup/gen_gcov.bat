for /R .MINGW %%I in (*.o) do (
    gcov -o %%I %%~nI.c
    mv %%~nI.c.gcov %%~dpI
)
del *.gcov
pause