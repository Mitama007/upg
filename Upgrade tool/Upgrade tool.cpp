// Upgrade tool.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "Upgrade tool.h"
#include "Upgrade toolDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUpgradetoolApp

BEGIN_MESSAGE_MAP(CUpgradetoolApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CUpgradetoolApp ����

CUpgradetoolApp::CUpgradetoolApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CUpgradetoolApp ����

CUpgradetoolApp theApp;


// CUpgradetoolApp ��ʼ��

BOOL CUpgradetoolApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));


	CUpgradetoolDlg objDlg;
	m_pMainWnd = &objDlg;

	INT_PTR nResponse = objDlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		TRACE("ok!");

		ST_SERVICE_CMD_DATA stMsg;
		memset(&stMsg, 0, sizeof(ST_SERVICE_CMD_DATA));

		stMsg.enServiceCode =  EN_EXIT_CMD;
		stMsg.stData.idatalen =  0;
		stMsg.stData.pcdata = new char[10];
		memcpy(stMsg.stData.pcdata, "2332322222222", stMsg.stData.idatalen);

		objDlg.m_objUpgrade.SendCmd(&stMsg);
		delete []stMsg.stData.pcdata;
		stMsg.stData.pcdata = NULL;

		Sleep(200);
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		 TRACE("CANCEL!");
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
