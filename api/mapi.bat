@echo off
setlocal enabledelayedexpansion
set /p ID=<apiname

@copy ..\datamodel\commonEnv\exinfo.!ID!.xml ..\datamodel\commonEnv\exinfo.xml
@copy ..\sourceapp\apiuserapi\package.!ID!.des ..\sourceapp\apiuserapi\package.des
@copy ..\sourceapp\apitraderapi\package.!ID!.des ..\sourceapp\apitraderapi\package.des

@copy apiuserapi\apiuserapi.!ID!.prj apiuserapi\apiuserapi.prj
@copy apitraderapi\apitraderapi.!ID!.prj apitraderapi\apitraderapi.prj

@echo off

for /d %%i in (apiuserapi,apitraderapi) do (
@echo make %%i
@cd %%i
@call amake %%i.prj
@call nmake clean /nologo
@call nmake /nologo
@cd ..
)