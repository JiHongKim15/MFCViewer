#pragma once


// FListName 대화 상자

class FListName : public CDialogEx
{
	DECLARE_DYNAMIC(FListName)
private:
	CString name;
	CString path;
	CString prevPath;
	FListName* pNext;
	FListName* pPrev;
	int num;

public:
	FListName(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~FListName();
	void setName(CString n);
	void setPath(CString n);
	void setpPath(CString n);
	void setNext(FListName* n);
	void setPrev(FListName* n);
	void setNum(int n);
	int getNum();
	CString getName();
	CString getPath();
	CString getpPath();
	FListName* getNext();
	FListName* getPrev();
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FOLDER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
