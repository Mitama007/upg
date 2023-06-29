#pragma once
#include "windows.h"
#include "../include/Oki/DrvErrCmn.h"
#include "../include/Oki/D_USB11.H"

typedef DWORD (*PFN_Device_Open)( LPCTSTR lpszDevice, DWORD dwTimeOut, LPHANDLE lphDevice, LPDRVERRINFO lpDrvErrInfo );
typedef DWORD (*PFN_Device_Close)( HANDLE hDevice, DWORD dwTimeOut, LPDRVERRINFO lpDrvErrInfo );
typedef DWORD (*PFN_Device_Send)( HANDLE hDevice, DWORD dwTimeOut, LPVOID lpSndDataBuff, DWORD dwSndDataSize, LPDRVERRINFO lpDrvErrInfo );
typedef DWORD (*PFN_Device_Receive)( HANDLE hDevice, DWORD dwTimeOut, LPVOID lpRcvDataBuff, DWORD dwRcvDataBuffSize,
									LPDWORD lpdwRcvDataSize, LPDRVERRINFO lpDrvErrInfo );
typedef DWORD (*PFN_Device_Reset)( HANDLE hDevice, DWORD dwTimeOut, LPDRVERRINFO lpDrvErrInfo );
typedef DWORD (*PFN_Device_GetSystemInfo)( LPSYSTEMINFO lpSystemInfo, LPDRVERRINFO lpDrvErrInfo );
typedef DWORD (*PFN_Device_GetTrace)( LPCTSTR lpszDevice, LPCTSTR lpcFileName, LPDRVERRINFO	lpDrvErrInfo );
typedef DWORD (*PFN_Device_OpenEx)( LPCTSTR lpszDevice, DWORD dwTimeOut, LPOPENPARAM lpOpenParam, LPHANDLE lphDevice, LPDRVERRINFO lpDrvErrInfo );

typedef enum
{
	EN_API_CODE_OPEN = 0,
	EN_API_CODE_CLOSE,
	EN_API_CODE_SEND,
	EN_API_CODE_RECEIVE,
	EN_API_CODE_RESET,
	EN_API_CODE_GETSYSTEMINFO,
	EN_API_CODE_GETTRACE,
	EN_API_CODE_OPENEX,
	EN_API_CODE_COUNT,
}EN_API_CODE;

typedef enum
{
	EN_DATA_TYPE_OUT = 0,
	EN_DATA_TYPE_IN,
	EN_DATA_TYPE_COUNT,
}EN_DATA_TYPE;

class CUsb11Drv
{
private:        
    BOOL IsValid ();

    HMODULE m_hDll;    

    void SaveHeaderInfo (EN_DATA_TYPE enType, EN_API_CODE enCode);
private:
    PFN_Device_Open             m_pfnDevice_Open;
    PFN_Device_Close            m_pfnDevice_Close;
    PFN_Device_Send             m_pfnDevice_Send;
    PFN_Device_Receive          m_pfnDevice_Receive;
    PFN_Device_Reset            m_pfnDevice_Reset; 
    PFN_Device_GetSystemInfo    m_pfnDevice_GetSystemInfo;
    PFN_Device_GetTrace         m_pfnDevice_GetTrace;
    PFN_Device_OpenEx           m_pfnDevice_OpenEx; 
public:
    BOOL LoadUsb11Drv (char *strDllPath);
    BOOL FreeUsb11Drv ();
    DWORD DeviceOpen (LPCTSTR lpszDevice, DWORD dwTimeOut, LPHANDLE lphDevice, LPDRVERRINFO lpDrvErrInfo);
    DWORD DeviceClose (HANDLE hDevice, DWORD dwTimeOut, LPDRVERRINFO lpDrvErrInfo);
    DWORD DeviceSend (HANDLE hDevice, DWORD dwTimeOut, LPVOID lpSndDataBuff, DWORD dwSndDataSize, LPDRVERRINFO lpDrvErrInfo);
    DWORD DeviceReceive (HANDLE hDevice, DWORD dwTimeOut, LPVOID lpRcvDataBuff, DWORD dwRcvDataBuffSize, 
		LPDWORD lpdwRcvDataSize, LPDRVERRINFO lpDrvErrInfo);
    DWORD DeviceReset (HANDLE hDevice, DWORD dwTimeOut, LPDRVERRINFO lpDrvErrInfo);
    DWORD DeviceGetSystemInfo (LPSYSTEMINFO lpSystemInfo, LPDRVERRINFO lpDrvErrInfo);
    DWORD DeviceGetTrace (LPCTSTR lpszDevice, LPCTSTR lpcFileName, LPDRVERRINFO	lpDrvErrInfo);
    DWORD DeviceOpenEx (LPCTSTR lpszDevice, DWORD dwTimeOut, LPOPENPARAM lpOpenParam, LPHANDLE lphDevice, LPDRVERRINFO lpDrvErrInfo);
public:
    CUsb11Drv(void);
    ~CUsb11Drv(void);
};
