// UdpServer.cpp: implementation of the CMdUdpSvr class.
//
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "SocketInit.h"
#include "MdUdpSvr.h"
#include "UdpChannel.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMdUdpSvr::CMdUdpSvr(CServiceName *pName)
:CServerBase(pName), m_ServiceName(pName->GetLocation())
{
	m_bConnected = false;
	
	m_nID = socket(AF_INET, SOCK_DGRAM, 0); //����UDP�׽���

	/* set reuse and non block for this socket */
	int on=1;
	setsockopt(m_nID, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
	//���ù㲥����, add by wang.xiping 20071008
	setsockopt(m_nID, SOL_SOCKET, SO_BROADCAST, (char *)&on, sizeof(on));
#ifdef HP_UX
	setsockopt(m_nID, SOL_SOCKET, SO_REUSEPORT, (char *)&on, sizeof(on));
#endif
	
	struct sockaddr_in servaddr; //IPv4�׽ӿڵ�ַ����
	memset(&servaddr, 0, sizeof(servaddr)); //��ַ�ṹ����
	servaddr.sin_family = AF_INET; //IPv4Э��
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//�ں�ָ����ַ
	servaddr.sin_port = htons(m_ServiceName.GetPort()); //�˿�
	
	//����Э���ַ,�󶨶˿�
	if (bind(m_nID, (sockaddr *) &servaddr, sizeof(servaddr)) != 0)
	{
		RAISE_RUNTIME_ERROR("bind fail");
	}
}

CMdUdpSvr::~CMdUdpSvr()
{

}

CChannel *CMdUdpSvr::Accept(int wait)
{
	if (m_bConnected)
	{
		return NULL;
	}
	m_bConnected = true;
	return new CUdpChannel(m_nID, m_ServiceName.GetHost(), m_ServiceName.GetPort()+1);
}

int CMdUdpSvr::GetId(void)
{
	if (!m_bConnected)
		return -1;
	else
		return 0;
}
