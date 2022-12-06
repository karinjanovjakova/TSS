
// TSSDlg.h : header file
//

#pragma once
# include <vector>
# include<string>
# include<gdipluspen.h>
#include <thread>

class CStaticImage : public CStatic
{
public:
	void DrawItem(LPDRAWITEMSTRUCT plDrawItemStruct) override;
};

class CStaticHistogram : public CStatic
{
public:
	void DrawItem(LPDRAWITEMSTRUCT plDrawItemStruct) override;
};

typedef struct
{
	std::vector<double> R;
	std::vector<double> G;
	std::vector<double> B;
}Histo;

typedef struct
{
	CString FileName;
	CString FilePath;
	Histo Hist;
	int cHist=0;
	bool cHistStarted = false;
	bool c90 = false;
	bool c180 = false;
	bool c270 = false;
	bool c90start = false;
	bool c180start = false;
	bool c270start = false;
	Gdiplus::Bitmap* bitmap = nullptr;
	Gdiplus::Bitmap* bitmap90 = nullptr;
	Gdiplus::Bitmap* bitmap180 = nullptr;
	Gdiplus::Bitmap* bitmap270 = nullptr;
}FileInfo;


// CTSSDlg dialog
class CTSSDlg : public CDialogEx
{
// Construction
public:
	CMenu m_menu;

	CTSSDlg(CWnd* pParent = nullptr);	// standard constructor
	CStaticImage m_staticImage;
	CStaticHistogram m_staticHistogram;
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

	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;

	enum {
		WM_DRAW_IMAGE = WM_USER+1,
		WM_DRAW_HISTOGRAM = WM_USER+2
	};

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
	afx_msg void OnHistogramR();
	afx_msg void OnHistogramG();
	afx_msg void OnHistogramB();
	afx_msg void OnRotation0();
	afx_msg void OnRotation90();
	afx_msg void OnRotation180();
	afx_msg void OnRotation270();
	afx_msg void OnFileOpen();
	afx_msg void OnFileClose(); 
	afx_msg LRESULT OnDrawImage(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnDrawHist(WPARAM wparam, LPARAM lparam);
	afx_msg void OnDestroy();
	void CalcHistStruct(int index);
	void Calc90Struct(int index);
	void Calc180Struct(int index);
	void Calc270Struct(int index);

	afx_msg void OnLvnItemChangedFileList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnStnClickedStaticImage();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


