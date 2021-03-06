// CChild.cpp: 구현 파일
//

#include "stdafx.h"
#include "Folder.h"
#include "CChild.h"
#include "afxdialogex.h"
#include "FolderDlg.h"
#include <string>
#include <atlimage.h>

// CChild 대화 상자

IMPLEMENT_DYNAMIC(CChild, CDialogEx)

CChild::CChild(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	 m_Parent = (CFolderDlg*)pParent;
}

CChild::~CChild()
{
}

void CChild::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CChild, CDialogEx)
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CChild 메시지 처리기

BOOL CChild::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	//parent = (FolderDlg*)AfxGetMainWnd();
	SetWindowPos(NULL, 250,35, 1000, 750, SWP_NOREPOSITION);
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.

}

void CChild::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	if (flg == 0)
		return;
	CImage image;
	CBitmap bitmap;
	BITMAP bmp;

	CRect rect;
	int windowWidth = GetSystemMetrics(SM_CXSCREEN);
	int windowHeight = GetSystemMetrics(SM_CYSCREEN);

	this->GetWindowRect(&rect);
//	this->ScreenToClient(rect);

	image.Load(path);
	bitmap.Attach(image.Detach());  //bitmap으로 변환

	CDC memDCimage;
	memDCimage.CreateCompatibleDC(&dc);
	memDCimage.SelectObject(&bitmap); //메모리에 bitmap 저장
	bitmap.GetBitmap(&bmp);

	CDC memDC; //도화지
	CBitmap pbitmap;
	memDC.CreateCompatibleDC(&dc); 
	pbitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height()); //도화지 생성
	memDC.SelectObject(&pbitmap); //도화지 선택
	memDC.SetStretchBltMode(COLORONCOLOR);

	memDC.StretchBlt(0, 0, rect.Width(), rect.Height(), &memDCimage, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
	
	if (effectOr != 0 && flg != 2)
	{
		CDC memDCprev;
		CImage prevImage;
		CBitmap prevBitmap;
		BITMAP prevBmp;
		
		prevImage.Load(prevPath);
		prevBitmap.Attach(prevImage.Detach());

		memDCprev.CreateCompatibleDC(&dc);
		memDCprev.SelectObject(&prevBitmap);
		prevBitmap.GetBitmap(&prevBmp);
		
		CDC DC; //도화지
		CBitmap B;
		DC.CreateCompatibleDC(&dc);
		B.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height()); //도화지 생성
		DC.SelectObject(&B); //도화지 선택
		DC.SetStretchBltMode(COLORONCOLOR);

		DC.StretchBlt(0, 0, rect.Width(), rect.Height(), &memDCprev, 0, 0, prevBmp.bmWidth, prevBmp.bmHeight, SRCCOPY);

		CDC DCimage; //도화지
		CBitmap Bit;
		DCimage.CreateCompatibleDC(&dc);
		Bit.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height()); //도화지 생성
		DCimage.SelectObject(&Bit); //도화지 선택
		DCimage.SetStretchBltMode(COLORONCOLOR);

		DCimage.BitBlt(0, 0, rect.right - rect.left, rect.bottom - rect.top, &memDC, 0, 0, SRCCOPY);


		int a = rect.Width() / 10;
		int b = rect.Width() / 10;

		g_sem.Lock();
		if (effectOr == 1)
		{
			key = 1;
			for (int i = 0; i < 10; i++)
			{
				memDC.StretchBlt(0, 0, rect.Width() - a, rect.Height(), &DC, 0, 0, rect.Width() - a, rect.Height(), SRCCOPY);
				memDC.StretchBlt(rect.Width() - a, 0, a, rect.Height(), &DCimage, rect.Width() - a, 0, a, rect.Height(), SRCCOPY);

				dc.BitBlt(0, 0, rect.right - rect.left, rect.bottom - rect.top, &memDC, 0, 0, SRCCOPY);

				a = a + b;
			}
		}
		else if (effectOr == -1)
		{
			for (int i = 0; i < 10; i++)
			{
				memDC.StretchBlt(a, 0, rect.Width() - a, rect.Height(), &DC, a, 0, rect.Width() - a, rect.Height(), SRCCOPY);
				memDC.StretchBlt(0, 0, a, rect.Height(), &DCimage, 0, 0, a, rect.Height(), SRCCOPY);

				dc.BitBlt(0, 0, rect.right - rect.left, rect.bottom - rect.top, &memDC, 0, 0, SRCCOPY);

				a = a + b;
			}
		}
		key = 0;
		g_sem.Unlock();
	}

	if (flg == 2 && DrawOn == 1)
	{

		//이미지 확대
		memDC.StretchBlt(pMouse.x - 99, pMouse.y - 99, 198, 198, &memDC, pMouse.x - 50, pMouse.y - 50, 100, 100, SRCCOPY);

		CPen pen;
		CDC memPen;
		pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		memDC.SelectObject(&pen);

		//위
		if (pMouse.y - 100 < 0)
		{
			memDC.MoveTo(pMouse.x - 100, 1);
			memDC.LineTo(pMouse.x + 100, 1);
		}
		else
		{
			memDC.MoveTo(pMouse.x - 100, pMouse.y - 100);
			memDC.LineTo(pMouse.x + 100, pMouse.y - 100);
		}
		//왼쪽
		if (pMouse.x - 100 < 0)
		{
			memDC.MoveTo(1, pMouse.y - 100);
			memDC.LineTo(1, pMouse.y + 100);
		}
		else
		{
			memDC.MoveTo(pMouse.x - 100, pMouse.y - 100);
			memDC.LineTo(pMouse.x - 100, pMouse.y + 100);
		}
		//오른쪽
		if (pMouse.x + 100 > rect.Width())
		{
			memDC.MoveTo(rect.Width() - 1, pMouse.y - 100);
			memDC.LineTo(rect.Width()- 1, pMouse.y + 100);
		}
		else
		{
			memDC.MoveTo(pMouse.x + 100, pMouse.y - 100);
			memDC.LineTo(pMouse.x + 100, pMouse.y + 100);
		}
		//아래
		if (pMouse.y + 100 > rect.Height()) 
		{
			memDC.MoveTo(pMouse.x + 100, rect.Height()-2);
			memDC.LineTo(pMouse.x - 100, rect.Height()-2);
		}
		else
		{
			memDC.MoveTo(pMouse.x + 100, pMouse.y + 100);
			memDC.LineTo(pMouse.x - 100, pMouse.y + 100);
		}
	}
	 
	dc.BitBlt(0, 0, rect.right - rect.left, rect.bottom - rect.top, &memDC, 0, 0, SRCCOPY);

}

