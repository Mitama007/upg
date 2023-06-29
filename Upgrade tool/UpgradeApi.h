#pragma once
#include "iupgradeapi.h"
#include "LocalUpgradeApi.h"
#include "LowUpgradeApi.h"

class UpgradeApi :
	public IUpgradeApi
{
public:
	UpgradeApi(void);
	~UpgradeApi(void);

	//overrade
	long ChannelEstablish(FileInfo* pFileInfo);
	long GetPacketSize(void);
	long SendUpdataData(unsigned char* pucData, long lLength);
	long ForceRecovery(long lProcid, long lVerid);
	long Restart(int iType);		//	=0  应用重启  =1  系统重启
	long GetVerCount(long lPronum);
	long GetUpgradeProcNum(void);
	long GetCurName(long lProcNum, char *pcFileName);
	long GetCurVersion(PST_VERSION pstVer, char *pcVersion);
	long GetMainCtrlVersion(PST_VERSION pstVer, char *pcVersion);
	long GetIp(char *pcIp);

private:
	//
	static const int m_sPcLowNum = 3;
	static const int m_sMainCtrlLowNum = 5;

#ifdef WIN32
	static const int m_sLowUpgradeNum = m_sPcLowNum;
#else
	static const int m_sLowUpgradeNum = m_sMainCtrlLowNum;
#endif

	IUpgradeApi* m_pCurApi;
	LocalUpgradeApi m_objLocal;
public:
	LowUpgradeApi m_aobjLow[m_sLowUpgradeNum];

};
