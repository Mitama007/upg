// Upgrade toolDlg.cpp : ʵ���ļ�
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




// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CUpgradetoolDlg �Ի���




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

// CUpgradetoolDlg ��Ϣ�������

BOOL CUpgradetoolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������


	m_hIconLedRed;
	m_hIconLedGreen;
	m_hIconLedRed= (HICON)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON1),IMAGE_ICON,40,40,LR_DEFAULTCOLOR);
	m_hIconLedGreen= (HICON)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON2),IMAGE_ICON,40,40,LR_DEFAULTCOLOR);	
	
	((CStatic*)GetDlgItem(IDC_LED))->SetIcon(m_hIconLedRed); 	

	//���ý������ķ�Χ
	m_ctrlProgress.SetRange(0,100);
	//���ý�������ÿһ��������
	m_ctrlProgress.SetStep(10);
	//���ý������ĵ�ǰλ��
	m_ctrlProgress.SetPos(0);

	m_objUpgrade.Init(UpdateOutputInfo, this);

	InitListCtrl();

	CRect rect;    
	GetClientRect(&rect);     //ȡ�ͻ�����С  
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CUpgradetoolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);	
	}
	else
	{
		//CPaintDC dc(this);
		//CBitmap   bitmap;
		//bitmap.LoadBitmap(IDB_BITMAP_BACK);    //���IDB_BITMAP1Ҫ�Լ����
		//CBrush   brush;
		//brush.CreatePatternBrush(&bitmap);
		//CBrush*   pOldBrush   =   dc.SelectObject(&brush);
		//dc.Rectangle(0,0,800,600);   // ��Щ�������Ե���ͼƬ���λ�úʹ�С
		//dc.SelectObject(pOldBrush);	

		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	POINT Newp; //��ȡ���ڶԻ���Ĵ�С
	CRect recta;    
	GetClientRect(&recta);     //ȡ�ͻ�����С  
	Newp.x=recta.right-recta.left;
	Newp.y=recta.bottom-recta.top;
	fsp[0]=(float)Newp.x/old.x;
	fsp[1]=(float)Newp.y/old.y;
	CRect Rect;
	int woc;
	CPoint OldTLPoint,TLPoint; //���Ͻ�
	CPoint OldBRPoint,BRPoint; //���½�
	HWND  hwndChild=::GetWindow(m_hWnd,GW_CHILD);  //�г����пؼ�  
	while(hwndChild)    
	{    
		woc=::GetDlgCtrlID(hwndChild);//ȡ��ID
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	m_bStatus = !m_bStatus;
	if(m_bStatus)
	{
		theApp.m_pMainWnd->GetDlgItem(IDC_ONOFF)->SetWindowText("�� ��");
			
		m_objUpgrade.m_objUpApi.m_aobjLow[0].SetId(EN_UPGRADE_MAIN_CTRL, 1);
		((CStatic*)GetDlgItem(IDC_LED))->SetIcon(m_hIconLedGreen); 
	}
	else
	{
		theApp.m_pMainWnd->GetDlgItem(IDC_ONOFF)->SetWindowText("�� ��");	
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	bResultClear = TRUE;
	bInfoClear = TRUE;

	theApp.m_pMainWnd->GetDlgItem(IDC_EDIT2)->SetWindowText(_T(""));

	CEdit* pedit = (CEdit*)theApp.m_pMainWnd->GetDlgItem(IDC_EDIT2);
	pedit->LineScroll(pedit->GetLineCount());

	theApp.m_pMainWnd->GetDlgItem(IDC_EDIT3)->SetWindowText(_T(""));

	pedit = (CEdit*)theApp.m_pMainWnd->GetDlgItem(IDC_EDIT3);
	pedit->LineScroll(pedit->GetLineCount());
}

#if 0	//	���Բ�ѯ����
void CUpgradetoolDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	CRect rc;    //�õ����ڻ��ư�ť��DC    
	ButtonDC.Attach(lpDrawItemStruct->hDC);    
	//׼��������ť������λͼ    
	mem.CreateCompatibleDC(&ButtonDC);    
	//��ȡ��ť��ռ�ľ��δ�С    
	rc=lpDrawItemStruct->rcItem;				 //��ȡ��ťĿǰ������״̬�����ݲ�ͬ��״̬���Ʋ�ͬ�İ�ť    
	UINT state = lpDrawItemStruct->itemState;    //�����ť�Ѿ��õ����㣬����ѡ��״̬�µİ�ť    
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
		CBitmap *old=mem.SelectObject(&bitmapTrans);        //��ť����λ�ô���λͼ       
		//ʹ��StretcnBlt��Ŀ����Ϊ����λͼ�水ť�Ĵ�С���ı�        
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

	// TODO:  �ڴ˸��� DC ���κ�����
	if (pWnd->GetDlgCtrlID() == (IDC_STATIC))
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(128,0,0));
		return HBRUSH(GetStockObject(HOLLOW_BRUSH));
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

void CUpgradetoolDlg::InitListCtrl(void)
{
	LONG lStyle;
	lStyle = GetWindowLong(m_list.m_hWnd, GWL_STYLE);	//��ȡ��ǰ����style
	lStyle &= ~LVS_TYPEMASK;							//�����ʾ��ʽλ
	lStyle |= LVS_REPORT;								//����style
	SetWindowLong(m_list.m_hWnd, GWL_STYLE, lStyle);	//����style

	DWORD dwStyle = m_list.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;					//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;						//�����ߣ�ֻ������report����listctrl��
	dwStyle |= LVS_EX_CHECKBOXES;						//itemǰ����checkbox�ؼ�
	dwStyle |= LVS_SHOWSELALWAYS;
	m_list.SetExtendedStyle(dwStyle);					//������չ���

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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
