#pragma once

class CFolderDlg;

// CChild 대화 상자

class CChild : public CDialogEx
{
	DECLARE_DYNAMIC(CChild)
public:
	CChild(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CChild();

	CFolderDlg *m_Parent;
	CImage img;
	int flg = 0;
	CString path;
	CRect parentSize;
	CPoint pMouse;
	int DrawOn = 0;

	//Effect
	int effectOr = 0;
	CString prevPath;

	void Wait(DWORD dwMillisecond);
	int key = 0;
	CCriticalSection g_sem;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();

	virtual void PostNcDestroy();

	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
