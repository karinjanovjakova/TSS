
// TSSDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "TSS.h"
#include "TSSDlg.h"
#include "afxdialogex.h"
#include <gdiplus.h>

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif

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
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_WM_TIMER()
	ON_COMMAND(ID_HISTOGRAM_R, &CTSSDlg::OnHistogramR)
	ON_COMMAND(ID_HISTOGRAM_G, &CTSSDlg::OnHistogramG)
	ON_COMMAND(ID_HISTOGRAM_B, &CTSSDlg::OnHistogramB)
	ON_COMMAND(ID_ROTATION_ORIGINAL, &CTSSDlg::OnRotation0)
	ON_COMMAND(ID_ROTATION_90, &CTSSDlg::OnRotation90)
	ON_COMMAND(ID_ROTATION_180, &CTSSDlg::OnRotation180)
	ON_COMMAND(ID_ROTATION_270, &CTSSDlg::OnRotation270)
	ON_MESSAGE(WM_DRAW_IMAGE, OnDrawImage)
	ON_MESSAGE(WM_DRAW_HISTOGRAM, OnDrawHist)
	ON_NOTIFY(LVN_ITEMCHANGED,IDC_FILE_LIST, &CTSSDlg::OnLvnItemChangedFileList)
	//ON_COMMAND(ID_EFFECT_POSTER_16, &CTSSDlg::OnEffectPoster16)
	//ON_COMMAND(ID_EFFECT_POSTER_32, &CTSSDlg::OnEffectPoster32)
	//ON_COMMAND(ID_EFFECT_POSTER_48, &CTSSDlg::OnEffectPoster48)
	//ON_COMMAND(ID_EFFECT_POSTER_64, &CTSSDlg::OnEffectPoster64)
	//ON_COMMAND(ID_EFFECT_ORIGINAL, &CTSSDlg::OnEffectOriginal)
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_FILE_OPEN, &CTSSDlg::OnFileOpen)
	ON_COMMAND(ID_FILE_CLOSE, &CTSSDlg::OnFileClose)
	ON_WM_DESTROY()
	//ON_NOTIFY(HDN_ITEMCHANGED, 0, &CTSSDlg::OnItemchangedFileList)
	ON_STN_CLICKED(IDC_STATIC_IMAGE, &CTSSDlg::OnStnClickedStaticImage)
	ON_WM_TIMER()
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
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	m_loadedFiles.reserve(100);
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
	if (::IsWindow(m_staticImage) && ::IsWindow(m_staticHistogram))
	{
		this->m_staticHistogram.GetWindowRect(&rect);
		this->m_fileList.GetWindowRect(&mrect);
		this->m_staticImage.SetWindowPos(nullptr, 0, 0, cx-(rect.Width()+8)-30, cy - 30, SWP_NOMOVE);
		this->m_staticHistogram.SetWindowPos(nullptr, 0, 0, rect.Width(), cy-(mrect.Height()+10)-30, SWP_NOMOVE);
		Invalidate(1);
		m_staticHistogram.Invalidate(1);
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

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}

void CTSSDlg::OnRotation0() {
	CMenu* mmenu = GetMenu();
	CMenu* submenu = mmenu->GetSubMenu(2);

	MENUITEMINFO info;
	info.cbSize = sizeof(MENUITEMINFO); // must fill up this field
	info.fMask = MIIM_STATE;             // get the state of the menu item
	VERIFY(submenu->GetMenuItemInfo(ID_ROTATION_ORIGINAL, &info));

	if (info.fState & MF_CHECKED) {
		submenu->CheckMenuItem(ID_ROTATION_ORIGINAL, MF_CHECKED | MF_BYCOMMAND);
	}
	else {
		submenu->CheckMenuItem(ID_ROTATION_ORIGINAL, MF_CHECKED | MF_BYCOMMAND);
		submenu->CheckMenuItem(ID_ROTATION_90, MF_UNCHECKED | MF_BYCOMMAND);
		submenu->CheckMenuItem(ID_ROTATION_180, MF_UNCHECKED | MF_BYCOMMAND);
		submenu->CheckMenuItem(ID_ROTATION_270, MF_UNCHECKED | MF_BYCOMMAND);
	}
	Invalidate(1);
}

void CTSSDlg::OnRotation90() {
	CMenu* mmenu = GetMenu();
	CMenu* submenu = mmenu->GetSubMenu(2);

	MENUITEMINFO info;
	info.cbSize = sizeof(MENUITEMINFO); // must fill up this field
	info.fMask = MIIM_STATE;             // get the state of the menu item
	VERIFY(submenu->GetMenuItemInfo(ID_ROTATION_90, &info));
	if (info.fState & MF_CHECKED) {
		submenu->CheckMenuItem(ID_ROTATION_90, MF_UNCHECKED | MF_BYCOMMAND);
		submenu->CheckMenuItem(ID_ROTATION_ORIGINAL, MF_CHECKED | MF_BYCOMMAND);
	}
	else {
		submenu->CheckMenuItem(ID_ROTATION_ORIGINAL, MF_UNCHECKED | MF_BYCOMMAND);
		submenu->CheckMenuItem(ID_ROTATION_90, MF_CHECKED | MF_BYCOMMAND);
		submenu->CheckMenuItem(ID_ROTATION_180, MF_UNCHECKED | MF_BYCOMMAND);
		submenu->CheckMenuItem(ID_ROTATION_270, MF_UNCHECKED | MF_BYCOMMAND);
	}
	Invalidate(1);
}

