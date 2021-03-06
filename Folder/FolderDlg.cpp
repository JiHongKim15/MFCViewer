
// FolderDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "Folder.h"
#include "FolderDlg.h"
#include "afxdialogex.h"
#include "FListName.h"
#include <string>
#include <atlimage.h>
#include "CChild.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_RBUTTONDOWN()
//ON_WM_TIMER()
END_MESSAGE_MAP()


// CFolderDlg 대화 상자



CFolderDlg::CFolderDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FOLDER_DIALOG, pParent)
	, m_path(_T(""))
	, fCount(0)
	, mvPage(0)
	, fname(_T(""))
	, turn(0)
	, size(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFolderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_path);
	DDX_Control(pDX, IDC_LIST1, FolderList);
	DDX_Text(pDX, IDC_EDIT3, mvPage);
	DDX_Text(pDX, IDC_EDIT4, fname);
	DDX_Control(pDX, IDC_SLIDER1, pSlider);
	DDX_Radio(pDX, IDC_RADIO1, turn);
	DDX_Control(pDX, IDC_COMBO1, tTime);
	DDX_Control(pDX, IDC_RADIO1, tM);
	DDX_Control(pDX, IDC_RADIO2, tA);
	DDX_Control(pDX, IDC_STATIC1, curStatic);
	DDX_Control(pDX, IDC_STATIC2, totalStatic);
	DDX_Radio(pDX, IDC_RADIO9, size);
}

BEGIN_MESSAGE_MAP(CFolderDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CFolderDlg::OnBnClickedClose)
	ON_BN_CLICKED(IDC_BUTTON4, &CFolderDlg::OnBnClickedOpen)
	ON_LBN_SELCHANGE(IDC_LIST1, &CFolderDlg::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON2, &CFolderDlg::OnBnClickedPrev)
	ON_BN_CLICKED(IDC_BUTTON3, &CFolderDlg::OnBnClickedNext)
	ON_BN_CLICKED(IDC_BUTTON5, &CFolderDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON8, &CFolderDlg::OnBnClickedFirst)
	ON_BN_CLICKED(IDC_BUTTON7, &CFolderDlg::OnBnClickedFinal)
	ON_BN_CLICKED(IDC_BUTTON6, &CFolderDlg::OnBnClickedMove)
	ON_BN_CLICKED(IDC_BUTTON9, &CFolderDlg::OnBnClickedFileOpen)
	ON_BN_CLICKED(IDC_RADIO2, &CFolderDlg::OnBnClickedAuto)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CFolderDlg::OnCbnSelchangeTime)
	ON_BN_CLICKED(IDC_RADIO1, &CFolderDlg::OnBnClickedManual)
	ON_BN_CLICKED(IDC_RADIO9, &CFolderDlg::OnBnClicked100)
	ON_BN_CLICKED(IDC_RADIO7, &CFolderDlg::OnBnClickedFull)
	ON_BN_CLICKED(IDC_RADIO10, &CFolderDlg::OnBnClicked50)
	ON_BN_CLICKED(IDC_RADIO3, &CFolderDlg::OnBnClickedOri)
	ON_BN_CLICKED(IDC_BUTTON11, &CFolderDlg::OnBnClickedFind)
	ON_EN_CHANGE(IDC_EDIT4, &CFolderDlg::OnEnChangeFind)
	ON_EN_CHANGE(IDC_EDIT1, &CFolderDlg::OnEnChangePath)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, &CFolderDlg::OnNMReleasedcaptureSlider1)
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_NCRBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_HSCROLL()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_SIZE()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON12, &CFolderDlg::OnBnClickedEffect)
END_MESSAGE_MAP()


// CFolderDlg 메시지 처리기

