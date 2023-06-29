/*
	����BRMģ���ͨѶ���ݽṹ���Լ�ͨѶ������//
	����
	ATM 			��Automated Teller Machine���ֽ��Զ���ȡ���
	RJ				��ReJect
	BRM				��Bill��Recycle��Module		����ֽ��ѭ����ȡ���
	SP				��Service Provider			�����ϲ�װ��
	USB 			��Universal Serial Bus
	IPL 			��Initial Program Loader
	IPL-A			����ָ��IPL�У�ʵװ��ROM���ϲ����Program��
	IPL-B			����ָ��IPL�У�ʵװ��FLASHMemory�ڿ��ܱ����Program��
	
	Category1����	�����鳮����ֽ���鳮�����һ�֣�ֽ����ָ�����ж��ĳ������ڱ�������ﶨ��Ϊ"������"��
	Category2������	�����鳮����ֽ���鳮�����һ�֣��ٳ���ָ�ѱ��ж��ĳ������ڱ�������ﶨ��Ϊ"�ٳ�"��
	Category3������	�����鳮����ֽ���鳮�����һ�֣���ָ�мٳ��Ŀ����Եĳ������ڱ�������ﶨ��Ϊ"�ɻ�"��
	Category4a����	�����鳮����ֽ���鳮�����һ�֣����ж�Ϊֽ�ң�ָ�ɽ���ֽ��ѭ���ĳ���	�ڱ�������ﶨ��Ϊ"��Recycle��"��
	Category4b����	�����鳮����ֽ���鳮�����һ�֣����ж�Ϊֽ�ң�ָ���ɽ���ֽ��ѭ���ĳ����ڱ�������ﶨ��Ϊ"����Recycle��"��

*/

#ifndef	__brm_command_h
#define __brm_command_h


#pragma		pack(push, 1)

//��������
#define		CASSETTE_A2E_CAPA			(2750)
#define		CASSETTE_R_CAPA				(600)
#define		CASSETTE_F_CAPA				(600)

//��������
#define		CASSETTE_A_NAME				"CassetteA"
#define		CASSETTE_B_NAME				"CassetteB"
#define		CASSETTE_C_NAME				"CassetteC"
#define		CASSETTE_D_NAME				"CassetteD"
#define		CASSETTE_E_NAME				"CassetteE"
#define		CASSETTE_R_NAME				"CassetteRT"//"CassetteR"	//�������Ҫ����������ΪCassetteRT
#define		CASSETTE_F_NAME				"CassetteRJ"//"CassetteF"	//�������Ҫ����������ΪCassetteRJ

//����ID
#define		CASSETTE_A_ID				"CAS_A"
#define		CASSETTE_B_ID				"CAS_B"
#define		CASSETTE_C_ID				"CAS_C"
#define		CASSETTE_D_ID				"CAS_D"
#define		CASSETTE_E_ID				"CAS_E"
#define		CASSETTE_R_ID				"RTCAS"		//"CAS_R"		//�������Ҫ����������ΪRTCAS
#define		CASSETTE_F_ID				"RJCAS"		//"CAS_F"		//�������Ҫ����������ΪRJCAS

//����ر�
#define		CASSETTE_A_CDM_CLOSE		0x00010000	//A�������ر�
#define		CASSETTE_B_CDM_CLOSE		0x00020000	//B�������ر�
#define		CASSETTE_C_CDM_CLOSE		0x00040000	//C�������ر�
#define		CASSETTE_D_CDM_CLOSE		0x00080000	//D�������ر�
#define		CASSETTE_E_CDM_CLOSE		0x00100000	//E�������ر�

#define		CASSETTE_A_CIM_CLOSE		0x00200000	//A�����ռ��ر�
#define		CASSETTE_B_CIM_CLOSE		0x00400000	//B�����ռ��ر�
#define		CASSETTE_C_CIM_CLOSE		0x00800000	//C�����ռ��ر�
#define		CASSETTE_D_CIM_CLOSE		0x01000000	//D�����ռ��ر�
#define		CASSETTE_E_CIM_CLOSE		0x02000000	//E�����ռ��ر�

//����鳮�������
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

//��Ʊ����λ��
#define		BILL_TRANS_PLACE_CAS_IN		0x02		//����������䣬��ֵָ��
#define		BILL_TRANS_PLACE_CAS_MIX	0x04		//���������䣬��ֵ��ָ��
#define		BILL_TRANS_PLACE_CAS_D		0x0B		//�����D����
#define		BILL_TRANS_PLACE_CAS_E		0x0C		//�����E����
#define		BILL_TRANS_PLACE_CAS_R		0x0D		//�����R����
#define		BILL_TRANS_PLACE_CAS_F		0x0E		//�����F����

/*brm������¼��ȴ���ʱʱ��*/
#define		EVENT_TIMEOUT				180000				//180s

/*��Ʊλ��*/
#define		BILL_POS_SHUTTER			0x0001				//�����г�Ʊ
#define		BILL_POS_ESCROW				0x0004				//�ݴ��г�Ʊ
#define		BILL_POS_TRANSPORT			0x0010				//ͨ���г�Ʊ

/*���ſ���*/
#define		SHUTTER_CTRL_FCLOSE			0x01				//ǿ�ƹ��ڳ���
#define		SHUTTER_CTRL_CLOSE			0x02				//���ڳ���
#define		SHUTTER_CTRL_OPEN			0x80				//���ڳ���

/*���շ���λ��*/
#define		RETRACT_FROM_SHUTTERESCROW	0x00				//�����ݴ���գ������ⲿ����
#define		RETRACT_FROM_ESCROW			0x80				//�ݴ���գ������ڲ�ȡ��ϳ�����

/*�鳮����ָʾ*/
#define		VERIFY_RETRY				0x81				//����鳮����
#define		VERIFY_NOT_RETRY			0x00				//����鳮������

/*ȡ��ʱ�Ľ�������*/
#define		TAKE_FOR_DISPENSE			0x01				//ȡ��ʱ��ȡ����
#define		TAKE_FOR_DEPOSIT			0x02				//���ܳ����˳�ʱ��ȡ����
	
