!!let exchangeid=""!!
!!let functionid=""!!
!!let macroid=""!!
!!let fileid=""!!
!!enter exchangeinfo!!
!!travel self!!
!!if @pumpid==0!!
!!let exchangeid=@name!!
!!elseif @pumpid==1!!
!!let functionid=@name!!
!!elseif @pumpid==2!!
!!let macroid=@name!!
!!elseif @pumpid==3!!
!!let fileid=@name!!
!!endif!!
!!next!!
!!leave!!
/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company 上海量投网络科技有限公司
///@file !!@functionid!!FtdcUserApiImpl.h
///@brief 定义了客户端接口实现
///@history 
///20150522 xuzh create
/////////////////////////////////////////////////////////////////////////

#if !defined(_FTDCUSERAPIIMPL_H)
#define _FTDCUSERAPIIMPL_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FtdcUserApiImplBase.h"

!!enter FTD!!
class CFtdcUserApiImpl : public CFtdcUserApiImplBase
{
public:	
	CFtdcUserApiImpl(const char *pszFlowPath, const char *pszUserApiType, CReactor *pReactor);
	virtual void HandleResponse(CFTDCPackage *pMessage, WORD nSequenceSeries);
!!travel packages!!
!!if !strncmp(@name,"Req",3) && strcmp(@name,"ReqUserLogin")!!

	///!!@comment!!
	virtual int !!@name!!(!!travel self!!!!if @pumpid!=0!!, !!endif!!C!!@functionid!!Ftdc!!@name!!Field *p!!@name!!!!next!!, int nRequestID);
!!endif!!
!!next!!
private:
!!travel packages!!
!!if !strncmp(@name,"Rsp",3) !!
	///!!@comment!!
	void On!!@name!!(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
!!elseif !strncmp(@name,"Rtn",3)!!
	///!!@comment!!
	void On!!@name!!(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
!!elseif !strncmp(@name,"ErrRtn",6)!!
	///!!@comment!!
	void On!!@name!!(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
!!endif!!
!!next!!
};
!!leave!!  

#endif
