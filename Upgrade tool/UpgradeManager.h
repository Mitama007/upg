#pragma once

#include<stdio.h>
#include<windows.h>
#include "stdafx.h"
#include "Upgrade tool.h"
#include "Upgradeapi.h"
#include "MsgQueueEx.h"

typedef int (*Fn_Update_Callback)(string strData);

#pragma pack(1)

#define BUSSER	"busser"
#define USBSER	"usbser"
#define BRM		"yh6040w"
#define PROCMON	"procmon"
#define UPGRADE	"upgrade"
#define LOG		"log"

typedef enum
{
	EN_UPGRADE_CMD = 0,
	EN_EXIT_CMD,
	EN_GET_UPGRADE_PROC_NUM_CMD,
	EN_GET_UPGRADE_VER_COUNT_CMD,
	EN_RECOVERY_UPGRADE_VER_CMD,
	EN_GET_UPGRADE_CURRENT_NAME_CMD,
	EN_GET_UPGRADE_CURRENT_VERSION_CMD,
	EN_GET_IP_CMD,
}EN_SERVICE_CODE;

typedef struct 
{
	int idatalen;
	char *pcdata;
}ST_RSP_DATA, *PST_RSP_DATA;




typedef struct 
{
	EN_SERVICE_CODE enServiceCode;
	ST_RSP_DATA stData;
}ST_SERVICE_CMD_DATA, *PST_SERVICE_CMD_DATA;

#define LIST_FILE_NUM_MAX 64
typedef struct 
{
	string strDir;
	string strFileList[LIST_FILE_NUM_MAX];
	int iFileNum;
	int aiProgress[LIST_FILE_NUM_MAX];
	BOOL abCheck[LIST_FILE_NUM_MAX];
}ST_UPGRADE_FILE, *PST_UPGRADE_FILE;

class CUpgradeManager
{
public:
	UpgradeApi m_objUpApi;


private:
	CNotifyQueue<PST_SERVICE_CMD_DATA>    m_objQueCmd;

	CWinThread *m_pThreadRecv;			//接收线程
	Fn_Update_Callback m_fnCallback;
	void *m_pvPri;
	


private:
	long UpGradeFile(string strFileName, int &iProgress);
	void UpgradeDir(string strFileDir);


public:
	CUpgradeManager(void);
	~CUpgradeManager(void);

	int Init(Fn_Update_Callback fnCallback, void * pvPri);
	int UnInit(void);
	int RecvThreadFn(void);
	int SendCmd(PST_SERVICE_CMD_DATA pstMsg);
	int ProcCmd(void);
};
