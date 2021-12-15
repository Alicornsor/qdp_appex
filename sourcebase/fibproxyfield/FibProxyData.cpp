#include "public.h"
#include "FibProxyData.h"

/*** 应用业务FieldID ***/
REGISTER_FIELD(FPP_FID_RspInfo, CFPPRspInfoField, "响应信息");
REGISTER_FIELD(FPP_Dissemination, CFPPDisseminationField, "信息分发");
REGISTER_FIELD(FPP_FID_ReqUserLogin, CFPPReqUserLoginField, "用户登录请求");
REGISTER_FIELD(FPP_FID_RspUserLogin, CFPPRspUserLoginField, "用户登录应答");
