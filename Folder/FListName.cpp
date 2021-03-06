// FListName.cpp: 구현 파일
//

#include "stdafx.h"
#include "Folder.h"
#include "FListName.h"
#include "afxdialogex.h"


// FListName 대화 상자

IMPLEMENT_DYNAMIC(FListName, CDialogEx)

FListName::FListName(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FOLDER_DIALOG, pParent)
{
	pNext = NULL;
	pPrev = NULL;
	num = 0;
}

FListName::~FListName()
{
}

void FListName::setName(CString n)
{
	name = n;
}

void FListName::setPath(CString n)
{
	path = n;
}

void FListName::setpPath(CString n)
{
	prevPath = n;
}

void FListName::setNext(FListName * n)
{
	pNext = n;
}

void FListName::setPrev(FListName * n)
{
	pPrev = n;
}

void FListName::setNum(int n)
{
	num = n;
}

void FListName::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(FListName, CDialogEx)
END_MESSAGE_MAP()


// FListName 메시지 처리기

int FListName::getNum()
{
	return num;
}

CString FListName::getName()
{
	return name;
}

CString FListName::getPath()
{
	return path;
}

CString FListName::getpPath()
{
	return prevPath;
}

FListName * FListName::getNext()
{
	return pNext;
}

FListName * FListName::getPrev()
{
	return pPrev;
}