/*ȡ��������ͣ� ָ�������������������ָ��������������*/
#define		DISPENSE_TYPE_DENOM			0x00				//ָ�������������
#define		DISPENSE_TYPE_CASSETTE		0x01				//ָ��������������
	
/*�豸��ʼ����λ�����õĸ�λģʽ��ͨ����ά����Զ�̣�ǿ��4��*/
#define		INIT_TYPE_NORMAL			0x01				//ͨ����ʼ��
#define		INIT_TYPE_MAINTAN			0x02				//ά����ʼ��
#define		INIT_TYPE_REMOTE			0x03				//Զ�̳�ʼ����OKI���鷽ʽ
#define		INIT_TYPE_FORCE				0x04				//ǿ�Ƴ�ʼ��

/*�ڳ���led�ƿ���*/
#define		SHUTTER_LED_OPEN			0xC1
#define		SHUTTER_LED_CLOSE			0xC0

/*����������¼�*/
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



/*Cassette��Ϣ*/
typedef struct _CASSETTEINFO
{
	BYTE	byUseClassInfo;					//hi-half��1-ȡ�� 2-�����ָ����3-ѭ�� 4-����ָ����8-������� F-����  lo-half��0-����ֽ��group��Ч 1-����ֽ��group��Ч	
	BYTE	byDIPSwitchInfo;				//����CAS_R,CAS_F,����Ϣ��Ч����byUseClassInfo��lo-half��Чʱ��ʹ�ø���Ϣ��0-��ʹ�� 1-8��Ӧgroup1-8��9-�������ר�ã�10-���ר�ã������ָ����11-14��Ӧ���ר��2-5.��2��Ӧgroup4, 3��Ӧgroup3������������
	BYTE	byszProcBillGroupNO[2];			//ֽ��group��Ӧ 1-16��Ϊ0��ʾ��ָ��ֽ��group
}CASSETTEINFO, *LPCASSETTEINFO;

/*Cassette������Ϣ*/
typedef struct _CASSETTECLASSINFO
{
	CASSETTEINFO	CassetteAInfo;			//Ĭ������ 0x10,0x00,0x04,0x00		//ȡ�� ֽ��group4
	CASSETTEINFO	CassetteBInfo;			//Ĭ������ 0x10,0x00,0x04,0x00		//ȡ�� ֽ��group4
	CASSETTEINFO	CassetteCInfo;			//Ĭ������ 0x10,0x00,0x03,0x00		//ȡ�� ֽ��group3
	CASSETTEINFO	CassetteDInfo;			//Ĭ������ 0x20,0x00,0x04,0x00		//��� ֽ��group4
	CASSETTEINFO	CassetteEInfo;			//Ĭ������ 0x40,0x00,0x00,0x00		//��� ���ָ����	
	CASSETTEINFO	CassetteRInfo;			//Ĭ������ 0xF0,0x00,0x00,0x00		//����ָ��
	CASSETTEINFO	CassetteFInfo;			//Ĭ������ 0xF0,0x00,0x00,0x00		//����ָ��
	BYTE			byszReserved[4];		//Ĭ������ 0x00,0x00,0x00,0x00
}CASSETTECLASSINFO, *LPCASSETTECLASSINFO;

/*�������õĿ�����Ϣ*/
typedef	struct _CTRLINFO
{
	CASSETTECLASSINFO	CassetteClassInfo;
	BYTE				bySensorRevise;						//������������ʽ			0��1~30						Ĭ�ϣ�0x00
	BYTE				byRetryWhenDepRJ;					//���ʱ������RJֽ���ٴμ����Ƿ���е��趨	0~10		Ĭ�ϣ�0x01
	BYTE				byRetryWhenMoveRJ;					//ֽ���ƶ�ʱ������RJֽ���ٴμ����Ƿ���е��趨	0~1		Ĭ�ϣ�0x00
	BYTE				bySaveEnergyTimer;					//ʡ��ʱ��b7=0���� 1���֡�b6~b0=ʱ��ֵ					Ĭ�ϣ�0x85
	BYTE				bySaveEnergyMode;					//ʡ��ģʽ00����ʡ�� 01����BRMʡ�� 02��BRM+BVʡ��		Ĭ�ϣ�0x00
	BYTE				byActionWhenDepRJ;					//���ʱ����RJ��Ķ������00���Ѵ���ͨ��������ʱ�ռ���Escrow�󣬴��䵽��ȡ���ڡ� 01���Ѵ���ͨ��������ʱֹͣ�ڴ���ͨ���Ϻ󣬴��䵽��ȡ���ڡ�Ĭ�ϣ�0x01
	BYTE				byLimitTimesOfDepRJ;				//���RJ�����޶ȴ�����1~200								Ĭ�ϣ�0x14
	BYTE				byLimitCntsOfDepRJ;					//���RJ�������޶ȡ�1~200								Ĭ�ϣ�0x19
	BYTE				bySpeedOfDepSeparateRetry;			//������Retryʱ�ķ����ٶȡ�00:�������루�޼�Ъ���룩01��1���ŷ��루�м�Ъ���룩	Ĭ�ϣ�0x01
	BYTE				byszReserved[0x3F - 0x28];
}CTRLINFO, *LPCTRLINFO;

