// Upgrade toolDlg.cpp : 实现文件
//


#include "stdafx.h"
#include "Upgrade tool.h"
#include "Upgrade toolDlg.h"
#include "Upgradeapi.h"

#include <stdio.h>
#include <windows.h>
#include <dbt.h>
#include <string>
#include <sstream>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif





int UpdateOutputInfo(string strdata);
void UptadeProgress(int iPosition);
int UpdateProcNum(long lProcNum);
int UpdateVerCount(long lVer);
int UpdateCurName(LONG lProcNum, char *pcFileName);
void UpdatelistProgress(void);
void OutputResult(int iResult);
int UpdateOutputResult(string strdata);

static bool bResultClear = FALSE;
static bool bInfoClear = FALSE;




// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CUpgradetoolDlg 对话框




CUpgradetoolDlg::CUpgradetoolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUpgradetoolDlg::IDD, pParent)
	, m_FileDir(_T("C:\\ATM\\SP\\FRM\\CC"))
	, m_lProcNum(0)
	, m_lVerCount(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bStatus = false;
	memset(&m_stFileList, 0, sizeof(m_stFileList));
}

void CUpgradetoolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_FileDir);	
	DDX_Text(pDX, IDC_EDIT4, m_lProcNum);	
	DDX_Text(pDX, IDC_EDIT5, m_lVerCount);	
	DDX_Control(pDX, IDC_PROGRESS1, m_ctrlProgress);
	DDX_Control(pDX, IDC_LIST2, m_list);
}

BEGIN_MESSAGE_MAP(CUpgradetoolDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_UPGRADE, &CUpgradetoolDlg::OnBnClickedUpgrade)
	ON_BN_CLICKED(IDC_BROWSE, &CUpgradetoolDlg::OnBnClickedFiledir)
	ON_BN_CLICKED(IDC_ONOFF, &CUpgradetoolDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_GET_VERSION, &CUpgradetoolDlg::OnBnClickedGetVersion)
	ON_BN_CLICKED(IDC_GET_VER_COUNT, &CUpgradetoolDlg::OnBnClickedGetVerCount)
	ON_BN_CLICKED(IDC_RECOVERY, &CUpgradetoolDlg::OnBnClickedRecovery)
	ON_BN_CLICKED(IDC_BUTTON1, &CUpgradetoolDlg::OnBnClickedButton1)
	ON_WM_DRAWITEM()
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_EDIT1, &CUpgradetoolDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_GETIP, &CUpgradetoolDlg::OnBnClickedGetip)
END_MESSAGE_MAP()

// CUpgradetoolDlg 消息处理程序

