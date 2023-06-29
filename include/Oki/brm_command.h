/*
	定义BRM模块的通讯数据结构，以及通讯函数。//
	用语
	ATM 			…Automated Teller Machine、现金自动存取款机
	RJ				…ReJect
	BRM				…Bill　Recycle　Module		＝　纸币循环存取款机
	SP				…Service Provider			＝　上层装置
	USB 			…Universal Serial Bus
	IPL 			…Initial Program Loader
	IPL-A			…是指在IPL中，实装在ROM部上不变的Program。
	IPL-B			…是指在IPL中，实装在FLASHMemory内可能变更的Program。
	
	Category1　　	…是验钞部的纸币验钞结果的一种，纸币是指不能判定的钞。　在本规格书里定义为"不明钞"。
	Category2　　　	…是验钞部的纸币验钞结果的一种，假钞是指已被判定的钞。　在本规格书里定义为"假钞"。
	Category3　　　	…是验钞部的纸币验钞结果的一种，是指有假钞的可疑性的钞。　在本规格书里定义为"疑惑钞"。
	Category4a　　	…是验钞部的纸币验钞结果的一种，被判定为纸币，指可进行纸币循环的钞。	在本规格书里定义为"可Recycle钞"。
	Category4b　　	…是验钞部的纸币验钞结果的一种，被判定为纸币，指不可进行纸币循环的钞。在本规格书里定义为"不可Recycle钞"。

*/

#ifndef	__brm_command_h
#define __brm_command_h


#pragma		pack(push, 1)

//钞箱容量
#define		CASSETTE_A2E_CAPA			(2750)
#define		CASSETTE_R_CAPA				(600)
#define		CASSETTE_F_CAPA				(600)

//钞箱名字
#define		CASSETTE_A_NAME				"CassetteA"
#define		CASSETTE_B_NAME				"CassetteB"
#define		CASSETTE_C_NAME				"CassetteC"
#define		CASSETTE_D_NAME				"CassetteD"
#define		CASSETTE_E_NAME				"CassetteE"
#define		CASSETTE_R_NAME				"CassetteRT"//"CassetteR"	//如果有需要，可以设置为CassetteRT
#define		CASSETTE_F_NAME				"CassetteRJ"//"CassetteF"	//如果有需要，可以设置为CassetteRJ

//钞箱ID
#define		CASSETTE_A_ID				"CAS_A"
#define		CASSETTE_B_ID				"CAS_B"
#define		CASSETTE_C_ID				"CAS_C"
#define		CASSETTE_D_ID				"CAS_D"
#define		CASSETTE_E_ID				"CAS_E"
#define		CASSETTE_R_ID				"RTCAS"		//"CAS_R"		//如果有需要，可以设置为RTCAS
#define		CASSETTE_F_ID				"RJCAS"		//"CAS_F"		//如果有需要，可以设置为RJCAS

//钞箱关闭
#define		CASSETTE_A_CDM_CLOSE		0x00010000	//A钞箱分离关闭
#define		CASSETTE_B_CDM_CLOSE		0x00020000	//B钞箱分离关闭
#define		CASSETTE_C_CDM_CLOSE		0x00040000	//C钞箱分离关闭
#define		CASSETTE_D_CDM_CLOSE		0x00080000	//D钞箱分离关闭
#define		CASSETTE_E_CDM_CLOSE		0x00100000	//E钞箱分离关闭

#define		CASSETTE_A_CIM_CLOSE		0x00200000	//A钞箱收集关闭
#define		CASSETTE_B_CIM_CLOSE		0x00400000	//B钞箱收集关闭
#define		CASSETTE_C_CIM_CLOSE		0x00800000	//C钞箱收集关闭
#define		CASSETTE_D_CIM_CLOSE		0x01000000	//D钞箱收集关闭
#define		CASSETTE_E_CIM_CLOSE		0x02000000	//E钞箱收集关闭

//存款验钞处理面额
#define		VERIFY_PROC_DENOM1			0x0001
#define		VERIFY_PROC_DENOM2			0x0002
#define		VERIFY_PROC_DENOM3			0x0004
#define		VERIFY_PROC_DENOM4			0x0008
#define		VERIFY_PROC_DENOM5			0x0010
#define		VERIFY_PROC_DENOM6			0x0020
#define		VERIFY_PROC_DENOM7			0x0040
#define		VERIFY_PROC_DENOM8			0x0080
#define		VERIFY_PROC_DENOM9			0x0100
#define		VERIFY_PROC_DENOM10			0x0200
#define		VERIFY_PROC_DENOM11			0x0400
#define		VERIFY_PROC_DENOM12			0x0800
#define		VERIFY_PROC_DENOM13			0x1000
#define		VERIFY_PROC_DENOM14			0x2000
#define		VERIFY_PROC_DENOM15			0x4000
#define		VERIFY_PROC_DENOM16			0x8000

//钞票传输位置
#define		BILL_TRANS_PLACE_CAS_IN		0x02		//传输进单存箱，面值指定
#define		BILL_TRANS_PLACE_CAS_MIX	0x04		//传输进混存箱，面值不指定
#define		BILL_TRANS_PLACE_CAS_D		0x0B		//传输进D钞箱
#define		BILL_TRANS_PLACE_CAS_E		0x0C		//传输进E钞箱
#define		BILL_TRANS_PLACE_CAS_R		0x0D		//传输进R钞箱
#define		BILL_TRANS_PLACE_CAS_F		0x0E		//传输进F钞箱

/*brm命令返回事件等待超时时间*/
#define		EVENT_TIMEOUT				180000				//180s

/*钞票位置*/
#define		BILL_POS_SHUTTER			0x0001				//钞口有钞票
#define		BILL_POS_ESCROW				0x0004				//暂存有钞票
#define		BILL_POS_TRANSPORT			0x0010				//通道有钞票

/*钞门控制*/
#define		SHUTTER_CTRL_FCLOSE			0x01				//强制关内钞门
#define		SHUTTER_CTRL_CLOSE			0x02				//关内钞门
#define		SHUTTER_CTRL_OPEN			0x80				//开内钞门

/*回收分离位置*/
#define		RETRACT_FROM_SHUTTERESCROW	0x00				//钞口暂存回收，用于外部命令
#define		RETRACT_FROM_ESCROW			0x80				//暂存回收，用于内部取款废钞回收

/*验钞重试指示*/
#define		VERIFY_RETRY				0x81				//存款验钞重试
#define		VERIFY_NOT_RETRY			0x00				//存款验钞不重试

/*取钞时的交易类型*/
#define		TAKE_FOR_DISPENSE			0x01				//取款时，取钞。
#define		TAKE_FOR_DEPOSIT			0x02				//存款拒钞，退钞时，取钞。
	
/*取款出钞类型， 指定面额张数出钞，或者指定钞箱张数出钞*/
#define		DISPENSE_TYPE_DENOM			0x00				//指定面额张数出钞
#define		DISPENSE_TYPE_CASSETTE		0x01				//指定钞箱张数出钞
	
/*设备初始化复位，采用的复位模式，通常，维护，远程，强制4种*/
#define		INIT_TYPE_NORMAL			0x01				//通常初始化
#define		INIT_TYPE_MAINTAN			0x02				//维护初始化
#define		INIT_TYPE_REMOTE			0x03				//远程初始化，OKI建议方式
#define		INIT_TYPE_FORCE				0x04				//强制初始化

/*内钞口led灯控制*/
#define		SHUTTER_LED_OPEN			0xC1
#define		SHUTTER_LED_CLOSE			0xC0

/*各个命令的事件*/
typedef	struct _EVENTHANDLE
{
	HANDLE			hFreeze;
	HANDLE			hLoadSG;
	HANDLE			hCIMModeSet;
	HANDLE			hCIMVerify;
	HANDLE			hCIMStore;
	HANDLE			hCIMCancel;
	HANDLE			hCDMModeSet;
	HANDLE			hCDMDispense;
	HANDLE			hTiming;
	HANDLE			hModeReset;
	HANDLE			hRetract;
	HANDLE			hMoveBill;
	HANDLE			hCleaning;
	HANDLE			hPathCheck;
	HANDLE			hLedCtrl;
	HANDLE			hInit;
	HANDLE			hShutterCtrl;
	HANDLE			hShutterCheck;
	HANDLE			hStatusCheck;
	HANDLE			hCountRead;
	HANDLE			hCountClear;
	HANDLE			hMEMRead;
	HANDLE			hLogRead;
	HANDLE			hGetDataSet;
	HANDLE			hGetCasCloseInfo;
	HANDLE			hGetCasConf;
	HANDLE			hSetDataSet;
	HANDLE			hSetCasCloseInfo;
	HANDLE			hSetCasConf;
}EVENTHANDLE,*LPEVENTHANDLE;



/*Cassette信息*/
typedef struct _CASSETTEINFO
{
	BYTE	byUseClassInfo;					//hi-half：1-取款 2-存款（面额指定）3-循环 4-存款（面额不指定）8-补充回收 F-其他  lo-half：0-处理纸币group有效 1-处理纸币group无效	
	BYTE	byDIPSwitchInfo;				//对于CAS_R,CAS_F,该信息无效。在byUseClassInfo的lo-half无效时，使用该信息。0-不使用 1-8对应group1-8。9-补充回收专用，10-存款专用，无面额指定，11-14对应存款专用2-5.（2对应group4, 3对应group3，其他保留）
	BYTE	byszProcBillGroupNO[2];			//纸币group对应 1-16。为0表示不指定纸币group
}CASSETTEINFO, *LPCASSETTEINFO;