/*�������õ�������Ϣ*/
typedef	struct _CAPAINFO
{
	BYTE				byCasAFull;							//A����������	0~9  0��50�� 1��100�� 2��150�� 3��200 ��4��250��5��300��6��350��7��400��8��450��9��500					Ĭ�ϣ�0x02
	BYTE				byCasANearEmpty;					//A���佫������	0~9ͬ�� 80~89	80��10��81��20��82��30��83��40��84��50��85��60��86��70��87��80��88��90��89��100			Ĭ�ϣ�0x00
	BYTE				byCasBFull;							//B����������	0~9  0��50�� 1��100�� 2��150�� 3��200 ��4��250��5��300��6��350��7��400��8��450��9��500					Ĭ�ϣ�0x02						
	BYTE				byCasBNearEmpty;					//B���佫������	0~9ͬ�� 80~89	80��10��81��20��82��30��83��40��84��50��85��60��86��70��87��80��88��90��89��100			Ĭ�ϣ�0x00								
	BYTE				byCasCFull;							//C����������	0~9  0��50�� 1��100�� 2��150�� 3��200 ��4��250��5��300��6��350��7��400��8��450��9��500					Ĭ�ϣ�0x02									
	BYTE				byCasCNearEmpty;					//C���佫������	0~9ͬ�� 80~89	80��10��81��20��82��30��83��40��84��50��85��60��86��70��87��80��88��90��89��100			Ĭ�ϣ�0x00					
	BYTE				byCasDFull;							//D����������	0~9  0��50�� 1��100�� 2��150�� 3��200 ��4��250��5��300��6��350��7��400��8��450��9��500					Ĭ�ϣ�0x02					
	BYTE				byCasDNearEmpty;					//D���佫������	0~9ͬ�� 80~89	80��10��81��20��82��30��83��40��84��50��85��60��86��70��87��80��88��90��89��100			Ĭ�ϣ�0x00
	BYTE				byCasEFull;							//E����������	0~9  0��50�� 1��100�� 2��150�� 3��200 ��4��250��5��300��6��350��7��400��8��450��9��500					Ĭ�ϣ�0x02	
	BYTE				byCasENearEmpty;					//E���佫������	0~9ͬ�� 80~89	80��10��81��20��82��30��83��40��84��50��85��60��86��70��87��80��88��90��89��100			Ĭ�ϣ�0x00	
	BYTE				byszReserved[0x4F - 0x49];			//����
	BYTE				byCasRFull;							//R����������	0~b  0��50�� 1��100�� 2��150�� 3��200 ��4��250��5��300��6��350��7��400��8��450��9��500��a��550��b��600	Ĭ�ϣ�0x0b	
	BYTE				byReserved1;						//����
	BYTE				byCasFFull;							//F����������	0~b  0��50�� 1��100�� 2��150�� 3��200 ��4��250��5��300��6��350��7��400��8��450��9��500	a��550��b��600	Ĭ�ϣ�0x0b	
	BYTE				byszReserved2[0x5F - 0x52];			//����
}CAPAINFO, *LPCAPAINFO;

/*�������õ���Ϣ*/
typedef struct _RUNSETINFO
{
	CTRLINFO			CtrlInfo;
	CAPAINFO			CapaInfo;
}RUNSETINFO, *LPRUNSETINFO;

/*�鳮����*/
typedef struct _VERIFYTYPE
{
	BYTE				byVerifyLevel1_CD;					//�鳮ˮƽ1������
	BYTE				byVerifyLevel2_GB;					//�鳮ˮƽ2������
	BYTE				byVerifyLevel3_TP;					//�鳮ˮƽ3����ֽ
	BYTE				byVerifyLevel4_TF;					//�鳮ˮƽ4����α
	BYTE				byVerifyLevel5_ZJ;					//�鳮ˮƽ5���۽�
	BYTE				byVerifyLevel6_KD;					//�鳮ˮƽ6���׶�
	BYTE				byReserved;							//����
	BYTE				byVerifyLevel8_RT;					//�鳮ˮƽ8�������鳮
}VERIFYTYPE,*LPVERIFYTYPE;

/*�鳮���õ���Ϣ*/
typedef struct _VERIFYSETINFO
{
	VERIFYTYPE			VerifyType[0x10];					
	//�鳮���͡��±�0x00-��� 0x01-���գ����� 0x02-���գ��볮�䷽��
	//0x03-���볮�� 0x04-���ȡ�� 0x05-ȡ�� 0x0a-����1����ȡ�ڣ�
	//0x0b-����2���ݴ棩 0x0c-����1�����䣩 0x0d-ֽ���ƶ������� 
	//0x0e-ֽ���ƶ����볮�䷽�� 
	BYTE				byszCurrencyData[16];				//���������ݡ������±�0~15�ֱ�Ϊ����1~����16�õ����ݡ�	
}VERIFYSETINFO, *LPVERIFYSETINFO;

typedef struct _USERLOGININFO
{
	RUNSETINFO			RunSetInfo;
	VERIFYSETINFO		VerifySetInfo;
	BYTE				byszReserved[0xFE - 0xEF];		//����
	BYTE				byHash;							//hash����ֵ
}USERLOGININFO,*LPUSERLOGININFO;

/*����״̬*/
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

/*���䵱ǰ����*/
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

/*��ֵ��Ϣ*/
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

/*BRM״̬*/
typedef	struct	_BRMSTATUS
{
	CASSETTECLASSINFO	CassetteClassInfo;
	CASSTATUS			CasStatus;
	BYTE				byReserved;
	WORD				wCasFuncSet;	//����ر���Ϣ��b0~b15��0-���ر� 1-�رա�  b0-A�����ռ� b1-A������� b2-B�����ռ� b3-B�������ȵȡ���
	BYTE				byszReserved[0x2F - 0x29];
}BRMSTATUS,*LPBRMSTATUS;

/*����λ��ͼ��ʾ����Ϣ*/
typedef	struct _ERRILLUSTRATION
{
	WORD				wDataLen;
	BYTE				byszErrIllustrationFlagInfo[2];		//by[0]:01-5cas brm. 02-3cas brm. by[1]:b0=1 ��casR��b0=0 ��casR��
	CASSETTECLASSINFO	CassetteClassInfo;
	CASCAPA				CasCapa;
	WORD				wReserved;
	DWORD				dwLeftMediaInfo;	//b0-��ȡ���� b1-����1/2sensor b2-�鳮 
											//b3-RejectBladeTrigger������ͨ������Sensor��R Cassette�ռ�ȷ��Sensor  
											//b4 b5-escrow	b6-��ȡ���ռ�ȷ�� b7-CASR b8-�ϲ����� b9-CASF����
											//b10-CASA���� b11-CASB���� b12-CASC���� b13-CASD���� b14-CASE����
											//b16-CASA b17-CASB b18-CASC b19-CASD b20-CASE b21-CASF
	BYTE				byErrPart;
	BYTE				byErrPath;
	CASSTATUS			CasStatus;
	BYTE				byszReserved1[0x46 - 0x40];
	DENOMINFO			DenomInfo;
	BYTE				byszReserved2[0x5F - 0X57];
}ERRILLUSTRATION,*LPERRILLUSTRATION;