void CTSSDlg::OnRotation180() {
	CMenu* mmenu = GetMenu();
	CMenu* submenu = mmenu->GetSubMenu(2);

	MENUITEMINFO info;
	info.cbSize = sizeof(MENUITEMINFO); // must fill up this field
	info.fMask = MIIM_STATE;             // get the state of the menu item
	VERIFY(submenu->GetMenuItemInfo(ID_ROTATION_180, &info));

	if (info.fState & MF_CHECKED) {
		submenu->CheckMenuItem(ID_ROTATION_180, MF_UNCHECKED | MF_BYCOMMAND);
		submenu->CheckMenuItem(ID_ROTATION_ORIGINAL, MF_CHECKED | MF_BYCOMMAND);
	}
	else {
		submenu->CheckMenuItem(ID_ROTATION_ORIGINAL, MF_UNCHECKED | MF_BYCOMMAND);
		submenu->CheckMenuItem(ID_ROTATION_90, MF_UNCHECKED | MF_BYCOMMAND);
		submenu->CheckMenuItem(ID_ROTATION_180, MF_CHECKED | MF_BYCOMMAND);
		submenu->CheckMenuItem(ID_ROTATION_270, MF_UNCHECKED | MF_BYCOMMAND);
	}
	Invalidate(1);
}

void CTSSDlg::OnRotation270() {
	CMenu* mmenu = GetMenu();
	CMenu* submenu = mmenu->GetSubMenu(2);

	MENUITEMINFO info;
	info.cbSize = sizeof(MENUITEMINFO); // must fill up this field
	info.fMask = MIIM_STATE;             // get the state of the menu item
	VERIFY(submenu->GetMenuItemInfo(ID_ROTATION_270, &info));

	if (info.fState & MF_CHECKED) {
		submenu->CheckMenuItem(ID_ROTATION_270, MF_UNCHECKED | MF_BYCOMMAND);
		submenu->CheckMenuItem(ID_ROTATION_ORIGINAL, MF_CHECKED | MF_BYCOMMAND);
	}
	else{
		submenu->CheckMenuItem(ID_ROTATION_ORIGINAL, MF_UNCHECKED | MF_BYCOMMAND);
		submenu->CheckMenuItem(ID_ROTATION_90, MF_UNCHECKED | MF_BYCOMMAND);
		submenu->CheckMenuItem(ID_ROTATION_180, MF_UNCHECKED | MF_BYCOMMAND);
		submenu->CheckMenuItem(ID_ROTATION_270, MF_CHECKED | MF_BYCOMMAND);
	}
	Invalidate(1);
}

void CTSSDlg::OnHistogramR() {
	CMenu* mmenu = GetMenu();
	CMenu* submenu = mmenu->GetSubMenu(1);

	MENUITEMINFO info;
	info.cbSize = sizeof(MENUITEMINFO); // must fill up this field
	info.fMask = MIIM_STATE;             // get the state of the menu item
	VERIFY(submenu->GetMenuItemInfo(ID_HISTOGRAM_R, &info));

	if (info.fState & MF_CHECKED) {
		submenu->CheckMenuItem(ID_HISTOGRAM_R, MF_UNCHECKED | MF_BYCOMMAND);
	}
	else {
		submenu->CheckMenuItem(ID_HISTOGRAM_R, MF_CHECKED | MF_BYCOMMAND);
	}
	Invalidate(1);
}

void CTSSDlg::OnHistogramG() {
	CMenu* mmenu = GetMenu();
	CMenu* submenu = mmenu->GetSubMenu(1);

	MENUITEMINFO info;
	info.cbSize = sizeof(MENUITEMINFO); // must fill up this field
	info.fMask = MIIM_STATE;             // get the state of the menu item
	VERIFY(submenu->GetMenuItemInfo(ID_HISTOGRAM_G, &info));

	if (info.fState & MF_CHECKED) {
		submenu->CheckMenuItem(ID_HISTOGRAM_G, MF_UNCHECKED | MF_BYCOMMAND);
	}
	else {
		submenu->CheckMenuItem(ID_HISTOGRAM_G, MF_CHECKED | MF_BYCOMMAND);
	}
	Invalidate(1);
}

void CTSSDlg::OnHistogramB() {
	CMenu* mmenu = GetMenu();
	CMenu* submenu = mmenu->GetSubMenu(1);

	MENUITEMINFO info;
	info.cbSize = sizeof(MENUITEMINFO); // must fill up this field
	info.fMask = MIIM_STATE;             // get the state of the menu item
	VERIFY(submenu->GetMenuItemInfo(ID_HISTOGRAM_B, &info));

	if (info.fState & MF_CHECKED) {
		submenu->CheckMenuItem(ID_HISTOGRAM_B, MF_UNCHECKED | MF_BYCOMMAND);
	}
	else {
		submenu->CheckMenuItem(ID_HISTOGRAM_B, MF_CHECKED | MF_BYCOMMAND);
	}
	Invalidate(1);
}

