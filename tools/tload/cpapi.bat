@echo off

@call copy ..\..\sourceapp\qdpuserapi\QdpFtdcUserApiStruct.h .\userapi\
@call copy ..\..\sourceapp\qdpuserapi\QdpFtdcUserApiDataType.h .\userapi\
@call copy ..\..\sourceapp\qdpuserapi\QdpFtdcUserApi.h .\userapi\
@call copy ..\..\api\qdpuserapi\*.dll .\userapi\
@call copy ..\..\api\qdpuserapi\*.lib .\userapi\
@call copy ..\..\api\qdpuserapi\*.dll .\