
// TSSDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "TSS.h"
#include "TSSDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTSSDlg dialog



CTSSDlg::CTSSDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TSS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTSSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_IMAGE, m_staticImage);
	DDX_Control(pDX, IDC_STATIC_HISTOGRAM, m_staticHistogram);
	DDX_Control(pDX, IDC_FILE_LIST, m_fileList);
}

BEGIN_MESSAGE_MAP(CTSSDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	//ON_MESSAGE(WM_DRAW_IMAGE, OnDrawImage)
	//ON_MESSAGE(WM_DRAW_HISTOGRAM, OnDrawHist)
	ON_WM_QUERYDRAGICON()
	//ON_COMMAND(ID_MENU_FILE_OPEN, &CTSSDlg::OnMenuFileOpen)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_WM_TIMER()
	//ON_COMMAND(ID_HISTOGRAM_R, &CTSSDlg::OnHistogramR)
	//ON_COMMAND(ID_HISTOGRAM_G, &CTSSDlg::OnHistogramG)
	//ON_COMMAND(ID_HISTOGRAM_B, &CTSSDlg::OnHistogramB)
	//ON_COMMAND(ID_MENU_FILE_CLOSE, &CTSSDlg::OnMenuFileClose)
	//ON_NOTIFY(LVN_ITEMCHANGED,IDC_FILE_LIST1, &CTSSDlg::OnLvnItemChangedFileList1)
	//ON_COMMAND(ID_EFFECT_POSTER_16, &CTSSDlg::OnEffectPoster16)
	//ON_COMMAND(ID_EFFECT_POSTER_32, &CTSSDlg::OnEffectPoster32)
	//ON_COMMAND(ID_EFFECT_POSTER_48, &CTSSDlg::OnEffectPoster48)
	//ON_COMMAND(ID_EFFECT_POSTER_64, &CTSSDlg::OnEffectPoster64)
	//ON_COMMAND(ID_EFFECT_ORIGINAL, &CTSSDlg::OnEffectOriginal)
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_FILE_OPEN, &CTSSDlg::OnFileOpen)
	ON_COMMAND(ID_FILE_CLOSE, &CTSSDlg::OnFileClose)
END_MESSAGE_MAP()


// CTSSDlg message handlers

BOOL CTSSDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	GetClientRect(&rect);
	m_staticImage.GetWindowRect(&mrect);
	mstatic_Lborder = mrect.left;
	mstatic_Tborder = mrect.top;
	mstatic_Rborder = rect.right - mrect.right;
	mstatic_Bborder = rect.bottom - mrect.bottom;

	GetClientRect(&recth);
	m_staticHistogram.GetWindowRect(&mrecth);
	mstatich_Lborder = mrecth.left;
	mstatich_Tborder = mrecth.top;
	mstatich_Rborder = recth.right - mrecth.right;
	mstatich_Bborder = recth.bottom - mrecth.bottom;

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTSSDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTSSDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTSSDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTSSDlg::OnSize(UINT nType, int cx, int cy)
{
	//CRect rect;
	CDialogEx::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if (::IsWindow(this->m_staticImage))
	{
		this->m_staticHistogram.GetWindowRect(&rect);
		this->m_fileList.GetWindowRect(&mrect);
		this->m_staticImage.SetWindowPos(nullptr, 0, 0, cx-(rect.Width()+8)-30, cy - 30, SWP_NOMOVE);
		this->m_staticHistogram.SetWindowPos(nullptr, 0, 0, rect.Width(), cy-(mrect.Height()+10)-30, SWP_NOMOVE);
		Invalidate(1);
	}
}


BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CTSSDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI)
{
	//lpMMI->ptMinTrackSize.x = this->mrect.Width();
	//lpMMI->ptMinTrackSize.y = this->mrect.Height();
	lpMMI->ptMinTrackSize.x = 500;
	lpMMI->ptMinTrackSize.y = 400;
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}


/*
void CTSSDlg::OnSize(UINT nType, int cx, int cy)
{
	//CRect rect;

	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (::IsWindow(this->m_staticImage))
	{
		this->m_staticImage.GetClientRect(&mrect)
		this->m_staticHistogram.GetWindowRect(&rect);
		this->m_staticImage.SetWindowPos(nullptr, 0, 0, cx - rect.Width(), cy, SWP_NOMOVE);
		Invalidate(1);
	}
}*/

void CTSSDlg::OnFileOpen()
{
	CString FileName, FilePath;
	FileInfo file;
	TCHAR szFilters[] = _T(" BMP file(*.bmp) |*.bmp| JPG file(*.jpg) |*.jpg| PNG file(*.png) |*.png| | ");
	CFileDialog dlg(TRUE, _T(""), _T("*,*"), OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST, szFilters);
	if (dlg.DoModal() == IDOK)
	{

		POSITION pos = dlg.GetStartPosition();
		while (pos)
		{
			file.FilePath = dlg.GetNextPathName(pos);
			file.FileName = file.FilePath.Mid(file.FilePath.ReverseFind(_T('\\'))+1);
			m_loadedFiles.push_back(file);
			//AfxMessageBox(Name);
		}
	}
	m_fileList.DeleteAllItems();
	for (int i = 0; i < m_loadedFiles.size(); i++) {
		m_fileList.InsertItem(m_loadedFiles.size(), m_loadedFiles[i].FileName);
		m_fileList.Update(m_loadedFiles.size());
	}

}


void CTSSDlg::OnFileClose()
{
	int iCount = m_fileList.GetSelectedCount();
	int nIndex = -1;
	for (int i = 0; i < iCount; i++)
	{
		nIndex = m_fileList.GetNextItem(nIndex, LVNI_SELECTED);
		if (nIndex == -1)
			break;
		m_loadedFiles.erase(m_loadedFiles.begin() + int(nIndex) -i );
	}
	m_fileList.DeleteAllItems();
	for (int i = 0; i < m_loadedFiles.size(); i++) {
		m_fileList.InsertItem(m_loadedFiles.size(), m_loadedFiles[i].FileName);
		m_fileList.Update(m_loadedFiles.size());
	}
}
