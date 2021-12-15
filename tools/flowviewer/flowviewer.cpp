#include "public.h"
#include "XtpPackageDesc.h"
#include "XTPPackage.h"

int main(int argc, char *argv[])
{
	if (argc != 5)
	{
		printf("用法: flowviewer flowfilename(含.con) tid(十进制,0表示所有) seqno_lower(seqno下限,0表示无限制) seqno_upper(seqno上限,0表示无限制)\n");
		return -1;
	}
	
	int nTid = atoi(argv[2]);
	int nSeqNoLower=atoi(argv[3]);//下限
	int nSeqNoUpper=atoi(argv[4]);//上限

	FILE *fp = fopen(argv[1], "rb");
	if (fp == NULL)
	{
		printf("can't open flow file [%s]\n", argv[1]);
		return -2;
	}

	CXTPPackage xtpPackage;
	xtpPackage.ConstructAllocate(10000, XTPHLEN);
	for (int i=0;;i++)
	{
		xtpPackage.AllocateMax();
		DWORD size = 0;
		if (fread(&size, sizeof(DWORD), 1, fp) != 1)
		{
			printf("read package size error\n");
			break;
		}
		CHANGE_ENDIAN(size);
		if (size > 10000)
		{
			printf("too large package\n");
			break;
		}
		printf("FLOW ID=[%d], SIZE=[%d]\n", i, size);
		if (fread(xtpPackage.Address(), 1, size, fp) != size)
		{
			printf("read package content error\n");
			break;
		}
		xtpPackage.Truncate(size);
		if (!xtpPackage.ValidPackage())
		{
			printf("invalid package\n");
			break;
		}
		if(nTid!=0&&xtpPackage.GetXTPHeader()->Tid != nTid)
		{
			//不符合tid的限制,忽略
			continue;
		}	
		if(nSeqNoLower!=0&&xtpPackage.GetXTPHeader()->SequenceNo<nSeqNoLower)
		{
			//小于seqno的下限，忽略
			continue;
		}
		if(nSeqNoUpper!=0&&xtpPackage.GetXTPHeader()->SequenceNo>nSeqNoUpper)
		{
			//大于seqno的上限，退出
			break;
		}	
		if (xtpPackage.GetTid()!=TID_NtfMemtableChange)
		{
			XTP_PACKAGE_DEBUG(&xtpPackage);
		}
		else
		{
			xtpPackage.OutputHeader(CLogger::GetInstance());
			CLogger::GetInstance()->output(LL_DEBUG, "\tXTP PACKAGE CONTENT START\n");

			char buf[1000];
			char buf1[1000];
			CMemtableChangeField fld;
			fld.dumpLine(buf,1000);
			XTP_GET_SINGLE_FIELD(&xtpPackage,&fld);
			fld.dumpLine(buf,1000);

			CLogger::GetInstance()->output(LL_DEBUG, "[%s]\n", buf);

			if (!strcmp(fld.MemTableName.getValue(),"t_Order"))
			{
				COrderField fld1;
				XTP_GET_SINGLE_FIELD(&xtpPackage,&fld1);
				fld1.dumpLine(buf1,1000);
				CLogger::GetInstance()->output(LL_DEBUG, "[%s]\n", buf1);
			}
			if (!strcmp(fld.MemTableName.getValue(),"t_Trade"))
			{
				CTradeField fld1;
				XTP_GET_SINGLE_FIELD(&xtpPackage,&fld1);
				fld1.dumpLine(buf1,1000);
				CLogger::GetInstance()->output(LL_DEBUG, "[%s]\n", buf1);
			}
			if (!strcmp(fld.MemTableName.getValue(),"t_InvestorAccount"))
			{
				CInvestorAccountField fld1;
				XTP_GET_SINGLE_FIELD(&xtpPackage,&fld1);
				fld1.dumpLine(buf1,1000);
// 				if (fld.MemtableChangeType==MTC_INSERT)
// 				{
// 					printf("插入\n");
// 				}
// 				if (fld.MemtableChangeType==MTC_UPDATE)
// 				{
// 					printf("修改\n");
// 				}
				CLogger::GetInstance()->output(LL_DEBUG, "[%s]\n", buf1);
			}	
			if (!strcmp(fld.MemTableName.getValue(),"t_InvestorPosition"))
			{
				CInvestorPositionField fld1;
				XTP_GET_SINGLE_FIELD(&xtpPackage,&fld1);
				fld1.dumpLine(buf1,1000);
// 				if (fld.MemtableChangeType==MTC_INSERT)
// 				{
// 					printf("插入\n");
// 				}
// 				if (fld.MemtableChangeType==MTC_UPDATE)
// 				{
// 					printf("修改\n");
// 				}
				CLogger::GetInstance()->output(LL_DEBUG, "[%s]\n", buf1);
			}				
			CLogger::GetInstance()->output(LL_DEBUG, "\tXTP PACKAGE CONTENT END\n");
		}

//		if (xtpPackage.GetXTPHeader()->Tid == TID_InitCurrPartPosiLimitDetail)
//		{
//			printf("---------------------------\n");
//			char buf[10000];
//			CNamedFieldIterator itor = xtpPackage.GetNamedFieldIterator(&CCurrPartPosiLimitDetailField::m_Describe);
//			while (!itor.IsEnd())
//			{
//				itor.Retrieve(buf);
//				XTP_FIELD_DEBUG(stdout, buf, &CCurrPartPosiLimitDetailField::m_Describe);
//				itor.Next();
//			}
//			printf("---------------------------\n");
//		}
	}

	fclose(fp);
	return 0;
}
