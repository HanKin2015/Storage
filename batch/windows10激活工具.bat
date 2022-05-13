@echo off
setlocal EnableDelayedExpansion
color 0a
title windows10激活工具
slmgr /ipk W269N-WFGWX-YVC9B-4J6C9-T83GX
slmgr /skms 32.13.11.11:22
slmgr /ato
pause