/*����denom��BYTE��С*/
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

/*����denom��WORD��С*/
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

/*�Ӽ��������ڷ��룬�ռ�����������*/
typedef struct _SUBCOUNT
{
	INVERSEDENOM		Category4a;
	INVERSEDENOM		Category4b;
	INVERSEDENOM		Category3;
	INVERSEDENOM		Category2;
	WORD				wCountOfUnknownCategory1;
	BYTE				byszReserve[0x8F - 0x81];
}SUBDEPARTCOUNT,SUBCOLLECTCOUNT,ART6COUNT,*LPSUBDEPARTCOUNT,*LPSUBCOLLECTCOUNT,*LPART6COUNT;

/*�Ӽ���������ʣ�ද������*/
typedef struct _SUBLEFTCOUNT
{
	INVERSEDENOM		Category;	
	WORD				wCountOfUnknownCategory;
	BYTE				byszReserved[0x2F - 0x21];
}SUBLEFTCOUNT,*LPSUBLEFTCOUNT;

/*�������*/
typedef struct _DEPARTCOUNT
{
	SUBDEPARTCOUNT		CountOfShutter;			//��ȡ��ڷ�������
	SUBDEPARTCOUNT		CountOfEscrow;			//�ݴ��������
	SUBDEPARTCOUNT		CountOfCasA;
	SUBDEPARTCOUNT		CountOfCasB;
	SUBDEPARTCOUNT		CountOfCasC;
	SUBDEPARTCOUNT		CountOfCasD;
	SUBDEPARTCOUNT		CountOfCasE;
}DEPARTCOUNT,*LPDEPARTCOUNT;


/*�ռ�����*/
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

/*ʣ�����*/
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

/*��������*/
typedef struct _ACTIONCOUNT
{
	DEPARTCOUNT			DepartCount;
	COLLECTCOUNT		CollectCount;
	LEFTCOUNT			LeftCount;
}ACTIONCOUNT,*LPACTIONCOUNT;

/*ֽ�ҳ�����������Ϣ*/
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

/*����ͨ����Ӧ��Ϣ*/
typedef struct _PUBRESP 
{
	DWORD				dwCasCloseInfo;
	WORD				wBillInfo;			//b0~b15,0-�ޣ�1-�� b1(�ͻ�ֽ��ʣ��)��b2(�ͻ�����ʱ)��b4(װ��ֽ��ʣ��)��b5(װ�ÿ���ʱ)��b7(������ֽ��)��b15(ֽ��ģʽ��0-�棬1-ģ��)
	WORD				wLeftMediaStatus;	//b0~b7,0-�ޣ�1-�� b0(��ȡ����) b2(�ݴ�) b7(ͨ��)
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

/*��ȫ��Ϣ*/
typedef struct _SAFEINFO
{
	BYTE				byInterLock;	//b0=1�ϲ���ȫinterlock���䡣b1=1�²���ȫinterlock���䡣
	BYTE				byCasA_EStatus;	//b0~b5 A~E ��missing��
	BYTE				byCasR_CasF_BV_UP_LOWStatus;//b0,b1,b4,b6,b7
	BYTE				byReserved1;
	BYTE				byszReserved[0x0F - 0x03];
}SAFEINFO,*LPSAFEINFO;

/*ʣ���ƶ���Ϣ-������0x30�ֽڻ���0x40�ֽ�*/
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
	BYTE				byCountryInfo;				//����Ϣ
	BYTE				byBillGroupOfDisType;		//ȡ����ֽ��group
	BYTE				byBillGroupOfDepType;		//�����ֽ��group
	BYTE				byDenomInfo;				//�����Ϣ
}SUBVERIFYDENOMINFO;

typedef struct _VERIFYDENOMINFO
{
	BYTE				byDenomNO;
	BYTE				byszReserved[3];
	SUBVERIFYDENOMINFO	SubVerifyDenomInfo[16];		//�±�0-15����ʾ����1-16	
}VERIFYDENOMINFO;

/*����ͨ��ͷ����������������errorcode��errorcodedetail*/
typedef struct _HEAD
{
	BYTE				byszReserved[4];		//����ͷ4�ֽڱ�����
	BYTE				byLU;				//�豸����
	BYTE				byIFCODE;			//cmd-1,resp-2,att-3
	BYTE				byCMD;				//��������
	BYTE				byErrorCode;
	BYTE				byszErrorCodeDetail[2];
	BYTE				byszReserved1[2];
	WORD				wErrStatus;
	BYTE				byszReserved2[0x0D - 0x09];
	WORD				wDataLen;		
}HEAD,*LPHEAD;

/*ȡ������ͷ����ͨ�õ���һ������*/
typedef struct _CDMHEAD
{
	BYTE				byszReserved[4];		//����ͷ4�ֽڱ�����
	BYTE				byLU;				//�豸����
	BYTE				byIFCODE;			//cmd-1,resp-2,att-3
	BYTE				byCMD;				//��������
	BYTE				byErrorCode;
	BYTE				byszErrorCodeDetail[2];
	BYTE				byszReserved1[0x0C - 0x05];
	BYTE				byDisType;			//ȡ��ָ��ģʽ��ָ�������߳���
	WORD				wDataLen;		
}CDMHEAD,*LPCDMHEAD;

/*���ϲ���������Ӳ��ͨѶ���õ������ݵ��ӽṹ��������Щ�ӽṹ�л�Ƕ�����ӽṹ*/
/*���²��ֽ������ӽṹ��ϳ�Ӳ�������/�������õ��������Ĳ���*/

/*������Ӧ������·�����Ļ�Ӧ�����й��ϳ���ʱ��Ӳ���������²����ṹ*/
typedef struct _BRM_ERRORRESP
{
	HEAD				HeadOfResp;
	PUBRESP				PubResp;
}BRM_ERRORRESP,*LPBRM_ERRORRESP;


/**************����������������Ӧ�����ṹ**********/

