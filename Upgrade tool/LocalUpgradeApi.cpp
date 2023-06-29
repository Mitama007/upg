#include "StdAfx.h"
#include "LocalUpgradeApi.h"

LocalUpgradeApi::LocalUpgradeApi(void)
{
	m_pFile = NULL;
}

LocalUpgradeApi::~LocalUpgradeApi(void)
{

}

long LocalUpgradeApi::ChannelEstablish(FileInfo* pFileInfo)
{
#ifdef WIN32
	return 1;
#else
	FileInfomation *pInfo = pFileInfo;
	if(pInfo->Id != 0x28367a)
		return 1;
	for(int i=0;i<pInfo->ConNum;i++)
	{
		if(pInfo->Con[i]<0x32)
			return 2;
	}
	m_pFile = Open("/yh6040w");
	return 0;
#endif
}

long LocalUpgradeApi::GetPacketSize(void)
{
	return 0;
}

long LocalUpgradeApi::SendUpdataData(unsigned char* pucData, long lLength)
{
	if(m_pFile != NULL)
	{
		ST_UPDATA_FILE_PACKET *pstFilePacket = (ST_UPDATA_FILE_PACKET *)pucData;
		unsigned char Sum = 0;

		for(int i=0;i<pstFilePacket->lPacketSize;i++)
		{
			Sum += pstFilePacket->aucFileData[i];
		}

		if(Sum != pstFilePacket->ucCheckSum)
		{
			return EN_UPGRADE_CHECKSUM_ERROR;
		}

		if(pstFilePacket->lPacketSize != lLength-sizeof(ST_UPDATA_FILE_PACKET)+1)
		{
			return EN_UPGRADE_LENGTH_ERROR;
		}

		if(m_lWriteSize+pstFilePacket->lPacketSize > pstFilePacket->lFileSize)
		{
			return EN_UPGRADE_LENGTH_ERROR;
		}

		int n = 0;
		n = Write(m_pFile,pstFilePacket->aucFileData,pstFilePacket->lPacketSize);

		if(n == pstFilePacket->lPacketSize)
		{
			m_lWriteSize += pstFilePacket->lPacketSize;
			if(m_lWriteSize == pstFilePacket->lFileSize)
			{
				Close(m_pFile);
				m_pFile = NULL;
			}
			return EN_UPGRADE_PACKET_SUCCESS;
		}
		else
		{
			return EN_UPGRADE_LENGTH_ERROR;
		}
	}
	return EN_UPGRADE_WRITE_ERROR;
}

long LocalUpgradeApi::ForceRecovery(long lProcid, long lVerid)
{
	return 0;
}

FILE* LocalUpgradeApi::Open(string strFileName)
{
	FILE * pFile = fopen(strFileName.data(),"wb");
	m_lWriteSize = 0;
	return pFile;
}

bool LocalUpgradeApi::Close(FILE*pFile)
{

	fclose(pFile);
	NotifyUpgradeFinished();
	return true;
}

void LocalUpgradeApi::NotifyUpgradeFinished()
{

}


long LocalUpgradeApi::Read(FILE*pFile, unsigned char* pData, long& rLength)
{
	return fread(pData,1,rLength,pFile);
}

long LocalUpgradeApi::Write( FILE*pFile , unsigned char* pData , long lLength)
{
	return fwrite(pData,1,lLength,pFile);
}


long LocalUpgradeApi::Restart(int iType)
{


	return 0;
}

long LocalUpgradeApi::GetUpgradeProcNum(void)
{
	return 0;
}
long LocalUpgradeApi::GetVerCount(long lProcnum)
{
	return 0;
}

long LocalUpgradeApi::GetCurName(long lProcNum, char *pcFileName)
{
	return 0;
}

long LocalUpgradeApi::GetCurVersion(PST_VERSION pstVer, char *pcVersion)
{
	return 0;
}

long LocalUpgradeApi::GetMainCtrlVersion(PST_VERSION pstVer, char *pcVersion)
{
	return 0;
}

long LocalUpgradeApi::GetIp(char *pcIp)
{
	return 0;
}