BOOL CFolderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	tTime.AddString(_T("1"));
	tTime.AddString(_T("2"));
	tTime.AddString(_T("5"));
	tTime.AddString(_T("10"));


	CRect rect;
	this->GetWindowRect(&rect);

	pDlg = new CChild(this);
	pDlg->parentSize = rect;
	pDlg->Create(IDD_DIALOG1, this);
	pDlg->ShowWindow(SW_SHOW);

	pWindow[0] = 0;
	pWindow[1] = 0;
	pWindow[2] = 0;
	pWindow[3] = 0;

	buttonEnalbeEnd();
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CFolderDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CFolderDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		if (ImageOn == 1)
		{
			if (fCount == 0 || index < 0)
			{
				CDialogEx::OnPaint();

				CString cur;
				cur.Format(_T("%d"), index);

				SetDlgItemText(IDC_STATIC1, cur);
				UpdateData(false);
				return;
			}
			CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

			CDC memDCimage;
			CDC memDCzoom;
			CDC memDC;

			CImage Image;
			CBitmap bitmap;
			CBitmap bitmap2;
			BITMAP bmp;


			Image.Load(pCur->getPath()); //다른 형식도 받음

			pDlg->SetFocus();
			pDlg->flg = 1;
			pDlg->img = Image;
			pDlg->path = pCur->getPath();

			bitmap.Attach(Image.Detach());  //bitmap으로 변환

			memDCimage.CreateCompatibleDC(&dc);
			memDC.CreateCompatibleDC(&dc);
			memDCimage.SelectObject(&bitmap); //메모리에 bitmap 저장

			bitmap.GetBitmap(&bmp);
			
/*
			dc.SetStretchBltMode(COLORONCOLOR);
*/

			int cx = GetSystemMetrics(SM_CXSCREEN);
			int cy = GetSystemMetrics(SM_CYSCREEN);

			sizeStyle(size);
			if (size == 0)
				cWidth = 500;
			else if (size == 2)
				cWidth = 250;
			else if (size == 1)
				cWidth = cx / 2;
			else if (size == 3) //수정필요
			{
				int oriWidth = windowWidth[0] - 1000 + bmp.bmWidth;
				int oriHeight = windowHeight[0];
	
				if (oriWidth + stWinRect[0].left > cx)
					oriWidth = cx - stWinRect[0].left;

				if (stWinRect[0].top + bmp.bmHeight > cy)
					oriHeight = cy - stWinRect[0].top;
				else if (stWinRect[0].top +bmp.bmHeight > windowHeight[0])
					oriHeight = stWinRect[0].top + bmp.bmHeight;
								
				::SetWindowPos(this->m_hWnd, HWND_TOPMOST, stWinRect[0].left, stWinRect[0].top, oriWidth, oriHeight, SWP_NOZORDER);
				pDlg->SetWindowPos(NULL, 250, 35, bmp.bmWidth, bmp.bmHeight, SWP_NOREPOSITION);
				cWidth = bmp.bmWidth / 2;
			}

			if (DrawOn == 1) {
				pDlg->flg = 2;
			}
			if (effect == TRUE) {
				pDlg->key = 1;
				if (prevIndex == -1)
					prevIndex = index;
				if (prevIndex < index)
				{
					pDlg->effectOr = -1;
				}
				else if (prevIndex > index)
				{
					pDlg->effectOr = 1;
				}

				FListName* pPrev = (FListName*)FolderList.GetItemDataPtr(prevIndex);
				pDlg->prevPath = pPrev->getPath();
			}
			pDlg->Invalidate();

			m_path = pCur->getPath();
			fname = pCur->getName();
			prevIndex = index;

			CString cur;
			cur.Format(_T("%d"), index + 1);
			SetDlgItemText(IDC_STATIC1, cur);
			UpdateData(false);
			

		}
		else
		{
			CDialogEx::OnPaint();

			sizeStyle(size);
		}
	}

}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CFolderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFolderDlg::OnBnClickedClose()
{
	OnOK();
}