/************************���������*******************/

/*���ģʽ��������*/
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
	BYTE				byTemperature;			//���������κ�ֵ
	BYTE				byHumidity;				//���������κ�ֵ
}BRM_CIMMODESET_REQ,*LPBRM_CIMMODESET_REQ;

/*���ģʽ����Ӧ��*/
typedef struct _BRM_CIMMODESET_RESP
{
	HEAD				HeadOfResp;
	PUBRESP				PubResp;
}BRM_CIMMODESET_RESP,*LPBRM_CIMMODESET_RESP;

/*����鳮����*/
typedef struct _BRM_CIMVERIFY_REQ
{
	HEAD				HeadOfReq;
	BYTE				byAutoResetMode;
	BYTE				byRetryFlag;				//����鳮����ָʾ
	WORD				wProcDenom;					//�������(������100��50��20��10)
	BYTE				byszBCDRestrictCount[4];	//�����������
	BYTE				byszBCDRestrictAmount[4];	//������ƽ��
	BYTE				byCategoryDepCtrlInfo;		//��Category��������Ϣ b1:0-category2���ʣ�α�������˻� 1-�˻�  b2:0-category3���ʣ��ɻ󳮣������� 1-���� b4:0-category4b���ʣ�����ѭ������������ 1-����
	BYTE				byReserved;
	WORD				wProcGroup;					//����ֽ��group(group���ǣ�����-��ȡ����ֽ��group-��ֵ��Ϣ)
}BRM_CIMVERIFY_REQ,*LPBRM_CIMVERIFY_REQ;

/*����鳮Ӧ��*/
typedef struct _BRM_CIMVERIFY_RESP
{
	HEAD				HeadOfResp;
	PUBRESP				PubResp;
	BYTE				byszBCDDepCount[4];
	BYTE				byszBCDDepAmount[4];
}BRM_CIMVERIFY_RESP,*LPBRM_CIMVERIFY_RESP;


/*����볮������*/
typedef struct _BRM_CIMSTORE_REQ
{
	HEAD				HeadOfReq;
	BYTE				byAutoResetMode;
	BYTE				byCategoryCanRecycle;					//��category��recycle�ɷ���Ϣ��b2-category3���ɻ󳮣��Ƿ�ѭ����b3-category4a��recycle���ܳ����Ƿ�ѭ����b4-category4b��recycle���ɳ����Ƿ�ѭ��
	BYTE				byszNonRecycleBillPlace[0x16 - 0x11];	//by[0]-category1���������� by[1]-category2��α����by[2]-category3���ɻ󳮣� by[3]-category4a��recycle���ܳ��� by[4]-category4b��recycle���ɳ�����0�������յ㲻ָ�� 2�����ר�ã���ֵָ���� 4�����ר�ã���ֵ��ָ���� B��CasD C��CasE D��CasR E��CasF
	BYINVERSEDENOM		Category;
	BYTE				byszFirstCollect[5];					//by[0]-1������ by[1]-2������ by[2]-3�����ȡ�������1��CasA 2��CasB 3��CasC 4��CasD 5��CasE
}BRM_CIMSTORE_REQ,*LPBRM_CIMSTORE_REQ;

/*����볮��Ӧ��*/
typedef struct _BRM_CIMSTORE_RESP
{	
	HEAD				HeadOfResp;
	PUBRESP				PubResp;
}BRM_CIMSTORE_RESP,*LPBRM_CIMSTORE_RESP;

/*���ȡ������*/
typedef struct _BRM_CIMCANCEL_REQ
{
	HEAD				HeadOfReq;
	BYTE				byAutoResetMode;
	BYTE				byCategoryRollBackInfo;				 //0-�����˻� 1-���˻ء�b1:category2��α���� b2-category3���ɻ󳮣�
	BYTE				byszNonRollBackBillPlace[0x16 - 0x11];//�����˻�ֽ�Ҵ����յ�	by[1]-category2 by[2]-category3��0�������յ㲻ָ�� 2�����ר�ã���ֵָ���� 4�����ר�ã���ֵ��ָ���� B��CasD C��CasE D��CasR E��CasF
}BRM_CIMCANCEL_REQ,*LPBRM_CIMCANCEL_REQ;

/*���ȡ��Ӧ��*/
typedef struct _BRM_CIMCANCEL_RESP
{
	HEAD				HeadOfResp;
	PUBRESP				PubResp;
}BRM_CIMCANCEL_RESP,*LPBRM_CIMCANCEL_RESP;


/*******************ȡ��������*********************/

/*ȡ��ģʽ��������*/
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
	BYTE				byTemperature;			//���������κ�ֵ
	BYTE				byHumidity;				//���������κ�ֵ
	BYTE				byUnknowDenomPlace;		//������Ʊ����λ��
}BRM_CDMMODESET_REQ,*LPBRM_CDMMODESET_REQ;

/*ȡ��ģʽ����Ӧ��*/
typedef struct _BRM_CDMMODESET_RESP
{
	HEAD				HeadOfResp;
	PUBRESP				PubResp;
}BRM_CDMMODESET_RESP,*LPBRM_CDMMODESET_RESP;

/*ȡ������*/
typedef struct _BRM_CDMDISPENSE_REQ
{
	CDMHEAD				CDMHeadOfReq;			
	BYTE				byAutoResetMode;
	BYTE				byCategoryCanDispense;		//��category��ȡ��ɷ���Ϣ��b2-category3���ɻ󳮣��Ƿ��ȡ��b4-category4b��recycle���ɳ����Ƿ��ȡ
	BYINVERSEDENOM		Category;					//denom14=CasAcnt denom13=CasBcnt denom12=CasCcnt denom11=CasDcnt denom10=CasEcnt
	BYTE				byszFirstDepart[5];			//by[0]-1������ by[1]-2������ by[2]-3�����ȡ�������1��CasA 2��CasB 3��CasC 4��CasD 5��CasE
}BRM_CDMDISPENSE_REQ,*LPBRM_CDMDISPENSE_REQ;

/*ȡ��Ӧ��*/
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

/**************��ȡ�������****************/

