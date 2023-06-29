#include "StdAfx.h"
#include "LowUpgradeApi.h"
#include <string>
using namespace std;

typedef unsigned char       BYTE;
typedef unsigned short      WORD;

/*命令通用头，请求类命令无视errorcode，errorcodedetail*/
typedef struct _HEAD
{
	BYTE				byszReserved[4];		//命令头4字节保留。
	BYTE				byLU;				//设备类型
	BYTE				byIFCODE;			//cmd-1,resp-2,att-3
	BYTE				byCMD;				//命令类型
	union
	{
		BYTE            aucErrCode[3];
		struct  
		{
			BYTE		byErrorCode;
			BYTE		byszErrorCodeDetail[2];
		};
	};        
	BYTE				byszReserved1[2];
	WORD				wErrStatus;
	BYTE				byszReserved2[0x0D - 0x09];
	WORD				wDataLen;		
}ST_HEAD, *PST_HEAD;


extern int UpdateOutputInfo(string strdata);
extern int UpdateOutputResult(string strdata);
extern int UpdateCurVersion(LONG lProcNum, char *pcFileVersion);

LowUpgradeApi::LowUpgradeApi(void)
{
	m_pobjDrv = NULL;
}

LowUpgradeApi::~LowUpgradeApi(void)
{
	DWORD dwRet = -1;
	if(NULL != m_pobjDrv)
	{
		if(0 != m_DeviceHandle)
		{
			dwRet = m_pobjDrv->DeviceClose(m_DeviceHandle,200,&m_ErrInfo);
			m_pobjDrv->FreeUsb11Drv();
			delete m_pobjDrv;
			m_pobjDrv = NULL;
			m_DeviceHandle = 0;
		}							
	}

}


long LowUpgradeApi::ChannelEstablish(FileInfo* pFileInfo)
{
	int MemSize = pFileInfo->lFileInfoSize + 1;
	if(MemSize > 512*1024)
	{
		return 1;
	}

	unsigned char *pucData=new unsigned char[MemSize] ;
	pucData[0] = EN_UPGRADE_CMD_MAKE_CHANNEL;
	memcpy(&pucData[1],pFileInfo,MemSize-1);
	Send(pucData,MemSize);
	printf("ChannelReq\n");

	long size = 4;
	long ChannelAck;
	Recv((unsigned char *)&ChannelAck,size);
	printf("ChannelAck\n");

	delete [] pucData;
	
	return ChannelAck;
}

long LowUpgradeApi::GetPacketSize(void)
{
	unsigned char *pData=new unsigned char[1] ;
	pData[0] = EN_UPGRADE_CMD_PACKET_SIZE;
	Send(pData,1);
	printf("PacketSizeReq\n");

	long size = 4;
	long Length = 0;
	Recv((unsigned char *)&Length,size);
	printf("PacketSizeAck\n");

	delete [] pData;

	return Length;
}

long LowUpgradeApi::SendUpdataData(unsigned char* pucData, long lLength)
{
	unsigned char *plData=new unsigned char[lLength+1] ;
	plData[0] = EN_UPGRADE_CMD_UPGRADE_FILE;
	memcpy(&plData[1],pucData,lLength);

	Send(plData,lLength+1);
	delete []plData;
	plData = NULL;

	long size = sizeof(ST_UPDATA_FILE_PACKET) - 1;
	ST_UPDATA_FILE_PACKET stUpFileAck ;

	Recv((unsigned char *)&stUpFileAck,size);

	return (long)stUpFileAck.enTranceferResult;
}

long LowUpgradeApi::ForceRecovery(long lProcid, long lVerid)
{
	ST_RECOVERY_INFO stInfo;
	unsigned char *pData=new unsigned char[1+ sizeof(ST_RECOVERY_INFO)] ;
	pData[0] = EN_UPGRADE_CMD_FORCE_BACKUP;

	stInfo.lProcid = lProcid;
	stInfo.lVer = lVerid;
	long size = sizeof(ST_RECOVERY_INFO) + 1;
	memcpy(&pData[1], &stInfo, sizeof(ST_RECOVERY_INFO));
	Send(pData,size);
	size = 4;
	unsigned char buff[20];
	Recv(buff,size);
	delete [] pData;

	return 0;
}