void CFolderDlg::OnBnClickedOpen()
{
	CFileDialog fDlg(true);
	CString FileN;
	BOOL bWorking;
	CFileFind finder;
	CString strFolderPath;
	

	//Browser Open
	ITEMIDLIST *pidlBrowse;
	
	BROWSEINFO BrInfo;

	BrInfo.hwndOwner = GetSafeHwnd();
	BrInfo.pidlRoot = NULL;

	memset(&BrInfo, 0, sizeof(BrInfo));
	BrInfo.pszDisplayName = (LPWSTR)(LPCTSTR)strFolderPath;
	BrInfo.lpszTitle = _T("Select Folder");
	BrInfo.ulFlags = BIF_RETURNONLYFSDIRS;

	// 다이얼로그 띄우기
	pidlBrowse = SHBrowseForFolder(&BrInfo);

	if (pidlBrowse != NULL)
	{
		BOOL bSuccess = ::SHGetPathFromIDList(pidlBrowse, (LPWSTR)(LPCTSTR)strFolderPath);
		

		if (!bSuccess)
		{
			MessageBox(_T("잘못된 폴더명 입니다."), _T(""), MB_OKCANCEL | MB_ICONASTERISK);
			return;
		}

	}
	else
	{
		return;
	}

	m_path.Format(_T("%s\\*.*"), strFolderPath); //path\\*,bmp, bmp 파일을 연다
	
	UpdateData(false);

	//List 연결

	bWorking = finder.FindFile(m_path); //m_path 위치에서 file 찾기
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (finder.IsDirectory() == FALSE && finder.IsDots() == FALSE) { //.과 directory가 아닐때

			if (finder.GetFileName().Find(_T("bmp")) != -1|| finder.GetFileName().Find(_T("jpg")) != -1 || finder.GetFileName().Find(_T(".png")) != -1 || finder.GetFileName().Find(_T(".PNG")) != -1)
			{
				FolderList.InsertString(fCount, finder.GetFileName());

				FListName* pNew = new FListName;
				pNew->setName(finder.GetFileName());
				pNew->setPath(finder.GetFilePath());
				pNew->setpPath(m_path);
				pNew->setNum(fCount);


				FolderList.SetItemDataPtr(fCount, (void*)pNew);

				fCount++;
			}
		}

	}
	buttonEnalbeStart();
	CreateHorizontalScroll();
	CString cur;
	cur.Format(_T("%d"), fCount);
	SetDlgItemText(IDC_STATIC2, cur);
	fname = _T(" ");

	pSlider.SetRange(0, fCount-1);
	UpdateData(false);
}

void CFolderDlg::OnBnClickedFileOpen()
{
	CFileDialog finder(true);
	if (finder.DoModal() == IDOK)
	{
		FListName* pNew = new FListName;
		pNew->setName(finder.GetFileName());

		m_path = finder.GetPathName();
		m_path.Replace(finder.GetFileName(), NULL);

		m_path.Format(_T("%s*.*"), m_path); //path\\*,bmp, bmp 파일을 연다
		if (finder.GetFileName().Find(_T(".bmp")) != -1 || finder.GetFileName().Find(_T(".jpg")) != -1 || finder.GetFileName().Find(_T(".png")) != -1 || finder.GetFileName().Find(_T(".PNG")) != -1)
		{
			FolderList.InsertString(fCount, finder.GetFileName());

			pNew->setPath(finder.GetPathName());
			pNew->setpPath(m_path);
			pNew->setNum(fCount);

			FolderList.SetItemDataPtr(fCount, (void*)pNew);

			fCount++;
		}
		else
			AfxMessageBox(_T("Select The Photo"));

		buttonEnalbeStart();
		CreateHorizontalScroll();
		CString cur;
		cur.Format(_T("%d"), fCount);
		SetDlgItemText(IDC_STATIC2, cur);
		pSlider.SetRange(0, fCount - 1);
		fname = _T(" ");
		UpdateData(false);
	}
}


void CFolderDlg::IMAGELOAD()
{
	if (size == 1 && button == TRUE)
		buttonHide();
	if (prevIndex != -1 && prevIndex != index && pDlg->key == 1)
	{
	}
	findSignal = 0;
	pCur = (FListName*)FolderList.GetItemDataPtr(index);
	FolderList.SetCurSel(index);
	pSlider.SetPos(index);
	ImageOn = 1;
	if (index >= fCount || index < 0 || fCount == 0)
	{
		ImageOn = 0;
	}
	if (fCount == 0)
	{
		buttonEnalbeEnd();
	}
	CRect tmp(250, 30, 10000, 10000);

	InvalidateRect(tmp, false);
	UpdateWindow();
}




void CFolderDlg::OnLbnSelchangeList1()
{
	index = FolderList.GetCurSel(); //선택된 위치 가져오기

	IMAGELOAD();
	
}

void CFolderDlg::OnBnClickedPrev()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (pCur == NULL || fCount == 0)
		return;

	if (index == 0) {
		AfxMessageBox(_T("Previous photo does not exist.")); //이전 사진이 존재하지 않음
		return;
	}
	index--;
	IMAGELOAD(); //출력
}


void CFolderDlg::OnBnClickedNext()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (pCur == NULL || fCount == 0)
		return;
	if (index == fCount-1) {
		AfxMessageBox(_T("Next photo does not exist.")); //다음 사진이 존재하지 않음
		return;
	}
	index++;

	IMAGELOAD(); //출력
}


void CFolderDlg::OnBnClickedButton5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	index = FolderList.GetCurSel(); //선택된 위치 가져오기

	if (index < 0 || fCount == 0)
		return;

	FolderList.DeleteString(index);


	--fCount;
	if(index != 0)
		--index;
	IMAGELOAD();

}