/*Timing,�ڵ�ģʽ����*/
typedef struct _BRM_TIMING_REQ
{
	HEAD				HeadOfReq;
	BYTE				byAutoResetMode;
	BYTE				byTimingDetails;
}BRM_TIMING_REQ,*LPBRM_TIMING_REQ;

/*Timing,�ڵ�ģʽӦ��*/
typedef struct _BRM_TIMING_RESP
{
	HEAD				HeadOfResp;
	PUBRESP				PubResp;
}BRM_TIMING_RESP,*LPBRM_TIMING_RESP;

/*ģʽ��λ����*/
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
	BYTE				byTemperature;			//���������κ�ֵ
	BYTE				byHumidity;				//���������κ�ֵ
}BRM_MODERESET_REQ,*LPBRM_MODERESET_REQ;

/*ģʽ��λӦ��*/
typedef struct _BRM_MODERESET_RESP
{
	HEAD				HeadOfResp;
	PUBRESP				PubResp;
}BRM_MODERESET_RESP,*LPBRM_MODERESET_RESP;

/*��������*/
typedef struct _BRM_RETRACT_REQ
{
	HEAD				HeadOfReq;
	BYTE				byAutoResetMode;
	BYTE				bySpecifSpecialRetract;		//�������ָ��  b0-1��ESCROW�ռ�ʱ���ص������cassette b0-0���������escrow�ռ�ʱ�������ռ��յ� b1-1:ȫ�����䵽escrow�������������� b1-0������������������ b7-1����escrow���� b7-0:���ڣ�escrow���롣
	BYTE				byCategoryCanRecycle;		//��category��recycle�ɷ���Ϣ��b2-category3���ɻ󳮣��Ƿ�ѭ����b3-category4a��recycle���ܳ����Ƿ�ѭ����b4-category4b��recycle���ɳ����Ƿ�ѭ��
	BYTE				byszNonRecycleBillPlace[0x17 - 0x12];	//by[0]-category1���������� by[1]-category2��α����by[2]-category3���ɻ󳮣� by[3]-category4a��recycle���ܳ��� by[4]-category4b��recycle���ɳ�����0�������յ㲻ָ�� 2�����ר�ã���ֵָ���� 4�����ר�ã���ֵ��ָ���� B��CasD C��CasE D��CasR E��CasF
	BYTE				byszFirstCollect[5];		//by[0]-1������ by[1]-2������ by[2]-3�����ȡ�������1��CasA 2��CasB 3��CasC 4��CasD 5��CasE
}BRM_RETRACT_REQ,*LPBRM_RETRACT_REQ;

/*����Ӧ��*/
typedef struct _BRM_RETRACT_RESP
{
	HEAD				HeadOfResp;
	PUBRESP				PubResp;
}BRM_RETRACT_RESP,*LPBRM_RETRACT_RESP;


/*ֽ���ƶ�����*/
typedef struct _BRM_MOVEBILL_REQ
{
	HEAD				HeadOfReq;
	BYTE				byAutoResetMode;
	WORD				wCountOfMoveBill;
	BYTE				byMoveSource;
	BYTE				byMoveTarget;
	BYTE				byUnknowDenomPlace;
	BYTE				byszFirstCollect[5];		//by[0]-1������ by[1]-2������ by[2]-3�����ȡ�������1��CasA 2��CasB 3��CasC 4��CasD 5��CasE
}BRM_MOVEBILL_REQ,*LPBRM_MOVEBILL_REQ;

/*ֽ���ƶ�Ӧ��*/
typedef struct  _BRM_MOVEBILL_RESP 
{
	HEAD				HeadOfResp;
	PUBRESP				PubResp;
}BRM_MOVEBILL_RESP,*LPBRM_MOVEBILL_RESP;

/*����������*/
typedef struct _BRM_CLEANING_REQ
{
	HEAD				HeadOfReq;
	BYTE				byAutoResetMode;
	BYTE				byszReserved[2];
}BRM_CLEANING_REQ,*LPBRM_CLEANING_REQ;

/*������Ӧ��*/
typedef struct _BRM_CLEANING_RESP
{
	HEAD				HeadOfResp;
	PUBRESP				PubResp;
}BRM_CLEANING_RESP,*LPBRM_CLEANING_RESP;

/*·���������*/
typedef struct _BRM_PATHCHECK_REQ
{
	HEAD				HeadOfReq;
	BYTE				byAutoResetMode;
	BYTE				byReserved;
	BYTE				byUnknowDenomPlace;		//6:CasD 7:CasE 8:CasR 9:CasF F:�������Cassette			
	BYTE				byCasADepartCount;
	BYTE				byCasBDepartCount;
	BYTE				byCasCDepartCount;
	BYTE				byCasDDepartCount;
	BYTE				byCasEDepartCount;
	BYTE				byReserved1;
}BRM_PATHCHECK_REQ,*LPBRM_PATHCHECK_REQ;

/*·�����Ӧ��*/
typedef struct _BRM_PATHCHECK_RESP
{
	HEAD				HeadOfResp;
	PUBRESP				PubResp;
}BRM_PATHCHECK_RESP,*LPBRM_PATHCHECK_RESP;

/*LED��������*/
typedef struct _BRM_LEDCONTROL_REQ
{
	HEAD				HeadOfReq;
	BYTE				byAutoResetMode;
	BYTE				byShutterLedCtrlInfo;		//b0-0:��� b0-1������ b6-0��ƽ������ b6-1�����ٷ��� b7-0��ledָʾ��Ч b7-1��ledָʾ��Ч
}BRM_LEDCONTROL_REQ,*LPBRM_LEDCONTROL_REQ;

/*LED����Ӧ��*/
typedef struct _BRM_LEDCONTROL_RESP
{	
	HEAD				HeadOfResp;
	PUBRESP				PubResp;
}BRM_LEDCONTROL_RESP,*LPBRM_LEDCONTROL_RESP;

/*��ʼ������*/
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
	BYTE				byTemperature;			//���������κ�ֵ
	BYTE				byHumidity;				//���������κ�ֵ
}BRM_INIT_REQ,*LPBRM_INIT_REQ;

