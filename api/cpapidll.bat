@echo off
@call copy apitraderapi\*.dll ..\tools\qdpallapi\
@call copy apitraderapi\*.lib ..\tools\qdpallapi\

@call copy apiuserapi\*.dll ..\tools\qdpuserapi\
@call copy apiuserapi\*.lib ..\tools\qdpuserapi\

@call copy ..\source\apiuserapi\QTFtdcUserApiStruct.h ..\tools\qdpallapi\
@call copy ..\source\apiuserapi\QTFtdcUserApiDataType.h ..\tools\qdpallapi\
@call copy ..\source\apitraderapi\QTFtdcTraderApi.h ..\tools\qdpallapi\

@call copy ..\source\userapi\QTFtdcUserApi.h ..\tools\qdpallapi\