void CFolderDlg::OnBnClickedFirst()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	index = 0;
	IMAGELOAD(); //출력
}


void CFolderDlg::OnBnClickedFinal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (fCount == 0)
		return;


	index = fCount - 1;

	IMAGELOAD(); //출력
}


void CFolderDlg::OnBnClickedMove()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (tAuto == 1) //manual 모드
	{
		tAuto = 0;
		KillTimer(1);
		tM.SetCheck(BST_CHECKED);
		tA.SetCheck(BST_UNCHECKED);

	}

	UpdateData(true);
	if (mvPage < 1 || mvPage > fCount) {
		AfxMessageBox(_T("Not Found Page"));
		return;
	}
	index = mvPage - 1;

	IMAGELOAD();
}



void CFolderDlg::OnNMReleasedcaptureSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	index = pSlider.GetPos();
	if (index > fCount-1 || index < 0)
		return;
	IMAGELOAD();
}



void CFolderDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	if (tAuto == 1) //manual 모드
	{
		tAuto = 0;
		KillTimer(1);
		tM.SetCheck(BST_CHECKED);
		tA.SetCheck(BST_UNCHECKED);
	}
	switch (nChar)
	{
	case VK_UP:
		--index;
		break;
	case VK_DOWN:
		++index;
		break;
	case VK_LEFT:
		--index;
		break;
	case VK_RIGHT:
		++index;
		break;
	case VK_PRIOR:
		index = 0;
		break;
	case VK_NEXT:
		index = fCount;
		break;
	}

	if (index >= fCount)
		index = fCount - 1;
	if (index < 0)
		index = 0;

	IMAGELOAD();

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}



void CFolderDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (tAuto == 0)
		KillTimer(1);
	++index;
	IMAGELOAD();
	CDialogEx::OnTimer(nIDEvent);
}

void CFolderDlg::OnBnClickedAuto()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	tAuto = 1;
	if (tCombo == 0)
		return;
	if (index >= fCount || index < 0)
		KillTimer(1);

	UpdateData(true);
	int item = tTime.GetCurSel();
	if (item < 0)
		return;
	CString tmp;
	tTime.GetLBText(item, tmp);
	int time = _ttoi(tmp);
	SetTimer(1, time * 1000, NULL);
	UpdateData(false);
}


void CFolderDlg::OnCbnSelchangeTime()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	tCombo = 1;
	if (tAuto == 0)
		return;
	OnBnClickedAuto();
}


void CFolderDlg::OnBnClickedManual()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	tAuto = 0;
	turn = 0;
	KillTimer(1);
}


void CFolderDlg::buttonEnalbeStart()
{
	GetDlgItem(IDC_LIST1)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON8)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON7)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO2)->EnableWindow(TRUE);;
	GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO1)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO9)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO7)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO10)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO3)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON11)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT4)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT3)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
	GetDlgItem(IDC_SLIDER1)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC1)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC2)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC3)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC4)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC5)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC6)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC7)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC8)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC9)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC10)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC11)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON12)->EnableWindow(TRUE);
}
void CFolderDlg::buttonEnalbeEnd()
{

	GetDlgItem(IDC_LIST1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON8)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON7)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO9)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO1)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO1)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO7)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO10)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO3)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON11)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT4)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	GetDlgItem(IDC_SLIDER1)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC1)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC2)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC3)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC4)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC5)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC6)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC7)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC8)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC9)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC10)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC11)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON12)->EnableWindow(FALSE);
}
void CFolderDlg::buttonHide()
{
	button = FALSE;
	GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LIST1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON5)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON8)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON7)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON6)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_RADIO2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON9)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_RADIO1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_RADIO9)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_RADIO7)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_RADIO10)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_RADIO3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON11)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT4)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_SLIDER1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC4)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC5)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC6)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC7)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC8)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC9)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC10)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC11)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON12)->ShowWindow(SW_HIDE);
}

void CFolderDlg::buttonShow()
{
	button = TRUE;
	GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LIST1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON3)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON5)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON8)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON7)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON6)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_RADIO2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON9)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_COMBO1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_RADIO1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_RADIO9)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_RADIO7)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_RADIO10)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_RADIO3)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON11)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT4)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT3)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_SLIDER1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC3)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC4)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC5)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC6)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC7)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC8)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC9)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC10)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC11)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON12)->ShowWindow(SW_SHOW);
}