void CTSSDlg::OnFileOpen()
{
	CString FileName, FilePath;
	FileInfo file;
	TCHAR szFilters[] = _T(" BMP file(*.bmp) |*.bmp| JPG file(*.jpg) |*.jpg| PNG file(*.png) |*.png|| ");
	CFileDialog dlg(TRUE, _T(""), _T(""), OFN_ALLOWMULTISELECT|OFN_FILEMUSTEXIST, szFilters);
	if (dlg.DoModal() == IDOK)
	{
		POSITION pos = dlg.GetStartPosition();
		while (pos)
		{
			file.FilePath = dlg.GetNextPathName(pos);
			file.FileName = file.FilePath.Mid(file.FilePath.ReverseFind(_T('\\'))+1);
			file.bitmap = Gdiplus::Bitmap::FromFile(file.FilePath);
			int already_loaded = 0;
			for (int i = 0; i < m_loadedFiles.size(); i++)
			{
				if (m_loadedFiles[i].FileName == file.FileName)
					already_loaded += 1;
			}
			if (already_loaded == 0)
				m_loadedFiles.push_back(file);
			else 
				AfxMessageBox(file.FileName + _T(" is already open."));
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
	bool calculating=false;
	for (int i = 0; i < m_loadedFiles.size(); i++) {
		if (m_loadedFiles[i].cHistStarted || m_loadedFiles[i].c90start || m_loadedFiles[i].c180start || m_loadedFiles[i].c270start)
			calculating = true;
	}
	if (calculating) {
		AfxMessageBox(_T("Unable to close files. Try again later."));
		return;
	}

	 iCount = m_fileList.GetSelectedCount();
	 nIndex = -1;
	for (int i = 0; i < iCount; i++)
	{
		nIndex = m_fileList.GetNextItem(nIndex, LVNI_SELECTED);
		if (nIndex == -1)
			break;
		m_loadedFiles.erase(m_loadedFiles.begin() + int(nIndex) - i);
	}
	m_fileList.DeleteAllItems();
	for (int i = 0; i < m_loadedFiles.size(); i++) {
		m_fileList.InsertItem(m_loadedFiles.size(), m_loadedFiles[i].FileName);
		m_fileList.Update(m_loadedFiles.size());
	}
	m_fileList.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);
	OnRotation0();
	Invalidate(1);
}

void CStaticImage::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	GetParent()->SendMessage(CTSSDlg::WM_DRAW_IMAGE, (WPARAM) lpDrawItemStruct);
}

void CStaticHistogram::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	GetParent()->SendMessage(CTSSDlg::WM_DRAW_HISTOGRAM, (WPARAM) lpDrawItemStruct);
}

/*LRESULT CTSSDlg::OnDrawImage(WPARAM wParam, LPARAM lparam) {
	LPDRAWITEMSTRUCT lpDI = (LPDRAWITEMSTRUCT)wParam;
	if (lpDI == nullptr)
		return LRESULT();
	Gdiplus::Graphics* GraphCDC = Gdiplus::Graphics::FromHDC(lpDI->hDC);
	int nIndex = -1;
	nIndex = m_fileList.GetNextItem(nIndex, LVNI_SELECTED);
	if (nIndex != -1) {		
		bool orig = FALSE, rot90 = FALSE, rot180 = FALSE, rot270 = FALSE;		//zistíme ako otoèený obrázok chceme vykresli
		CMenu* mmenu = GetMenu();
		MENUITEMINFO info;
		info.cbSize = sizeof(MENUITEMINFO);
		info.fMask = MIIM_STATE;
		VERIFY(mmenu->GetSubMenu(2)->GetMenuItemInfo(ID_ROTATION_ORIGINAL, &info));
		if (info.fState & MF_CHECKED) {//originál sa vykreslí
			orig = TRUE;
		}
		VERIFY(mmenu->GetSubMenu(2)->GetMenuItemInfo(ID_ROTATION_90, &info));
		if (info.fState & MF_CHECKED) {//rotacia o 90 sa vykres¾uje.
			rot90 = TRUE;
		}
		VERIFY(mmenu->GetSubMenu(2)->GetMenuItemInfo(ID_ROTATION_180, &info));
		if (info.fState & MF_CHECKED) {//rotacia o 180 sa vykres¾uje. 
			rot180 = TRUE;
		}
		VERIFY(mmenu->GetSubMenu(2)->GetMenuItemInfo(ID_ROTATION_270, &info));
		if (info.fState & MF_CHECKED) {//rotacia o 270 sa vykres¾uje. 
			rot270 = TRUE;
		}
		
		m_staticImage.GetWindowRect(&rect);
		double height = rect.Height();
		double width = rect.Width();
		double heightI = m_loadedFiles[nIndex].bitmap->GetHeight();
		double widthI = m_loadedFiles[nIndex].bitmap->GetWidth();
		
		if (orig) {
			if ((height / heightI) * widthI > width) {
				GraphCDC->DrawImage(m_loadedFiles[nIndex].bitmap, 0, 0, width, (width / widthI) * heightI);
			}
			if ((width / widthI) * heightI > height)
				GraphCDC->DrawImage(m_loadedFiles[nIndex].bitmap, 0, 0, (height / heightI) * widthI, height);
		}
		if (rot90) {
			m_loadedFiles[nIndex].bitmap->RotateFlip(Gdiplus::Rotate90FlipNone);
			if ((height / widthI) * heightI > width) 
				GraphCDC->DrawImage(m_loadedFiles[nIndex].bitmap, 0, 0, width, (width / heightI) * widthI);
			if ((width / heightI) * widthI > height)
				GraphCDC->DrawImage(m_loadedFiles[nIndex].bitmap, 0, 0, (height / widthI) * heightI, height);
			m_loadedFiles[nIndex].bitmap->RotateFlip(Gdiplus::Rotate270FlipNone);
		}
		if (rot180) {
			m_loadedFiles[nIndex].bitmap->RotateFlip(Gdiplus::Rotate180FlipNone);
			if ((height / heightI) * widthI > width) 
				GraphCDC->DrawImage(m_loadedFiles[nIndex].bitmap, 0, 0, width, (width / widthI) * heightI);
			if ((width / widthI) * heightI > height)
				GraphCDC->DrawImage(m_loadedFiles[nIndex].bitmap, 0, 0, (height / heightI) * widthI, height);
			m_loadedFiles[nIndex].bitmap->RotateFlip(Gdiplus::Rotate180FlipNone);
		}
		if (rot270) {
			m_loadedFiles[nIndex].bitmap->RotateFlip(Gdiplus::Rotate270FlipNone);
			if ((height / widthI) * heightI > width) 
				GraphCDC->DrawImage(m_loadedFiles[nIndex].bitmap, 0, 0, width, (width / heightI) * widthI);
			if ((width / heightI) * widthI > height)
				GraphCDC->DrawImage(m_loadedFiles[nIndex].bitmap, 0, 0, (height / widthI) * heightI, height);
			m_loadedFiles[nIndex].bitmap->RotateFlip(Gdiplus::Rotate90FlipNone);
		}
	}
	return LRESULT();

}*/