/*Cassette分类信息*/
typedef struct _CASSETTECLASSINFO
{
	CASSETTEINFO	CassetteAInfo;			//默认设置 0x10,0x00,0x04,0x00		//取款 纸币group4
	CASSETTEINFO	CassetteBInfo;			//默认设置 0x10,0x00,0x04,0x00		//取款 纸币group4
	CASSETTEINFO	CassetteCInfo;			//默认设置 0x10,0x00,0x03,0x00		//取款 纸币group3
	CASSETTEINFO	CassetteDInfo;			//默认设置 0x20,0x00,0x04,0x00		//存款 纸币group4
	CASSETTEINFO	CassetteEInfo;			//默认设置 0x40,0x00,0x00,0x00		//存款 面额指定无	
	CASSETTEINFO	CassetteRInfo;			//默认设置 0xF0,0x00,0x00,0x00		//个别指定
	CASSETTEINFO	CassetteFInfo;			//默认设置 0xF0,0x00,0x00,0x00		//个别指定
	BYTE			byszReserved[4];		//默认设置 0x00,0x00,0x00,0x00
}CASSETTECLASSINFO, *LPCASSETTECLASSINFO;

/*运用设置的控制信息*/
typedef	struct _CTRLINFO
{
	CASSETTECLASSINFO	CassetteClassInfo;
	BYTE				bySensorRevise;						//传感器补正方式			0，1~30						默认：0x00
	BYTE				byRetryWhenDepRJ;					//存款时发生的RJ纸币再次计数是否进行的设定	0~10		默认：0x01
	BYTE				byRetryWhenMoveRJ;					//纸币移动时发生的RJ纸币再次计数是否进行的设定	0~1		默认：0x00
	BYTE				bySaveEnergyTimer;					//省电时钟b7=0：秒 1：分。b6~b0=时间值					默认：0x85
	BYTE				bySaveEnergyMode;					//省电模式00：不省电 01：仅BRM省电 02：BRM+BV省电		默认：0x00
	BYTE				byActionWhenDepRJ;					//存款时发生RJ后的动作规格。00：把传输通道介质暂时收集到Escrow后，传输到存取钞口。 01：把传输通道介质暂时停止在传输通道上后，传输到存取钞口。默认：0x01
	BYTE				byLimitTimesOfDepRJ;				//存款RJ连续限度次数。1~200								默认：0x14
	BYTE				byLimitCntsOfDepRJ;					//存款RJ总张数限度。1~200								默认：0x19
	BYTE				bySpeedOfDepSeparateRetry;			//存款分离Retry时的分离速度。00:连续分离（无间歇分离）01：1张张分离（有间歇分离）	默认：0x01
	BYTE				byszReserved[0x3F - 0x28];
}CTRLINFO, *LPCTRLINFO;

/*运用设置的容量信息*/
typedef	struct _CAPAINFO
{
	BYTE				byCasAFull;							//A钞箱满设置	0~9  0：50， 1：100， 2：150， 3：200 ，4：250，5：300，6：350，7：400，8：450，9：500					默认：0x02
	BYTE				byCasANearEmpty;					//A钞箱将空设置	0~9同上 80~89	80：10，81：20，82：30，83：40，84：50，85：60，86：70，87：80，88：90，89：100			默认：0x00
	BYTE				byCasBFull;							//B钞箱满设置	0~9  0：50， 1：100， 2：150， 3：200 ，4：250，5：300，6：350，7：400，8：450，9：500					默认：0x02						
	BYTE				byCasBNearEmpty;					//B钞箱将空设置	0~9同上 80~89	80：10，81：20，82：30，83：40，84：50，85：60，86：70，87：80，88：90，89：100			默认：0x00								
	BYTE				byCasCFull;							//C钞箱满设置	0~9  0：50， 1：100， 2：150， 3：200 ，4：250，5：300，6：350，7：400，8：450，9：500					默认：0x02									
	BYTE				byCasCNearEmpty;					//C钞箱将空设置	0~9同上 80~89	80：10，81：20，82：30，83：40，84：50，85：60，86：70，87：80，88：90，89：100			默认：0x00					
	BYTE				byCasDFull;							//D钞箱满设置	0~9  0：50， 1：100， 2：150， 3：200 ，4：250，5：300，6：350，7：400，8：450，9：500					默认：0x02					
	BYTE				byCasDNearEmpty;					//D钞箱将空设置	0~9同上 80~89	80：10，81：20，82：30，83：40，84：50，85：60，86：70，87：80，88：90，89：100			默认：0x00
	BYTE				byCasEFull;							//E钞箱满设置	0~9  0：50， 1：100， 2：150， 3：200 ，4：250，5：300，6：350，7：400，8：450，9：500					默认：0x02	
	BYTE				byCasENearEmpty;					//E钞箱将空设置	0~9同上 80~89	80：10，81：20，82：30，83：40，84：50，85：60，86：70，87：80，88：90，89：100			默认：0x00	
	BYTE				byszReserved[0x4F - 0x49];			//保留
	BYTE				byCasRFull;							//R钞箱满设置	0~b  0：50， 1：100， 2：150， 3：200 ，4：250，5：300，6：350，7：400，8：450，9：500，a：550，b：600	默认：0x0b	
	BYTE				byReserved1;						//保留
	BYTE				byCasFFull;							//F钞箱满设置	0~b  0：50， 1：100， 2：150， 3：200 ，4：250，5：300，6：350，7：400，8：450，9：500	a：550，b：600	默认：0x0b	
	BYTE				byszReserved2[0x5F - 0x52];			//保留
}CAPAINFO, *LPCAPAINFO;

/*运用设置的信息*/
typedef struct _RUNSETINFO
{
	CTRLINFO			CtrlInfo;
	CAPAINFO			CapaInfo;
}RUNSETINFO, *LPRUNSETINFO;

/*验钞种类*/
typedef struct _VERIFYTYPE
{
	BYTE				byVerifyLevel1_CD;					//验钞水平1，污损
	BYTE				byVerifyLevel2_GB;					//验钞水平2，破损
	BYTE				byVerifyLevel3_TP;					//验钞水平3，胶纸
	BYTE				byVerifyLevel4_TF;					//验钞水平4，真伪
	BYTE				byVerifyLevel5_ZJ;					//验钞水平5，折角
	BYTE				byVerifyLevel6_KD;					//验钞水平6，孔洞
	BYTE				byReserved;							//保留
	BYTE				byVerifyLevel8_RT;					//验钞水平8，重新验钞
}VERIFYTYPE,*LPVERIFYTYPE;

/*验钞设置的信息*/
typedef struct _VERIFYSETINFO
{
	VERIFYTYPE			VerifyType[0x10];					
	//验钞类型。下标0x00-存款 0x01-回收（存款方向） 0x02-回收（入钞箱方向）
	//0x03-存入钞箱 0x04-存款取消 0x05-取款 0x0a-计数1（存取口）
	//0x0b-计数2（暂存） 0x0c-计数1（钞箱） 0x0d-纸币移动（存款方向） 
	//0x0e-纸币移动（入钞箱方向） 
	BYTE				byszCurrencyData[16];				//币种用数据。组数下标0~15分别为币种1~币种16用的数据。	
}VERIFYSETINFO, *LPVERIFYSETINFO;

typedef struct _USERLOGININFO
{
	RUNSETINFO			RunSetInfo;
	VERIFYSETINFO		VerifySetInfo;
	BYTE				byszReserved[0xFE - 0xEF];		//保留
	BYTE				byHash;							//hash修正值
}USERLOGININFO,*LPUSERLOGININFO;

/*钞箱状态*/
typedef	struct _CASSTATUS
{
	BYTE				byCasAStatus;
	BYTE				byCasBStatus;
	BYTE				byCasCStatus;
	BYTE				byCasDStatus;
	BYTE				byCasEStatus;
	BYTE				byCasRStatus;
	BYTE				byCasFStatus;
}CASSTATUS,*LPCASSTATUS;

/*钞箱当前容量*/
typedef struct _CASCAPA
{
	WORD				wCasACapa;
	WORD				wCasBCapa;
	WORD				wCasCCapa;
	WORD				wCasDCapa;
	WORD				wCasECapa;
	WORD				wCasRCapa;
	WORD				wCasFCapa;
}CASCAPA,*LPCASCAPA;

/*面值信息*/
typedef struct _DENOMINFO
{
	BYTE				byDenomInfo;
	BYTE				byDenomInfo1;
	BYTE				byDenomInfo2;
	BYTE				byDenomInfo3;
	BYTE				byDenomInfo4;
	BYTE				byDenomInfo5;
	BYTE				byDenomInfo6;
	BYTE				byDenomInfo7;
	BYTE				byDenomInfo8;
	BYTE				byDenomInfo9;
	BYTE				byDenomInfo10;
	BYTE				byDenomInfo11;
	BYTE				byDenomInfo12;
	BYTE				byDenomInfo13;
	BYTE				byDenomInfo14;
	BYTE				byDenomInfo15;
	BYTE				byDenomInfo16;	
}DENOMINFO,*LPDENOMINFO;

/*BRM状态*/
typedef	struct	_BRMSTATUS
{
	CASSETTECLASSINFO	CassetteClassInfo;
	CASSTATUS			CasStatus;
	BYTE				byReserved;
	WORD				wCasFuncSet;	//钞箱关闭信息。b0~b15，0-不关闭 1-关闭。  b0-A钞箱收集 b1-A钞箱分离 b2-B钞箱收集 b3-B钞箱分离等等。。
	BYTE				byszReserved[0x2F - 0x29];
}BRMSTATUS,*LPBRMSTATUS;

/*故障位置图显示用信息*/
typedef	struct _ERRILLUSTRATION
{
	WORD				wDataLen;
	BYTE				byszErrIllustrationFlagInfo[2];		//by[0]:01-5cas brm. 02-3cas brm. by[1]:b0=1 有casR，b0=0 无casR。
	CASSETTECLASSINFO	CassetteClassInfo;
	CASCAPA				CasCapa;
	WORD				wReserved;
	DWORD				dwLeftMediaInfo;	//b0-存取钞口 b1-存款第1/2sensor b2-验钞 
											//b3-RejectBladeTrigger／传输通道残留Sensor／R Cassette收集确认Sensor  
											//b4 b5-escrow	b6-存取口收集确认 b7-CASR b8-上部交接 b9-CASF交接
											//b10-CASA交接 b11-CASB交接 b12-CASC交接 b13-CASD交接 b14-CASE交接
											//b16-CASA b17-CASB b18-CASC b19-CASD b20-CASE b21-CASF
	BYTE				byErrPart;
	BYTE				byErrPath;
	CASSTATUS			CasStatus;
	BYTE				byszReserved1[0x46 - 0x40];
	DENOMINFO			DenomInfo;
	BYTE				byszReserved2[0x5F - 0X57];
}ERRILLUSTRATION,*LPERRILLUSTRATION;