BOOL CUpgradetoolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码


	m_hIconLedRed;
	m_hIconLedGreen;
	m_hIconLedRed= (HICON)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON1),IMAGE_ICON,40,40,LR_DEFAULTCOLOR);
	m_hIconLedGreen= (HICON)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON2),IMAGE_ICON,40,40,LR_DEFAULTCOLOR);	
	
	((CStatic*)GetDlgItem(IDC_LED))->SetIcon(m_hIconLedRed); 	

	//设置进度条的范围
	m_ctrlProgress.SetRange(0,100);
	//设置进度条的每一步的增量
	m_ctrlProgress.SetStep(10);
	//设置进度条的当前位置
	m_ctrlProgress.SetPos(0);

	m_objUpgrade.Init(UpdateOutputInfo, this);

	InitListCtrl();

	CRect rect;    
	GetClientRect(&rect);     //取客户区大小  
	old.x=rect.right-rect.left;
	old.y=rect.bottom-rect.top;

	/*CWnd *pWnd = (CWnd *)(theApp.m_pMainWnd->GetDlgItem(IDC_ONOFF));
	pWnd->SetWindowPos( NULL,0,0,109,53,SWP_NOZORDER | SWP_NOMOVE ); 

	pWnd = (CWnd *)(theApp.m_pMainWnd->GetDlgItem(IDC_BROWSE));
	pWnd->SetWindowPos( NULL,0,0,109,53,SWP_NOZORDER | SWP_NOMOVE ); 

	pWnd = (CWnd *)(theApp.m_pMainWnd->GetDlgItem(IDOK));
	pWnd->SetWindowPos( NULL,0,0,109,53,SWP_NOZORDER | SWP_NOMOVE ); 

	pWnd = (CWnd *)(theApp.m_pMainWnd->GetDlgItem(IDC_UPGRADE));
	pWnd->SetWindowPos( NULL,0,0,109,53,SWP_NOZORDER | SWP_NOMOVE ); */

	theApp.m_pMainWnd->GetDlgItem(IDC_RESULT)->ShowWindow(SW_HIDE);
	theApp.m_pMainWnd->GetDlgItem(IDC_EDIT2)->ShowWindow(SW_HIDE);
	theApp.m_pMainWnd->GetDlgItem(IDC_EDIT3)->ShowWindow(SW_HIDE);
	theApp.m_pMainWnd->GetDlgItem(IDC_PROGRESS1)->ShowWindow(SW_HIDE); 
	theApp.m_pMainWnd->GetDlgItem(IDC_STATIC6)->ShowWindow(SW_HIDE);

	theApp.m_pMainWnd->GetDlgItem(IDC_EDIT4)->ShowWindow(SW_HIDE);
//	theApp.m_pMainWnd->GetDlgItem(IDC_GET_VERSION)->ShowWindow(SW_HIDE);
	theApp.m_pMainWnd->GetDlgItem(IDC_EDIT5)->ShowWindow(SW_HIDE);
	theApp.m_pMainWnd->GetDlgItem(IDC_GET_VER_COUNT)->ShowWindow(SW_HIDE); 
	theApp.m_pMainWnd->GetDlgItem(IDC_RECOVERY)->ShowWindow(SW_HIDE);
//	theApp.m_pMainWnd->GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_HIDE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CUpgradetoolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CUpgradetoolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);	
	}
	else
	{
		//CPaintDC dc(this);
		//CBitmap   bitmap;
		//bitmap.LoadBitmap(IDB_BITMAP_BACK);    //这个IDB_BITMAP1要自己添加
		//CBrush   brush;
		//brush.CreatePatternBrush(&bitmap);
		//CBrush*   pOldBrush   =   dc.SelectObject(&brush);
		//dc.Rectangle(0,0,800,600);   // 这些参数可以调整图片添加位置和大小
		//dc.SelectObject(pOldBrush);	

		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CUpgradetoolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CUpgradetoolDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	// TODO: Add your message handler code here
	if (nType==SIZE_RESTORED||nType==SIZE_MAXIMIZED)
	{
		ReSize();
	}
}

void CUpgradetoolDlg::ReSize()
{
	float fsp[2];
	POINT Newp; //获取现在对话框的大小
	CRect recta;    
	GetClientRect(&recta);     //取客户区大小  
	Newp.x=recta.right-recta.left;
	Newp.y=recta.bottom-recta.top;
	fsp[0]=(float)Newp.x/old.x;
	fsp[1]=(float)Newp.y/old.y;
	CRect Rect;
	int woc;
	CPoint OldTLPoint,TLPoint; //左上角
	CPoint OldBRPoint,BRPoint; //右下角
	HWND  hwndChild=::GetWindow(m_hWnd,GW_CHILD);  //列出所有控件  
	while(hwndChild)    
	{    
		woc=::GetDlgCtrlID(hwndChild);//取得ID
		GetDlgItem(woc)->GetWindowRect(Rect);  
		ScreenToClient(Rect);  
		OldTLPoint = Rect.TopLeft();  
		TLPoint.x = long(OldTLPoint.x*fsp[0]);  
		TLPoint.y = long(OldTLPoint.y*fsp[1]);  
		OldBRPoint = Rect.BottomRight();  
		BRPoint.x = long(OldBRPoint.x *fsp[0]);  
		BRPoint.y = long(OldBRPoint.y *fsp[1]);  
		Rect.SetRect(TLPoint,BRPoint);  
		GetDlgItem(woc)->MoveWindow(Rect,TRUE);
		hwndChild=::GetWindow(hwndChild, GW_HWNDNEXT);    
	}
	old=Newp;
}

