// Upgrade tool.cpp : 定义应用程序的类行为。
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


// CUpgradetoolApp 构造

CUpgradetoolApp::CUpgradetoolApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CUpgradetoolApp 对象

CUpgradetoolApp theApp;


// CUpgradetoolApp 初始化

BOOL CUpgradetoolApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));


	CUpgradetoolDlg objDlg;
	m_pMainWnd = &objDlg;

	INT_PTR nResponse = objDlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
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
		// TODO: 在此放置处理何时用
		 TRACE("CANCEL!");
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}