long LowUpgradeApi::Restart(int iType)
{
	ST_RESTART stInfo;
	unsigned char *pData=new unsigned char[1 + sizeof(ST_RESTART)] ;
	pData[0] = EN_UPGRADE_CMD_RESTART_APP;

	stInfo.iType = iType;
	memcpy(&pData[1], &stInfo, sizeof(ST_RESTART));
	long size = sizeof(ST_RESTART) + 1;
	Send(pData,size);
	printf("RestartReq\n");

	size = 4;
	long lResult = 0;
	Recv((unsigned char *)&lResult,size);
	printf("RestartAck\n");

	delete [] pData;

	return lResult;

}

long LowUpgradeApi::GetUpgradeProcNum(void)
{
	unsigned char *pData=new unsigned char[1] ;
	pData[0] = EN_UPGRADE_CMD_GET_UPGRADE_PROC_NUM;
	Send(pData,1);
	printf("GetUpgradeProcNumReq\n");

	long size = 4;
	long lResult = 0;
	Recv((unsigned char *)&lResult,size);
	printf("GetUpgradeProcNumAck\n");

	delete [] pData;
	if(0 == lResult)
	{
		printf("==\n");
	}

	return lResult;

}

long LowUpgradeApi::GetVerCount(long lProcnum)
{
	int iSize = sizeof(lProcnum) + 1;
	unsigned char *pData=new unsigned char[iSize] ;
	pData[0] = EN_UPGRADE_CMD_GET_UPGRADE_VER_COUNT;
	memcpy(&pData[1], &lProcnum, iSize  - 1);

	
	Send(pData,iSize);
	printf("GetVerCountReq\n");

	long size = 4;
	long lResult = 0;
	Recv((unsigned char *)&lResult,size);
	printf("GetVerCountAck\n");

	delete [] pData;

	return lResult;

}

long LowUpgradeApi::GetCurName(long lProcNum, char *pcFileName)
{
	int iSize = sizeof(lProcNum) + 1;
	unsigned char *pData=new unsigned char[iSize] ;
	pData[0] = EN_UPGRADE_CMD_GET_UPGRADE_CUR_NAME;
	memcpy(&pData[1], &lProcNum, iSize  - 1);


	Send(pData,iSize);
	printf("GetCurNameReq\n");

	long size = 64;
	long lResult = 0;
	Recv((unsigned char *)pcFileName,size);
	printf("GetCurNameAck\n");

	delete [] pData;

	return 0;
}

long LowUpgradeApi::GetCurVersion(PST_VERSION pstVer, char *pcVersion)
{
	int iSize = sizeof(ST_VERSION) + 1;
	unsigned char *pData=new unsigned char[iSize];
	pData[0] = EN_UPGRADE_CMD_GET_UPGRADE_CUR_VERSION;
	memcpy(&pData[1], pstVer, iSize  - 1);

	Send(pData,iSize);
	TRACE("GetCurVersionReq\n");

	long size = VERSION_BUFFER_SIZE;
	long lResult = 0;
	Recv((unsigned char *)pcVersion,size);
	TRACE("GetCurVersionAck\n");

	delete [] pData;
	return 0;
}

long LowUpgradeApi::GetIp(char *pcIp)
{
	int iSize =  1;
	unsigned char ucData= 0;
	ucData = EN_UPGRADE_CMD_GET_IP;

	Send(&ucData,iSize);
	TRACE("GetIPReq\n");

	long size = VERSION_BUFFER_SIZE;
	long lResult = 0;
	Recv((unsigned char *)pcIp,size);
	TRACE("GetIP\n");

	return 0;
}

long LowUpgradeApi::GetMainCtrlVersion(PST_VERSION pstVer, char *pcVersion)
{
	int iSize = sizeof(ST_VERSION) + 1;
	unsigned char *pData=new unsigned char[iSize];
	pData[0] = EN_UPGRADE_CMD_GET_UPGRADE_CUR_VERSION;
		
	TRACE("GetMainCtrlVersionReq\n");

	long size = VERSION_BUFFER_SIZE;
	long lResult = 0;
	for(int i=0; i< DEVICE_COUNT;i++)
	{		
		pstVer->iIndex = i;
		memcpy(&pData[1], pstVer, iSize  - 1);
		Send(pData,iSize);
		Recv((unsigned char *)pcVersion, size);
		UpdateCurVersion(pstVer->lProcNum, pcVersion);
	}		
	TRACE("GetMainCtrlVersionAck\n");
	delete [] pData;
	
	return 0;
}

