@echo off
setlocal enabledelayedexpansion

set /p ID=<apiname

set tarstr=
for /d %%i in (traderapi) do (
set tarstr=!tarstr! api%%i\!ID!*.dll api%%i\!ID!*.lib
)
@echo !tarstr!
@call zip api.zip !tarstr!

set includestr=
@call mkdir include
@call copy ..\sourceapp\apiuserapi\!ID!FtdcUserApiStruct.h .\include\
@call copy ..\sourceapp\apiuserapi\!ID!FtdcUserApiDataType.h .\include\
@call copy ..\sourceapp\apitraderapi\!ID!FtdcTraderApi.h .\include\

@echo !includestr!
@cd include
@call zip include.zip *
@cd ..