void CUpgradetoolDlg::OnBnClickedUpgrade()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	string strFileDir = m_FileDir;
	PST_UPGRADE_FILE pstFile = &m_stFileList;
	stringstream ss;
	string str;

	ST_SERVICE_CMD_DATA stMsg;
	memset(&stMsg, 0, sizeof(ST_SERVICE_CMD_DATA));
	theApp.m_pMainWnd->GetDlgItem(IDC_EDIT3)->ShowWindow(SW_HIDE);
	
	if(m_bStatus)
	{
		OutputResult(2);
		for(int i=0; i<m_list.GetItemCount(); i++)
		{
			m_stFileList.abCheck[i] = m_list.GetCheck(i);
			pstFile->aiProgress[i] = 0;				
		}	

		for(int i=0; i<m_stFileList.iFileNum; i++)
		{
			ss.str("");
			ss << m_stFileList.aiProgress[i];
			str = ss.str() + "  %";
			m_list.SetItemText(i, 2, str.data());
		}

		OnBnClickedButton1();	
		UpdateData(FALSE);

		stMsg.enServiceCode =  EN_UPGRADE_CMD;
		stMsg.stData.idatalen =  sizeof(ST_UPGRADE_FILE);
		stMsg.stData.pcdata = (char *)pstFile;

		m_objUpgrade.SendCmd(&stMsg);
	}	
	
	
}

void CUpgradetoolDlg::OnBnClickedFiledir()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strPath;
	BROWSEINFO bInfo;
	LPITEMIDLIST pidl;

	UpdateData(TRUE);

	ZeroMemory ( (PVOID) &bInfo,sizeof (BROWSEINFO));
	bInfo.hwndOwner = this->m_hWnd;
	bInfo.pszDisplayName = strPath.GetBuffer(MAX_PATH);
	bInfo.lpszTitle = "";
	bInfo.ulFlags = BIF_RETURNFSANCESTORS|BIF_RETURNONLYFSDIRS;
	bInfo.lpfn = NULL;
	bInfo.lParam = 0;

	if ((pidl = ::SHBrowseForFolder(&bInfo)) == NULL)
	{
		return;
	}

	if (::SHGetPathFromIDList(pidl,strPath.GetBuffer(MAX_PATH)) == FALSE)
	{
		return;
	}

	m_FileDir = strPath;
	UpdateData(FALSE);
	OnEnChangeEdit1();
}

void CUpgradetoolDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码

	m_bStatus = !m_bStatus;
	if(m_bStatus)
	{
		theApp.m_pMainWnd->GetDlgItem(IDC_ONOFF)->SetWindowText("关 闭");
			
		m_objUpgrade.m_objUpApi.m_aobjLow[0].SetId(EN_UPGRADE_MAIN_CTRL, 1);
		((CStatic*)GetDlgItem(IDC_LED))->SetIcon(m_hIconLedGreen); 
	}
	else
	{
		theApp.m_pMainWnd->GetDlgItem(IDC_ONOFF)->SetWindowText("打 开");	
		m_objUpgrade.m_objUpApi.m_aobjLow[0].SetId(EN_UPGRADE_MAIN_CTRL, 0);
		((CStatic*)GetDlgItem(IDC_LED))->SetIcon(m_hIconLedRed); 
	}
}