LRESULT CTSSDlg::OnDrawImage(WPARAM wParam, LPARAM lparam) {
	LPDRAWITEMSTRUCT lpDI = (LPDRAWITEMSTRUCT)wParam;
	if (lpDI == nullptr)
		return LRESULT();
	Gdiplus::Graphics* GraphCDC = Gdiplus::Graphics::FromHDC(lpDI->hDC);
	int nIndex = -1;
	nIndex = m_fileList.GetNextItem(nIndex, LVNI_SELECTED);
	if (nIndex != -1) {
		bool orig = FALSE, rot90 = FALSE, rot180 = FALSE, rot270 = FALSE;		//zistíme ako otoèený obrázok chceme vykresli
		CMenu* mmenu = GetMenu();
		MENUITEMINFO info;
		info.cbSize = sizeof(MENUITEMINFO);
		info.fMask = MIIM_STATE;
		VERIFY(mmenu->GetSubMenu(2)->GetMenuItemInfo(ID_ROTATION_ORIGINAL, &info));
		if (info.fState & MF_CHECKED) {//originál sa vykreslí
			orig = TRUE;
		}
		VERIFY(mmenu->GetSubMenu(2)->GetMenuItemInfo(ID_ROTATION_90, &info));
		if (info.fState & MF_CHECKED) {//rotacia o 90 sa vykres¾uje.
			rot90 = TRUE;
		}
		VERIFY(mmenu->GetSubMenu(2)->GetMenuItemInfo(ID_ROTATION_180, &info));
		if (info.fState & MF_CHECKED) {//rotacia o 180 sa vykres¾uje. 
			rot180 = TRUE;
		}
		VERIFY(mmenu->GetSubMenu(2)->GetMenuItemInfo(ID_ROTATION_270, &info));
		if (info.fState & MF_CHECKED) {//rotacia o 270 sa vykres¾uje. 
			rot270 = TRUE;
		}
				
		m_staticImage.GetWindowRect(&rect);
		double height = rect.Height();
		double width = rect.Width();
		double heightI, widthI;


		if (orig) {
			heightI = m_loadedFiles[nIndex].bitmap->GetHeight();
			widthI = m_loadedFiles[nIndex].bitmap->GetWidth();
			if ((height / heightI) * widthI > width) {
				GraphCDC->DrawImage(m_loadedFiles[nIndex].bitmap, 0, 0, width, (width / widthI) * heightI);
			}
			if ((width / widthI) * heightI > height)
				GraphCDC->DrawImage(m_loadedFiles[nIndex].bitmap, 0, 0, (height / heightI) * widthI, height);
		}
		if (rot90) {
			if (!m_loadedFiles[nIndex].c90 && !m_loadedFiles[nIndex].c90start) {
				int timer = int(SetTimer(nIndex + 101, 1000, NULL));
				if (timer != 0) {
					std::thread calc(&CTSSDlg::Calc90Struct, this, nIndex);
					calc.detach();
				}
			}
			if (m_loadedFiles[nIndex].c90) {
				//vykreslenie
				heightI = m_loadedFiles[nIndex].bitmap90->GetHeight();
				widthI = m_loadedFiles[nIndex].bitmap90->GetWidth();
				if ((height / heightI) * widthI > width) {
					GraphCDC->DrawImage(m_loadedFiles[nIndex].bitmap90, 0, 0, width, (width / widthI) * heightI);
				}
				if ((width / widthI) * heightI > height)
					GraphCDC->DrawImage(m_loadedFiles[nIndex].bitmap90, 0, 0, (height / heightI) * widthI, height);
			}

		}
		if (rot180) {
			if (!m_loadedFiles[nIndex].c180 && !m_loadedFiles[nIndex].c180start) {
				int timer = int(SetTimer(nIndex + 201, 1000, NULL));
				if (timer != 0) {
					std::thread calc(&CTSSDlg::Calc180Struct, this, nIndex);
					calc.detach();
				}
			}
			if (m_loadedFiles[nIndex].c180) {
				//vykreslenie
				heightI = m_loadedFiles[nIndex].bitmap180->GetHeight();
				widthI = m_loadedFiles[nIndex].bitmap180->GetWidth();
				if ((height / heightI) * widthI > width) {
					GraphCDC->DrawImage(m_loadedFiles[nIndex].bitmap180, 0, 0, width, (width / widthI) * heightI);
				}
				if ((width / widthI) * heightI > height)
					GraphCDC->DrawImage(m_loadedFiles[nIndex].bitmap180, 0, 0, (height / heightI) * widthI, height);
			}

		}
		
		if (rot270) {
			if (!m_loadedFiles[nIndex].c270 && !m_loadedFiles[nIndex].c270start) {
				int timer = int(SetTimer(nIndex + 201, 1000, NULL));
				if (timer != 0) {
					std::thread calc(&CTSSDlg::Calc270Struct, this, nIndex);
					calc.detach();
				}
			}
			if (m_loadedFiles[nIndex].c270) {
				//vykreslenie
				heightI = m_loadedFiles[nIndex].bitmap270->GetHeight();
				widthI = m_loadedFiles[nIndex].bitmap270->GetWidth();
				if ((height / heightI) * widthI > width) {
					GraphCDC->DrawImage(m_loadedFiles[nIndex].bitmap270, 0, 0, width, (width / widthI) * heightI);
				}
				if ((width / widthI) * heightI > height)
					GraphCDC->DrawImage(m_loadedFiles[nIndex].bitmap270, 0, 0, (height / heightI) * widthI, height);
			}

		}
	}
	return LRESULT();

}



