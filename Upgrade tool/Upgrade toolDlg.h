// Upgrade toolDlg.h : ͷ�ļ�
//

#pragma once
#include "UpgradeManager.h"
#include "afxcmn.h"
#include "afxext.h"



// CUpgradetoolDlg �Ի���
class CUpgradetoolDlg : public CDialog
{
// ����
public:
	CUpgradetoolDlg(CWnd* pParent = NULL);	// ��׼���캯��

public:
	CUpgradeManager m_objUpgrade;



// �Ի�������
	enum { IDD = IDD_UPGRADETOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	HICON m_hIconLedRed;
	HICON m_hIconLedGreen;

private:
	ST_UPGRADE_FILE m_stFileList;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedUpgrade();

	// �����ļ�Ŀ¼,�����ļ���׺Ϊ.upg
	CString m_FileDir;
	afx_msg void OnBnClickedFiledir();
	afx_msg void OnBnClickedButton4();
	CProgressCtrl m_ctrlProgress;
	bool m_bStatus;

	// �����Ľ�������
	long m_lProcNum;
	// �����汾����
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
