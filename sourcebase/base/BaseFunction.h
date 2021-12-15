/////////////////////////////////////////////////////////////////////////
///@system 量投系统基础库
///@company 上海量投网络科技有限公司
///@file CBaseFunction.h 
///@brief定义需要用到的公共函数
///@history 
///20151012	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef _BaseFunction_H_
#define _BaseFunction_H_

#include "platform.h"

string& Txttrim(string &s);
vector<string> Txtsplit(const string& str, string separate_character);

#ifdef WIN32
//此函数在windows情况下使用
////////////////////////////////////////////////////////////////////////////
// 函数名： GetMacByCmd(char *lpszMac)
// 参数：
//      输入： void
//      输出： lpszMac,返回的MAC地址串
// 返回值：
//      TRUE:  获得MAC地址。
//      FALSE: 获取MAC地址失败。
// 过程：
//      1. 创建一个无名管道。
//      2. 创建一个IPCONFIG 的进程，并将输出重定向到管道。
//      3. 从管道获取命令行返回的所有信息放入缓冲区lpszBuffer。
//      4. 从缓冲区lpszBuffer中获得抽取出MAC串。
//
//  提示：可以方便的由此程序获得IP地址等其他信息。
//        对于其他的可以通过其他命令方式得到的信息只需改变strFetCmd 和 
//        str4Search的内容即可。
///////////////////////////////////////////////////////////////////////////
bool GetMacByCmd(char *lpszMac);
#endif

bool GetIPAddress(vector<string> *pIPVec);

#endif
