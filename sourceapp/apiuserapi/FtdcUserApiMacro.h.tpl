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
///@file FtdcUserApiMacro.h
///@brief 定义了客户端接口中区分交易所的宏
///@history 
/////////////////////////////////////////////////////////////////////////
#if !defined(_!!@macroid!!FTDCUSERAPIMACRO_H)
#define _!!@macroid!!FTDCUSERAPIMACRO_H
#if !defined(FTDCUSERAPI)
#define FTDCUSERAPI C!!@functionid!!FtdcUserApi
#endif
#if !defined(FTDCUSERSPI)
#define FTDCUSERSPI C!!@functionid!!FtdcUserSpi
#endif
#if !defined(FTDCREQUSERLOGINFIELD)
#define FTDCREQUSERLOGINFIELD C!!@functionid!!FtdcReqUserLoginField
#endif
#if !defined(FTDCREQUSERLOGINFIELD)
#define FTDCREQUSERLOGINFIELD C!!@functionid!!FtdcReqUserLoginField
#endif
#if !defined(FTDCDEPTHMARKETDATAFIELD)
#define FTDCDEPTHMARKETDATAFIELD C!!@functionid!!FtdcDepthMarketDataField
#endif
#if !defined(FTDCDISSEMINATIONINFOFIELD)
#define FTDCDISSEMINATIONINFOFIELD C!!@functionid!!FtdcDisseminationField
#endif
#if !defined(FTDCMEMDBFIELD)
#define FTDCMEMDBFIELD C!!@functionid!!FtdcMemDbField
#endif

#include "versionValue.h"

#ifndef SUFFIX_STR
#define SUFFIX_STR  "L300"
#endif


#ifdef TRADERAPI
	#ifdef WIN32
		#define INTERFACE_PRODUCT_INFO "!!@fileid!!TraderAPI Win32 "QVERSION" "SUFFIX_STR	
	#endif
	#ifdef UNIX
		#ifdef LINUX
			#define INTERFACE_PRODUCT_INFO "!!@fileid!!TraderAPI Lnx64 "QVERSION" "SUFFIX_STR
		#else
			#define INTERFACE_PRODUCT_INFO "!!@fileid!!TraderAPI Unx64 "QVERSION" "SUFFIX_STR	
		#endif	
	#endif	
#endif

#ifdef MDUSERAPI
	#ifdef WIN32
		#define INTERFACE_PRODUCT_INFO "!!@fileid!!MdAPI Win32 "QVERSION" "SUFFIX_STR	
	#endif
	#ifdef UNIX
		#ifdef LINUX
			#define INTERFACE_PRODUCT_INFO "!!@fileid!!MdAPI Lnx64 "QVERSION" "SUFFIX_STR
		#else
			#define INTERFACE_PRODUCT_INFO "!!@fileid!!MdAPI Unx64 "QVERSION" "SUFFIX_STR	
		#endif	
	#endif	
#endif

#ifdef USERAPI
	#ifdef WIN32
		#define INTERFACE_PRODUCT_INFO "!!@fileid!!UserAPI Win32 "QVERSION" "SUFFIX_STR	
	#endif
	#ifdef UNIX
		#ifdef LINUX
			#define INTERFACE_PRODUCT_INFO "!!@fileid!!UserAPI Lnx64 "QVERSION" "SUFFIX_STR
		#else
			#define INTERFACE_PRODUCT_INFO "!!@fileid!!UserAPI Unx64 "QVERSION" "SUFFIX_STR	
		#endif	
	#endif	
#endif


#ifndef INTERFACE_PRODUCT_INFO
#define INTERFACE_PRODUCT_INFO "!!@fileid!!API "QVERSION" "SUFFIX_STR
#endif

#ifndef FTDCUSERAPI_H
#define FTDCUSERAPI_H "!!@fileid!!FtdcUserApi.h"
#endif

#ifndef TE_RESUME_TYPE
#define TE_RESUME_TYPE !!@macroid!!_TE_RESUME_TYPE
#endif
#ifndef TERT_RESTART
#define TERT_RESTART   !!@macroid!!_TERT_RESTART
#endif
#ifndef TERT_RESUME 
#define TERT_RESUME    !!@macroid!!_TERT_RESUME
#endif
#ifndef TERT_QUICK 
#define TERT_QUICK   !!@macroid!!_TERT_QUICK
#endif

#endif
