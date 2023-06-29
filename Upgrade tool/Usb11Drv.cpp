#include "StdAfx.h"
#include "Usb11Drv.h"

CUsb11Drv::CUsb11Drv(void)
{
    m_pfnDevice_Open            = 0;
    m_pfnDevice_Close           = 0;
    m_pfnDevice_Send            = 0;
    m_pfnDevice_Receive         = 0;
    m_pfnDevice_Reset           = 0;
    m_pfnDevice_GetSystemInfo   = 0;
    m_pfnDevice_GetTrace        = 0;
    m_pfnDevice_OpenEx          = 0;
}

CUsb11Drv::~CUsb11Drv(void)
{
}

BOOL CUsb11Drv::LoadUsb11Drv (char *strDllPath)
{	
    m_hDll = LoadLibrary(strDllPath);

    if (0 != m_hDll)
    {
        m_pfnDevice_Open = (PFN_Device_Open)GetProcAddress (m_hDll, "Device_Open");
        m_pfnDevice_Close = (PFN_Device_Close)GetProcAddress (m_hDll, "Device_Close");
        m_pfnDevice_Send = (PFN_Device_Send)GetProcAddress (m_hDll, "Device_Send");
        m_pfnDevice_Receive = (PFN_Device_Receive)GetProcAddress (m_hDll, "Device_Receive");
        m_pfnDevice_Reset = (PFN_Device_Reset)GetProcAddress (m_hDll, "Device_Reset");
        m_pfnDevice_GetSystemInfo = (PFN_Device_GetSystemInfo)GetProcAddress (m_hDll, "Device_GetSystemInfo");
        m_pfnDevice_GetTrace = (PFN_Device_GetTrace)GetProcAddress (m_hDll, "Device_GetTrace");
        m_pfnDevice_OpenEx = (PFN_Device_OpenEx)GetProcAddress (m_hDll, "Device_OpenEx");

        return TRUE;
    }
    return FALSE;
}

BOOL CUsb11Drv::FreeUsb11Drv ()
{
    if (0 != m_hDll)
    {
        ::FreeLibrary(m_hDll);
        m_hDll = 0;

        m_pfnDevice_Open            = 0;
        m_pfnDevice_Close           = 0;
        m_pfnDevice_Send            = 0;
        m_pfnDevice_Receive         = 0;
        m_pfnDevice_Reset           = 0;
        m_pfnDevice_GetSystemInfo   = 0;
        m_pfnDevice_GetTrace        = 0;
        m_pfnDevice_OpenEx          = 0;
        return TRUE;
    }    
    return FALSE;
}

BOOL CUsb11Drv::IsValid ()
{
    return (0 != m_hDll);
}

DWORD CUsb11Drv::DeviceOpen (LPCTSTR lpszDevice, DWORD dwTimeOut, LPHANDLE lphDevice, LPDRVERRINFO lpDrvErrInfo)
{
	DWORD	dwRet = ERROR_DRV_DEVICE;

    if (IsValid())
    {  

        SaveHeaderInfo (EN_DATA_TYPE_OUT, EN_API_CODE_OPEN);
        
        dwRet = m_pfnDevice_Open (lpszDevice, dwTimeOut, lphDevice, lpDrvErrInfo);

        SaveHeaderInfo (EN_DATA_TYPE_IN, EN_API_CODE_OPEN);
    }
    return dwRet;
}

DWORD CUsb11Drv::DeviceClose (HANDLE hDevice, DWORD dwTimeOut, LPDRVERRINFO lpDrvErrInfo)
{
	DWORD	dwRet = ERROR_DRV_DEVICE;

    if (IsValid())
    {
		
        SaveHeaderInfo (EN_DATA_TYPE_OUT, EN_API_CODE_CLOSE);

        dwRet =  m_pfnDevice_Close (hDevice, dwTimeOut, lpDrvErrInfo);

        SaveHeaderInfo (EN_DATA_TYPE_IN, EN_API_CODE_CLOSE);
    }
    return dwRet;
}

DWORD CUsb11Drv::DeviceSend (HANDLE hDevice, DWORD dwTimeOut, LPVOID lpSndDataBuff, DWORD dwSndDataSize, LPDRVERRINFO lpDrvErrInfo)
{
	DWORD	dwRet = ERROR_DRV_DEVICE;

    if (IsValid())
    {

        SaveHeaderInfo (EN_DATA_TYPE_OUT, EN_API_CODE_SEND);

		
        dwRet = m_pfnDevice_Send (hDevice, dwTimeOut, lpSndDataBuff, dwSndDataSize, lpDrvErrInfo);

        SaveHeaderInfo (EN_DATA_TYPE_IN, EN_API_CODE_SEND);

    }
    return dwRet;
}

