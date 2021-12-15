@echo off
setlocal enabledelayedexpansion
set /p ID=<apiname

set versionprefix=QDP_V2.1.1_intl

set versiondate=%1

if not "%versiondate%"=="" ( 
set version=!versionprefix!_!versiondate!
rem 将此刻的时间变成编译version的时间
echo #define QVERSION "!version!" > ../sourcebase/version/versionValue.h
)

@copy ..\datamodel\commonEnv\exinfo.!ID!.xml ..\datamodel\commonEnv\exinfo.xml
@copy ..\sourcebase\openssl\package.des.win32 ...\sourcebase\openssl\package.des
@copy ..\sourceapp\apiuserapi\package.!ID!.des ..\sourceapp\apiuserapi\package.des
@copy ..\api\apiuserapi\apiuserapi.!ID!.prj ..\api\apiuserapi\apiuserapi.prj
@copy ..\target\qfixfront\qfixfront.win32.prj ..\target\qfixfront\qfixfront.prj

for /d %%i in (qtrade,qdata,qquery) do (
@echo make %%i
@cd %%i
@call amake %%i.prj
@call nmake clean /nologo
@call nmake /nologo
@cd ..
)


@cd ../tools
for /d %%i in (dumptool,testapi,tload,slogparser,flowviewer) do (
@echo make %%i
@cd %%i
@call amake %%i.prj
@call nmake /nologo
@cd ..
)

@cd ../target
