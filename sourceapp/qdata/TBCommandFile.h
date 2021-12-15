// TBCommandFile.h: interface for the CTBCommandFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TBCOMMANDFILE_H__6F0E5A7C_8496_449A_B06F_A12822C7FFFB__INCLUDED_)
#define AFX_TBCOMMANDFILE_H__6F0E5A7C_8496_449A_B06F_A12822C7FFFB__INCLUDED_
#include "platform.h"
#include "customDataType.h"

enum {
	FILENAMELENGTH = 100,
	MAXLINELENGTH = 1000,
}; 

struct sTBCMD
{
	CTradingDayType TradingDay;
	CCommandNoType CommandNo;
	CDateType CommandDate;
	CTimeType CommandTime;
	CCommandTypeType CommandType;
	CFieldNameType FieldName;
	CFieldContentType FieldContent;
};

class CTBCommandFile
{
public:
	CTBCommandFile(const char *dataFile);
	virtual ~CTBCommandFile();

	bool AppendCommand(const struct sTBCMD &CMDPackage);
	bool ReadCommand(struct sTBCMD &CMDPackage);
	CCommandNoType  GetLastCommandNo();
private:
	void Lock();
	void UnLock();
	int  Gets(FILE *fp,char *buffer);
	inline void RTrim(char *buffer);
	inline void FZero(char *buffer);
	
private:
	char m_sDataFile[FILENAMELENGTH];
};

inline void CTBCommandFile::RTrim(char *buffer)
{
	int notSpacePos=0;
	for(int i=0;i<MAXLINELENGTH;i++)
	{
		if( *(buffer+i)=='\n')
		{
			*(buffer+i)=0;
			break;
		}
		else if ( *(buffer+i)==0 )
		{
			break;
		}
		else if ( *(buffer+i)!=' ')
		{
			notSpacePos=i;
		}

	}
	*(buffer+notSpacePos+1)=0;
	return ;	
}

inline void CTBCommandFile::FZero(char *buffer)
{
	for(int i=0;i<MAXLINELENGTH;i++)
	{
		if ( *(buffer+i)==0 )
		{
			break;
		}
		else 
		{
			*(buffer+i)=0 ;
		}

	}
	return ;	
}

#endif // !defined(AFX_TBCOMMANDFILE_H__6F0E5A7C_8496_449A_B06F_A12822C7FFFB__INCLUDED_)
