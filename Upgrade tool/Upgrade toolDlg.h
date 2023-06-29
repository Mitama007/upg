// Upgrade toolDlg.h : 头文件
//

#pragma once
#include "UpgradeManager.h"
#include "afxcmn.h"
#include "afxext.h"



// CUpgradetoolDlg 对话框
class CUpgradetoolDlg : public CDialog
{
// 构造
public:
	CUpgradetoolDlg(CWnd* pParent = NULL);	// 标准构造函数

public:
	CUpgradeManager m_objUpgrade;



// 对话框数据
	enum { IDD = IDD_UPGRADETOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	HICON m_hIconLedRed;
	HICON m_hIconLedGreen;

private:
	ST_UPGRADE_FILE m_stFileList;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedUpgrade();

	// 升级文件目录,升级文件后缀为.upg
	CString m_FileDir;
	afx_msg void OnBnClickedFiledir();
	afx_msg void OnBnClickedButton4();
	CProgressCtrl m_ctrlProgress;
	bool m_bStatus;

	// 升级的进程数量
	long m_lProcNum;
	// 升级版本数量
	long m_lVerCount;
	afx_msg void OnBnClickedGetVersion();
	afx_msg void OnBnClickedGetVerCount();
	afx_msg void OnBnClickedRecovery();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	void draw(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void InitListCtrl(void);
	CListCtrl m_list;
	afx_msg void OnEnChangeEdit1();
	void UpdateListCtrl(void);
	void Progress(void);

	void ReSize();
	POINT old;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
	afx_msg void OnBnClickedGetip();
};