// =0 pass =1 fail =2 run
enum 
{
	EN_PASS,
	EN_FAIL,
	EN_RUN,
}EN_UPGRADE_RESULT;
void OutputResult(int iResult)
{
	CBitmap bitmap;
	CStatic *p;
	CWnd *pWnd;

	switch(iResult)
	{
	case EN_PASS:
		bitmap.LoadBitmap(IDB_BITMAP_PASS);
		break;
		
	case EN_FAIL:
		bitmap.LoadBitmap(IDB_BITMAP_FAIL);
		break;

	case EN_RUN:
		bitmap.LoadBitmap(IDB_BITMAP_RUN);
		break;

	default:
		break;
	}

	p=(CStatic *)(theApp.m_pMainWnd->GetDlgItem(IDC_RESULT)); 
	p->ModifyStyle(0xf,SS_BITMAP|SS_CENTERIMAGE); 
	pWnd = (CWnd *)(theApp.m_pMainWnd->GetDlgItem(IDC_RESULT));
	pWnd->SetWindowPos( NULL,0,0,185,85,SWP_NOZORDER | SWP_NOMOVE ); 
	p->SetBitmap(bitmap); 
	theApp.m_pMainWnd->GetDlgItem(IDC_RESULT)->ShowWindow(SW_NORMAL);
}



int UpdateOutputInfo(string strdata)
{
	CString str ;
	static CString s_str;

	if(bInfoClear)
	{
		s_str =_T("");
		bInfoClear = FALSE;
	}

	str.Format("%s", strdata.c_str()); 
	s_str += str;

	theApp.m_pMainWnd->GetDlgItem(IDC_EDIT2)->SetWindowText(s_str);

	CEdit* pedit = (CEdit*)theApp.m_pMainWnd->GetDlgItem(IDC_EDIT2);
	pedit->LineScroll(pedit->GetLineCount());

	return 0;
}

int UpdateProcNum(long lProcNum)
{
	CString str ;
	str.Format("%ld", lProcNum);

	theApp.m_pMainWnd->GetDlgItem(IDC_EDIT4)->SetWindowText(str);

	CUpgradetoolDlg *pcDlg = (CUpgradetoolDlg *)(theApp.m_pMainWnd);
	pcDlg->m_lProcNum = lProcNum;
	return 0;	
}

int UpdateVerCount(long lVer)
{
	CString str ;
	str.Format("%ld", lVer);

	theApp.m_pMainWnd->GetDlgItem(IDC_EDIT5)->SetWindowText(str);
	return 0;	
}

int UpdateCurName(LONG lProcNum, char *pcFileName)
{

	CString str ;
	str.Format("%s", pcFileName);

	switch(lProcNum)
	{
	case 2:
		//theApp.m_pMainWnd->GetDlgItem(IDC_USBSER)->SetWindowText(str);
		break;

	case 3:
		//theApp.m_pMainWnd->GetDlgItem(IDC_BRM)->SetWindowText(str);
		break;

	case 5:
		//theApp.m_pMainWnd->GetDlgItem(IDC_UP)->SetWindowText(str);
		break;

	default:
		break;
	}

	return 0;
}


int UpdateCurVersion(LONG lProcNum, char *pcFileVersion)
{
	string str = pcFileVersion;
	char acBuf[64] = {0};
	string str1("");
	BOOL bValidflag = FALSE;

	switch(lProcNum)
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:		
		bValidflag = TRUE;
		break;
	default:
		break;
	}

	if(bValidflag)
	{
		str1 = acBuf;
		str = str1 + "  " + str + "\r\n";
		UpdateOutputResult(str);
	}

	return 0;
}


int UpdateGetIp(char *pcFileVersion)
{
	string str = pcFileVersion;
	char acBuf[64] = {0};
	string str1("");

	str1 = acBuf;
	str = str1 + "  " + str + "\r\n";
	UpdateOutputResult(str);
	return 0;
}


void UptadeProgress(int iPosition)
{
	CUpgradetoolDlg *pcDlg = NULL;
	CProgressCtrl *pProgress = (CProgressCtrl *)theApp.m_pMainWnd->GetDlgItem(IDC_PROGRESS1);

	int nLower=0;
	int nUpper=0;
	pProgress->GetRange(nLower,nUpper);
	if(iPosition >= nLower && iPosition <= nUpper)
	{
		pProgress->SetPos(iPosition);
	}	
}