void CFolderDlg::sizeStyle(int size)
{
	switch (size)
	{
	case 0:
		::GetWindowRect(m_hWnd, &stWinRect[0]); //현재 윈도우 스타일 저장
		if (pWindow[0] == 0)
		{
			windowWidth[0] = stWinRect[0].right - stWinRect[0].left;
			windowHeight[0] = stWinRect[0].bottom - stWinRect[0].top;
		}
		pWindow[0] = ::GetWindowLong(this->m_hWnd, GWL_STYLE); //스타일 읽기
		break;
	case 1:
		::GetWindowRect(m_hWnd, &stWinRect[1]); //현재 윈도우 스타일 저장
		if (pWindow[1] == 0)
		{
			windowWidth[1] = stWinRect[1].right - stWinRect[1].left;
			windowHeight[1] = stWinRect[1].bottom - stWinRect[1].top;
		}
		pWindow[1] = ::GetWindowLong(this->m_hWnd, GWL_STYLE); //스타일 읽기
		break;
	case 2:
		::GetWindowRect(m_hWnd, &stWinRect[0]); //현재 윈도우 스타일 저장
		pWindow[2] = ::GetWindowLong(this->m_hWnd, GWL_STYLE); //스타일 읽기
		break;
	case 3:
		::GetWindowRect(m_hWnd, &stWinRect[0]); //현재 윈도우 스타일 저장
		pWindow[3] = ::GetWindowLong(this->m_hWnd, GWL_STYLE); //스타일 읽기
		break;
	}
}

void CFolderDlg::OnBnClicked100()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (size != 0) {
		buttonShow();
		sizeStyle(size);
		LONG style;
		style = pWindow[0]; //환경로드

		::SetWindowLong(this->m_hWnd, GWL_STYLE, style); //저장된 스타일로 돌아간다.
		//::ShowWindow(this->m_hWnd, SW_RESTORE); //저장된 사이즈로 돌아간다.
		//::SetWindowPos(this->m_hWnd, HWND_TOPMOST, stWinRect[0].left, stWinRect[0].top, stWinRect[0].right - stWinRect[0].left, stWinRect[0].bottom - stWinRect[0].top, SWP_NOZORDER);
		::SetWindowPos(this->m_hWnd, HWND_TOPMOST, stWinRect[0].left, stWinRect[0].top, windowWidth[0], windowHeight[0], SWP_NOZORDER);

	}
	pDlg->SetWindowPos(NULL, 250, 35, 1000, 750, SWP_NOREPOSITION);
	size = 0;
	IMAGELOAD();

}


void CFolderDlg::OnBnClickedFull()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	;

	//LONG style = ::GetWindowLong(this->m_hWnd, GWL_STYLE); //스타일 읽기
	//pWindow[1] = style;
	//::GetWindowRect(m_hWnd, &stWinRect[1]); //현재 윈도우 스타일 저장


	/*::ShowWindow(this->m_hWnd, SW_MAXIMIZE);
	// 타이틀바 삭제
	style &= ~(WS_DLGFRAME | WS_THICKFRAME);
	::SetWindowLong(this->m_hWnd, GWL_STYLE, style);

	// 타이틀바 변경사항 표시 ( SetWindowPos를 해주어야 Title Bar가 표시된다 )
	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);
	::SetWindowPos(this->m_hWnd, HWND_TOPMOST, -1, -1, cx + 3, cy + 3, SWP_FRAMECHANGED);
	::SetWindowPos(m_hWnd, HWND_TOP, 0, 0, stWinRect[1]., stWinRect[1].Height(), SWP_HIDEWINDOW);*/
	sizeStyle(size);
	ModifyStyle(WS_CAPTION, NULL); //캡션 삭제
	ShowWindow(SW_SHOWMAXIMIZED); //전체화면

	int windowWidth = GetSystemMetrics(SM_CXSCREEN);
	int windowHeight = GetSystemMetrics(SM_CYSCREEN);

	pDlg->SetWindowPos(NULL, 0, 0, windowWidth, windowHeight, SWP_NOREPOSITION);

	size = 1;
	IMAGELOAD();
}


