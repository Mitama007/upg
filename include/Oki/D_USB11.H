
/*        Copyright (C) 2004 Oki Electric Industry Co.,Ltd.        */

/*******************************************************************
********************************************************************
****															****
****				Device Driver Library (DLL)					****
****															****
****															****
****						Ver 02.00							****
****															****
********************************************************************
*******************************************************************/
/*	file name	D_USB11.h										*/


#ifdef	__cplusplus
extern "C" {
#endif

/*******************************************************
*	include section
********************************************************/
#include "DrvErrDev.h"
#pragma once

/*******************************************************
*
*	Data define
*
********************************************************/
/*===============================
	Driver Name
	��������
================================*/
#define		DEVDRV_FILE_NAME					"D_USB11.dll"

/*===============================
	Line Status Attention
	�߳�״̬
================================*/
#define		LINE_STATUS_CHANGE					0x10000000		// ��ԑJ��
#define		LINE_STATUS_TROUBLE					0x20000000		// �����Q

#define		LINE_STATUS_CHANGE_BASE				LINE_STATUS_CHANGE
#define		LINE_STATUS_CHANGE_CONNECT			(LINE_STATUS_CHANGE_BASE + 0x0001)
#define		LINE_STATUS_CHANGE_DISCONNECT		(LINE_STATUS_CHANGE_BASE + 0x0002)
#define		LINE_STATUS_CHANGE_ETC				(LINE_STATUS_CHANGE_BASE + 0x0003)

#define		LINE_STATUS_TROUBLE_BASE			LINE_STATUS_TROUBLE
#define		LINE_STATUS_TROUBLE_SLIGHT_ALARM	(LINE_STATUS_TROUBLE_BASE + 0x0001)
#define		LINE_STATUS_TROUBLE_ALARM			(LINE_STATUS_TROUBLE_BASE + 0x0002)
#define		LINE_STATUS_TROUBLE_ETC				(LINE_STATUS_TROUBLE_BASE + 0x0003)



/*===============================
	etc...
================================*/
#define		DEVICE_NAME_MAX			16

#define		ATTENTION_ENABLE		0
#define		ATTENTION_DISABLE		1

/*******************************************************
*
*	Structure define
*
********************************************************/
#pragma pack(1)
/*===============================
	Driver Information
================================*/
typedef struct _SYSTEMINFO {
	struct	__DEVICE_INFORMATION
	{
		BYTE	bDeviceName[ DEVICE_NAME_MAX ];//// �豸��
	} DeviceInfo;
	struct	__VERSION
	{
		DWORD	dwFileVersionMS;		//���ļ��汾��
		DWORD	dwFileVersionLS;		//���ļ��汾��
		DWORD	dwProductVersionMS;		//�߲�Ʒ�汾��
		DWORD	dwProductVersionLS;		//�Ͳ�Ʒ�汾��
	} Version;
} SYSTEMINFO, *LPSYSTEMINFO;


/*===============================
	Line Status Attention
================================*/
typedef	struct	__LINESTATUS {
	DWORD	dwStatus;					
	DWORD	dwKind;						
										
	DWORD	dwDetail[8];
} LINESTATUS, *LPLINESTATUS;


typedef struct _OpenParameter_{
    BYTE  byAttention;          
} OPENPARAM, *LPOPENPARAM ;



#pragma pack()

/*******************************************************
*
*	Function(API)//����
*
********************************************************/
/*******************************************
* ��������Device_Open()
* ��  �ܣ� ����ָ����ͨ���豸,�������豸ֵ��
* �������壺
		IN	lpszDevice,		// ͨ���豸��("RPR" or "JPR")
		IN	dwTimeOut,		// ��ʱ(Ĭ��ֵΪ300000ms�����ֵ"n"��Ϊ0xffffffff)
		OUT	lphDevice,		// ͨ���豸ָ��
		OUT	lpDrvErrInfo	// ������Ϣ
* ����ֵ��
		NO_ERROR							��ʾ����������
		ERROR_DRV_RESULT_CANCELED			ȡ������(δʹ��)
		ERROR_DRV_RESULT_PARAMETER_ERROR	��������
		ERROR_DRV_RESULT_SLIGHT_ALARM		��΢����
		ERROR_DRV_RESULT_ALARM				�ش����
		ERROR_DRV_RESULT_SYSTEM_ERROR		ϵͳ����
		ERROR_DRV_RESULT_INTERNAL_ERROR		�ڲ�����
*******************************************/
//DWORD Device_Open( LPCTSTR lpszDevice, DWORD dwTimeOut, LPHANDLE lphDevice, LPDRVERRINFO lpDrvErrInfo );


/*******************************************
* ��������Device_Close()
* ��  �ܣ� �ر�ͨ���豸,���ռ�á�
* �������壺
		IN	hDevice,		// ͨ���豸���
		IN	dwTimeOut,		// ��ʱ(Ĭ��ֵΪ300000ms�����ֵ"n"��Ϊ0xffffffff)
		OUT	lpDrvErrInfo	// ������Ϣ
* ����ֵ��
		NO_ERROR							��������
		ERROR_DRV_RESULT_CANCELED			ȡ������(δʹ��)
		ERROR_DRV_RESULT_PARAMETER_ERROR	��������
		ERROR_DRV_RESULT_SLIGHT_ALARM		��΢����
		ERROR_DRV_RESULT_ALARM				�ش����
		ERROR_DRV_RESULT_SYSTEM_ERROR		ϵͳ����
		ERROR_DRV_RESULT_INTERNAL_ERROR		�ڲ�����
*******************************************/
//DWORD Device_Close( HANDLE hDevice, DWORD dwTimeOut, LPDRVERRINFO lpDrvErrInfo );


/*******************************************
* ��������Device_Send()
* ��  �ܣ� ����ָ�������ݷ��͵������豸
* �������壺
		IN	hDevice,		// ͨ���豸���
		IN	dwTimeOut,		// ��ʱ(Ĭ��ֵΪ300000ms�����ֵ"n"��Ϊ0xffffffff)
		IN	lpSndDataBuff,	// ���ͻ�������Pointer
		IN	dwSndDataSize,	// �������ݵĴ�С
		OUT	lpDrvErrInfo	// ������Ϣ
* ����ֵ��
		NO_ERROR							��������
		ERROR_DRV_RESULT_CANCELD			ȡ������
		ERROR_DRV_RESULT_PARAMETER_ERROR	��������
		ERROR_DRV_RESULT_SLIGHT_ALARM		��΢����
		ERROR_DRV_RESULT_ALARM				�ش����
		ERROR_DRV_RESULT_SYSTEM_ERROR		ϵͳ����
		ERROR_DRV_RESULT_INTERNAL_ERROR		�ڲ�����
*******************************************/
//DWORD 	Device_Send( HANDLE hDevice, DWORD dwTimeOut, LPVOID lpSndDataBuff, DWORD dwSndDataSize, LPDRVERRINFO lpDrvErrInfo );


/*******************************************
* ��������Device_Receive()
* ��  �ܣ� �������������������ݣ������õ�ָ���Ļ����С�
* �������壺
		IN	hDevice,			// ͨ���豸���
		IN	dwTimeOut,			// ��ʱ(Ĭ��ֵΪ300000ms�����ֵ"n"��Ϊ0xffffffff)
		OUT	lpRcvDataBuff,		// �������ݻ����ָ��
		IN	dwRcvDataBuffSize,	// �������ݻ�����ֽ�
		OUT	lpdwRcvDataSize,	// ���������ֽ�ָ��
		OUT	lpDrvErrInfo		// ������Ϣ
* ����ֵ��
		NO_ERROR							��������
		ERROR_DRV_RESULT_CANCELD			ȡ������
		ERROR_DRV_RESULT_PARAMETER_ERROR	��������
		ERROR_DRV_RESULT_SLIGHT_ALARM		��΢����
		ERROR_DRV_RESULT_ALARM				�ش����
		ERROR_DRV_RESULT_SYSTEM_ERROR		ϵͳ����
		ERROR_DRV_RESULT_INTERNAL_ERROR		�ڲ�����
*******************************************/
//DWORD 	Device_Receive( HANDLE hDevice, DWORD dwTimeOut, LPVOID lpRcvDataBuff, DWORD dwRcvDataBuffSize, LPDWORD lpdwRcvDataSize, LPDRVERRINFO lpDrvErrInfo );


/******************************************************************************
* ��������Device_Reset()
* ��  �ܣ� ����
* �������壺
		IN 	hDevice,		// ͨ���豸���
		IN 	dwTimeOut,		// ��ʱ(Ĭ��ֵΪ300000ms�����ֵ"n"��Ϊ0xffffffff)	
		OUT	lpDrvErrInfo	// ������Ϣ
* ����ֵ��
******************************************************************************/
//DWORD 	Device_Reset( HANDLE hDevice, DWORD dwTimeOut, LPDRVERRINFO lpDrvErrInfo );


/******************************************************************************
* ��������Device_GetSystemInfo()
* ��  �ܣ� ��ȡϵͳ��Ϣ(�豸�����ļ��汾�š���Ʒ�汾��)
* �������壺
		OUT	LPSYSTEMINFO	lpSystemInfo,	// �汾��Ϣ
		OUT	LPDRVERRINFO	lpDrvErrInfo	// ������Ϣ
******************************************************************************/
//DWORD Device_GetSystemInfo( LPSYSTEMINFO lpSystemInfo, LPDRVERRINFO lpDrvErrInfo );

//DWORD Device_GetTrace( LPCTSTR lpszDevice, LPCTSTR lpcFileName, LPDRVERRINFO lpDrvErrInfo );
//DWORD Device_OpenEx( LPCTSTR lpszDevice, DWORD dwTimeOut, LPOPENPARAM lpOpenParam, LPHANDLE lphDevice, LPDRVERRINFO lpDrvErrInfo );

//����DLL�еĺ���
typedef DWORD (*func_Device_Open)( LPCTSTR lpszDevice, DWORD dwTimeOut, LPHANDLE lphDevice, LPDRVERRINFO lpDrvErrInfo );
typedef DWORD (*func_Device_Close)( HANDLE hDevice, DWORD dwTimeOut, LPDRVERRINFO lpDrvErrInfo );
typedef DWORD (*func_Device_Send)( HANDLE hDevice, DWORD dwTimeOut, LPVOID lpSndDataBuff, DWORD dwSndDataSize, LPDRVERRINFO lpDrvErrInfo );
typedef DWORD (*func_Device_Receive)( HANDLE hDevice, DWORD dwTimeOut, LPVOID lpRcvDataBuff, DWORD dwRcvDataBuffSize, LPDWORD lpdwRcvDataSize, LPDRVERRINFO lpDrvErrInfo );
typedef DWORD (*func_Device_Reset)( HANDLE hDevice, DWORD dwTimeOut, LPDRVERRINFO lpDrvErrInfo );
typedef DWORD (*func_Device_GetSystemInfo)( LPSYSTEMINFO lpSystemInfo, LPDRVERRINFO lpDrvErrInfo );
typedef DWORD (*func_Device_GetTrace)( LPCTSTR lpszDevice, LPCTSTR lpcFileName, LPDRVERRINFO	lpDrvErrInfo );
typedef DWORD (*func_Device_OpenEx)( LPCTSTR lpszDevice, DWORD dwTimeOut, LPOPENPARAM lpOpenParam, LPHANDLE lphDevice, LPDRVERRINFO lpDrvErrInfo );
/*func_Device_Open Device_Open;
func_Device_Close Device_Close;
func_Device_Send Device_Send;
func_Device_Receive Device_Receive;
func_Device_Reset Device_Reset; 
func_Device_GetSystemInfo Device_GetSystemInfo;
func_Device_GetTrace Device_GetTrace;
func_Device_OpenEx Device_OpenEx; */
#ifdef	__cplusplus
}
#endif

/*        Copyright (C) 2004 Oki Electric Industry Co.,Ltd.        */