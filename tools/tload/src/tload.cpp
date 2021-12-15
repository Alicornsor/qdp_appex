#include "QdpFtdcUserApiDataType.h"

#include "CConfig.h"
#include "utility.h"
#include "platform.h"
#include "Processor.h"
#include "ProcessCmd.h"
#include "CFilelogService.h"

CProcessor *pProcessor;

const char *INI_FILE_NAME = "tload.ini";
bool	bWaitActionFlag = false;
bool    bCmdLFlag = false;
ST_MARCO  sMarcoArray[200]; //	全局宏应用
int		  iMarcoCount = 0;	//	宏总数
bool bFastFlag = false;
ST_INPUT_CMD  *sInputCmd;
ST_INPUT_CMD  * sInputCmdArray;
list<int>  orderActionList; //xuzh begin 增加已报订单的本地保单号
int iProcessorCount = 0;


char  m_TradeIp[30];
char  m_DefaultUser[30];
char  m_DefaultPass[30];
char  m_ExternCmd[30];

int		iTotalCmdNum  = 0;
int		iCurCmdPos	  = 0;	// 当前提交的InputCmd 的 序号
int		iLastCmdPos	  = 0;	// 最后一笔委托应答的InputCmd 的 序号
int		iWaitOrderPos = 0;  // 在途委托总数 
int		iTotalOrderCnt= 0;  // 总委托总数 
UF_INT8    lReqTime=0;    //请求开始时间
UF_INT8    lRspTime=0;	   //请求结束时间


