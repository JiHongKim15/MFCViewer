
// FolderDlg.h: 헤더 파일
//

#pragma once
#include "FListName.h"

class CChild;


// CFolderDlg 대화 상자
class CFolderDlg : public CDialogEx
{
// 생성입니다.
public:
	CFolderDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	CChild *pDlg;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FOLDER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedClose(); //close
	afx_msg void OnBnClickedOpen(); //folder open
	afx_msg void OnLbnSelchangeList1(); //list image
	afx_msg void OnBnClickedPrev(); //prev
	afx_msg void OnBnClickedNext(); //next
	afx_msg void OnBnClickedFirst(); //first
	afx_msg void OnBnClickedFinal(); //final
	afx_msg void OnBnClickedButton5(); //delete
	CString m_path; //path
	void IMAGELOAD(); //image load
	CListBox FolderList; //list
	FListName* pCur = NULL; //current image
	int index; //current index
	int ImageOn = 0; //image load
	int fCount = 0; //total image

	afx_msg void OnBnClickedMove();
	afx_msg void OnNMReleasedcaptureSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedFileOpen();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	int mvPage;
	CString fname;
	CSliderCtrl pSlider;
	int turn = 0;
	CComboBox tTime;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedAuto();
	afx_msg void OnCbnSelchangeTime();
	afx_msg void OnBnClickedManual();
	int tCombo = 0;
	int tAuto = 0;
	CButton tM;
	CButton tA;
	CStatic curStatic;
	CStatic totalStatic;

	int size;
	afx_msg void OnBnClicked100();
	afx_msg void OnBnClickedFull();
	afx_msg void OnBnClickedOri();
	afx_msg void OnBnClicked50();

	void sizeStyle(int size);
	void buttonEnalbeStart();
	void buttonEnalbeEnd();
	void buttonHide();
	void buttonShow();
	BOOL button = TRUE;
	LONG pWindow[4];
	RECT stWinRect[4];
	int windowWidth[4];
	int windowHeight[4];

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);

	int mX = 0;
	int mY = 0;

	int DrawOn = 0;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);


	int findSignal = 0;
	afx_msg void OnBnClickedFind();
	afx_msg void OnEnChangeFind();
	afx_msg void OnEnChangePath();

	int cWidth;
	CRect rectWindow;

	void CreateHorizontalScroll();
	
	afx_msg void OnBnClickedEffect();

	BOOL effect = FALSE;
	int prevIndex = -1;

	void Wait(DWORD dwMillisecond);
};
