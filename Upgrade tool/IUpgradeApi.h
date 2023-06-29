#pragma once
#include "../include/Upgrade.h"

typedef ST_FILE_INFO FileInfo;
#define VERSION_BUFFER_SIZE	128
#define DEVICE_COUNT 7

typedef struct  
{
	long lProcNum;
	int iIndex;
}ST_VERSION, *PST_VERSION;

class IUpgradeApi
{
public:
	IUpgradeApi(void);
	virtual ~IUpgradeApi(void);
	virtual long ChannelEstablish(FileInfo* pFileInfo)=0;
	virtual long GetPacketSize(void)=0;
	virtual long SendUpdataData(unsigned char* pucData, long lLength)=0;
	virtual long ForceRecovery(long lProcid, long lVerid)=0;
	virtual long Restart(int iType)=0;
	virtual long GetUpgradeProcNum(void)= 0;
	virtual long GetVerCount(long lProcNum)= 0;
	virtual long GetCurName(long lProcNum, char *pcFileName)= 0;
	virtual long GetCurVersion(PST_VERSION pstVer, char *pcVersion)=0;
	virtual long GetMainCtrlVersion(PST_VERSION pstVer, char *pcVersion)=0;
	virtual long GetIp(char *pcIp) = 0;
};
