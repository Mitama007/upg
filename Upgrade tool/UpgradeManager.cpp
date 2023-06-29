#include "StdAfx.h"
#include "UpgradeManager.h"
#include <sstream>
using namespace std;

static UINT __cdecl  do_fn( LPVOID  p);

unsigned long get_file_size(const char *path);
extern int UpdateOutputInfo(string strdata);
extern void UptadeProgress(int iPosition);
extern int UpdateOutputResult(string strdata);
extern int UpdateProcNum(long lProcNum);
extern int UpdateVerCount(long lVer);
extern int UpdateCurName(LONG lProcNum, char *pcFileName);
extern void UpdatelistProgress(void);
extern void OutputResult(int iResult);
extern int UpdateCurVersion(LONG lProcNum, char *pcFileVersion);
extern int UpdateGetIp(char *pcIp);

CUpgradeManager::CUpgradeManager(void)
{
}

CUpgradeManager::~CUpgradeManager(void)
{
}

int CUpgradeManager::Init(Fn_Update_Callback fnCallback, void *pvPri)
{
	m_fnCallback = fnCallback;
	m_pvPri = pvPri;

	m_objQueCmd.Init();
	m_pThreadRecv = AfxBeginThread(do_fn, (LPVOID)this);
	
	return 0;
}

int CUpgradeManager::UnInit(void)
{
	m_objQueCmd.Uninit();

	return 0;
}


static UINT __cdecl  do_fn( LPVOID  p)
{
	CUpgradeManager *pObjUpgrade;

	pObjUpgrade = (CUpgradeManager *)p;

	return pObjUpgrade->RecvThreadFn();
}


int CUpgradeManager::RecvThreadFn(void)
{
	int iRet = -1;

	while(1)
	{
		iRet = ProcCmd();
		if(iRet < 0)
		{
			break;
		}
		Sleep(2);
	}
	
	m_objQueCmd.Uninit();
	return 0;
}


int CUpgradeManager::SendCmd(PST_SERVICE_CMD_DATA pstMsg)
{
	if(NULL != pstMsg)
	{
		PST_SERVICE_CMD_DATA pstMsgdata = new ST_SERVICE_CMD_DATA;
		pstMsgdata->enServiceCode = pstMsg->enServiceCode;
		pstMsgdata->stData.idatalen = pstMsg->stData.idatalen;
		pstMsgdata->stData.pcdata = pstMsg->stData.pcdata;
		
		m_objQueCmd.PushTail(pstMsgdata);
	}

	return 0;
}

extern void UpgradeDir(string strFileDir);
int CUpgradeManager::ProcCmd(void)
{
	int iRet = 0;
	PST_SERVICE_CMD_DATA pstMsg = 0;
	long lProcNum = 0;
	long lVerCnt = 0;
	PST_RECOVERY_INFO pstInfo = NULL;
	char acFileName[64] = {0};
	char acFileVersion[VERSION_BUFFER_SIZE] = {0};
	long lResult = -1;
	ST_VERSION stVer = {0};
	int iType = 0;

	if (m_objQueCmd.PopHead(pstMsg, -1))
	{
		switch(pstMsg->enServiceCode)
		{
		case EN_UPGRADE_CMD:
			{
				PST_UPGRADE_FILE pstUpFile = (PST_UPGRADE_FILE)pstMsg->stData.pcdata;
				for(int i=0; i<pstUpFile->iFileNum;i++)
				{
					if(pstUpFile->abCheck[i])
					{
						OutputResult(2);
						string strFileDir = pstUpFile->strDir + "\\" + pstUpFile->strFileList[i];
						lResult = UpGradeFile(strFileDir, pstUpFile->aiProgress[i]);
						if(0 != lResult)
						{
							break;
						}
						if((string::npos != pstUpFile->strFileList[i].find("uImage", 0)) ||
							(string::npos != pstUpFile->strFileList[i].find("u-boot", 0)))
						{
							iType = 1;	// =1 ÏµÍ³ÖØÆô
						}
					}
				}

				if(0 != lResult)
				{
					OutputResult(1);
				}
				else
				{
					m_objUpApi.Restart(iType);
					OutputResult(0);
				}

				//string strFileDir(pstMsg->stData.pcdata, pstMsg->stData.idatalen);
				//UpgradeDir(strFileDir);
				break;
			}	
		case EN_EXIT_CMD:
			iRet = -1;
			break;

		case EN_GET_UPGRADE_PROC_NUM_CMD:
			lProcNum = m_objUpApi.GetUpgradeProcNum();
			UpdateProcNum(lProcNum);
			break;

		case EN_GET_UPGRADE_VER_COUNT_CMD:
			lProcNum = *((long *)pstMsg->stData.pcdata);
			lVerCnt = m_objUpApi.GetVerCount(lProcNum);
			UpdateVerCount(lVerCnt);
			break;

		case EN_RECOVERY_UPGRADE_VER_CMD:
			pstInfo = (PST_RECOVERY_INFO)pstMsg->stData.pcdata;
			m_objUpApi.ForceRecovery(pstInfo->lProcid, pstInfo->lVer);
			m_objUpApi.Restart(0);
			break;

		case EN_GET_UPGRADE_CURRENT_NAME_CMD:		
			lProcNum = *((long *)pstMsg->stData.pcdata);
			m_objUpApi.GetCurName(lProcNum, acFileName);
			UpdateCurName(lProcNum, acFileName);
			break;

		case EN_GET_UPGRADE_CURRENT_VERSION_CMD:	
			lProcNum = m_objUpApi.GetUpgradeProcNum();
			for(int i=1; i<= lProcNum; i++)
			{
				memset(acFileVersion, 0, sizeof(acFileVersion));
				stVer.lProcNum = i;
				stVer.iIndex = 0;
				if(3 != i)
				{					
					m_objUpApi.GetCurVersion(&stVer, acFileVersion);
					UpdateCurVersion(i, acFileVersion);
				}
				else
				{
					m_objUpApi.GetMainCtrlVersion(&stVer, acFileVersion);
				}
			}
			break;

		case EN_GET_IP_CMD:
			m_objUpApi.GetIp(acFileVersion);
			UpdateGetIp(acFileVersion);
			break;

		default:
			break;
		}

		delete []pstMsg;
		pstMsg = NULL;
	}

	return iRet;
}