/*倒序denom，BYTE大小*/
typedef struct _BYINVERSEDENOM
{
	BYTE				byCountOfDenomInfo16;
	BYTE				byCountOfDenomInfo15;
	BYTE				byCountOfDenomInfo14;
	BYTE				byCountOfDenomInfo13;
	BYTE				byCountOfDenomInfo12;
	BYTE				byCountOfDenomInfo11;
	BYTE				byCountOfDenomInfo10;
	BYTE				byCountOfDenomInfo9;
	BYTE				byCountOfDenomInfo8;
	BYTE				byCountOfDenomInfo7;
	BYTE				byCountOfDenomInfo6;
	BYTE				byCountOfDenomInfo5;
	BYTE				byCountOfDenomInfo4;
	BYTE				byCountOfDenomInfo3;
	BYTE				byCountOfDenomInfo2;
	BYTE				byCountOfDenomInfo1;
}BYINVERSEDENOM,*LPBYINVERSEDENOM;

/*倒序denom，WORD大小*/
typedef struct _INVERSEDENOM
{
	WORD				wCountOfDenomInfo16;
	WORD				wCountOfDenomInfo15;
	WORD				wCountOfDenomInfo14;
	WORD				wCountOfDenomInfo13;
	WORD				wCountOfDenomInfo12;
	WORD				wCountOfDenomInfo11;
	WORD				wCountOfDenomInfo10;
	WORD				wCountOfDenomInfo9;
	WORD				wCountOfDenomInfo8;
	WORD				wCountOfDenomInfo7;
	WORD				wCountOfDenomInfo6;
	WORD				wCountOfDenomInfo5;
	WORD				wCountOfDenomInfo4;
	WORD				wCountOfDenomInfo3;
	WORD				wCountOfDenomInfo2;
	WORD				wCountOfDenomInfo1;
}INVERSEDENOM,*LPINVERSEDENOM;

/*子计数，用于分离，收集动作计数中*/
typedef struct _SUBCOUNT
{
	INVERSEDENOM		Category4a;
	INVERSEDENOM		Category4b;
	INVERSEDENOM		Category3;
	INVERSEDENOM		Category2;
	WORD				wCountOfUnknownCategory1;
	BYTE				byszReserve[0x8F - 0x81];
}SUBDEPARTCOUNT,SUBCOLLECTCOUNT,ART6COUNT,*LPSUBDEPARTCOUNT,*LPSUBCOLLECTCOUNT,*LPART6COUNT;

/*子计数，用于剩余动作计数*/
typedef struct _SUBLEFTCOUNT
{
	INVERSEDENOM		Category;	
	WORD				wCountOfUnknownCategory;
	BYTE				byszReserved[0x2F - 0x21];
}SUBLEFTCOUNT,*LPSUBLEFTCOUNT;

/*分离计数*/
typedef struct _DEPARTCOUNT
{
	SUBDEPARTCOUNT		CountOfShutter;			//存取款钞口分离张数
	SUBDEPARTCOUNT		CountOfEscrow;			//暂存分离张数
	SUBDEPARTCOUNT		CountOfCasA;
	SUBDEPARTCOUNT		CountOfCasB;
	SUBDEPARTCOUNT		CountOfCasC;
	SUBDEPARTCOUNT		CountOfCasD;
	SUBDEPARTCOUNT		CountOfCasE;
}DEPARTCOUNT,*LPDEPARTCOUNT;


/*收集计数*/
typedef struct _COLLECTCOUNT
{
	SUBCOLLECTCOUNT		CountOfShutter;
	SUBCOLLECTCOUNT		CountOfEscrow;
	SUBCOLLECTCOUNT		CountOfCasA;
	SUBCOLLECTCOUNT		CountOfCasB;
	SUBCOLLECTCOUNT		CountOfCasC;
	SUBCOLLECTCOUNT		CountOfCasD;
	SUBCOLLECTCOUNT		CountOfCasE;
	SUBCOLLECTCOUNT		CountOfCasR;
	SUBCOLLECTCOUNT		CountOfCasF;
}COLLECTCOUNT,*LPCOLLECTCOUNT;

/*剩余计数*/
typedef struct _LEFTCOUNT
{

	SUBLEFTCOUNT		CountOfCasA;
	SUBLEFTCOUNT		CountOfCasB;
	SUBLEFTCOUNT		CountOfCasC;
	SUBLEFTCOUNT		CountOfCasD;
	SUBLEFTCOUNT		CountOfCasE;
	SUBLEFTCOUNT		CountOfCasR;
	SUBLEFTCOUNT		CountOfCasF;
	SUBLEFTCOUNT		CountOfEscrow;
}LEFTCOUNT,*LPLEFTCOUNT;

/*动作计数*/
typedef struct _ACTIONCOUNT
{
	DEPARTCOUNT			DepartCount;
	COLLECTCOUNT		CollectCount;
	LEFTCOUNT			LeftCount;
}ACTIONCOUNT,*LPACTIONCOUNT;

/*纸币钞箱条形码信息*/
typedef struct _CASBARCODE
{
	BYTE				byszCasABarCode[6];
	BYTE				byszReserved[2];
	BYTE				byszCasBBarCode[6];
	BYTE				byszReserved1[2];
	BYTE				byszCasCBarCode[6];
	BYTE				byszReserved2[2];
	BYTE				byszCasDBarCode[6];
	BYTE				byszReserved3[2];
	BYTE				byszCasEBarCode[6];
	BYTE				byszReserved4[2];
	BYTE				byszCasASubUnitID[4];
	BYTE				byszCasBSubUnitID[4];
	BYTE				byszCasCSubUnitID[4];
	BYTE				byszCasDSubUnitID[4];
	BYTE				byszCasESubUnitID[4];
	BYTE				byszReserved5[4];
}CASBARCODE,*LPCASBARCODE;

/*命令通用响应信息*/
typedef struct _PUBRESP 
{
	DWORD				dwCasCloseInfo;
	WORD				wBillInfo;			//b0~b15,0-无，1-有 b1(客户纸币剩余)，b2(客户卡钞时)，b4(装置纸币剩余)，b5(装置卡钞时)，b7(管理外纸币)，b15(纸币模式，0-真，1-模拟)
	WORD				wLeftMediaStatus;	//b0~b7,0-无，1-有 b0(存取钞口) b2(暂存) b7(通道)
	DWORD				dwActionResultStatus;//b0~b31
	BYTE				byszReserved[2];
	WORD				wEquipFlagInfo;
	BRMSTATUS			BRMStatus;
	ERRILLUSTRATION		ErrIllustration;
	DENOMINFO			Denominfo;
	BYTE				byszReserve[0xCF - 0xC0];
	ACTIONCOUNT			ActionCount;
	CASBARCODE			CasBarCode;
}PUBRESP,*LPPUBRESP;

/*安全信息*/
typedef struct _SAFEINFO
{
	BYTE				byInterLock;	//b0=1上部安全interlock脱落。b1=1下部安全interlock脱落。
	BYTE				byCasA_EStatus;	//b0~b5 A~E （missing）
	BYTE				byCasR_CasF_BV_UP_LOWStatus;//b0,b1,b4,b6,b7
	BYTE				byReserved1;
	BYTE				byszReserved[0x0F - 0x03];
}SAFEINFO,*LPSAFEINFO;

/*剩余移动信息-到底是0x30字节还是0x40字节*/
typedef struct _LEFTMOVEINFO 
{
	BYTE				byszShutter[6];
	BYTE				byszEscrow[2];
	BYTE				byszCasA[2];
	BYTE				byszCasB[2];
	BYTE				byszCasC[2];
	BYTE				byszCasD[2];
	BYTE				byszCasE[2];	
	BYTE				byszUpTransport[2];
	BYTE				byszLowTransport[2];
	BYTE				byszUpOther[6];
	BYTE				byszLowCommon[2];
	BYTE				byCasA1;
	BYTE				byCasB1;
	BYTE				byCasC1;
	BYTE				byCasD1;
	BYTE				byCasE1;
	BYTE				byReserved;
	BYTE				byszReserved1[5];
	BYTE				byVerifyLeftInfo;
	BYTE				byszReserved[0x3F - 0x29];
}LEFTMOVEINFO,*LPLEFTMOVEINFO;

typedef struct _SUBVERIFYDENOMINFO
{
	BYTE				byCountryInfo;				//国信息
	BYTE				byBillGroupOfDisType;		//取款类纸币group
	BYTE				byBillGroupOfDepType;		//存款类纸币group
	BYTE				byDenomInfo;				//面额信息
}SUBVERIFYDENOMINFO;

typedef struct _VERIFYDENOMINFO
{
	BYTE				byDenomNO;
	BYTE				byszReserved[3];
	SUBVERIFYDENOMINFO	SubVerifyDenomInfo[16];		//下标0-15，表示币种1-16	
}VERIFYDENOMINFO;

/*命令通用头，请求类命令无视errorcode，errorcodedetail*/
typedef struct _HEAD
{
	BYTE				byszReserved[4];		//命令头4字节保留。
	BYTE				byLU;				//设备类型
	BYTE				byIFCODE;			//cmd-1,resp-2,att-3
	BYTE				byCMD;				//命令类型
	BYTE				byErrorCode;
	BYTE				byszErrorCodeDetail[2];
	BYTE				byszReserved1[2];
	WORD				wErrStatus;
	BYTE				byszReserved2[0x0D - 0x09];
	WORD				wDataLen;		
}HEAD,*LPHEAD;