int main(int argc,char *argv[])
{
	if(strcmp(argv[argc-1],"-v") == 0)
	{
		ShowMsg("20150719 for qdp test \n");
		exit(0);
	}

	int				iPos;
	char			infile[150],outfile[150];
	FILE			*fp_in;
	FILE			*fp_out;
	char			szbuf[2000];


	CConfig *pConfig = new CConfig(INI_FILE_NAME);	
	char *syslogFileName=pConfig->getConfig("SyslogPath");
	CMonitorIndex::init(CFilelogService::CreateInstance(argc,argv,syslogFileName),pConfig);

	strcpy(m_TradeIp,pConfig->getConfig("TradeIp"));
	strcpy(m_DefaultUser,pConfig->getConfig("DefaultUser"));
	strcpy(m_DefaultPass,pConfig->getConfig("DefaultPass"));
	strcpy(m_ExternCmd,pConfig->getConfig("ExternCmd"));


	//记录失败的次数，当失败次数超过 failtimes时，说明及其不稳定，应该退出。
	int imaxfailtimes=atoi(pConfig->getConfig("MAX_FAIL_TIMES"));
	int ifailtimes=0;

	int MAX_CMD_NUM=atoi(pConfig->getConfig("MAX_CMD_NUM"));
	sInputCmdArray = new ST_INPUT_CMD[MAX_CMD_NUM];

	if(argc < 3)
	{
		 printf("\n QDP 基准测试工具 V1.0  build 20150723 \n"); 
		 printf("\n 用法: TLOAD 输入文件 输出文件 \n");
		 printf("\n ");
		 exit(1);
	}

	strcpy(infile,argv[1]);
	strcpy(outfile,argv[2]);

	fp_in = fopen(infile,"rt");
	if(fp_in == NULL)
	{
		sprintf(szbuf,"can not open file [%s]",infile);
		printf(szbuf);
		exit(1);
	}

	fp_out = fopen(outfile,"wt");
	if(fp_out == NULL)
	{
		sprintf(szbuf,"can not open file [%s]",outfile);
		printf(szbuf);
		exit(1);
	}

	while(fgets(szbuf,1023,fp_in) != NULL)
	{
		// 注释行，跳过
		trim(szbuf);
		delFrontCh(szbuf,'\n');
		if(szbuf[0] == ';' || szbuf[0] == 0x0 || szbuf[0] == '/'|| szbuf[0] == '#')	
			continue;
		DecodeInputLine(szbuf,sInputCmdArray[iTotalCmdNum]);		
		iTotalCmdNum ++;
	}
	fclose(fp_in);

	for(iPos = 0;iPos < iTotalCmdNum;iPos++)
	{
		sInputCmd = &sInputCmdArray[iPos];
		sInputCmd->iRowCount = 1;	// init
		sInputCmd->bReciveRsp=true;	// init

		iCurCmdPos  = iPos;

		if(strcmp(sInputCmd->sCmdType,"SKIP") == 0)
		{
		  if(sInputCmd->iRepeatNum > 0)
		  {
			sInputCmd->iRepeatNum --;
			if(bWaitActionFlag != true)
			{
				ShowMsg("%s,指令跳转",sInputCmd->sCmdNo);
				ShowMsg(" ==> ");
				ShowMsg(" 成功 , SKIP  %d 条指令, 剩余执行次数 %d \n",sInputCmd->ReqField.Volume,sInputCmd->iRepeatNum);
			}				
			iPos  = iPos + sInputCmd->ReqField.Volume - 1;
		  }
			continue;
		}

		if(strcmp(sInputCmd->sCmdType,"JUDGE") == 0)
		{
			ShowMsg("%s,逻辑判定",sInputCmd->sCmdNo);
			ShowMsg(" ==> ");
			
 			if(CheckCondition(iPos) == true)
			{
				if(bWaitActionFlag != true)
					ShowMsg(" 成功 , 跳过 %d 条指令 \n",sInputCmd->ReqField.Volume);
				iPos  = iPos + sInputCmd->ReqField.Volume - 1;
			}
			else
				ShowMsg(" 失败,继续下一指令 ");
			continue;
		}

		int iRet = ProcessCmd(sInputCmd,fp_out,iPos);

		//20140516 如果上述指令执行失败，考虑重新执行
		if(iRet!=0)
		{
			ShowMsg("reqerror 错误代码: %d,resend!\n ",iRet);
			//本地保单号回退
			if(strcmp(sInputCmd->sCmdType,"ORDER") == 0)
				pProcessor->m_iLocalNo--;
			pProcessor->m_bReLogin = true;
			pProcessor->m_semAction.Lock(10);
			iPos --;
			ifailtimes++;
		}
		//20140519 xuzh 如果没有接受到rsp，说明服务端处理异常，需要重新发送相同的本地报单号的报单
		else 
		{
			if(!sInputCmd->bReciveRsp)
			{
				//没有收到回报
				ShowMsg("\n norsperror,resend!\n");
				//本地保单号回退
				if(strcmp(sInputCmd->sCmdType,"ORDER") == 0)
					pProcessor->m_iLocalNo--;
				pProcessor->m_bResend = true;
				pProcessor->m_pFfexFtdcUserApi->RegisterFront(pProcessor->m_sTradeRUL);
				printf("registe front !\n");
				pProcessor->m_bReLogin = true;
				pProcessor->m_semAction.Lock(10);
				iPos--;
				ifailtimes++;
			}
			else
			{
				if(pProcessor!=NULL)
					pProcessor->m_bResend = false;
			}
		}

		if(ifailtimes>imaxfailtimes)
		{
			ShowMsg("\n error: failtimes is %d, is larger than maxfailtimes %d !!\n",ifailtimes,imaxfailtimes);
			exit(9);
		}

		if( sInputCmd->iRepeatNum != 1 && sInputCmd->iRepeatNum>sInputCmd->iCount) 
		{
		  sInputCmd->iCount ++;
		  iPos --;		//	指针回拨
		}
		sInputCmd->iCycleTimes ++;

		if(bWaitActionFlag == true)
		{
		  //printf("\n");
		  printf(" --- %d ---- %d --- %d \r",pProcessor->m_nRequestID,pProcessor->m_nRecvCount,sInputCmd->iCycleTimes);
		  while (pProcessor->m_nRequestID - pProcessor->m_nRecvCount > 300)
		  {
			SLEEP_SECONDS(1);		
		  }
		  //printf("\n");
		}
	}
	  
	// 执行结果记入日志
	for(iPos = 0;iPos < iTotalCmdNum;iPos++)
	{
	///xuzh 20140511 这里的输出极为重要，是和场下冒烟比对的接口，此接口不能随便修改!
		
	 /* sprintf(szbuf,"%s,%d,%d,%0.2f,%0.2f,%0.2f,%s,%s,%s\n",
			sInputCmdArray[iPos].sCmdNo,
			sInputCmdArray[iPos].pRspInfo.ErrorID,
			sInputCmdArray[iPos].iRowCount,
			sInputCmdArray[iPos].dFrozenMargin,
			sInputCmdArray[iPos].dCurrMargin,
			sInputCmdArray[iPos].dCurMoney,
			sInputCmdArray[iPos].pRspInfo.ErrorMsg,
			sInputCmdArray[iPos].ReqField.OrderSysID,
			sInputCmdArray[iPos].sNote
			);*/

// 	  sprintf(szbuf,"CmdNo:%s,ErrorID:%d,ErrorMsg:%s,%s\n",
// 		  sInputCmdArray[iPos].sCmdNo,			  
// 		  sInputCmdArray[iPos].pRspInfo.ErrorID,			 
// 		  sInputCmdArray[iPos].pRspInfo.ErrorMsg,			  
// 		  sInputCmdArray[iPos].sNote
//			);

	  sprintf(szbuf,"%s,%d,%d,%0.2f,%s,%s=>%s\n",
			sInputCmdArray[iPos].sCmdNo,  
			sInputCmdArray[iPos].pRspInfo.ErrorID,
			sInputCmdArray[iPos].iRowCount,
			sInputCmdArray[iPos].dCurMoney,
			sInputCmdArray[iPos].pRspInfo.ErrorMsg,
			sInputCmdArray[iPos].ReqField.OrderSysID,
			sInputCmdArray[iPos].sNote);
	  
	  fwrite(szbuf,strlen(szbuf),1,fp_out);
	}
	fclose(fp_out);
	return 0;
};