void CUpgradeManager::UpgradeDir(string strFileDir)
{	
#if 0
	WIN32_FIND_DATA p;
	string strDirectory = strFileDir  + string("\\");
	string strExt = "*.Upg";
	string strFindPath = strDirectory + strExt;

	HANDLE h=FindFirstFile(strFindPath.data(),&p);	
	long lRet = 0;
	long lResult = -1;
	
	do
	{
		string strPathFile = strDirectory + string((char *)p.cFileName);
		lResult = UpGradeFile(strPathFile.data());
		if(lResult != 0)
		{
			lRet = -1;
		}
	}while(FindNextFile(h,&p));

	UpdateOutputInfo("Upgrade file finish!\r\n\r\n");
	if(lRet < 0)
	{
		UpdateOutputResult("Upgrade all fail!\r\n\r\n");
	}
	else
	{
		UpdateOutputResult("Upgrade all success!\r\n\r\n");
	}
	

	m_objUpApi.RestartApp();
#endif
}


unsigned long get_file_size(const char *path)
{
	unsigned long filesize = -1;
	FILE *fp;
	fp = fopen(path, "r");
	if(fp == NULL)
		return filesize;
	fseek(fp, 0L, SEEK_END);
	filesize = ftell(fp);
	fclose(fp);
	return filesize;
}