/*取款命令头，和通用的有一点区别*/
typedef struct _CDMHEAD
{
	BYTE				byszReserved[4];		//命令头4字节保留。
	BYTE				byLU;				//设备类型
	BYTE				byIFCODE;			//cmd-1,resp-2,att-3
	BYTE				byCMD;				//命令类型
	BYTE				byErrorCode;
	BYTE				byszErrorCodeDetail[2];
	BYTE				byszReserved1[0x0C - 0x05];
	BYTE				byDisType;			//取款指定模式，指定面额或者钞箱
	WORD				wDataLen;		
}CDMHEAD,*LPCDMHEAD;

/*以上部分是所有硬件通讯中用到的数据的子结构，其中有些子结构中还嵌套有子结构*/
/*以下部分将以上子结构组合成硬件命令发送/接受所用到的完整的参数*/

/*故障响应，针对下发命令的回应，当有故障出现时，硬件返回如下参数结构*/
typedef struct _BRM_ERRORRESP
{
	HEAD				HeadOfResp;
	PUBRESP				PubResp;
}BRM_ERRORRESP,*LPBRM_ERRORRESP;


/**************动作类命令，请求与回应参数结构**********/

/************************存款类命令*******************/

/*存款模式设置请求*/
typedef struct _BRM_CIMMODESET_REQ
{
	HEAD				HeadOfReq;
	BYTE				byAutoResetMode;
	BYTE				byszBCDYear[2];
	BYTE				byBCDMonth;
	BYTE				byBCDDay;
	BYTE				byBCDHour;
	BYTE				byBCDMinute;
	BYTE				byBCDSecond;
	BYTE				byTemperature;			//可以设置任何值
	BYTE				byHumidity;				//可以设置任何值
}BRM_CIMMODESET_REQ,*LPBRM_CIMMODESET_REQ;

/*存款模式设置应答*/
typedef struct _BRM_CIMMODESET_RESP
{
	HEAD				HeadOfResp;
	PUBRESP				PubResp;
}BRM_CIMMODESET_RESP,*LPBRM_CIMMODESET_RESP;

/*存款验钞请求*/
typedef struct _BRM_CIMVERIFY_REQ
{
	HEAD				HeadOfReq;
	BYTE				byAutoResetMode;
	BYTE				byRetryFlag;				//存款验钞重试指示
	WORD				wProcDenom;					//处理面额(面额就是100，50，20，10)
	BYTE				byszBCDRestrictCount[4];	//存款限制张数
	BYTE				byszBCDRestrictAmount[4];	//存款限制金额
	BYTE				byCategoryDepCtrlInfo;		//各Category存款控制信息 b1:0-category2介质（伪钞）不退回 1-退回  b2:0-category3介质（疑惑钞）不受理 1-受理 b4:0-category4b介质（不可循环钞）不受理 1-受理
	BYTE				byReserved;
	WORD				wProcGroup;					//处理纸币group(group就是，国别-存取款类纸币group-面值信息)
}BRM_CIMVERIFY_REQ,*LPBRM_CIMVERIFY_REQ;

/*存款验钞应答*/
typedef struct _BRM_CIMVERIFY_RESP
{
	HEAD				HeadOfResp;
	PUBRESP				PubResp;
	BYTE				byszBCDDepCount[4];
	BYTE				byszBCDDepAmount[4];
}BRM_CIMVERIFY_RESP,*LPBRM_CIMVERIFY_RESP;


/*存款入钞箱请求*/
typedef struct _BRM_CIMSTORE_REQ
{
	HEAD				HeadOfReq;
	BYTE				byAutoResetMode;
	BYTE				byCategoryCanRecycle;					//各category的recycle可否信息。b2-category3（疑惑钞）是否循环，b3-category4a（recycle可能钞）是否循环，b4-category4b（recycle不可钞）是否循环
	BYTE				byszNonRecycleBillPlace[0x16 - 0x11];	//by[0]-category1（不明钞） by[1]-category2（伪钞）by[2]-category3（疑惑钞） by[3]-category4a（recycle可能钞） by[4]-category4b（recycle不可钞）。0：传输终点不指定 2：存款专用（面值指定） 4：存款专用（面值不指定） B：CasD C：CasE D：CasR E：CasF
	BYINVERSEDENOM		Category;
	BYTE				byszFirstCollect[5];					//by[0]-1级优先 by[1]-2级优先 by[2]-3级优先。。。。1：CasA 2：CasB 3：CasC 4：CasD 5：CasE
}BRM_CIMSTORE_REQ,*LPBRM_CIMSTORE_REQ;

/*存款入钞箱应答*/
typedef struct _BRM_CIMSTORE_RESP
{	
	HEAD				HeadOfResp;
	PUBRESP				PubResp;
}BRM_CIMSTORE_RESP,*LPBRM_CIMSTORE_RESP;

/*存款取消请求*/
typedef struct _BRM_CIMCANCEL_REQ
{
	HEAD				HeadOfReq;
	BYTE				byAutoResetMode;
	BYTE				byCategoryRollBackInfo;				 //0-不可退回 1-可退回。b1:category2（伪钞） b2-category3（疑惑钞）
	BYTE				byszNonRollBackBillPlace[0x16 - 0x11];//不可退回纸币传输终点	by[1]-category2 by[2]-category3，0：传输终点不指定 2：存款专用（面值指定） 4：存款专用（面值不指定） B：CasD C：CasE D：CasR E：CasF
}BRM_CIMCANCEL_REQ,*LPBRM_CIMCANCEL_REQ;

/*存款取消应答*/
typedef struct _BRM_CIMCANCEL_RESP
{
	HEAD				HeadOfResp;
	PUBRESP				PubResp;
}BRM_CIMCANCEL_RESP,*LPBRM_CIMCANCEL_RESP;


/*******************取款类命令*********************/

/*取款模式设置请求*/
typedef struct _BRM_CDMMODESET_REQ
{
	HEAD				HeadOfReq;
	BYTE				byAutoResetMode;
	BYTE				byszBCDYear[2];
	BYTE				byBCDMonth;
	BYTE				byBCDDay;
	BYTE				byBCDHour;
	BYTE				byBCDMinute;
	BYTE				byBCDSecond;
	BYTE				byTemperature;			//可以设置任何值
	BYTE				byHumidity;				//可以设置任何值
	BYTE				byUnknowDenomPlace;		//不明钞票传输位置
}BRM_CDMMODESET_REQ,*LPBRM_CDMMODESET_REQ;

/*取款模式设置应答*/
typedef struct _BRM_CDMMODESET_RESP
{
	HEAD				HeadOfResp;
	PUBRESP				PubResp;
}BRM_CDMMODESET_RESP,*LPBRM_CDMMODESET_RESP;

/*取款请求*/
typedef struct _BRM_CDMDISPENSE_REQ
{
	CDMHEAD				CDMHeadOfReq;			
	BYTE				byAutoResetMode;
	BYTE				byCategoryCanDispense;		//各category的取款可否信息。b2-category3（疑惑钞）是否可取，b4-category4b（recycle不可钞）是否可取
	BYINVERSEDENOM		Category;					//denom14=CasAcnt denom13=CasBcnt denom12=CasCcnt denom11=CasDcnt denom10=CasEcnt
	BYTE				byszFirstDepart[5];			//by[0]-1级优先 by[1]-2级优先 by[2]-3级优先。。。。1：CasA 2：CasB 3：CasC 4：CasD 5：CasE
}BRM_CDMDISPENSE_REQ,*LPBRM_CDMDISPENSE_REQ;

/*取款应答*/
typedef struct _BRM_CDM_RESP
{
	HEAD				HeadOfResp;
	PUBRESP				PubResp;
	BYTE				byCasADisCount;			
	BYTE				byCasBDisCount;			
	BYTE				byCasCDisCount;			
	BYTE				byCasDDisCount;		
	BYTE				byCasEDisCount;
}BRM_CDMDISPENSE_RESP,*LPBRM_CDMDISPENSE_RESP;

/**************存取款共用命令****************/

/*Timing,节电模式请求*/
typedef struct _BRM_TIMING_REQ
{
	HEAD				HeadOfReq;
	BYTE				byAutoResetMode;
	BYTE				byTimingDetails;
}BRM_TIMING_REQ,*LPBRM_TIMING_REQ;

/*Timing,节电模式应答*/
typedef struct _BRM_TIMING_RESP
{
	HEAD				HeadOfResp;
	PUBRESP				PubResp;
}BRM_TIMING_RESP,*LPBRM_TIMING_RESP;

/*模式复位请求*/
typedef struct _BRM_MODERESET_REQ
{
	HEAD				HeadOfReq;
	BYTE				byAutoResetMode;
	BYTE				byszBCDYear[2];
	BYTE				byBCDMonth;
	BYTE				byBCDDay;
	BYTE				byBCDHour;
	BYTE				byBCDMinute;
	BYTE				byBCDSecond;
	BYTE				byTemperature;			//可以设置任何值
	BYTE				byHumidity;				//可以设置任何值
}BRM_MODERESET_REQ,*LPBRM_MODERESET_REQ;

/*模式复位应答*/
typedef struct _BRM_MODERESET_RESP
{
	HEAD				HeadOfResp;
	PUBRESP				PubResp;
}BRM_MODERESET_RESP,*LPBRM_MODERESET_RESP;

