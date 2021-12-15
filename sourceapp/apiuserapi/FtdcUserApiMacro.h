/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company 上海量投网络科技有限公司
///@file FtdcUserApiMacro.h
///@brief 定义了客户端接口中区分交易所的宏
///@history 
/////////////////////////////////////////////////////////////////////////
#if !defined(_QDPFTDCUSERAPIMACRO_H)
#define _QDPFTDCUSERAPIMACRO_H
#if !defined(FTDCUSERAPI)
#define FTDCUSERAPI CQdpFtdcUserApi
#endif
#if !defined(FTDCUSERSPI)
#define FTDCUSERSPI CQdpFtdcUserSpi
#endif
#if !defined(FTDCREQUSERLOGINFIELD)
#define FTDCREQUSERLOGINFIELD CQdpFtdcReqUserLoginField
#endif
#if !defined(FTDCREQUSERLOGINFIELD)
#define FTDCREQUSERLOGINFIELD CQdpFtdcReqUserLoginField
#endif
#if !defined(FTDCDEPTHMARKETDATAFIELD)
#define FTDCDEPTHMARKETDATAFIELD CQdpFtdcDepthMarketDataField
#endif
#if !defined(FTDCDISSEMINATIONINFOFIELD)
#define FTDCDISSEMINATIONINFOFIELD CQdpFtdcDisseminationField
#endif
#if !defined(FTDCMEMDBFIELD)
#define FTDCMEMDBFIELD CQdpFtdcMemDbField
#endif

#include "versionValue.h"

#ifndef SUFFIX_STR
#define SUFFIX_STR  "L300"
#endif


#ifdef TRADERAPI
	#ifdef WIN32
		#define INTERFACE_PRODUCT_INFO "QdpTraderAPI Win32 "QVERSION" "SUFFIX_STR	
	#endif
	#ifdef UNIX
		#ifdef LINUX
			#define INTERFACE_PRODUCT_INFO "QdpTraderAPI Lnx64 "QVERSION" "SUFFIX_STR
		#else
			#define INTERFACE_PRODUCT_INFO "QdpTraderAPI Unx64 "QVERSION" "SUFFIX_STR	
		#endif	
	#endif	
#endif

#ifdef MDUSERAPI
	#ifdef WIN32
		#define INTERFACE_PRODUCT_INFO "QdpMdAPI Win32 "QVERSION" "SUFFIX_STR	
	#endif
	#ifdef UNIX
		#ifdef LINUX
			#define INTERFACE_PRODUCT_INFO "QdpMdAPI Lnx64 "QVERSION" "SUFFIX_STR
		#else
			#define INTERFACE_PRODUCT_INFO "QdpMdAPI Unx64 "QVERSION" "SUFFIX_STR	
		#endif	
	#endif	
#endif

#ifdef USERAPI
	#ifdef WIN32
		#define INTERFACE_PRODUCT_INFO "QdpUserAPI Win32 "QVERSION" "SUFFIX_STR	
	#endif
	#ifdef UNIX
		#ifdef LINUX
			#define INTERFACE_PRODUCT_INFO "QdpUserAPI Lnx64 "QVERSION" "SUFFIX_STR
		#else
			#define INTERFACE_PRODUCT_INFO "QdpUserAPI Unx64 "QVERSION" "SUFFIX_STR	
		#endif	
	#endif	
#endif


#ifndef INTERFACE_PRODUCT_INFO
#define INTERFACE_PRODUCT_INFO "QdpAPI "QVERSION" "SUFFIX_STR
#endif

#ifndef FTDCUSERAPI_H
#define FTDCUSERAPI_H "QdpFtdcUserApi.h"
#endif

#ifndef TE_RESUME_TYPE
#define TE_RESUME_TYPE QDP_TE_RESUME_TYPE
#endif
#ifndef TERT_RESTART
#define TERT_RESTART   QDP_TERT_RESTART
#endif
#ifndef TERT_RESUME 
#define TERT_RESUME    QDP_TERT_RESUME
#endif
#ifndef TERT_QUICK 
#define TERT_QUICK   QDP_TERT_QUICK
#endif

#endif
