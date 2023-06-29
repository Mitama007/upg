
/*        Copyright (C) 2002 Oki Electric Industry Co.,Ltd.        */

/*******************************************************************
********************************************************************
****															****
****															****
****			Router driver error header file					****
****															****
****						Ver 00.10							****
****															****
********************************************************************
*******************************************************************/

/*	file name	DrvErrDev.h									*/


#include "DrvErrCmn.h"


/*======================================================
Error type
=======================================================*/
/*------------------------------------------------------

  Router driver	(ReturnCode + 0x10XXX)
  
-------------------------------------------------------*/
//--------------------------
// ERROR_DRV_RESULT_CANCELED

//--------------------------
// ERROR_DRV_RESULT_PARAMETER_ERROR

//--------------------------
// ERROR_DRV_RESULT_SLIGHT_ALARM

//--------------------------
// ERROR_DRV_RESULT_ALARM

//--------------------------
// ERROR_DRV_RESULT_SYSTEM_ERROR
#define		ERROR_D_CREATE_MUTEX				(ERROR_DRV_RESULT_SYSTEM_ERROR + ERROR_DRV_DEVICE + 0x0011)
#define		ERROR_D_OPEN_MUTEX					(ERROR_DRV_RESULT_SYSTEM_ERROR + ERROR_DRV_DEVICE + 0x0012)
#define		ERROR_D_RELEASE_MUTEX				(ERROR_DRV_RESULT_SYSTEM_ERROR + ERROR_DRV_DEVICE + 0x0013)
#define		ERROR_D_CREATE_SEMAPHORE			(ERROR_DRV_RESULT_SYSTEM_ERROR + ERROR_DRV_DEVICE + 0x0014)
#define		ERROR_D_RELEASE_SEMAPHORE			(ERROR_DRV_RESULT_SYSTEM_ERROR + ERROR_DRV_DEVICE + 0x0015)

//--------------------------
// ERROR_DRV_RESULT_INTERNAL_ERROR
#define		ERROR_D_WAIT_FOR_OBJECT				(ERROR_DRV_RESULT_INTERNAL_ERROR + ERROR_DRV_DEVICE + 0x0011)
#define		ERROR_D_BAD_MUTEX					(ERROR_DRV_RESULT_INTERNAL_ERROR + ERROR_DRV_DEVICE + 0x0012)

#define		ERROR_D_COM_QUE						(ERROR_DRV_RESULT_INTERNAL_ERROR + ERROR_DRV_DEVICE + 0x0020)
#define		ERROR_D_SET_COM_QUE					(ERROR_D_COM_QUE + 0x01)
#define		ERROR_D_GET_COM_QUE					(ERROR_D_COM_QUE + 0x02)

#define		ERROR_D_RCV_QUE						(ERROR_DRV_RESULT_INTERNAL_ERROR + ERROR_DRV_DEVICE + 0x0030)
#define		ERROR_D_SET_RCV_QUE					(ERROR_D_RCV_QUE + 0x01)
#define		ERROR_D_GET_RCV_QUE					(ERROR_D_RCV_QUE + 0x02)

#define		ERROR_D_VER_INFO					(ERROR_DRV_RESULT_INTERNAL_ERROR + ERROR_DRV_DEVICE + 0x0040)
#define		ERROR_D_GET_VER_INFO				(ERROR_D_VER_INFO + 0x01)
#define		ERROR_D_GET_DRV_INFO				(ERROR_D_VER_INFO + 0x02)

#define		ERROR_D_GET_OVR_RSLT				(ERROR_DRV_RESULT_INTERNAL_ERROR + ERROR_DRV_DEVICE + 0x0050)

#define		ERROR_D_							(ERROR_DRV_RESULT_INTERNAL_ERROR + ERROR_DRV_DEVICE + 0x0F00)

/*******************************************************
*
*	Structure define
*	结构定义
********************************************************/
#pragma pack(1)
/*===============================
Error Information
错误信息
================================*/
typedef struct _DEVICEDRV_ERRORINFO
{
	DWORD	dwType;			
	DWORD	dwDetail;		
	DWORD	dwPosition;		
} DEVERRINFO, *LPDEVERRINFO;

#pragma pack()

/*        Copyright (C) 2002 Oki Electric Industry Co.,Ltd.        */