void CChild::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	delete this;

	CDialogEx::PostNcDestroy();
}


void CChild::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	m_Parent->OnKeyDown(nChar, nRepCnt, nFlags);
	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CChild::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE)
		{
			m_Parent->PreTranslateMessage(pMsg);
			return TRUE;
		}
		switch (pMsg->wParam) {
		case VK_UP:
			break;
		case VK_DOWN:
			break;
		case VK_LEFT:
			break;
		case VK_RIGHT:
			break;
		case VK_PRIOR:
			break;
		case VK_NEXT:
			break;
		default:
			return TRUE;
		}
		UINT nRepCnt = (UINT)((pMsg->lParam) & 0x0000FFFF);
		UINT nFlags = (UINT)((pMsg->lParam) >> 16);
		this->OnKeyDown(pMsg->wParam, nRepCnt, nFlags);

	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CChild::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	DrawOn = 1;
	ShowCursor(false);
	pMouse.x = point.x;
	pMouse.y = point.y;

	m_Parent->OnRButtonDblClk(nFlags, point);
	CDialogEx::OnRButtonDown(nFlags, point);
}


void CChild::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	DrawOn = 0;
	ReleaseCapture();
	::ClipCursor(NULL);
	ShowCursor(true);

	m_Parent->OnRButtonUp(nFlags, point);

	CDialogEx::OnRButtonUp(nFlags, point);
}



void CChild::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (flg == 2) {

		DrawOn = 1;
		CRect rt;
		CRect rect;

		SetCapture();
		GetClientRect(&rect);
		ClientToScreen(&rect);
		::ClipCursor(&rect);

		this->GetWindowRect(&rt);
		ScreenToClient(&rt);

		if (!rt.PtInRect(point))
			return;

		pMouse.x = point.x;
		pMouse.y = point.y;


		m_Parent->OnMouseMove(nFlags, point);
	}
	CDialogEx::OnMouseMove(nFlags, point);
}



void CChild::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	DrawOn = 1;
	ShowCursor(false);
	pMouse.x = point.x;
	pMouse.y = point.y;

	m_Parent->OnRButtonDown(nFlags, point);

	CDialogEx::OnRButtonDown(nFlags, point);
}


BOOL CChild::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return TRUE;// CDialogEx::OnEraseBkgnd(pDC);
}


void CChild::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_Parent->ImageOn == 1)
	{

		if (point.x < m_Parent->cWidth)
		{
			m_Parent->index--;
		}
		else if (point.x > m_Parent->cWidth)
		{
			m_Parent->index++;
		}

		if (m_Parent->index >= m_Parent->fCount)
			m_Parent->index = m_Parent->fCount - 1;
		if (m_Parent->index < 0)
			m_Parent->index = 0;

		m_Parent->IMAGELOAD();
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CChild::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.ageOn != 1)

	if (m_Parent->ImageOn != 1)
	{
		m_Parent->OnBnClickedFileOpen();
		m_Parent->index = 0;
		m_Parent->IMAGELOAD();
		return;
	}
	OnLButtonDown(nFlags, point);
	CDialogEx::OnLButtonDblClk(nFlags, point);
}


void CChild::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnTimer(nIDEvent);
}

void CChild::Wait(DWORD dwMillisecond)
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
