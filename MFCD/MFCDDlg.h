
// MFCDDlg.h: 头文件
//

#pragma once


// CMFCDDlg 对话框
class CMFCDDlg : public CDialogEx
{
// 构造
public:
	CMFCDDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCD_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedBaocun();
	afx_msg void OnBnClickedHd();
	afx_msg void OnBnClickedBaocun2();
	afx_msg void OnBnClickedBaocun3();
	afx_msg void OnBnClickedHd5();
	afx_msg void OnBnClickedHd6();
	afx_msg void OnBnClickedHd2();
	afx_msg void OnBnClickedHd4();
	afx_msg void OnBnClickedHd3();
	afx_msg void OnBnClickedHd7();
};