/*��ʼ��Ӧ��*/
typedef struct _BRM_INIT_RESP
{
	HEAD				HeadOfResp;
	PUBRESP				PubResp;
}BRM_INIT_RESP,*LPBRM_INIT_RESP;


/*���ſ�������*/
typedef struct _BRM_SHUTTERCTRL_REQ
{
	HEAD				HeadOfReq;
	BYTE				byAutoResetMode;
	BYTE				byTradeType;		//1��ȡ��� 2������
	BYTE				byShutterCtrlFlag;	//b0-ǿ�ƹأ� b1-��ǿ�ƹ� b7-��
}BRM_SHUTTERCTRL_REQ,*LPBRM_SHUTTERCTRL_REQ;

/*���ſ���Ӧ��*/
typedef struct _BRM_SHUTTERCTRL_RESP
{
	HEAD				HeadOfResp;
	PUBRESP				PubResp;
	WORD				wShutterBillCntEst;			//���ڳ�Ʊ����Ԥ��
}BRM_SHUTTERCTRL_RESP,*LPBRM_SHUTTERCTRL_RESP;

/*���ż������*/
typedef struct _BRM_SHUTTERCHECK_REQ
{
	HEAD				HeadOfReq;
	BYTE				byAutoResetMode;
	BYTE				byTradeType;
	BYTE				byTimeFlag;				//shuttercheck��������ȶ�ʱ��500/1000ms��Ϊ�˸���ļ�⣬ 20120423
}BRM_SHUTTERCHECK_REQ,*LPBRM_SHUTTERCHECK_REQ;  //oki�������µ�firmware����Ҫsp��Ӧ�������ʽ���˸��ֶΣ�byTimeFlag������Ϊ0����sg����delay����������delay��ͨ��sp��delayȷ���ȶ�ʱ�䡣

/*���ż��Ӧ��*/
typedef struct _BRM_SHUTTERCHECK_RESP
{
	HEAD				HeadOfResp;
	PUBRESP				PubResp;
}BRM_SHUTTERCHECK_RESP,*LPBRM_SHUTTERCHECK_RESP;

/*�豸�������*/
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
	BYTE				byTemperature;			//���������κ�ֵ
	BYTE				byHumidity;				//���������κ�ֵ
}BRM_CHECK_REQ,*LPBRM_CHECK_REQ;

/*�豸���Ӧ��*/
typedef struct _BRM_CHECK_RESP
{
	HEAD				HeadOfResp;
	PUBRESP				PubResp;
	SAFEINFO			SafeInfo;
	LEFTMOVEINFO		LeftMoveInfo;
	VERIFYDENOMINFO		VerifyDenomInfo;
}BRM_CHECK_RESP,*LPBRM_CHECK_RESP;


/*������ȡ����*/
typedef struct _BRM_COUNTREAD_REQ
{
	HEAD				HeadOfReq;
}BRM_COUNTREAD_REQ,*LPBRM_COUNTREAD_REQ;

/*������ȡӦ��*/
typedef struct _BRM_COUNTREAD_RESP
{
	HEAD				HeadOfResp;
	ACTIONCOUNT			ActionCount;
}BRM_COUNTREAD_RESP,*LPBRM_COUNTREAD_RESP;

/*�����������*/
typedef struct _BRM_COUNTCLEAR_REQ
{
	HEAD				HeadOfReq;
	BYTE				byClearFlag;
}BRM_COUNTCLEAR_REQ,*LPBRM_COUNTCLEAR_REQ;

/*�������Ӧ��*/
typedef struct _BRM_COUNTCLEAR_RESP
{
	HEAD				HeadOfResp;
	ACTIONCOUNT			ActionCount;
}BRM_COUNTCLEAR_RESP,*LPBRM_COUNTCLEAR_RESP;

/*DownLoad UpLoad�����룬δ��ͷ�ļ���д����SP�в�ʹ��*/

/*�ڴ��ȡ����*/
typedef struct _BRM_MEMREAD_REQ
{
	HEAD				HeadOfReq;
}BRM_MEMREAD_REQ,*LPBRM_MEMREAD_REQ;

/*�ڴ��ȡӦ��-����ȫ��Ӧ���ڴ�����û���ڽṹ������-��ʹ��*/
typedef struct _BRM_MEMREAD_RESP
{
	HEAD				HeadOfResp;
}BRM_MEMREAD_RESP,*LPBRM_MEMREAD_RESP;


/*��¼��ȡ����-����ȫ��Ӧ����ʹ��*/
typedef struct _BRM_RECORDREAD_REQ
{
	HEAD				HeadOfReq;
}BRM_RECORDREAD_REQ,*LPBRM_RECORDREAD_REQ;

/*��¼��ȡӦ��-����ȫ��Ӧ����ʹ��*/
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
	BYTE				byszBoardRevision[2];		//����Revision
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

	BYTE				byszShutterBarCode[6];		//����������
	BYTE				byszShutterMechaRevision[2];
	BYTE				byszReserved2[2];
	BYTE				byszShutterBCDYear[2];
	BYTE				byShutterBCDMonth;
	BYTE				byShutterBCDDay;
	BYTE				byszReserved3[2];

	BYTE				byszEscrowBarCode[6];		//�ݴ�������
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

/*SG��������*/
typedef struct _BRM_LOADSG_REQ
{
	HEAD				HeadOfReq;
	UNITINFO84H			UnitInfo84h;	
}BRM_LOADSG_REQ,*LPBRM_LOADSG_REQ;

/*SG����Ӧ��*/
typedef struct _BRM_LOADSG_RESP
{
	HEAD				HeadOfResp;
	VERSIONINFO			VersionInfo;
	UNITINFO100H		UnitInfo100h;
}BRM_LOADSG_RESP,*LPBRM_LOADSG_RESP;

/*�鳮DownLoad�����룬δ��ͷ�ļ���д����SP�в�ʹ��*/