void CTSSDlg::Calc90Struct(int nIndex) {
	m_loadedFiles[nIndex].c90start = TRUE;
	m_staticImage.GetWindowRect(&rect);
	double height = rect.Height();
	double width = rect.Width();
	double heightI = m_loadedFiles[nIndex].bitmap->GetHeight();
	double widthI = m_loadedFiles[nIndex].bitmap->GetWidth();


	Gdiplus::Rect bmpRect(0, 0, m_loadedFiles[nIndex].bitmap->GetWidth(), m_loadedFiles[nIndex].bitmap->GetHeight());
	Gdiplus::Bitmap* bitmap ;
	bitmap = Gdiplus::Bitmap::FromFile(m_loadedFiles[nIndex].FilePath);

	Gdiplus::BitmapData bmpData;
	unsigned int* pBmpScan;
	unsigned int bmpPixel;
	unsigned int bmpStride;
	bitmap->LockBits(&bmpRect, Gdiplus::ImageLockModeRead, PixelFormat32bppARGB, &bmpData);
	pBmpScan = (unsigned int*)bmpData.Scan0;
	bmpStride = bmpData.Stride;

	//bitmap->
	Gdiplus::Bitmap* image = new Gdiplus::Bitmap(heightI, widthI, PixelFormat32bppARGB);
	Gdiplus::BitmapData bmpData2;
	Gdiplus::Rect bmpRect2(0, 0, image->GetWidth(), image->GetHeight());
	unsigned int* pBmpScan2;
	unsigned int bmpStride2;
	
	image->LockBits(&bmpRect2, Gdiplus::ImageLockModeWrite, PixelFormat32bppARGB, &bmpData2);
	pBmpScan2 = (unsigned int*)bmpData2.Scan0;
	bmpStride2 = bmpData2.Stride;
	for (int j = 0; j < (int)bitmap->GetHeight(); j++) {
		for (int i = 0; i < (int)bitmap->GetWidth(); i++) {
			bmpPixel = pBmpScan[((int)bitmap->GetHeight() - 1 - j) * (int)bmpStride / 4 + i];
			pBmpScan2[i * (int)bmpStride2 / 4 + j] = bmpPixel;
		}
	}
	bitmap->UnlockBits(&bmpData);
	image->UnlockBits(&bmpData2); 
	m_loadedFiles[nIndex].bitmap90 = image; 
	m_loadedFiles[nIndex].c90=TRUE;
	m_loadedFiles[nIndex].c90start = FALSE;
	delete[] bitmap;
}