/*回收请求*/
typedef struct _BRM_RETRACT_REQ
{
	HEAD				HeadOfReq;
	BYTE				byAutoResetMode;
	BYTE				bySpecifSpecialRetract;		//特殊回收指定  b0-1：ESCROW收集时返回到分离的cassette b0-0：传输根据escrow收集时的面额的收集终点 b1-1:全部传输到escrow，无视其他参数 b1-0：根据其他参数传输 b7-1：仅escrow分离 b7-0:钞口，escrow分离。
	BYTE				byCategoryCanRecycle;		//各category的recycle可否信息。b2-category3（疑惑钞）是否循环，b3-category4a（recycle可能钞）是否循环，b4-category4b（recycle不可钞）是否循环
	BYTE				byszNonRecycleBillPlace[0x17 - 0x12];	//by[0]-category1（不明钞） by[1]-category2（伪钞）by[2]-category3（疑惑钞） by[3]-category4a（recycle可能钞） by[4]-category4b（recycle不可钞）。0：传输终点不指定 2：存款专用（面值指定） 4：存款专用（面值不指定） B：CasD C：CasE D：CasR E：CasF
	BYTE				byszFirstCollect[5];		//by[0]-1级优先 by[1]-2级优先 by[2]-3级优先。。。。1：CasA 2：CasB 3：CasC 4：CasD 5：CasE
}BRM_RETRACT_REQ,*LPBRM_RETRACT_REQ;

/*回收应答*/
typedef struct _BRM_RETRACT_RESP
{
	HEAD				HeadOfResp;
	PUBRESP				PubResp;
}BRM_RETRACT_RESP,*LPBRM_RETRACT_RESP;


/*纸币移动请求*/
typedef struct _BRM_MOVEBILL_REQ
{
	HEAD				HeadOfReq;
	BYTE				byAutoResetMode;
	WORD				wCountOfMoveBill;
	BYTE				byMoveSource;
	BYTE				byMoveTarget;
	BYTE				byUnknowDenomPlace;
	BYTE				byszFirstCollect[5];		//by[0]-1级优先 by[1]-2级优先 by[2]-3级优先。。。。1：CasA 2：CasB 3：CasC 4：CasD 5：CasE
}BRM_MOVEBILL_REQ,*LPBRM_MOVEBILL_REQ;

/*纸币移动应答*/
typedef struct  _BRM_MOVEBILL_RESP 
{
	HEAD				HeadOfResp;
	PUBRESP				PubResp;
}BRM_MOVEBILL_RESP,*LPBRM_MOVEBILL_RESP;

/*清理动作请求*/
typedef struct _BRM_CLEANING_REQ
{
	HEAD				HeadOfReq;
	BYTE				byAutoResetMode;
	BYTE				byszReserved[2];
}BRM_CLEANING_REQ,*LPBRM_CLEANING_REQ;

/*清理动作应答*/
typedef struct _BRM_CLEANING_RESP
{
	HEAD				HeadOfResp;
	PUBRESP				PubResp;
}BRM_CLEANING_RESP,*LPBRM_CLEANING_RESP;

/*路径检测请求*/
typedef struct _BRM_PATHCHECK_REQ
{
	HEAD				HeadOfReq;
	BYTE				byAutoResetMode;
	BYTE				byReserved;
	BYTE				byUnknowDenomPlace;		//6:CasD 7:CasE 8:CasR 9:CasF F:分离起点Cassette			
	BYTE				byCasADepartCount;
	BYTE				byCasBDepartCount;
	BYTE				byCasCDepartCount;
	BYTE				byCasDDepartCount;
	BYTE				byCasEDepartCount;
	BYTE				byReserved1;
}BRM_PATHCHECK_REQ,*LPBRM_PATHCHECK_REQ;

/*路径检测应答*/
typedef struct _BRM_PATHCHECK_RESP
{
	HEAD				HeadOfResp;
	PUBRESP				PubResp;
}BRM_PATHCHECK_RESP,*LPBRM_PATHCHECK_RESP;

/*LED控制请求*/
typedef struct _BRM_LEDCONTROL_REQ
{
	HEAD				HeadOfReq;
	BYTE				byAutoResetMode;
	BYTE				byShutterLedCtrlInfo;		//b0-0:灭灯 b0-1：亮灯 b6-0：平缓发光 b6-1：快速发光 b7-0：led指示无效 b7-1：led指示有效
}BRM_LEDCONTROL_REQ,*LPBRM_LEDCONTROL_REQ;

/*LED控制应答*/
typedef struct _BRM_LEDCONTROL_RESP
{	
	HEAD				HeadOfResp;
	PUBRESP				PubResp;
}BRM_LEDCONTROL_RESP,*LPBRM_LEDCONTROL_RESP;

/*初始化请求*/
typedef struct _BRM_INIT_REQ
{
	HEAD				HeadOfReq;
	BYTE				byAutoResetMode;
	BYTE				byInitFlag;
	BYTE				byReserved;
	BYTE				byUpperConnInfo;
	BYTE				byszReserved[0x16 - 0x13];
	BYTE				byszBCDYear[2];
	BYTE				byBCDMonth;
	BYTE				byBCDDay;
	BYTE				byBCDHour;
	BYTE				byBCDMinute;
	BYTE				byBCDSecond;
	BYTE				byTemperature;			//可以设置任何值
	BYTE				byHumidity;				//可以设置任何值
}BRM_INIT_REQ,*LPBRM_INIT_REQ;

/*初始化应答*/
typedef struct _BRM_INIT_RESP
{
	HEAD				HeadOfResp;
	PUBRESP				PubResp;
}BRM_INIT_RESP,*LPBRM_INIT_RESP;


/*钞门控制请求*/
typedef struct _BRM_SHUTTERCTRL_REQ
{
	HEAD				HeadOfReq;
	BYTE				byAutoResetMode;
	BYTE				byTradeType;		//1：取款交易 2：存款交易
	BYTE				byShutterCtrlFlag;	//b0-强制关， b1-非强制关 b7-开
}BRM_SHUTTERCTRL_REQ,*LPBRM_SHUTTERCTRL_REQ;

/*钞门控制应答*/
typedef struct _BRM_SHUTTERCTRL_RESP
{
	HEAD				HeadOfResp;
	PUBRESP				PubResp;
	WORD				wShutterBillCntEst;			//钞口钞票张数预估
}BRM_SHUTTERCTRL_RESP,*LPBRM_SHUTTERCTRL_RESP;

/*钞门检测请求*/
typedef struct _BRM_SHUTTERCHECK_REQ
{
	HEAD				HeadOfReq;
	BYTE				byAutoResetMode;
	BYTE				byTradeType;
	BYTE				byTimeFlag;				//shuttercheck命令会有稳定时间500/1000ms，为了更快的检测， 20120423
}BRM_SHUTTERCHECK_REQ,*LPBRM_SHUTTERCHECK_REQ;  //oki给了最新的firmware，需要sp对应，命令格式多了个字段，byTimeFlag，设置为0，则按sg进行delay，否则该命令不delay，通过sp来delay确保稳定时间。

/*钞门检测应答*/
typedef struct _BRM_SHUTTERCHECK_RESP
{
	HEAD				HeadOfResp;
	PUBRESP				PubResp;
}BRM_SHUTTERCHECK_RESP,*LPBRM_SHUTTERCHECK_RESP;

/*设备检查请求*/
typedef struct _BRM_CHECK_REQ
{
	HEAD				HeadOfReq;
	BYTE				byReserved;
	BYTE				byszBCDYear[2];
	BYTE				byBCDMonth;
	BYTE				byBCDDay;
	BYTE				byBCDHour;
	BYTE				byBCDMinute;
	BYTE				byBCDSecond;
	BYTE				byTemperature;			//可以设置任何值
	BYTE				byHumidity;				//可以设置任何值
}BRM_CHECK_REQ,*LPBRM_CHECK_REQ;

/*设备检查应答*/
typedef struct _BRM_CHECK_RESP
{
	HEAD				HeadOfResp;
	PUBRESP				PubResp;
	SAFEINFO			SafeInfo;
	LEFTMOVEINFO		LeftMoveInfo;
	VERIFYDENOMINFO		VerifyDenomInfo;
}BRM_CHECK_RESP,*LPBRM_CHECK_RESP;


/*计数读取请求*/
typedef struct _BRM_COUNTREAD_REQ
{
	HEAD				HeadOfReq;
}BRM_COUNTREAD_REQ,*LPBRM_COUNTREAD_REQ;

/*计数读取应答*/
typedef struct _BRM_COUNTREAD_RESP
{
	HEAD				HeadOfResp;
	ACTIONCOUNT			ActionCount;
}BRM_COUNTREAD_RESP,*LPBRM_COUNTREAD_RESP;

/*计数清除请求*/
typedef struct _BRM_COUNTCLEAR_REQ
{
	HEAD				HeadOfReq;
	BYTE				byClearFlag;
}BRM_COUNTCLEAR_REQ,*LPBRM_COUNTCLEAR_REQ;

/*计数清除应答*/
typedef struct _BRM_COUNTCLEAR_RESP
{
	HEAD				HeadOfResp;
	ACTIONCOUNT			ActionCount;
}BRM_COUNTCLEAR_RESP,*LPBRM_COUNTCLEAR_RESP;

/*DownLoad UpLoad不参与，未在头文件中写出，SP中不使用*/

/*内存读取请求*/
typedef struct _BRM_MEMREAD_REQ
{
	HEAD				HeadOfReq;
}BRM_MEMREAD_REQ,*LPBRM_MEMREAD_REQ;

/*内存读取应答-不完全对应，内存数据没有在结构中体现-不使用*/
typedef struct _BRM_MEMREAD_RESP
{
	HEAD				HeadOfResp;
}BRM_MEMREAD_RESP,*LPBRM_MEMREAD_RESP;


/*记录读取请求-不完全对应，不使用*/
typedef struct _BRM_RECORDREAD_REQ
{
	HEAD				HeadOfReq;
}BRM_RECORDREAD_REQ,*LPBRM_RECORDREAD_REQ;

/*记录读取应答-不完全对应，不使用*/
typedef struct _BRM_RECORDREAD_RESP
{
	HEAD				HeadOfResp;
}BRM_RECORDREAD_RESP,*LPBRM_RECORDREAD_RESP;


