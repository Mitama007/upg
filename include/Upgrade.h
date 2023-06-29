//===========================================================================
//			文件名：upgrade.h
//			描述：	升级协议结构定义及接口定义
//			
//			
//			版本：1.1
//			删除函数接口声明。2014-08-04
//			创建日期：2014-07-31
//			作者：zhangxy
//===========================================================================

#ifndef UPGRADE_H
#define UPGRADE_H
#include <string.h>
#ifndef WIN32
typedef int  HANDLE;
#endif

#ifndef TRACE
#define TRACE printf
#endif

#pragma pack (1)

typedef enum
{
	EN_UPGRADE_CMD_MAKE_CHANNEL = long(0),
	EN_UPGRADE_CMD_PACKET_SIZE,
	EN_UPGRADE_CMD_UPGRADE_FILE,
	EN_UPGRADE_CMD_FORCE_BACKUP,
	EN_UPGRADE_CMD_RESTART_APP,
	EN_UPGRADE_CMD_GET_UPGRADE_PROC_NUM,
	EN_UPGRADE_CMD_GET_UPGRADE_VER_COUNT,
	EN_UPGRADE_CMD_GET_UPGRADE_CUR_NAME,
	EN_UPGRADE_CMD_GET_UPGRADE_CUR_VERSION,
	EN_UPGRADE_CMD_GET_IP = 11,
	EN_UPGRADE_CMD_UNKNOWN,
}EN_UPGRADE_CMD_TYPE;

typedef struct
{
	long lProcid;
	long lVer;
}ST_RECOVERY_INFO, *PST_RECOVERY_INFO;

typedef struct
{
	int iType;
}ST_RESTART, *PST_RESTART;

typedef enum
{
	EN_UPGRADE_OPEN_CHANNEL_SUCCESS = long(0),
	EN_UPGRADE_OPEN_CHANNEL_FILE_UNRECOGNIZED,
	EN_UPGRADE_OPEN_CHANNEL_CONDUCTION_UNSUIT,
	EN_UPGRADE_OPEN_CHANNEL_OTHER_ERROR,

}EN_UPGRADE_ESTABLISH_CHANNEL_RESULT;

typedef enum
{
	EN_UPGRADE_PACKET_SUCCESS = long(0),
	EN_UPGRADE_CHECKSUM_ERROR,
	EN_UPGRADE_WRITE_ERROR,
	EN_UPGRADE_LENGTH_ERROR,
	EN_UPGRADE_OTHER_ERROR,
}EN_UPGRADE_PACKET_RESULT;

typedef enum
{
	EN_UPGRADE_RECOVERY_SUCCESS = long(0),
	EN_UPGRADE_RECOVERY_FAIL,
}EN_UPGRADE_RECOVERY_RESULT;

typedef enum
{
	EN_UPGRADE_RESTART_SUCCESS = long(0),
	EN_UPGRADE_RESTART_FAIL,
}EN_UPGRADE_RESTART_RESULT;

typedef enum
{
	EN_UPGRADE_GET_UPGRADE_PROC_NUM_SUCCESS = long(0),
	EN_UPGRADE_GET_UPGRADE_PROC_NUM_FAIL,
}EN_UPGRADE_GET_UPGRADE_PROC_NUM_RESULT;



typedef enum
{
	EN_UPGRADE_PC_TOOLS = long(0),
	EN_UPGRADE_MAIN_CTRL,
	EN_UPGRADE_CABC,
	EN_UPGRADE_CDU,
	EN_UPGRADE_UIM,
	EN_UPGRADE_TSM,
	EN_UPGRADE_FOC,
	EN_UPGRADE_LFUA,
	EN_UPGRADE_LFUB,

}EN_UPGRADE_DEV_TYPE;


typedef struct _FILE_INFO
{
	long lFileInfoSize;
	unsigned char aucFileInfoData[1];
}ST_FILE_INFO,*PST_FILE_INFO;

typedef struct _UPDATA_FILE_PACKET
{
	long lFileSize;
	long lPacketIndex;
	long lPacketSize;

	union
	{
		EN_UPGRADE_PACKET_RESULT enTranceferResult;
		unsigned char ucCheckSum;
	};
	unsigned char aucFileData[1];
} ST_UPDATA_FILE_PACKET,*PST_UPDATA_FILE_PACKET;



#endif //UPGRADE_H
