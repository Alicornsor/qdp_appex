/////////////////////////////////////////////////////////////////////////
///@system ��Ͷϵͳ������
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file CBaseFunction.h 
///@brief������Ҫ�õ��Ĺ�������
///@history 
///20151012	xuzh		�������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef _BaseFunction_H_
#define _BaseFunction_H_

#include "platform.h"

string& Txttrim(string &s);
vector<string> Txtsplit(const string& str, string separate_character);

#ifdef WIN32
//�˺�����windows�����ʹ��
////////////////////////////////////////////////////////////////////////////
// �������� GetMacByCmd(char *lpszMac)
// ������
//      ���룺 void
//      ����� lpszMac,���ص�MAC��ַ��
// ����ֵ��
//      TRUE:  ���MAC��ַ��
//      FALSE: ��ȡMAC��ַʧ�ܡ�
// ���̣�
//      1. ����һ�������ܵ���
//      2. ����һ��IPCONFIG �Ľ��̣���������ض��򵽹ܵ���
//      3. �ӹܵ���ȡ�����з��ص�������Ϣ���뻺����lpszBuffer��
//      4. �ӻ�����lpszBuffer�л�ó�ȡ��MAC����
//
//  ��ʾ�����Է�����ɴ˳�����IP��ַ��������Ϣ��
//        ���������Ŀ���ͨ���������ʽ�õ�����Ϣֻ��ı�strFetCmd �� 
//        str4Search�����ݼ��ɡ�
///////////////////////////////////////////////////////////////////////////
bool GetMacByCmd(char *lpszMac);
#endif

bool GetIPAddress(vector<string> *pIPVec);

#endif
