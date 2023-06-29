
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
	驱动名子
================================*/
#define		DEVDRV_FILE_NAME					"D_USB11.dll"

/*===============================
	Line Status Attention
	线程状态
================================*/
#define		LINE_STATUS_CHANGE					0x10000000		// 忬懺慗堏
#define		LINE_STATUS_TROUBLE					0x20000000		// 夞慄忈奞

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
		BYTE	bDeviceName[ DEVICE_NAME_MAX ];//// 设备名
	} DeviceInfo;
	struct	__VERSION
	{
		DWORD	dwFileVersionMS;		//高文件版本号
		DWORD	dwFileVersionLS;		//低文件版本号
		DWORD	dwProductVersionMS;		//高产品版本号
		DWORD	dwProductVersionLS;		//低产品版本号
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
*	Function(API)//功能
*
********************************************************/
/*******************************************
* 函数名：Device_Open()
* 功  能： 打开所指定的通信设备,并返回设备值。
* 参数含义：
		IN	lpszDevice,		// 通信设备名("RPR" or "JPR")
		IN	dwTimeOut,		// 延时(默认值为300000ms，最大值"n"设为0xffffffff)
		OUT	lphDevice,		// 通信设备指针
		OUT	lpDrvErrInfo	// 错误信息
* 返回值：
		NO_ERROR							表示正常结束。
		ERROR_DRV_RESULT_CANCELED			取消结束(未使用)
		ERROR_DRV_RESULT_PARAMETER_ERROR	参数错误
		ERROR_DRV_RESULT_SLIGHT_ALARM		轻微故障
		ERROR_DRV_RESULT_ALARM				重大故障
		ERROR_DRV_RESULT_SYSTEM_ERROR		系统错误
		ERROR_DRV_RESULT_INTERNAL_ERROR		内部错误
*******************************************/
//DWORD Device_Open( LPCTSTR lpszDevice, DWORD dwTimeOut, LPHANDLE lphDevice, LPDRVERRINFO lpDrvErrInfo );


/*******************************************
* 函数名：Device_Close()
* 功  能： 关闭通信设备,解除占用。
* 参数含义：
		IN	hDevice,		// 通信设备句柄
		IN	dwTimeOut,		// 延时(默认值为300000ms，最大值"n"设为0xffffffff)
		OUT	lpDrvErrInfo	// 错误信息
* 返回值：
		NO_ERROR							正常结束
		ERROR_DRV_RESULT_CANCELED			取消结束(未使用)
		ERROR_DRV_RESULT_PARAMETER_ERROR	参数错误
		ERROR_DRV_RESULT_SLIGHT_ALARM		轻微故障
		ERROR_DRV_RESULT_ALARM				重大故障
		ERROR_DRV_RESULT_SYSTEM_ERROR		系统错误
		ERROR_DRV_RESULT_INTERNAL_ERROR		内部错误
*******************************************/
//DWORD Device_Close( HANDLE hDevice, DWORD dwTimeOut, LPDRVERRINFO lpDrvErrInfo );


/*******************************************
* 函数名：Device_Send()
* 功  能： 将所指定的数据发送到物理设备
* 参数含义：
		IN	hDevice,		// 通信设备句柄
		IN	dwTimeOut,		// 延时(默认值为300000ms，最大值"n"设为0xffffffff)
		IN	lpSndDataBuff,	// 发送缓冲区的Pointer
		IN	dwSndDataSize,	// 发送数据的大小
		OUT	lpDrvErrInfo	// 错误信息
* 返回值：
		NO_ERROR							正常结束
		ERROR_DRV_RESULT_CANCELD			取消结束
		ERROR_DRV_RESULT_PARAMETER_ERROR	参数错误
		ERROR_DRV_RESULT_SLIGHT_ALARM		轻微故障
		ERROR_DRV_RESULT_ALARM				重大故障
		ERROR_DRV_RESULT_SYSTEM_ERROR		系统错误
		ERROR_DRV_RESULT_INTERNAL_ERROR		内部错误
*******************************************/
//DWORD 	Device_Send( HANDLE hDevice, DWORD dwTimeOut, LPVOID lpSndDataBuff, DWORD dwSndDataSize, LPDRVERRINFO lpDrvErrInfo );


/*******************************************
* 函数名：Device_Receive()
* 功  能： 从物理驱动器接收数据，并设置到指定的缓存中。
* 参数含义：
		IN	hDevice,			// 通信设备句柄
		IN	dwTimeOut,			// 延时(默认值为300000ms，最大值"n"设为0xffffffff)
		OUT	lpRcvDataBuff,		// 接收数据缓存的指针
		IN	dwRcvDataBuffSize,	// 接收数据缓存的字节
		OUT	lpdwRcvDataSize,	// 接收数据字节指针
		OUT	lpDrvErrInfo		// 错误信息
* 返回值：
		NO_ERROR							正常结束
		ERROR_DRV_RESULT_CANCELD			取消结束
		ERROR_DRV_RESULT_PARAMETER_ERROR	参数错误
		ERROR_DRV_RESULT_SLIGHT_ALARM		轻微故障
		ERROR_DRV_RESULT_ALARM				重大故障
		ERROR_DRV_RESULT_SYSTEM_ERROR		系统错误
		ERROR_DRV_RESULT_INTERNAL_ERROR		内部错误
*******************************************/
//DWORD 	Device_Receive( HANDLE hDevice, DWORD dwTimeOut, LPVOID lpRcvDataBuff, DWORD dwRcvDataBuffSize, LPDWORD lpdwRcvDataSize, LPDRVERRINFO lpDrvErrInfo );


/******************************************************************************
* 函数名：Device_Reset()
* 功  能： 重排
* 参数含义：
		IN 	hDevice,		// 通信设备句柄
		IN 	dwTimeOut,		// 延时(默认值为300000ms，最大值"n"设为0xffffffff)	
		OUT	lpDrvErrInfo	// 错误信息
* 返回值：
******************************************************************************/
//DWORD 	Device_Reset( HANDLE hDevice, DWORD dwTimeOut, LPDRVERRINFO lpDrvErrInfo );


/******************************************************************************
* 函数名：Device_GetSystemInfo()
* 功  能： 获取系统信息(设备名、文件版本号、产品版本号)
* 参数含义：
		OUT	LPSYSTEMINFO	lpSystemInfo,	// 版本信息
		OUT	LPDRVERRINFO	lpDrvErrInfo	// 错误信息
******************************************************************************/
//DWORD Device_GetSystemInfo( LPSYSTEMINFO lpSystemInfo, LPDRVERRINFO lpDrvErrInfo );

//DWORD Device_GetTrace( LPCTSTR lpszDevice, LPCTSTR lpcFileName, LPDRVERRINFO lpDrvErrInfo );
//DWORD Device_OpenEx( LPCTSTR lpszDevice, DWORD dwTimeOut, LPOPENPARAM lpOpenParam, LPHANDLE lphDevice, LPDRVERRINFO lpDrvErrInfo );

//导出DLL中的函数
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