int UpdateOutputResult(string strdata)
{
	CString str ;
	static CString s_str;

	if(bResultClear)
	{
		s_str =_T("");
		bResultClear = FALSE;
	}
	str.Format("%s", strdata.c_str()); 
	s_str += str;

	theApp.m_pMainWnd->GetDlgItem(IDC_EDIT3)->SetWindowText(s_str);

	CEdit* pedit = (CEdit*)theApp.m_pMainWnd->GetDlgItem(IDC_EDIT3);
	pedit->LineScroll(pedit->GetLineCount());

	return 0;
}

void CUpgradetoolDlg::OnBnClickedGetVersion()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	ST_SERVICE_CMD_DATA stMsg;
	memset(&stMsg, 0, sizeof(ST_SERVICE_CMD_DATA));
	theApp.m_pMainWnd->GetDlgItem(IDC_EDIT3)->ShowWindow(SW_NORMAL);

	if(m_bStatus)
	{
		stMsg.enServiceCode =  EN_GET_UPGRADE_CURRENT_VERSION_CMD;
		m_objUpgrade.SendCmd(&stMsg);
	}
}

void CUpgradetoolDlg::OnBnClickedGetVerCount()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	ST_SERVICE_CMD_DATA stMsg;
	memset(&stMsg, 0, sizeof(ST_SERVICE_CMD_DATA));

	if(m_bStatus)
	{
		stMsg.enServiceCode =  EN_GET_UPGRADE_VER_COUNT_CMD;
		stMsg.stData.idatalen =  1 + sizeof(m_lProcNum);
		stMsg.stData.pcdata = new char[stMsg.stData.idatalen];
		memcpy(stMsg.stData.pcdata, &m_lProcNum, sizeof(m_lProcNum));

		m_objUpgrade.SendCmd(&stMsg);
	}	
}

void CUpgradetoolDlg::OnBnClickedRecovery()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	ST_SERVICE_CMD_DATA stMsg;
	memset(&stMsg, 0, sizeof(ST_SERVICE_CMD_DATA));

	ST_RECOVERY_INFO stInfo;
	memset(&stInfo, 0, sizeof(ST_RECOVERY_INFO));

	stInfo.lProcid = m_lProcNum;
	stInfo.lVer = m_lVerCount;

	if(m_bStatus)
	{
		stMsg.enServiceCode =  EN_RECOVERY_UPGRADE_VER_CMD;
		stMsg.stData.idatalen =  1+sizeof(ST_RECOVERY_INFO);
		stMsg.stData.pcdata = new char[stMsg.stData.idatalen];
		memcpy(stMsg.stData.pcdata, &stInfo, sizeof(stInfo));

		m_objUpgrade.SendCmd(&stMsg);
	}	
}

void CUpgradetoolDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	bResultClear = TRUE;
	bInfoClear = TRUE;

	theApp.m_pMainWnd->GetDlgItem(IDC_EDIT2)->SetWindowText(_T(""));

	CEdit* pedit = (CEdit*)theApp.m_pMainWnd->GetDlgItem(IDC_EDIT2);
	pedit->LineScroll(pedit->GetLineCount());

	theApp.m_pMainWnd->GetDlgItem(IDC_EDIT3)->SetWindowText(_T(""));

	pedit = (CEdit*)theApp.m_pMainWnd->GetDlgItem(IDC_EDIT3);
	pedit->LineScroll(pedit->GetLineCount());
}

