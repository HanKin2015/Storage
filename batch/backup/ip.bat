@echo off
SETLOCAL ENABLEDELAYEDEXPANSION
for /f %%a in ('wmic nicconfig where^(ipenabled^=true^) get index^|findstr [0-99]') do set i=%%a
for /f %%a in ('wmic nicconfig where^(index^=%i%^) get macaddress^|findstr [0-99]') do set a=%%a &set a=!a::=!


if "%a%" == "FEFE00101010 " (netsh interface ip set address name="localnet" source="static" addr="199.201.132.25" mask="255.255.252.0" gateway="199.201.135.254" )
if "%a%" == "FEFE00111111 " (netsh interface ip set address name="localnet" source="static" addr="199.201.132.28" mask="255.255.252.0" gateway="199.201.135.254" )
if "%a%" == "FEFE00121212 " (netsh interface ip set address name="localnet" source="static" addr="199.201.132.29" mask="255.255.252.0" gateway="199.201.135.254" )
if "%a%" == "FEFE00131313 " (netsh interface ip set address name="localnet" source="static" addr="199.201.132.39" mask="255.255.252.0" gateway="199.201.135.254" )
if "%a%" == "FEFE00141414 " (netsh interface ip set address name="localnet" source="static" addr="199.201.132.46" mask="255.255.252.0" gateway="199.201.135.254" )
if "%a%" == "FEFE00151515 " (netsh interface ip set address name="localnet" source="static" addr="199.201.132.52" mask="255.255.252.0" gateway="199.201.135.254" )
if "%a%" == "FEFE00161616 " (netsh interface ip set address name="localnet" source="static" addr="199.201.132.53" mask="255.255.252.0" gateway="199.201.135.254" )
if "%a%" == "FEFE00171717 " (netsh interface ip set address name="localnet" source="static" addr="199.201.132.59" mask="255.255.252.0" gateway="199.201.135.254" )
if "%a%" == "FEFE00181818 " (netsh interface ip set address name="localnet" source="static" addr="199.201.132.60" mask="255.255.252.0" gateway="199.201.135.254" )
if "%a%" == "FEFE00191919 " (netsh interface ip set address name="localnet" source="static" addr="199.201.132.65" mask="255.255.252.0" gateway="199.201.135.254" )
if "%a%" == "FEFE00202020 " (netsh interface ip set address name="localnet" source="static" addr="199.201.132.69" mask="255.255.252.0" gateway="199.201.135.254" )
if "%a%" == "FEFE00212121 " (netsh interface ip set address name="localnet" source="static" addr="199.201.132.70" mask="255.255.252.0" gateway="199.201.135.254" )
if "%a%" == "FEFE00222222 " (netsh interface ip set address name="localnet" source="static" addr="199.201.132.74" mask="255.255.252.0" gateway="199.201.135.254" )
if "%a%" == "FEFE00232323 " (netsh interface ip set address name="localnet" source="static" addr="199.201.132.76" mask="255.255.252.0" gateway="199.201.135.254" )
if "%a%" == "FEFE00242424 " (netsh interface ip set address name="localnet" source="static" addr="199.201.132.81" mask="255.255.252.0" gateway="199.201.135.254" )
if "%a%" == "FEFE00252525 " (netsh interface ip set address name="localnet" source="static" addr="199.201.132.82" mask="255.255.252.0" gateway="199.201.135.254" )
if "%a%" == "FEFE00262626 " (netsh interface ip set address name="localnet" source="static" addr="199.201.132.85" mask="255.255.252.0" gateway="199.201.135.254" )
if "%a%" == "FEFE00272727 " (netsh interface ip set address name="localnet" source="static" addr="199.201.132.87" mask="255.255.252.0" gateway="199.201.135.254" )
if "%a%" == "FEFE00282828 " (netsh interface ip set address name="localnet" source="static" addr="199.201.132.91" mask="255.255.252.0" gateway="199.201.135.254" )
if "%a%" == "FEFE00292929 " (netsh interface ip set address name="localnet" source="static" addr="199.201.132.92" mask="255.255.252.0" gateway="199.201.135.254" )
