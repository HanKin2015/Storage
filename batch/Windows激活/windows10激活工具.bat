@echo off
setlocal EnableDelayedExpansion
color 0a
title windows10激活工具
slmgr /ipk ABCDE-ABCDE-ABCDE-ABCDE-ABCDE
slmgr /skms 32.13.11.11:22
slmgr /ato
pause