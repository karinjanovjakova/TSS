
// TSSDlg.h : header file
//

#pragma once
# include <vector>
# include<string>

typedef struct
{
	CString FileName;
	CString FilePath;

}FileInfo;


// CTSSDlg dialog
class CTSSDlg : public CDialogEx
{
// Construction
public:
	CTSSDlg(CWnd* pParent = nullptr);	// standard constructor
	CStatic m_staticImage;
	CStatic m_staticHistogram;
	CListCtrl m_fileList;

	CRect rect;
	CRect mrect;
	LONG mstatic_Lborder;
	LONG mstatic_Tborder;
	LONG mstatic_Rborder;
	LONG mstatic_Bborder;

	CRect recth;
	CRect mrecth;
	LONG mstatich_Lborder;
	LONG mstatich_Tborder;
	LONG mstatich_Rborder;
	LONG mstatich_Bborder;

	std::vector<FileInfo> m_loadedFiles;


// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TSS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnFileOpen();
	afx_msg void OnFileClose();
};