#if 0	//	测试查询功能
void CUpgradetoolDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	ST_SERVICE_CMD_DATA stMsg;
	long lProcnum1 = 2;
	memset(&stMsg, 0, sizeof(ST_SERVICE_CMD_DATA));

	if(m_bStatus)
	{
		stMsg.enServiceCode =  EN_GET_UPGRADE_CURRENT_NAME_CMD;
		stMsg.stData.idatalen =  1 + sizeof(long);
		stMsg.stData.pcdata = new char[stMsg.stData.idatalen];

		memcpy(stMsg.stData.pcdata, &lProcnum1, sizeof(lProcnum1));

		m_objUpgrade.SendCmd(&stMsg);
	}

	lProcnum1 = 3;
	memset(&stMsg, 0, sizeof(ST_SERVICE_CMD_DATA));
	if(m_bStatus)
	{
		stMsg.enServiceCode =  EN_GET_UPGRADE_CURRENT_NAME_CMD;
		stMsg.stData.idatalen =  1 + sizeof(long);
		stMsg.stData.pcdata = new char[stMsg.stData.idatalen];

		memcpy(stMsg.stData.pcdata, &lProcnum1, sizeof(lProcnum1));

		m_objUpgrade.SendCmd(&stMsg);
	}

	lProcnum1 = 5;
	memset(&stMsg, 0, sizeof(ST_SERVICE_CMD_DATA));
	if(m_bStatus)
	{
		stMsg.enServiceCode =  EN_GET_UPGRADE_CURRENT_NAME_CMD;
		stMsg.stData.idatalen =  1 + sizeof(long);
		stMsg.stData.pcdata = new char[stMsg.stData.idatalen];

		memcpy(stMsg.stData.pcdata, &lProcnum1, sizeof(lProcnum1));

		m_objUpgrade.SendCmd(&stMsg);
	}
}
#endif

void CUpgradetoolDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(IDC_BROWSE == nIDCtl|| IDOK == nIDCtl ||
		IDC_UPGRADE == nIDCtl|| IDC_ONOFF == nIDCtl)
	{
		draw(nIDCtl, lpDrawItemStruct);
	}

	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CUpgradetoolDlg::draw(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{    
	CDC ButtonDC;    
	CBitmap bitmapTrans;    
	BITMAP bmp;    
	CDC mem;    
	CRect rc;    //得到用于绘制按钮的DC    
	ButtonDC.Attach(lpDrawItemStruct->hDC);    
	//准备用于向按钮区域传输位图    
	mem.CreateCompatibleDC(&ButtonDC);    
	//获取按钮所占的矩形大小    
	rc=lpDrawItemStruct->rcItem;				 //获取按钮目前所处的状态，根据不同的状态绘制不同的按钮    
	UINT state = lpDrawItemStruct->itemState;    //如果按钮已经得到焦点，绘制选中状态下的按钮    
	if(state&ODS_SELECTED)    
	{        
		switch(nIDCtl)
		{
		case IDC_BROWSE:
			break;
		case IDOK:
			break;
		case IDC_UPGRADE:
			break;
		case IDC_ONOFF:
			break;
		default:
			break;
		}       
		bitmapTrans.GetBitmap(&bmp);        
		CBitmap *old=mem.SelectObject(&bitmapTrans);        //向按钮所在位置传输位图       
		//使用StretcnBlt的目的是为了让位图随按钮的大小而改变        
		ButtonDC.StretchBlt(rc.left,rc.top,rc.right,rc.bottom,&mem,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY); 
		mem.SelectObject(old);        
		bitmapTrans.DeleteObject();    
	}    
	else    
	{       
		switch(nIDCtl)
		{
		case IDC_BROWSE: 
			break;
		case IDOK:
			break;
		case IDC_UPGRADE: 
			break;
		case IDC_ONOFF:
			break;
		default:
			break;
		}           
		CBitmap *old2 = mem.SelectObject(&bitmapTrans);       
		bitmapTrans.GetBitmap(&bmp);        
		CBitmap *old=mem.SelectObject(&bitmapTrans);       
		ButtonDC.StretchBlt(rc.left,rc.top,rc.right,rc.bottom,&mem,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);        
		mem.SelectObject(old2);        
		bitmapTrans.DeleteObject();    
	}
}

HBRUSH CUpgradetoolDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性
	if (pWnd->GetDlgCtrlID() == (IDC_STATIC))
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(128,0,0));
		return HBRUSH(GetStockObject(HOLLOW_BRUSH));
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void CUpgradetoolDlg::InitListCtrl(void)
{
	LONG lStyle;
	lStyle = GetWindowLong(m_list.m_hWnd, GWL_STYLE);	//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK;							//清除显示方式位
	lStyle |= LVS_REPORT;								//设置style
	SetWindowLong(m_list.m_hWnd, GWL_STYLE, lStyle);	//设置style

	DWORD dwStyle = m_list.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;					//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;						//网格线（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_CHECKBOXES;						//item前生成checkbox控件
	dwStyle |= LVS_SHOWSELALWAYS;
	m_list.SetExtendedStyle(dwStyle);					//设置扩展风格

	//m_list.SetBkColor(RGB(177,151,240));
	//m_list.SetTextBkColor(RGB(177,151,240));
	//m_list.SetTextColor(RGB(0, 0, 255));

	m_list.InsertColumn( 0, "NO.", LVCFMT_LEFT, 40 );	
	m_list.InsertColumn( 1, "FileName", LVCFMT_LEFT, 240 );
	m_list.InsertColumn( 2, "Progress", LVCFMT_LEFT, 80 );

	OnEnChangeEdit1();
	UpdateListCtrl();

}

void CUpgradetoolDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CFileFind objFind;
	BOOL bExit = FALSE;
	memset(&m_stFileList, 0, sizeof(m_stFileList));
	m_stFileList.strDir = m_FileDir;
	if(SetCurrentDirectory(m_stFileList.strDir.data()) == FALSE)
	{
		return;
	}

	bExit = objFind.FindFile("*.upg");

	while(bExit)
	{
		bExit = objFind.FindNextFile();
		string strFile = objFind.GetFileName();
		m_stFileList.strFileList[m_stFileList.iFileNum++] = strFile;
	}

	UpdateListCtrl();
}

void CUpgradetoolDlg::UpdateListCtrl(void)
{
	stringstream ss;
	string str;

	UpdateData(TRUE);
	m_list.DeleteAllItems();
	for(int i=0; i<m_stFileList.iFileNum; i++)
	{
		ss.str("");
		ss << i+1;
		int iRow = m_list.InsertItem(i, ss.str().data());
		m_list.SetCheck(iRow, TRUE);
		m_list.SetItemText(iRow, 1, m_stFileList.strFileList[i].data());

		ss.str("");
		ss << m_stFileList.aiProgress[i];
		str = ss.str() + "  %";
		m_list.SetItemText(iRow, 2, str.data());
	}

	UpdateData(FALSE);
}

void UpdatelistProgress(void)
{
	CUpgradetoolDlg *pobjDlg = (CUpgradetoolDlg *)theApp.m_pMainWnd; 
	pobjDlg->Progress();
}

void CUpgradetoolDlg::Progress(void)
{
	stringstream ss;
	string str;
	PST_UPGRADE_FILE pstFile = (PST_UPGRADE_FILE)&m_stFileList;

	for(int i=0; i<pstFile->iFileNum; i++)
	{
		ss.str("");
		ss << i+1;
		ss.str("");
		ss << pstFile->aiProgress[i];
		str = ss.str() + "  %";
		m_list.SetItemText(i, 2, str.data());
	}
}

void CUpgradetoolDlg::OnBnClickedGetip()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	ST_SERVICE_CMD_DATA stMsg;
	memset(&stMsg, 0, sizeof(ST_SERVICE_CMD_DATA));
	theApp.m_pMainWnd->GetDlgItem(IDC_EDIT3)->ShowWindow(SW_NORMAL);

	if(m_bStatus)
	{
		stMsg.enServiceCode =  EN_GET_IP_CMD;
		m_objUpgrade.SendCmd(&stMsg);
	}
}