void CTSSDlg::Calc180Struct(int nIndex) {
	m_loadedFiles[nIndex].c180start = TRUE;

	m_staticImage.GetWindowRect(&rect);
	double height = rect.Height();
	double width = rect.Width();
	double heightI = m_loadedFiles[nIndex].bitmap->GetHeight();
	double widthI = m_loadedFiles[nIndex].bitmap->GetWidth();


	Gdiplus::Rect bmpRect(0, 0, m_loadedFiles[nIndex].bitmap->GetWidth(), m_loadedFiles[nIndex].bitmap->GetHeight());
	Gdiplus::Bitmap* bitmap;
	bitmap = Gdiplus::Bitmap::FromFile(m_loadedFiles[nIndex].FilePath);

	Gdiplus::BitmapData bmpData;
	unsigned int* pBmpScan;
	unsigned int bmpPixel;
	unsigned int bmpStride;
	bitmap->LockBits(&bmpRect, Gdiplus::ImageLockModeRead, PixelFormat32bppARGB, &bmpData);
	pBmpScan = (unsigned int*)bmpData.Scan0;
	bmpStride = bmpData.Stride;

	Gdiplus::Bitmap* image = new Gdiplus::Bitmap(widthI,heightI, PixelFormat32bppARGB);
	Gdiplus::BitmapData bmpData2;
	Gdiplus::Rect bmpRect2(0, 0, image->GetWidth(), image->GetHeight());
	unsigned int* pBmpScan2;
	unsigned int bmpStride2;
	image->LockBits(&bmpRect2, Gdiplus::ImageLockModeWrite, PixelFormat32bppARGB, &bmpData2);
	pBmpScan2 = (unsigned int*)bmpData2.Scan0;
	bmpStride2 = bmpData2.Stride;
	for (int j = 0; j < (int)bitmap->GetHeight(); j++) {
		for (int i = 0; i < (int)bitmap->GetWidth(); i++) {
			bmpPixel = pBmpScan[j * (int)bmpStride / 4 + i];
			pBmpScan2[((int)bitmap->GetHeight() - 1 - j) * (int)bmpStride2 / 4 + ((int)bitmap->GetWidth() - 1 - i)] = bmpPixel;
		}
	}
	bitmap->UnlockBits(&bmpData);
	image->UnlockBits(&bmpData2);

	m_loadedFiles[nIndex].bitmap180 = image;
	m_loadedFiles[nIndex].c180 = TRUE;
	m_loadedFiles[nIndex].c180start = FALSE;
	delete[] bitmap;
}

void CTSSDlg::Calc270Struct(int nIndex) {
	m_loadedFiles[nIndex].c270start = TRUE;
	m_staticImage.GetWindowRect(&rect);
	double height = rect.Height();
	double width = rect.Width();
	double heightI = m_loadedFiles[nIndex].bitmap->GetHeight();
	double widthI = m_loadedFiles[nIndex].bitmap->GetWidth();


	Gdiplus::Rect bmpRect(0, 0, m_loadedFiles[nIndex].bitmap->GetWidth(), m_loadedFiles[nIndex].bitmap->GetHeight());
	Gdiplus::Bitmap* bitmap;
	bitmap = Gdiplus::Bitmap::FromFile(m_loadedFiles[nIndex].FilePath);

	Gdiplus::BitmapData bmpData;
	unsigned int* pBmpScan;
	unsigned int bmpPixel;
	unsigned int bmpStride;
	bitmap->LockBits(&bmpRect, Gdiplus::ImageLockModeRead, PixelFormat32bppARGB, &bmpData);
	pBmpScan = (unsigned int*)bmpData.Scan0;
	bmpStride = bmpData.Stride;

	//bitmap->
	Gdiplus::Bitmap* image = new Gdiplus::Bitmap(heightI, widthI, PixelFormat32bppARGB);
	Gdiplus::BitmapData bmpData2;
	Gdiplus::Rect bmpRect2(0, 0, image->GetWidth(), image->GetHeight());
	unsigned int* pBmpScan2;
	unsigned int bmpStride2;
	image->LockBits(&bmpRect2, Gdiplus::ImageLockModeWrite, PixelFormat32bppARGB, &bmpData2);
	pBmpScan2 = (unsigned int*)bmpData2.Scan0;
	bmpStride2 = bmpData2.Stride;
	image->LockBits(&bmpRect2, Gdiplus::ImageLockModeWrite, PixelFormat32bppARGB, &bmpData2);
	pBmpScan2 = (unsigned int*)bmpData2.Scan0;
	bmpStride2 = bmpData2.Stride;
	for (int j = 0; j < (int)bitmap->GetHeight(); j++) {
		for (int i = 0; i < (int)bitmap->GetWidth(); i++) {
			bmpPixel = pBmpScan[j * (int)bmpStride / 4 + ((int)bitmap->GetWidth() - 1 - i)];
			pBmpScan2[i * (int)bmpStride2 / 4 + j] = bmpPixel;
		}
	}
	bitmap->UnlockBits(&bmpData);
	image->UnlockBits(&bmpData2);

	m_loadedFiles[nIndex].bitmap270 = image;
	m_loadedFiles[nIndex].c270 = TRUE;
	m_loadedFiles[nIndex].c270start = FALSE;
	delete[] bitmap;
}




