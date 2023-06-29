#include "StdAfx.h"
#include "UpgradeApi.h"

UpgradeApi::UpgradeApi(void)
{
	m_pCurApi = &m_objLocal;
	m_aobjLow[0].SetId(EN_UPGRADE_MAIN_CTRL, 0);
	m_aobjLow[1].SetId(EN_UPGRADE_CDU, 0);
	m_aobjLow[2].SetId(EN_UPGRADE_CABC, 0);
}

UpgradeApi::~UpgradeApi(void)
{
}


long UpgradeApi::ChannelEstablish(FileInfo* pFileInfo)
{

	long lResult = m_objLocal.ChannelEstablish(pFileInfo);
	switch(lResult)
	{
	case EN_UPGRADE_OPEN_CHANNEL_SUCCESS:
		{
			m_pCurApi = &m_objLocal;
			return lResult;
		}
		break;
	case EN_UPGRADE_OPEN_CHANNEL_FILE_UNRECOGNIZED:
		for(int i=0;i<m_sLowUpgradeNum;i++)
		{
			lResult = m_aobjLow[i].ChannelEstablish(pFileInfo);
			switch(lResult)
			{
			case EN_UPGRADE_OPEN_CHANNEL_SUCCESS:
				m_pCurApi = &m_aobjLow[i];
				return lResult;
				break;
			case EN_UPGRADE_OPEN_CHANNEL_FILE_UNRECOGNIZED:
				continue;
				break;
			case EN_UPGRADE_OPEN_CHANNEL_CONDUCTION_UNSUIT:
				m_pCurApi = NULL;
				return lResult;

				break;
			default:
				m_pCurApi = NULL;
				return lResult;

				break;
			}
		}
		m_pCurApi = NULL;

		return EN_UPGRADE_OPEN_CHANNEL_FILE_UNRECOGNIZED;
		break;
	case EN_UPGRADE_OPEN_CHANNEL_CONDUCTION_UNSUIT:
		m_pCurApi = NULL;
		return lResult;
		break;
	default:
		m_pCurApi = NULL;
		return lResult;
		break;
	}

	return 0;
}

long UpgradeApi::GetPacketSize(void)
{
	if(m_pCurApi != NULL)
	{
		return m_pCurApi->GetPacketSize();
	}

	return -1;
}

long UpgradeApi::SendUpdataData(unsigned char* pucData, long lLength)
{
	if(m_pCurApi != NULL)
	{
		return m_pCurApi->SendUpdataData(pucData,lLength);
	}
	return EN_UPGRADE_OPEN_CHANNEL_OTHER_ERROR;
}

long UpgradeApi::ForceRecovery(long lProcid, long lVerid)
{
	if(m_pCurApi != NULL)
	{
		return m_pCurApi->ForceRecovery(lProcid, lVerid);
	}
	return EN_UPGRADE_RECOVERY_FAIL;
}

long UpgradeApi::Restart(int iType)
{
	long lResult = 1;

	if(m_pCurApi != NULL)
	{
		return m_pCurApi->Restart(iType);
	}
	return EN_UPGRADE_RESTART_FAIL;
}

long UpgradeApi::GetUpgradeProcNum(void)
{
	m_pCurApi = &m_aobjLow[0];
	if(m_pCurApi != NULL)
	{
		return m_pCurApi->GetUpgradeProcNum();
	}
	return 0;
}

long UpgradeApi::GetVerCount(long lProcnum)
{
	m_pCurApi = &m_aobjLow[0];
	if(m_pCurApi != NULL)
	{
		return m_pCurApi->GetVerCount(lProcnum);
	}
	return 0;
}

long UpgradeApi::GetCurName(long lProcNum, char *pcFileName)
{
	m_pCurApi = &m_aobjLow[0];
	if(m_pCurApi != NULL)
	{
		return m_pCurApi->GetCurName(lProcNum, pcFileName);
	}
	return 0;
}

long UpgradeApi::GetCurVersion(PST_VERSION pstVer, char *pcVersion)
{
	m_pCurApi = &m_aobjLow[0];
	if(m_pCurApi != NULL)
	{
		return m_pCurApi->GetCurVersion(pstVer, pcVersion);
	}
	return 0;
}

long UpgradeApi::GetIp(char *pcIp)
{
	m_pCurApi = &m_aobjLow[0];
	if(m_pCurApi != NULL)
	{
		return m_pCurApi->GetIp(pcIp);
	}
	return 0;
}

long UpgradeApi::GetMainCtrlVersion(PST_VERSION pstVer, char *pcVersion)
{
	m_pCurApi = &m_aobjLow[0];
	if(m_pCurApi != NULL)
	{
		return m_pCurApi->GetMainCtrlVersion(pstVer, pcVersion);
	}
	return 0;
}


