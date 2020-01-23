
// AboutDlg.cpp : implementation file
//

#include "framework.h"
#include "AboutDlg.h"
#include "afxdialogex.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CAboutDlg::CAboutDlg(CWnd* pParent) : CDialogEx(IDD_ABOUTBOX, pParent)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()