LRESULT CTSSDlg::OnDrawHist(WPARAM wParam, LPARAM lparam) {
	double width;
	double height;
	bool r=FALSE , g = FALSE, b = FALSE;
	int maxr=0, maxg=0, maxb=0, max=0;
	LPDRAWITEMSTRUCT lpDI = (LPDRAWITEMSTRUCT)wParam;
	if (lpDI == nullptr)
		return LRESULT();

	CMenu* mmenu = GetMenu();
	MENUITEMINFO info;
	info.cbSize = sizeof(MENUITEMINFO);

	info.fMask = MIIM_STATE;             

	Gdiplus::Graphics* GraphCDC = Gdiplus::Graphics::FromHDC(lpDI->hDC);
	int nIndex = -1;
	int countH = 0;
	VERIFY(mmenu->GetSubMenu(1)->GetMenuItemInfo(ID_HISTOGRAM_R, &info));
	if (info.fState & MF_CHECKED) {//R sa vykres¾uje.
		countH++;
		r = TRUE;
	}
	VERIFY(mmenu->GetSubMenu(1)->GetMenuItemInfo(ID_HISTOGRAM_G, &info));
	if (info.fState & MF_CHECKED) {//G sa vykres¾uje.
		countH++;
		g = TRUE;
	}
	VERIFY(mmenu->GetSubMenu(1)->GetMenuItemInfo(ID_HISTOGRAM_B, &info));
	if (info.fState & MF_CHECKED) {//B sa vykres¾uje. 
		countH++;
		b = TRUE;
	}
	nIndex = m_fileList.GetNextItem(nIndex, LVNI_SELECTED);
	if (nIndex != -1 && countH > 0) {
		if (m_loadedFiles[nIndex].cHist == 0 && m_loadedFiles[nIndex].cHistStarted == false) {
			//CalcHistStruct(nIndex);
			int timer = int(SetTimer(nIndex + 1, 1000, NULL));
			if (timer != 0) {
				std:: thread calc(&CTSSDlg::CalcHistStruct, this, nIndex);
				calc.detach();
			}
		}
	}
	if (nIndex != -1 && countH > 0 && m_loadedFiles[nIndex].cHist == 1 && m_loadedFiles[nIndex].cHistStarted == false) {
		if (r) {//R sa vykres¾uje. Pozrieme aká je max hodnota.
			maxr = 0;
			for (int i = 0; i < m_loadedFiles[nIndex].Hist.R.size(); i++) {
				if (maxr < m_loadedFiles[nIndex].Hist.R[i])
					maxr = m_loadedFiles[nIndex].Hist.R[i];
			}
			TRACE(_T("\n\n maxR= %d \n\n"), maxr);
		}
		if (g) {//G sa vykres¾uje. Pozrieme aká je max hodnota.
			maxg = 0;
			for (int i = 0; i < m_loadedFiles[nIndex].Hist.G.size(); i++) {
				if (maxg < m_loadedFiles[nIndex].Hist.G[i])
					maxg = m_loadedFiles[nIndex].Hist.G[i];
			}
			TRACE(_T("\n\n maxG= %d \n\n"), maxg);
		}
		if (b) {//B sa vykres¾uje. Pozrieme aká je max hodnota.
			maxb = 0;
			for (int i = 0; i < m_loadedFiles[nIndex].Hist.B.size(); i++) {
				if (maxb < m_loadedFiles[nIndex].Hist.B[i])
					maxb = m_loadedFiles[nIndex].Hist.B[i];
			}
			TRACE(_T("\n\n maxB= %d \n\n"), maxb);
		}
		
		if (maxr >= maxg) {
			if (maxr >= maxb)
				max = maxr;
			if (maxr <= maxb)
				max = maxb;
		}
		if (maxg >= maxr) {
			if (maxg <= maxb)
				max = maxb;
			if (maxg >= maxb)
				max = maxg;
		}

		TRACE(_T("\n\n absolútny max= %d \n\n"), max);

		m_staticHistogram.GetWindowRect(&rect);
		double height= rect.Height();
		double width = rect.Width();
		TRACE(_T("\n\n šírka histogramu je  %f \n výška histogramu je  %f \n\n"), width, height );;


		//tu preškálujeme a pustíme sa do kreslenia
		double scaleY=0, scaleX=0;
		scaleX =  width/256.0;
		scaleY =  (height - 5.0)/max;
		TRACE(_T("\n\n scaleX je  %f \n scaleY je  %f \n\n"), scaleX, scaleY);

		Gdiplus::Pen  pen(Gdiplus::Color(255, 255, 0, 0), 0.5f);
		                               
		if (r) {//R sa vykres¾uje.
			pen.SetColor(Gdiplus::Color(255, 255, 0, 0));
			for (int i = 1; i <= 255; i++) {
				Gdiplus::PointF A;
				A.X = scaleX * (i-1);
				A.Y = height - (scaleY * m_loadedFiles[nIndex].Hist.R[i - 1]);
				Gdiplus::PointF B;
				B.X = scaleX * i;
				B.Y = height - (scaleY * m_loadedFiles[nIndex].Hist.R[i]);
				GraphCDC->DrawLine(&pen, A, B);
			}
		}
		if (g) {//G sa vykres¾uje.
			pen.SetColor(Gdiplus::Color(255, 0, 255, 0));
			for (int i = 1; i <= 255; i++) {
				Gdiplus::PointF A;
				A.X = scaleX * (i - 1);
				A.Y = height - (scaleY * m_loadedFiles[nIndex].Hist.G[i - 1]);
				Gdiplus::PointF B;
				B.X = scaleX * i;
				B.Y = height - (scaleY * m_loadedFiles[nIndex].Hist.G[i]);
				GraphCDC->DrawLine(&pen, A, B);
			}
			TRACE(_T("G sa vykresli"));
		}
		if (b) {//B sa vykres¾uje.
			pen.SetColor(Gdiplus::Color(255, 0, 0, 255));
			for (int i = 1; i <= 255; i++) {
				Gdiplus::PointF A;
				A.X = scaleX * (i - 1);
				A.Y = height - (scaleY * m_loadedFiles[nIndex].Hist.B[i - 1]);
				Gdiplus::PointF B;
				B.X = scaleX * i;
				B.Y = height - (scaleY * m_loadedFiles[nIndex].Hist.B[i]);
				GraphCDC->DrawLine(&pen, A, B);
			}
		}
	}
	return LRESULT();
}