typedef struct _UNITINFO84H
{
	BYTE				byShutterStatus;
	BYTE				byDisStatus;
	BYTE				byCleaningStatus;
	BYTE				byCountStatus;
	BYTE				byszReserved[3];
	BYTE				byAutoClearStatus;
	WORD				wAutoClearEscrowCount;
	BYTE				byErrCtrlInfo;
	BYTE				byMechaInitPos;
	BYTE				byDepRJCountCheckMode;
	BYTE				byArt6NoticeMode;
	BYTE				byszReserved1[0x2E - 0x1D];
	DENOMINFO			DenomInfo;
	BYTE				byszReserved2[0x4F - 0x3F];
	VERIFYDENOMINFO		VerifyDenomInfo;
}UNITINFO84H;

typedef struct _BRMINFO
{
	BYTE				byszBarCode[6];
	BYTE				byszMechaRevision[2];
	BYTE				byszBoardRevision[2];		//基板Revision
	BYTE				byszBCDYear[2];
	BYTE				byBCDMonth;
	BYTE				byBCDDay;
	BYTE				byszReserved[2];

	BYTE				byszLowFrameBarCode[6];	
	BYTE				byszLowFrameMechaRevision[2];
	BYTE				byszLowFrameBoardRevision[2];
	BYTE				byszLowFrameBCDYear[2];
	BYTE				byLowFrameBCDMonth;
	BYTE				byLowFrameBCDDay;
	BYTE				byszReserved1[2];

	BYTE				byszShutterBarCode[6];		//钞口条形码
	BYTE				byszShutterMechaRevision[2];
	BYTE				byszReserved2[2];
	BYTE				byszShutterBCDYear[2];
	BYTE				byShutterBCDMonth;
	BYTE				byShutterBCDDay;
	BYTE				byszReserved3[2];

	BYTE				byszEscrowBarCode[6];		//暂存条形码
	BYTE				byszEscrowMechaRevision[2];	
	BYTE				byszReserved4[2];
	BYTE				byszEscrowBCDYear[2];
	BYTE				byEscrowBCDMonth;
	BYTE				byEscrowBCDDay;
	BYTE				byszReserved5[2];

	BYTE				byszCasABarCode[6];			//
	BYTE				byszCasAMechaRevision[2];	
	BYTE				byszCasABoardRevision[2];
	BYTE				byszCasABCDYear[2];
	BYTE				byCasABCDMonth;
	BYTE				byCasABCDDay;
	BYTE				byszReserved6[2];

	BYTE				byszCasBBarCode[6];			//
	BYTE				byszCasBMechaRevision[2];	
	BYTE				byszCasBBoardRevision[2];
	BYTE				byszCasBBCDYear[2];
	BYTE				byCasBBCDMonth;
	BYTE				byCasBBCDDay;
	BYTE				byszReserved7[2];

	BYTE				byszCasCBarCode[6];			//
	BYTE				byszCasCMechaRevision[2];	
	BYTE				byszCasCBoardRevision[2];
	BYTE				byszCasCBCDYear[2];
	BYTE				byCasCBCDMonth;
	BYTE				byCasCBCDDay;
	BYTE				byszReserved8[2];

	BYTE				byszCasDBarCode[6];			//
	BYTE				byszCasDMechaRevision[2];	
	BYTE				byszCasDBoardRevision[2];
	BYTE				byszCasDBCDYear[2];
	BYTE				byCasDBCDMonth;
	BYTE				byCasDBCDDay;
	BYTE				byszReserved9[2];

	BYTE				byszCasEBarCode[6];			//
	BYTE				byszCasEMechaRevision[2];	
	BYTE				byszCasEBoardRevision[2];
	BYTE				byszCasEBCDYear[2];
	BYTE				byCasEBCDMonth;
	BYTE				byCasEBCDDay;
	BYTE				byszReserved10[2];
	
	BYTE				byszTranMBarCode[6];
	BYTE				byszTranMMechaRevision[2];
	BYTE				byszReserved11[2];
	BYTE				byszTranMBCDYear[2];
	BYTE				byTranMBCDMonth;
	BYTE				byTranMBCDDay;
	BYTE				byszReserved12[2];
	
	BYTE				byszCasFBarCode[6];
	BYTE				byszCasFMechaRevision[2];
	BYTE				byszReserved13[2];
	BYTE				byszCasFBCDYear[2];
	BYTE				byCasFBCDMonth;
	BYTE				byCasFBCDDay;
	BYTE				byszReserved14[2];

	BYTE				byszCasRBarCode[6];
	BYTE				byszCasRMechaRevision[2];
	BYTE				byszReserved15[2];
	BYTE				byszCasRBCDYear[2];
	BYTE				byCasRBCDMonth;
	BYTE				byCasRBCDDay;
	BYTE				byszReserved16[2];

	BYTE				byszReserved17[16];
}BRMINFO;

typedef struct _BRMINFO2
{
	BYTE				byszUpperSubUnitIDInfo[4];
	BYTE				byszReserved[12];
	BYTE				byszLowerSubUnitIDInfo[4];
	BYTE				byszReserved1[12];
	BYTE				byszShutterSubUnitIDInfo[4];
	BYTE				byszReserved2[12];
	BYTE				byszEscrowSubUnitIDInfo[4];
	BYTE				byszReserved3[12];
	BYTE				byszCasASubUnitIDInfo[4];
	BYTE				byszReserved4[12];
	BYTE				byszCasBSubUnitIDInfo[4];
	BYTE				byszReserved5[12];
	BYTE				byszCasCSubUnitIDInfo[4];
	BYTE				byszReserved6[12];
	BYTE				byszCasDSubUnitIDInfo[4];
	BYTE				byszReserved7[12];
	BYTE				byszCasESubUnitIDInfo[4];
	BYTE				byszReserved8[12];
	BYTE				byszReserved9[112];
}BRMINFO2;

typedef struct _FPGAINFO
{
	BYTE				byszVersion[2];
	BYTE				byszReserved[2];
	BYTE				byszSensorCPU1Ver[2];
	BYTE				byszSensorCPU2Ver[2];
	BYTE				byszBLKRAM1Ver[2];
	BYTE				byszBLKRAM2Ver[2];
	BYTE				byszReserved1[4];
}FPGAINFO;

typedef struct _BV
{
	BYTE				byszIPLROMFileNO[4];
	BYTE				byszIPLROMVer[2];
	BYTE				byszBVBarCode[6];
	BYTE				byszBVMechaRevision[2];
	BYTE				byszBCDYear[2];
	BYTE				byBCDMonth;
	BYTE				byBCDDay;
	BYTE				byReserved[14];
}BV;


typedef struct _UNITINFO100H 
{
	BRMINFO				BrmInfo;
	FPGAINFO			Fpga1;
	FPGAINFO			Fpga2;
	FPGAINFO			Fpga3;
	BYTE				byszReserved[16];
	BYTE				byszReserved1[16];
	BV					Bv;
	BRMINFO2			BrmInfo2;
}UNITINFO100H;

typedef struct _IPL
{
	BYTE				byszIPL_B[2];
	BYTE				byType;
	BYTE				byFile;
	BYTE				byCountry;
	BYTE				byRelease;
	BYTE				byGroupNO;
	BYTE				byROMNO;
	BYTE				byszIPL_A[2];
	BYTE				byszReserved[2];
	WORD				wDown_UpLoad;
	BYTE				byszReserved1[2];
}IPL;

typedef struct _MAIN
{
	BYTE				byszMain[2];
	BYTE				byType;
	BYTE				byFile;
	BYTE				byCountry;
	BYTE				byRelease;
	BYTE				byGroupNO;
	BYTE				byROMNO;
	BYTE				byszReserved[4];
	WORD				wDown_UpLoad;
	WORD				wLoadInfo;
}MAIN;

typedef struct _REF
{
	BYTE				byszVer[2];
	BYTE				byType;
	BYTE				byFile;
	BYTE				byCountry;
	BYTE				byRelease;
	BYTE				byGroupNO;
	BYTE				byROMNO;
	BYTE				byVerifyID1;
	BYTE				byVerifyID2;
	BYTE				byVerifyID3;
	BYTE				byVerifyID4;
	WORD				wDown_UpLoad;
	BYTE				byszReserved1[2];
}FPGA,REC;

typedef struct _MACHPARAM
{
	BYTE				byszParam1[2];
	BYTE				byszParam2[2];
	BYTE				byszParam3[2];
	BYTE				byszParam4[2];
	BYTE				byszParam5[2];
	BYTE				byszParam6[2];
	BYTE				byszParam7[2];
	BYTE				byszParam8[2];
	BYTE				byszParam9[2];
	BYTE				byszParam10[2];
	BYTE				byszParam11[2];
	BYTE				byszParam12[2];
	BYTE				byszParam13[2];
	BYTE				byszParam14[2];
	BYTE				byszParam15[2];
	BYTE				byszParam16[2];
}MACHPARAM;

typedef struct _VERSIONINFO
{
	IPL					Ipl;
	MAIN				Main;
	FPGA				Fpga;
	REC					Rec1;
	REC					Rec2;
	REC					Rec3;
	REC					Rec4;
	BYTE				byszReserved[112];
	MACHPARAM			MachParam;
}VERSIONINFO;

/*SG载入请求*/
typedef struct _BRM_LOADSG_REQ
{
	HEAD				HeadOfReq;
	UNITINFO84H			UnitInfo84h;	
}BRM_LOADSG_REQ,*LPBRM_LOADSG_REQ;

/*SG载入应答*/
typedef struct _BRM_LOADSG_RESP
{
	HEAD				HeadOfResp;
	VERSIONINFO			VersionInfo;
	UNITINFO100H		UnitInfo100h;
}BRM_LOADSG_RESP,*LPBRM_LOADSG_RESP;

/*验钞DownLoad不参与，未在头文件中写出，SP中不使用*/