int LowUpgradeApi::Send(unsigned char * pucData, long lLength)
{
	//m_iId,pData,Length

	PST_HEAD pData = (PST_HEAD)new char[sizeof(ST_HEAD)+lLength];
	pData->byLU = 0x07;
	pData->byCMD = 0xF0;
	pData->byIFCODE = 1;
	pData->wDataLen = lLength;
	memcpy((unsigned char*)(&(pData->wDataLen))+2,pucData,lLength);
	
	if(m_pobjDrv != NULL)
	{
		m_pobjDrv->DeviceSend(m_DeviceHandle,200,pData,sizeof(ST_HEAD)+lLength,&m_ErrInfo);
	}
	delete []pData;
	return 0;
}



int LowUpgradeApi::GetData(unsigned char *pucBuf,long lLength)
{
	int ReadSize = lLength;
	DWORD RealReadSize = 0;
	WORD dwResult = -1;
	int iRet = -1;

	for(;ReadSize != 0;)
	{
		if(m_pobjDrv != NULL)
		{
			dwResult = m_pobjDrv->DeviceReceive(m_DeviceHandle,2000,pucBuf+lLength-ReadSize,ReadSize,&RealReadSize,&m_ErrInfo);			
		}
		if(0 == dwResult)
		{
			ReadSize -= RealReadSize;
		}
		else
		{
			break;
		}
	}

	if(0 == ReadSize)
	{
		iRet = 0;
	}
	return iRet;
}

int LowUpgradeApi::Recv(unsigned char *pData, long &rLength)
{
	//m_Id,pData,Length
	int iRet = -1;
	long lRecvLength = sizeof(ST_HEAD)+rLength;
	PST_HEAD pRecvData = (PST_HEAD)new char[lRecvLength];
//	pData->byLU = 0x07;
//	pData->byCMD = 0xF0;
//	pData->byIFCODE = 1;
//	pData->wDataLen = lLength;
//	memcpy((unsigned char*)(&(pData->wDataLen))+2,pucData,lLength);

	if(m_pobjDrv != NULL)
	{
		iRet = GetData((PBYTE)pRecvData,lRecvLength);
	}
	
	if(iRet == 0)
	{
		memcpy(pData,(unsigned char*)(&(pRecvData->wDataLen))+2,rLength);
	}	

	delete []pRecvData;
	return iRet;
}



void LowUpgradeApi::SetId(int iId, int iflag)
{
	m_iId = iId;
	DWORD dwRet = -1;

	if(m_iId == EN_UPGRADE_MAIN_CTRL)
	{
		switch(iflag)
		{
		case 0:
			if(NULL != m_pobjDrv)
			{
				if(0 != m_DeviceHandle)
				{
					dwRet = m_pobjDrv->DeviceClose(m_DeviceHandle,200,&m_ErrInfo);
					if(0 == dwRet)
					{
						delete m_pobjDrv;
						m_pobjDrv = NULL;
						//UpdateOutputResult("Close usb device success! \r\n");
					}
					else
					{
						//UpdateOutputResult("Close usb device fail! \r\n");
					}
					m_DeviceHandle = 0;
				}							
			}

			break;

		case 1:
			if(m_pobjDrv == NULL)
			{
				m_pobjDrv = new CUsb11Drv;
				if (m_pobjDrv->LoadUsb11Drv ("D_USB11.dll"))
				{			
					dwRet = m_pobjDrv->DeviceOpen((LPCTSTR)"CC",2000,&m_DeviceHandle,&m_ErrInfo);
					if(0 != dwRet)
					{
						//UpdateOutputResult("Open usb device fail! \r\n");
					}
					else
					{
						//UpdateOutputResult("Open usb device success! \r\n");

					}
				}
			}
			else
			{
				dwRet = m_pobjDrv->DeviceOpen((LPCTSTR)"CC",2000,&m_DeviceHandle,&m_ErrInfo);
				if(0 != dwRet)
				{
					//UpdateOutputResult("Open usb device fail! \r\n");
				}
				else
				{
					//UpdateOutputResult("Open usb device success! \r\n");
				}
			}

			break;

		default:
			break;
		}
		
	}
}
