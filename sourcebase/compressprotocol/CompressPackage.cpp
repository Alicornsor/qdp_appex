// CompressPackage.cpp: implementation of the CCompressPackage class.
//
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "CompressPackage.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCompressPackage::CCompressPackage()
{

}

CCompressPackage::~CCompressPackage()
{

}

DWORD CCompressPackage::GetActiveID()
{
	return (DWORD)m_header.Type;
}

int CCompressPackage::ValidPackage()
{
	int pkglen = Length();
	if(pkglen < CRPHLEN){			//包头尚未收全
		return -1;
	}

	m_header.FromStream(m_pHead);

	Pop(CRPHLEN);

	return pkglen;
}

int CCompressPackage::MakePackage()
{
	char *buf = Push(CRPHLEN);
	if(buf == NULL)
	{
		return -1;
	}

	m_header.ToStream(buf);
	
	return 0;
}