/*���ݶ�ȡ����*/
typedef struct _BRM_DATAREAD_REQ
{
	HEAD				HeadOfReq;
	BYTE				byDataType;			//0x01���趨data 10������ر���Ϣ 0x20:cas�ӳ�������Ϣ
	BYTE				byInfoType;			//
}BRM_DATAREAD_REQ,BRM_GETDATASET_REQ,BRM_GETCASCLOSEINFO_REQ,BRM_GETCASCONF_REQ,*LPBRM_DATAREAD_REQ,*LPBRM_GETDATASET_REQ,*LPBRM_GETCASCLOSEINFO_REQ,*LPBRM_GETCASCONF_REQ;;

/*���ݶ�ȡӦ��-����ȫ��Ӧ-��ʹ��*/
typedef struct _BRM_DATAREAD_RESP
{
	HEAD				HeadOfResp;
}BRM_DATAREAD_RESP,*LPBRM_DATAREAD_RESP;

/*��ȡ�����趨Ӧ��*/
typedef struct _BRM_GETDATASET_RESP
{
	HEAD				HeadOfResp;
	BYTE				byReserved;
	USERLOGININFO		UserLoginInfo;
}BRM_GETDATASET_RESP,*LPBRM_GETDATASET_RESP;

/*��ȡ����ر���Ϣ*/
typedef struct _BRM_GETCASCLOSEINFO_RESP
{
	HEAD				HeadOfResp;
	BYTE				byReserved;
	DWORD				dwCasCloseInfo;
}BRM_GETCASCLOSEINFO_RESP,*LPBRM_GETCASCLOSEINFO_RESP;

/*��������*/
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

/*��ȡ��������Ӧ��*/
typedef struct _BRM_GETCASCONF_RESP
{
	HEAD				HeadOfResp;
	BYTE				byReserved;
	BYTE				byszReserved[3];
	CASDATA				CasData;
}BRM_GETCASCONF_RESP,*LPBRM_GETCASCONF_RESP;

/*����д������-����ȫ��Ӧ-��ʹ��*/
typedef struct _BRM_DATAWRITE_REQ
{
	HEAD				HeadOfReq;
	BYTE				byDataType;			//0X01���趨data 0x10������ر���Ϣ 0x20��cas�ӳ�������Ϣ 0x21��׷���ֲ������� 0x22��ȡ���ֻ�������
}BRM_DATAWRITE_REQ,*LPBRM_DATAWRITE_REQ;


/*����д��Ӧ��-����ȫ��Ӧ-��ʹ��*/
typedef struct _BRM_DATAWRITE_RESP
{
	HEAD				HeadOfResp;
}BRM_DATAWRITE_RESP,*LPBRM_DATAWRITE_RESP;

/*���������趨����*/
typedef struct _BRM_SETDATASET_REQ
{
	HEAD				HeadOfReq;
	BYTE				byDataType;
	USERLOGININFO		UserLoginInfo;
}BRM_SETDATASET_REQ,*LPBRM_SETDATASET_REQ;

/*���������趨Ӧ��*/
typedef struct _BRM_SETDATASET_RESP
{
	HEAD				HeadOfResp;
	BYTE				byReserved;
	USERLOGININFO		UserLoginInfo;
}BRM_SETDATASET_RESP,*LPBRM_SETDATASET_RESP;

/*���ó���ر�����*/
typedef struct _BRM_SETCASCLOSEINFO_REQ
{
	HEAD				HeadOfReq;
	BYTE				byDataType;
	DWORD				dwCasCloseInfo;
}BRM_SETCASCLOSEINFO_REQ,*LPBRM_SETCAACLOSEINFO_REQ;

/*���ó���ر�Ӧ��*/
typedef	struct _BRM_SETCASCLOSEINFO_RESP
{
	HEAD				HeadOfResp;
	BYTE				byReserved;
	DWORD				dwCasCloseInfo;
}BRM_SETCASCLOSEINFO_RESP,*LPBRM_SETCASCLOSEINFO_RESP;

/*���ó�����������*/
typedef struct _BRM_SETCASCONF_REQ
{
	HEAD				HeadOfReq;
	BYTE				byDataType;			//0x20��cas�ӳ�������Ϣ 0x21��׷���ֲ������� 0x22��ȡ���ֻ��������� һ��ʹ��0x20
	BYTE				bySetCasCountType;	//�ӳ����� b0-CasA�ӳ� b1-CasB�ӳ� b2-CasC�ӳ� b3-CasD�ӳ� b4-CasE�ӳ�
	BYTE				byszReserved[2];
	CASDATA				CasData;
}BRM_SETCASCONF_REQ,*LPBRM_SETCASCONF_REQ;

/*���ó�������Ӧ��*/
typedef struct _BRM_SETCASCONF_RESP
{
	HEAD				HeadOfResp;
	BYTE				byReserved;   
	BYTE				bySetCasCountType;	//�ӳ����� b0-CasA�ӳ� b1-CasB�ӳ� b2-CasC�ӳ� b3-CasD�ӳ� b4-CasE�ӳ�
	BYTE				bySetCasCountResult;//�ӳ���� b0-CasA�ӳ��и��� b1-CasB�ӳ��и��� b2-CasC�ӳ��и��� b3-CasD�ӳ��и��� b4-CasE�ӳ��и���
	BYTE				byCasIDStatus;		//CASID״̬��b0-CasA��ֵ��Ϣ��һ�£�b1-CasB��ֵ��һ�£�b2-CasC��ֵ��һ�£�b3-CasD��ֵ��һ�£�b4-CasE��ֵ��һ��
	CASDATA				CasData;
}BRM_SETCASCONF_RESP,*LPBRM_SETCASCONF_RESP;
/**********************ATTENTION**ATTENTION***************************/

/*attention-����ȫ��Ӧ-ʹ��-attention��ϸ��Ϣ��Ҫ����Ŀռ�*/
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

/*record collect attention-����ȫ��Ӧ-��¼��Ϣ��Ҫ����Ŀռ�*/
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

/*Art6 ֽ�Ҹ�����Ϣ attention*/
typedef struct _BRM_ART6_ATT
{
	BRM_ATTENTION		Att;
	BYTE				byReserved;
	ART6COUNT			Art6Count;
}BRM_ATR6_ATT,*LPBRM_ART6_ATT;

/*ֽ����ϸ��Ϣ������λ�õ�*/
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