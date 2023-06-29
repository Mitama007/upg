#pragma once
#include "iupgradeapi.h"
#include "Usb11Drv.h"

class LowUpgradeApi :
	public IUpgradeApi
{
public:
	LowUpgradeApi(void);
	~LowUpgradeApi(void);

	//override
	long ChannelEstablish(FileInfo* pFileInfo);
	long GetPacketSize(void);
	long SendUpdataData(unsigned char* pucData, long lLength);
	long ForceRecovery(long lProcid, long lVerid);
	long Restart(int iType);
	long GetUpgradeProcNum(void);
	long GetVerCount(long lProcnum);
	long GetCurName(long lProcNum, char *pcFileName);
	long GetCurVersion(PST_VERSION pstVer, char *pcVersion);
	long GetMainCtrlVersion(PST_VERSION pstVer, char *pcVersion);
	long GetIp(char *pcIp);

private:
	int Send(unsigned char *pucData, long lLength);
	int Recv(unsigned char *pucData, long &rLength);
	int m_iId;
	int GetData(unsigned char *pucBuf,long lLength);
	CUsb11Drv	*m_pobjDrv;
	HANDLE m_DeviceHandle;
	DRVERRINFO m_ErrInfo;
public:
	void SetId(int iId, int iflag);
};