/*数据读取请求*/
typedef struct _BRM_DATAREAD_REQ
{
	HEAD				HeadOfReq;
	BYTE				byDataType;			//0x01：设定data 10：钞箱关闭信息 0x20:cas加钞张数信息
	BYTE				byInfoType;			//
}BRM_DATAREAD_REQ,BRM_GETDATASET_REQ,BRM_GETCASCLOSEINFO_REQ,BRM_GETCASCONF_REQ,*LPBRM_DATAREAD_REQ,*LPBRM_GETDATASET_REQ,*LPBRM_GETCASCLOSEINFO_REQ,*LPBRM_GETCASCONF_REQ;;

/*数据读取应答-不完全对应-不使用*/
typedef struct _BRM_DATAREAD_RESP
{
	HEAD				HeadOfResp;
}BRM_DATAREAD_RESP,*LPBRM_DATAREAD_RESP;

/*获取数据设定应答*/
typedef struct _BRM_GETDATASET_RESP
{
	HEAD				HeadOfResp;
	BYTE				byReserved;
	USERLOGININFO		UserLoginInfo;
}BRM_GETDATASET_RESP,*LPBRM_GETDATASET_RESP;

/*获取钞箱关闭信息*/
typedef struct _BRM_GETCASCLOSEINFO_RESP
{
	HEAD				HeadOfResp;
	BYTE				byReserved;
	DWORD				dwCasCloseInfo;
}BRM_GETCASCLOSEINFO_RESP,*LPBRM_GETCASCLOSEINFO_RESP;

/*钞箱数据*/
typedef struct _CASDATA
{
	CASSETTEINFO		CasAInfo;
	WORD				wCasACount;
	BYTE				byszReserved1[2];
	CASSETTEINFO		CasBInfo;
	WORD				wCasBCount;
	BYTE				byszReserved2[2];
	CASSETTEINFO		CasCInfo;
	WORD				wCasCCount;
	BYTE				byszReserved3[2];
	CASSETTEINFO		CasDInfo;
	WORD				wCasDCount;
	BYTE				byszReserved4[2];
	CASSETTEINFO		CasEInfo;
	WORD				wCasECount;
	BYTE				byszReserved5[2];
}CASDATA,*LPCASDATA;

/*获取钞箱配置应答*/
typedef struct _BRM_GETCASCONF_RESP
{
	HEAD				HeadOfResp;
	BYTE				byReserved;
	BYTE				byszReserved[3];
	CASDATA				CasData;
}BRM_GETCASCONF_RESP,*LPBRM_GETCASCONF_RESP;

/*数据写入请求-不完全对应-不使用*/
typedef struct _BRM_DATAWRITE_REQ
{
	HEAD				HeadOfReq;
	BYTE				byDataType;			//0X01：设定data 0x10：钞箱关闭信息 0x20：cas加钞张数信息 0x21：追加手补充张数 0x22：取出手回收张数
}BRM_DATAWRITE_REQ,*LPBRM_DATAWRITE_REQ;


/*数据写入应答-不完全对应-不使用*/
typedef struct _BRM_DATAWRITE_RESP
{
	HEAD				HeadOfResp;
}BRM_DATAWRITE_RESP,*LPBRM_DATAWRITE_RESP;

/*设置数据设定请求*/
typedef struct _BRM_SETDATASET_REQ
{
	HEAD				HeadOfReq;
	BYTE				byDataType;
	USERLOGININFO		UserLoginInfo;
}BRM_SETDATASET_REQ,*LPBRM_SETDATASET_REQ;

/*设置数据设定应答*/
typedef struct _BRM_SETDATASET_RESP
{
	HEAD				HeadOfResp;
	BYTE				byReserved;
	USERLOGININFO		UserLoginInfo;
}BRM_SETDATASET_RESP,*LPBRM_SETDATASET_RESP;

/*设置钞箱关闭请求*/
typedef struct _BRM_SETCASCLOSEINFO_REQ
{
	HEAD				HeadOfReq;
	BYTE				byDataType;
	DWORD				dwCasCloseInfo;
}BRM_SETCASCLOSEINFO_REQ,*LPBRM_SETCAACLOSEINFO_REQ;

/*设置钞箱关闭应答*/
typedef	struct _BRM_SETCASCLOSEINFO_RESP
{
	HEAD				HeadOfResp;
	BYTE				byReserved;
	DWORD				dwCasCloseInfo;
}BRM_SETCASCLOSEINFO_RESP,*LPBRM_SETCASCLOSEINFO_RESP;

/*设置钞箱配置请求*/
typedef struct _BRM_SETCASCONF_REQ
{
	HEAD				HeadOfReq;
	BYTE				byDataType;			//0x20：cas加钞张数信息 0x21：追加手补充张数 0x22：取出手回收张数。 一般使用0x20
	BYTE				bySetCasCountType;	//加钞类型 b0-CasA加钞 b1-CasB加钞 b2-CasC加钞 b3-CasD加钞 b4-CasE加钞
	BYTE				byszReserved[2];
	CASDATA				CasData;
}BRM_SETCASCONF_REQ,*LPBRM_SETCASCONF_REQ;

/*设置钞箱配置应答*/
typedef struct _BRM_SETCASCONF_RESP
{
	HEAD				HeadOfResp;
	BYTE				byReserved;   
	BYTE				bySetCasCountType;	//加钞类型 b0-CasA加钞 b1-CasB加钞 b2-CasC加钞 b3-CasD加钞 b4-CasE加钞
	BYTE				bySetCasCountResult;//加钞结果 b0-CasA加钞有更新 b1-CasB加钞有更新 b2-CasC加钞有更新 b3-CasD加钞有更新 b4-CasE加钞有更新
	BYTE				byCasIDStatus;		//CASID状态。b0-CasA面值信息不一致，b1-CasB面值不一致，b2-CasC面值不一致，b3-CasD面值不一致，b4-CasE面值不一致
	CASDATA				CasData;
}BRM_SETCASCONF_RESP,*LPBRM_SETCASCONF_RESP;
/**********************ATTENTION**ATTENTION***************************/

/*attention-不完全对应-使用-attention详细信息需要另外的空间*/
typedef struct _BRM_ATTENTION
{
	HEAD				HeadOfAtt;
	BYTE				byAttType;
}BRM_ATTENTION,*LPBRM_ATTENTION;

/*power on attention*/
typedef struct _BRM_POWERON_ATT
{
	BRM_ATTENTION		Att;
	BYTE				byAttDetail1;
	WORD				wAttDetail2;	
}BRM_POWERON_ATT,*LPBRM_POWERON_ATT;

/*record collect attention-不完全对应-记录信息需要另外的空间*/
typedef struct _BRM_RECORDCOLLECT_ATT
{
	BRM_ATTENTION		Att;
	BYTE				byEquip;
	BYTE				byRecordType;
	BYTE				byRecordDetail;
}BRM_RECORDCOLLECT_ATT,*LPBRM_RECORDCOLLECT_ATT;

/*safe attention*/
typedef struct _BRM_SAFE_ATT
{
	BRM_ATTENTION		Att;
	SAFEINFO			SafeInfo;
}BRM_SAFE_ATT,*LPBRM_SAFE_ATT;

/*status change attention*/
typedef struct _BRM_STATUSCHANGE_ATT
{
	BRM_ATTENTION		Att;
	BRMSTATUS			BRMStatus;
}BRM_STATUSCHANGE_ATT,*LPBRM_STATUSCHANGE_ATT;

/*left move info attention*/
typedef struct _BRM_LEFTMOVEINFO_ATT
{	
	BRM_ATTENTION		Att;
	LEFTMOVEINFO		LeftMoveInfo;
}BRM_LEFTMOVEINFO_ATT,*LPBRM_LEFTMOVEINFO_ATT;

/*err illustration attention*/
typedef struct _BRM_ERRILLUSTRATION_ATT
{
	BRM_ATTENTION		Att;
	ERRILLUSTRATION		ErrIllustration;
}BRM_ERRILLUSTRATION_ATT,*LPBRM_ERRILLUSTRATION_ATT;

/*err check attention*/
typedef struct _BRM_ERRCHECK_ATT
{
	BRM_ATTENTION		Att;
	PUBRESP				PubResp;
}BRM_ERRCHECK_ATT,*LPBRM_ERRCHECK_ATT;

/*auto reset attention*/
typedef struct _BRM_AUTORESET_ATT
{
	BRM_ATTENTION		Att;
	BYTE				byAttDetail;
	PUBRESP				PubResp;
}BRM_AUTORESET_ATT,*LPBRM_AUTORESET_ATT;

/*Art6 纸币跟踪信息 attention*/
typedef struct _BRM_ART6_ATT
{
	BRM_ATTENTION		Att;
	BYTE				byReserved;
	ART6COUNT			Art6Count;
}BRM_ATR6_ATT,*LPBRM_ART6_ATT;

/*纸币详细信息。包含位置等*/
typedef struct _BRM_SNDETAILS_ATT
{
	BRM_ATTENTION		Att;
	BYTE				byAttDetail;
}BRM_SNDETAILS_ATT,*LPBRM_SNDETAILS_ATT;
/************************************Device*APIs*****************************************/
bool	brm_CMD_open();

bool	brm_CMD_close();

bool	brm_CMD_Send(LPVOID lpSndDataBuff,DWORD dwSndDataSize);		

bool	brm_CMD_Recv(LPVOID lpRcvDataBuff,LPDWORD lpdwRcvDataSize, DWORD* pdwresult);		

bool	brm_CMD_Reset();
													
bool	brm_CMD_getsysinfo(char* sysinfo);

/***************functions*****************/

/***************start*********************/

WORD	brm_CMD_Freeze();

WORD	brm_RESP_Freeze(BYTE* RecvDataBuff);

WORD	brm_CMD_LoadSG(IN DWORD dwTimeOut, OUT LPBRM_LOADSG_RESP lpbrm_loadsg_resp);

WORD	brm_RESP_LoadSG(BYTE* RecvDataBuff);

/***************deposit*******************/