DWORD CUsb11Drv::DeviceReceive (HANDLE hDevice, DWORD dwTimeOut, LPVOID lpRcvDataBuff, DWORD dwRcvDataBuffSize, 
								LPDWORD lpdwRcvDataSize, LPDRVERRINFO lpDrvErrInfo)
{
	DWORD	dwRet = ERROR_DRV_DEVICE;

    if (IsValid())
    {

        SaveHeaderInfo (EN_DATA_TYPE_OUT, EN_API_CODE_RECEIVE);


        dwRet = m_pfnDevice_Receive (hDevice, dwTimeOut, lpRcvDataBuff, dwRcvDataBuffSize, lpdwRcvDataSize, lpDrvErrInfo);

        SaveHeaderInfo (EN_DATA_TYPE_IN, EN_API_CODE_RECEIVE);


		if (20 <= *lpdwRcvDataSize)
		{
		}

    }
    return dwRet;
}

DWORD CUsb11Drv::DeviceReset (HANDLE hDevice, DWORD dwTimeOut, LPDRVERRINFO lpDrvErrInfo)
{
	DWORD	dwRet = ERROR_DRV_DEVICE;

    if (IsValid())
    {

        SaveHeaderInfo (EN_DATA_TYPE_OUT, EN_API_CODE_RESET);
		

        dwRet = m_pfnDevice_Reset (hDevice, dwTimeOut, lpDrvErrInfo);

        SaveHeaderInfo (EN_DATA_TYPE_IN, EN_API_CODE_RESET);

    }
    return dwRet;
}

DWORD CUsb11Drv::DeviceGetSystemInfo (LPSYSTEMINFO lpSystemInfo, LPDRVERRINFO lpDrvErrInfo)
{
	DWORD	dwRet = ERROR_DRV_DEVICE;

    if (IsValid())
    {

        SaveHeaderInfo (EN_DATA_TYPE_OUT, EN_API_CODE_GETSYSTEMINFO);

        dwRet = m_pfnDevice_GetSystemInfo (lpSystemInfo, lpDrvErrInfo);

        SaveHeaderInfo (EN_DATA_TYPE_IN, EN_API_CODE_GETSYSTEMINFO);

    }
    return dwRet;
}

DWORD CUsb11Drv::DeviceGetTrace (LPCTSTR lpszDevice, LPCTSTR lpcFileName, LPDRVERRINFO	lpDrvErrInfo)
{
	DWORD	dwRet = ERROR_DRV_DEVICE;

    if (IsValid())
    {

        SaveHeaderInfo (EN_DATA_TYPE_OUT, EN_API_CODE_GETTRACE);

        dwRet = m_pfnDevice_GetTrace (lpszDevice, lpcFileName, lpDrvErrInfo);

        SaveHeaderInfo (EN_DATA_TYPE_IN, EN_API_CODE_GETTRACE);

    }
    return dwRet;
}

DWORD CUsb11Drv::DeviceOpenEx (LPCTSTR lpszDevice, DWORD dwTimeOut, LPOPENPARAM lpOpenParam, LPHANDLE lphDevice, LPDRVERRINFO lpDrvErrInfo)
{
	DWORD	dwRet = ERROR_DRV_DEVICE;

    if (IsValid())
    {

        SaveHeaderInfo (EN_DATA_TYPE_OUT, EN_API_CODE_OPENEX);

        dwRet = m_pfnDevice_OpenEx (lpszDevice, dwTimeOut, lpOpenParam, lphDevice, lpDrvErrInfo);

        SaveHeaderInfo (EN_DATA_TYPE_IN, EN_API_CODE_OPENEX);

    }    
    return dwRet;
}

void CUsb11Drv::SaveHeaderInfo (EN_DATA_TYPE enType, EN_API_CODE enCode)
{
    char		strApiCode[EN_API_CODE_COUNT][50] = {"DeviceOpen",
                                                     "DeviceClose",
                                                     "DeviceSend",
                                                     "DeviceReceive",
                                                     "DeviceReset",
                                                     "DeviceGetSystemInfo",
                                                     "DeviceGetTrace",
                                                     "DeviceOpenEx"};
    char		acDataType[EN_DATA_TYPE_COUNT] = {'O', 'I'};
    SYSTEMTIME  stSysTime = {0};

    ::GetLocalTime(&stSysTime);
}