long CUpgradeManager::UpGradeFile(string strFileName, int &iProgress)
{
	char *pData = new char [500];
	const char *pFileName = strFileName.data();
	long fSize = get_file_size(pFileName);
	static long lHaveRead = 0;
	long lResult = -1;
	unsigned char *pFileData = NULL;
	stringstream ss;
	string str1("");
	string str2("");
	string str3("");

	FILE *pFile = fopen(pFileName,"rb");
	fread(pData,sizeof(FileInfo),1,pFile);

	FileInfo*pFileInfo = (FileInfo*)pData;
	fread(pData+sizeof(FileInfo),pFileInfo->lFileInfoSize-5,1,pFile);
	fSize = fSize - pFileInfo->lFileInfoSize;

	string strPath = pFileName;					
	int pos = strPath.find_last_of('\\');
	string str(strPath.substr(pos + 1) );

	str = "Begin to Upgrade file: " + str + "\r\n";
	UpdateOutputInfo(str);

	UpdateOutputInfo("ChannelEstablish Request\r\n");
	long Result = m_objUpApi.ChannelEstablish(pFileInfo);
	if(Result == EN_UPGRADE_OPEN_CHANNEL_SUCCESS)
	{
		UpdateOutputInfo("ChannelEstablish Ack\r\n");
		UpdateOutputInfo("GetPacketSize Request\r\n");
		long PacketSize = m_objUpApi.GetPacketSize();

		stringstream ss;
		ss << PacketSize;
		string str1 = ss.str();
		string str = "GetPacketSize Ack (" + str1 + ")\r\n";
		UpdateOutputInfo(str);
		//UptadeProgress(0);
		iProgress = 0;
		UpdatelistProgress();

		pFileData = new unsigned char[sizeof(ST_UPDATA_FILE_PACKET)+PacketSize - 1];
		ST_UPDATA_FILE_PACKET*pSendPacket = (ST_UPDATA_FILE_PACKET*)pFileData;

		for(int i=0;i<fSize/PacketSize;i++)
		{
			pSendPacket->lPacketSize = PacketSize;
			pSendPacket->lFileSize = fSize;
			pSendPacket->lPacketIndex = i;
			memset(pSendPacket->aucFileData,0x55,PacketSize);
			long ReadSize = fread(pSendPacket->aucFileData,PacketSize,1,pFile);
			pSendPacket->ucCheckSum = 0x00;
			for(int j=0;j<PacketSize;j++)
			{
				pSendPacket->ucCheckSum += pSendPacket->aucFileData[j];
			}

			TRACE("SendPacketReq:%d\n",pSendPacket->lPacketIndex);

			lHaveRead += pSendPacket->lPacketSize;
			
			ss.str("");	
			ss << pSendPacket->lPacketIndex;
			str1 = ss.str();
			ss.str("");	
			ss << lHaveRead;
			str2 = ss.str();
			ss.str("");	
			ss << (int)fSize;
			str3 = ss.str();
			string str = "UpdateData index:" + str1 + " have write: (" + str2+ " / "+ str3 + ")\r\n";
			UpdateOutputInfo(str);

			long size = sizeof(ST_UPDATA_FILE_PACKET);			
			lResult = m_objUpApi.SendUpdataData(pFileData,sizeof(ST_UPDATA_FILE_PACKET)+PacketSize - 1);
			if(0 != lResult)
			{
				delete [] pFileData;
				fclose(pFile);
				delete [] pData;
				pData = NULL;

				ss.str("");	
				ss << (int)lResult;
				string str1 = ss.str();

				string strPath = pFileName;					
				int pos = strPath.find_last_of('\\');
				string str2(strPath.substr(pos + 1) );


				str2 = "Upgrade file "+ str2 + " Fail! SendUpdataData Nak (" + str1 +")\r\n\r\n";

				UpdateOutputInfo(str2);
				//UpdateOutputResult(str2);
				//UptadeProgress(0);				
				
				return lResult;
			}
			
			TRACE("SendPacketAck:%d\n",pSendPacket->lPacketIndex);
			str = "UpdateDataAck index:" + str1+ "\r\n";
			UpdateOutputInfo(str);
			//UptadeProgress((int)(100*lHaveRead/fSize));
			iProgress = (int)(100*lHaveRead/fSize);
			UpdatelistProgress();
		}

		if(fSize%PacketSize)
		{
			pSendPacket->lPacketSize = fSize%PacketSize;
			pSendPacket->lFileSize = fSize;
			pSendPacket->lPacketIndex = fSize/PacketSize;
			memset(pSendPacket->aucFileData,0x55,PacketSize);
			long ReadSize = fread(pSendPacket->aucFileData,pSendPacket->lPacketSize,1,pFile);
			pSendPacket->ucCheckSum = 0x00;
			for(int j=0;j<pSendPacket->lPacketSize;j++)
			{
				pSendPacket->ucCheckSum += pSendPacket->aucFileData[j];
			}

			TRACE("SendPacketReq:%d\n",pSendPacket->lPacketIndex);
			lHaveRead += pSendPacket->lPacketSize;


			ss.str("");	
			ss << (int)pSendPacket->lPacketIndex;
			string str1 = ss.str();
			ss.str("");	
			ss << (int)lHaveRead;
			string str2 = ss.str();
			ss.str("");	
			ss << (int)fSize;
			string str3 = ss.str();
			string str = "UpdateData index:" + str1 + " have write: (" + str2+ " / "+ str3 + ")\r\n";
			UpdateOutputInfo(str);
			
			lResult = m_objUpApi.SendUpdataData(pFileData,sizeof(ST_UPDATA_FILE_PACKET)+pSendPacket->lPacketSize - 1);
			if(0 != lResult)
			{
				delete [] pFileData;
				pFileData = NULL;
				fclose(pFile);
				delete [] pData;
				pData = NULL;

				ss.str("");	
				ss << (int)lResult;
				string str1 = ss.str();
				string strPath = pFileName;					
				int pos = strPath.find_last_of('\\');
				string str2(strPath.substr(pos + 1) );

				str2 = "Upgrade file "+ str2 + " Fail! SendUpdataData Nak (" + str1 +")\r\n\r\n";

				UpdateOutputInfo(str2);
				//UpdateOutputResult(str2);
				//UptadeProgress(0);
				return lResult;
			}

			//UptadeProgress((int)(100*lHaveRead/fSize));			
			iProgress = (int)(100*lHaveRead/fSize);
			UpdatelistProgress();
			TRACE("SendPacketAck:%d\n",pSendPacket->lPacketIndex);
		}
		
		str = "";
		string strPath = pFileName;					
		int pos = strPath.find_last_of('\\');
		str = strPath.substr(pos + 1) ;

		str = "Upgrade file  "+ str +" Success!\r\n";

		//UpdateOutputResult(str);
		//UptadeProgress(100);
		UpdatelistProgress();
		iProgress = 100;
		lHaveRead = 0;

		delete [] pFileData;
		pFileData = NULL;
	}
	else
	{
		ss.str("");	
		ss << (int)Result;
		string str1 = ss.str();
		string strPath = pFileName;					
		int pos = strPath.find_last_of('\\');
		string str2(strPath.substr(pos + 1));
		str2 = "Upgrade file "+ str2 + " Fail! ChannelEstablish Nak (" + str1 +")\r\n\r\n";

		UpdateOutputInfo(str2);
		//UpdateOutputResult(str2);
		//UptadeProgress(0);
	}

	fclose(pFile);	
	delete [] pData;
	pData = NULL;

	if(0 != pFileData)
	{
		delete [] pFileData;
		pFileData = NULL;
	}

	return lResult;
}
