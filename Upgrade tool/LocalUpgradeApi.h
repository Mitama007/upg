#pragma once
#include <string>
#include "iupgradeapi.h"

using namespace std;

class LocalUpgradeApi :
	public IUpgradeApi
{
public:
	LocalUpgradeApi(void);
	~LocalUpgradeApi(void);

	//override
	long ChannelEstablish(FileInfo* pFileInfo);
	long GetPacketSize(void);
	long SendUpdataData(unsigned char* pucData, long lLength);
	long ForceRecovery(long lProcid, long lVerid);
	void NotifyUpgradeFinished();

	long Restart(int iType);
	long GetUpgradeProcNum(void);
	long GetVerCount(long lProcnum);
	long GetCurName(long lProcNum, char *pcFileName);
	long GetCurVersion(PST_VERSION pstVer, char *pcVersion);
	long GetMainCtrlVersion(PST_VERSION pstVer, char *pcVersion);
	long GetIp(char *pcIp);

private:
	FILE* m_pFile;
	long m_lWriteSize;
	FILE* Open(string strFileName);
	bool Close(FILE* pFile);
	long Read(FILE* pFile, unsigned char* pData, long& rLength);
	long Write(FILE* pFile, unsigned char* pData, long lLength);
};
