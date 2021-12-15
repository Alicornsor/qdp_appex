@echo off

@copy ..\sourceapp\qtrade\apextradelink\apextraderapi.dll .\qtrade\bin\
@copy ..\sourceapp\qtrade\qtesttradelink\qtesttraderapi.dll .\qtrade\bin\

@copy ..\sourceapp\qtrade\apextradelink\apextraderapi.dll .\qquery\bin\
@copy ..\sourceapp\qtrade\qtesttradelink\qtesttraderapi.dll .\qquery\bin\
@copy ..\sourceapp\qquery\qdpmdlink\qdmdapi.dll .\qquery\bin\

@copy ..\sourcebase\db\sqlapiso\libmysql.dll .\qdata\bin\
@copy ..\sourcebase\db\sqlapiso\sqlapi.dll .\qdata\bin\

@copy ..\sourcebase\db\sqlapiso\libmysql.dll .\qquery\bin\
@copy ..\sourcebase\db\sqlapiso\sqlapi.dll .\qquery\bin\

@copy ..\datamodel\envGenerated\dbmt.cmd qdata\bin\

@copy .\target\qdata\bin\libmysql.dll .\qdata\bin\
@copy .\target\qquery\bin\libmysql.dll .\qquery\bin\

setlocal enabledelayedexpansion
set tarstr=
for /d %%i in (qtrade,qdata,qquery) do (
set tarstr=!tarstr! %%i\bin\%%i.exe %%i\bin\%%i.ini %%i\bin\*.dll %%i\flow\ %%i\cleanflow.bat %%i\dump\ 
)

set tarstr=!tarstr! qdata\bin\dbmt.cmd start.bat stop.bat clean.bat
@echo !tarstr!
@call zip run.zip !tarstr!

@cd ..\tools
set tarstr=
for /d %%i in (dumptool,testapi,tload,slogparser) do (
set tarstr=!tarstr! %%i\%%i.exe %%i\%%i.ini
)
set tarstr=!tarstr! flowviewer\flowviewer.exe
set tarstr=!tarstr! testapi\Order.csv  tload\readme.txt tload\test.in slogparser\slogparser.exe
@echo !tarstr!
@call zip tools.zip !tarstr!