WORD	brm_CMD_CIM_ModeSet(IN DWORD dwTimeOut, OUT LPBRM_CIMMODESET_RESP lpbrm_cimmodeset_resp);

WORD	brm_RESP_CIM_ModeSet(BYTE* RecvDataBuff);

WORD	brm_CMD_CIM_Verify(IN BYTE byRetryFlag, IN WORD wProcDenom, IN ULONG ulRestrictCount, IN ULONG ulRestrictAmount, IN DWORD dwTimeOut, OUT LPBRM_CIMVERIFY_RESP lpbrm_cimverify_resp, IN BYTE byAutoResetMode);

WORD	brm_RESP_CIM_Verify(BYTE* RecvDataBuff);

WORD	brm_CMD_CIM_Store(IN BYTE byCategoryCanRecycle, IN BYTE byNonRecycleBillPlace, IN BYTE byNonRecycleBillPlaceOf4a4b, IN WORD* wszDenomCount, IN DWORD dwTimeOut, OUT LPBRM_CIMSTORE_RESP lpbrm_cimstore_resp);

WORD	brm_RESP_CIM_Store(BYTE* RecvDataBuff);

WORD	brm_CMD_CIM_Cancel(IN BYTE byCategoryRollBackInfo, IN BYTE byNonRollBackBillPlace, IN DWORD dwTimeOut, OUT LPBRM_CIMCANCEL_RESP lpbrm_cimcancel_resp);

WORD	brm_RESP_CIM_Cancel(BYTE* RecvDataBuff);

/***************dispense******************/

WORD	brm_CMD_CDM_ModeSet(IN DWORD dwTimeOut, OUT LPBRM_CDMMODESET_RESP lpbrm_cdmmodeset_resp);

WORD	brm_RESP_CDM_ModeSet(BYTE* RecvDataBuff);

WORD	brm_CMD_CDM_Dispense(IN BYTE byDisType, IN BYTE byCategoryCanDispense, IN BYTE byDenom1_CasA_Count, IN BYTE byDenom2_CasB_Count, IN BYTE byDenom3_CasC_Count, IN BYTE byDenom4_CasD_Count, IN BYTE byDenom5_CasE_Count, IN DWORD dwTimeOut, OUT LPBRM_CDMDISPENSE_RESP lpbrm_cdmdispense_resp);

WORD	brm_RESP_CDM_Dispense(BYTE* RecvDataBuff);

/***************common********************/

WORD	brm_CMD_ModeReset(IN DWORD dwTimeOut, OUT LPBRM_MODERESET_RESP lpbrm_modereset_resp);

WORD	brm_RESP_ModeReset(BYTE* RecvDataBuff);

WORD	brm_CMD_Retract(IN BYTE bySpecifSpecialRetract, IN BYTE byCategoryCanRecycle, IN BYTE byNonRecycleBillPlace, IN DWORD dwTimeOut, OUT LPBRM_RETRACT_RESP lpbrm_retract_resp);

WORD	brm_RESP_Retract(BYTE* RecvDataBuff);

WORD	brm_CMD_MoveBill(IN DWORD dwTimeOut, OUT LPBRM_MOVEBILL_RESP lpbrm_movebill_resp);

WORD	brm_RESP_MoveBill(BYTE* RecvDataBuff);

WORD	brm_CMD_Cleaning(IN DWORD dwTimeOut, OUT LPBRM_CLEANING_RESP lpbrm_cleaning_resp);

WORD	brm_RESP_Cleaning(BYTE* RecvDataBuff);

WORD	brm_CMD_PathCheck(IN DWORD dwTimeOut, OUT LPBRM_PATHCHECK_RESP lpbrm_pathcheck_resp);

WORD	brm_RESP_PathCheck(BYTE* RecvDataBuff);

WORD	brm_CMD_Init(IN BYTE byInitFlag, IN DWORD dwTimeOut, OUT LPBRM_INIT_RESP lpbrm_init_resp);

WORD	brm_RESP_Init(BYTE* RecvDataBuff);

WORD	brm_CMD_ShutterCtrl(BYTE byShutterCtrlFlag, BYTE byTradeType, IN DWORD dwTimeOut, OUT LPBRM_SHUTTERCTRL_RESP lpbrm_shutterctrl_resp);

WORD	brm_RESP_ShutterCtrl(BYTE* RecvDataBuff);

WORD	brm_CMD_ShutterCheck(IN BYTE byTradeType, IN DWORD dwTimeOut, OUT LPBRM_SHUTTERCHECK_RESP lpbrm_shuttercheck_resp);

WORD	brm_RESP_ShutterCheck(BYTE* RecvDataBuff);

/***************getinfo******************/

WORD	brm_CMD_StatusCheck(IN DWORD dwTimeOut, OUT LPBRM_CHECK_RESP lpbrm_check_resp);

WORD	brm_RESP_StatusCheck(BYTE* RecvDataBuff);

WORD	brm_CMD_CountRead(IN DWORD dwTimeOut, OUT LPBRM_COUNTREAD_RESP lpbrm_countread_resp);

WORD	brm_RESP_CountRead(BYTE* RecvDataBuff);

WORD	brm_CMD_CountClear(IN DWORD dwTimeOut, IN BYTE byClearFlag, OUT LPBRM_COUNTCLEAR_RESP lpbrm_countclear_resp);

WORD	brm_RESP_CountClear(BYTE* RecvDataBuff);

WORD	brm_CMD_MEMRead(IN DWORD dwTimeOut, OUT LPBRM_MEMREAD_RESP lpbrm_memread_resp);

WORD	brm_RESP_MEMRead(BYTE* RecvDataBuff);

WORD	brm_CMD_LogRead(IN DWORD dwTimeOut, OUT LPBRM_RECORDREAD_RESP lpbrm_recordread_resp);

WORD	brm_RESP_LogRead(BYTE* RecvDataBuff);

WORD	brm_CMD_GetDataSet(IN DWORD dwTimeOut, OUT LPBRM_GETDATASET_RESP lpbrm_getdataset_resp);

WORD	brm_RESP_GetDataSet(BYTE* RecvDataBuff);

WORD	brm_CMD_GetCasCloseInfo(IN DWORD dwTimeOut, OUT LPBRM_GETCASCLOSEINFO_RESP lpbrm_getcascloseinfo_resp);

WORD	brm_RESP_GetCasCloseInfo(BYTE* RecvDataBuff);

WORD	brm_CMD_GetCasConf(IN DWORD dwTimeOut, OUT LPBRM_GETCASCONF_RESP lpbrm_getcasconf_resp);

WORD	brm_RESP_GetCasConf(BYTE* RecvDataBuff);

WORD	brm_CMD_SetDataSet(IN DWORD dwTimeOut, OUT LPBRM_SETDATASET_RESP lpbrm_setdataset_resp);

WORD	brm_RESP_SetDataSet(BYTE* RecvDataBuff);

WORD	brm_CMD_SetCasCloseInfo(IN DWORD dwTimeOut, IN DWORD dwCasCloseInfo, IN BYTE byDataType, OUT LPBRM_SETCASCLOSEINFO_RESP lpbrm_setcascloseinfo_resp);

WORD	brm_RESP_SetCasCloseInfo(BYTE* RecvDataBuff);

WORD	brm_CMD_SetCasConf(IN DWORD dwTimeOut, IN OUT LPBRM_SETCASCONF_RESP lpbrm_setcasconf_resp);

WORD	brm_RESP_SetCasConf(BYTE* RecvDataBuff);

/*************attentions**************/
WORD	brm_ATT_PowerOn(BYTE* RecvDataBuff);

WORD	brm_ATT_RecordCollect(BYTE* RecvDataBuff);

WORD	brm_ATT_Safe(BYTE* RecvDataBuff);

WORD	brm_ATT_StatusChange(BYTE* RecvDataBuff);

WORD	brm_ATT_LeftMoveInfo(BYTE* RecvDataBuff);

WORD	brm_ATT_ErrIllustration(BYTE* RecvDataBuff);

WORD	brm_ATT_ErrCheck(BYTE* RecvDataBuff);

WORD	brm_ATT_AutoReset(BYTE* RecvDataBuff);
 
WORD	brm_ATT_ATR6(BYTE* RecvDataBuff);
/*************receive thread**********/

void brm_CMD_Recv_Thread(PVOID   pvoid);

void brm_CMD_Thread_Proc(BYTE* RecvDataBuff);

/*************others*****************/
bool	brm_source_init();

void	brm_source_del();

void	LoadErrorCodes();

char*	GetErrorCodeExplain(char *code, char* Explain);

void	LogWrite(BYTE byTraceLevel, LPCSTR szMode, LPBYTE lpData, DWORD dwLen);

void	ProcHead(HEAD Head);

void	ProcBRMStatus(BRMSTATUS BRMStatus);

void	ProcErrIllustration(ERRILLUSTRATION ErrIllustration);

void	ProcActionCounter(ACTIONCOUNT Actioncount);

void	ProcBRMCasBarCode(CASBARCODE CasBarCode);

void	ProcSafeInfo(SAFEINFO SafeInfo);

void	ProcLeftMoveInfo(LEFTMOVEINFO LeftMoveInfo);

void	ProcVerifyDenomInfo(VERIFYDENOMINFO VerifyDenomInfo);

void	ProcVerifySetInfo(VERIFYSETINFO VerifySetInfo);

void	ProcVersionInfo(VERSIONINFO	VersionInfo);

void	ProcUnitInfo100h(UNITINFO100H UnitInfo100h);

void	ProcDataSet(USERLOGININFO UserLoginInfo);

void	ProcCasData(CASDATA CasData);

void	ProcPubResp(PUBRESP	PubResp);

bool	EventCreate();

void	EventDelete();

void	BRMErrorCheck(BYTE* byszerrorcode);

void	BRMErrorSet(bool bInitCmd, BYTE* byszerrorcode);

bool	BRMPubRespModify(LPPUBRESP lppubresp);

#pragma		pack(pop)

#endif  //__brm_command_h