/*void CTSSDlg::CalcHistStruct(int nIndex) {
	FileInfo* file;
	//AfxMessageBox(_T("Wooo histogram!!"));
	file = &m_loadedFiles[nIndex];
	file->cHistStarted = true;
	
	Gdiplus::BitmapData bmpData;
	Gdiplus::Rect bmpRect(0, 0, file->bitmap->GetWidth(), file->bitmap->GetHeight());

	Gdiplus::Bitmap* bitmap = file->bitmap->Clone(bmpRect, PixelFormat32bppARGB);
	unsigned int* pBmpScan;
	unsigned int bmpPixel;
	unsigned int bmpStride;
	file->bitmap->LockBits(&bmpRect, Gdiplus::ImageLockModeRead, PixelFormat32bppARGB, &bmpData);
	file->Hist.R.resize(256, 0);
	file->Hist.G.resize(256, 0);
	file->Hist.B.resize(256, 0);
	int r, g, b;
	pBmpScan = (unsigned int*)bmpData.Scan0;
	bmpStride = bmpData.Stride;
	for (int j = 0; j < (int)file->bitmap->GetHeight(); j++) {
		for (int i = 0; i < (int)file->bitmap->GetWidth(); i++) {
			//Sleep(5);
			bmpPixel = pBmpScan[j * (int)bmpStride / 4 + i];
			b=(bmpPixel & 0xff) ;
			g=(bmpPixel & 0xff00) >> 8;
			r=(bmpPixel & 0xff0000) >> 16;
			file->Hist.B[b] += 1;
			file->Hist.G[g] += 1;
			file->Hist.R[r] += 1;
		}
	}
	file->cHist = 1;
	file->cHistStarted = false;
	file->bitmap->UnlockBits(&bmpData);
}*/

void CTSSDlg::CalcHistStruct(int nIndex) {
	FileInfo* file;
	//AfxMessageBox(_T("Wooo histogram!!"));
	file = &m_loadedFiles[nIndex];
	file->cHistStarted = true;

	Gdiplus::BitmapData bmpData;
	Gdiplus::Rect bmpRect(0, 0, file->bitmap->GetWidth(), file->bitmap->GetHeight());

	Gdiplus::Bitmap* bitmap;
	bitmap = Gdiplus::Bitmap::FromFile(m_loadedFiles[nIndex].FilePath);
	unsigned int* pBmpScan;
	unsigned int bmpPixel;
	unsigned int bmpStride;
	if (bitmap == NULL) {
		int pos = nIndex + 1;
		file->cHistStarted = false;
		KillTimer(pos);
		CString temp;
		temp.Format(L"%d", pos);
		AfxMessageBox(_T("Computing histogram failed. Try again for picture on position ") + temp);
		return;
	}
	bitmap->LockBits(&bmpRect, Gdiplus::ImageLockModeRead, PixelFormat32bppARGB, &bmpData); 
	/*Histo Hist;
	Hist.R.resize(256, 0);
	Hist.G.resize(256, 0);
	Hist.B.resize(256, 0);*/

	std::vector<double> R;
	std::vector<double> G;
	std::vector<double> B;
	R.resize(256, 0);
	G.resize(256, 0);
	B.resize(256, 0);
	int r, g, b;
	pBmpScan = (unsigned int*)bmpData.Scan0;
	bmpStride = bmpData.Stride;
	for (int j = 0; j < (int)bitmap->GetHeight(); j++) {
		for (int i = 0; i < (int)bitmap->GetWidth(); i++) {
			//Sleep(5);
			bmpPixel = pBmpScan[j * (int)bmpStride / 4 + i];
			b = (bmpPixel & 0xff);
			g = (bmpPixel & 0xff00) >> 8;
			r = (bmpPixel & 0xff0000) >> 16;
			B[b] += 1;
			G[g] += 1;
			R[r] += 1;
		}
	}
	file->Hist.R = R;
	file->Hist.G = G;
	file->Hist.B = B;
	file->cHist = 1;
	file->cHistStarted = false;
	bitmap->UnlockBits(&bmpData);
	delete[] bitmap;
}

void CTSSDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	Gdiplus::GdiplusShutdown(gdiplusToken);
}

void CTSSDlg::OnLvnItemChangedFileList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0; 
	OnRotation0();
	Invalidate(1);
}

void CTSSDlg::OnStnClickedStaticImage()
{
	// TODO: Add your control notification handler code here
}

void CTSSDlg::OnTimer(UINT_PTR nIDEvent)
{
	int nIndex =  -1;
	nIndex = m_fileList.GetNextItem(nIndex, LVNI_SELECTED);

	if (nIndex > -1 && nIndex == nIDEvent - 1 && m_loadedFiles[nIndex].cHist == 1 ) {
		m_staticHistogram.Invalidate(1);
		KillTimer(nIDEvent);
	}

	if (nIndex > -1 && nIndex == nIDEvent - 101 && m_loadedFiles[nIndex].c90) {
		m_staticHistogram.Invalidate(1);
		KillTimer(nIDEvent);
	}
	if (nIndex > -1 && nIndex == nIDEvent - 201 && m_loadedFiles[nIndex].c180) {
		m_staticHistogram.Invalidate(1);
		KillTimer(nIDEvent);
	}
	if (nIndex > -1 && nIndex == nIDEvent - 301 && m_loadedFiles[nIndex].c270) {
		m_staticHistogram.Invalidate(1);
		KillTimer(nIDEvent);
	}


	m_staticImage.Invalidate(1);
	//CDialogEx::OnTimer(nIDEvent);
}