void CFolderDlg::OnBnClicked50()
{
	buttonShow();
	sizeStyle(size);
	if (pWindow[2] == 0)
	{
		stWinRect[0].right -= 500;
		windowWidth[2] = stWinRect[0].right - stWinRect[0].left;
		windowHeight[2] = stWinRect[0].bottom - stWinRect[0].top;
	}

	LONG style;
	
	style = pWindow[0]; //환경로드
	::SetWindowLong(this->m_hWnd, GWL_STYLE, style); //저장된 스타일로 돌아간다.
	//::SetWindowPos(this->m_hWnd, HWND_TOPMOST, stWinRect[2].left, stWinRect[2].top, stWinRect[2].right - stWinRect[2].left, stWinRect[2].bottom - stWinRect[2].top, SWP_NOZORDER);
	::SetWindowPos(this->m_hWnd, HWND_TOPMOST, stWinRect[0].left, stWinRect[0].top, windowWidth[2], windowHeight[2], SWP_NOZORDER);
	
	pDlg->SetWindowPos(NULL, 250, 35, 500, 350, SWP_NOREPOSITION);
	size = 2;


	IMAGELOAD();
}


void CFolderDlg::OnBnClickedOri()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	buttonShow();
	sizeStyle(size);
	LONG style = pWindow[0];


		::SetWindowLong(this->m_hWnd, GWL_STYLE, style); //저장된 스타일로 돌아간다.
		::ShowWindow(this->m_hWnd, SW_RESTORE); //저장된 사이즈로 돌아간다.
	//	::SetWindowPos(this->m_hWnd, HWND_TOPMOST, stWinRect[3].left, stWinRect[3].top, stWinRect[3].right - stWinRect[3].left, stWinRect[3].bottom - stWinRect[3].top, SWP_NOZORDER);

	size = 3;
	IMAGELOAD();
}



BOOL CFolderDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	
	if (pMsg->message == WM_KEYDOWN) {
		if (pMsg->wParam == VK_F11)
		{
			OnBnClickedFull();
			return TRUE;
		}
		if (pMsg->wParam == VK_ESCAPE)
		{
			if (size == 1) {
				OnBnClicked100();
				UpdateData(false);
				return TRUE;
			}
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CFolderDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	//ShowCursor(false);
	mX = point.x;
	mY = point.y; 
	DrawOn = 1;

	IMAGELOAD();
	CDialogEx::OnRButtonDown(nFlags, point);
}


void CFolderDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	DrawOn = 0;
	IMAGELOAD();

	CDialogEx::OnRButtonUp(nFlags, point);
}



void CFolderDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (DrawOn == 1) {
		mX = point.x;
		mY = point.y;

		IMAGELOAD();
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


void CFolderDlg::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	OnRButtonDown(nFlags, point);
	CDialogEx::OnRButtonDblClk(nFlags, point);
}

void CFolderDlg::OnBnClickedFind()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (findSignal == 1)
	{
		UpdateData(true);
		for (int i = 0; i < fCount; i++)
		{
			FListName* item = (FListName*)FolderList.GetItemDataPtr(i);
			if (fname == item->getName())
			{
				index = i;
				IMAGELOAD();
				return;
			}
		}
		AfxMessageBox(_T("Not Found Image"));
	}
	else if (findSignal == 2)
	{
		UpdateData(true);
		for (int i = 0; i < fCount; i++)
		{
			FListName* item = (FListName*)FolderList.GetItemDataPtr(i);
			if (m_path == item->getPath())
			{
				index = i;
				IMAGELOAD();
				return;
			}
		}
		AfxMessageBox(_T("Not Found Image"));
	}
}


void CFolderDlg::OnEnChangeFind()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	findSignal = 1;
}


void CFolderDlg::OnEnChangePath()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	findSignal = 2;
}

void CFolderDlg::CreateHorizontalScroll()
{
	CString str;
	CSize sz;
	int dx = 0;
	CDC *pDC = FolderList.GetDC();

	for (int i = 0; i < FolderList.GetCount(); i++)
	{
		FolderList.GetText(i, str);
		sz = pDC->GetTextExtent(str);

		if (sz.cx > dx)
			dx = sz.cx;
	}
	FolderList.ReleaseDC(pDC);

	if (FolderList.GetHorizontalExtent() < dx)
	{
		FolderList.SetHorizontalExtent(dx);
		ASSERT(FolderList.GetHorizontalExtent() == dx);
	}


}


void CFolderDlg::OnBnClickedEffect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (effect == FALSE) {
	
		effect = TRUE;
	}
	else if (effect = TRUE) {
		effect = FALSE;
		pDlg->effectOr = 0;
	}
}

void CFolderDlg::Wait(DWORD dwMillisecond)
{
	MSG msg;
	DWORD dwStart;
	dwStart = GetTickCount();

	while (GetTickCount() - dwStart < dwMillisecond)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}
