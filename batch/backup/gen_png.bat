@echo off

setlocal

for %%I in (.\debug_out\png\*.dot) do (
::    "D:\Program Files\Graphviz2.30\bin\dot" -Tpng -Kneato %%I > %%I.png
    "D:\Program Files\Graphviz2.30\bin\dot" -Tpng -Kdot -o %%I.png %%I
)

pause
