/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

#include "framework.h"
#include "Polynomials.h"
#include "PolySelectionDialog.h"
#include "afxdialogex.h"
#include <string>


 // PolySelectionDialog dialog

IMPLEMENT_DYNAMIC(PolySelectionDialog, CDialogEx)

PolySelectionDialog::PolySelectionDialog(int low, int high, const std::wstring & action, CWnd* pParent /*=nullptr*/)
	: leftPolyIndex(low), rightPolyIndex(low), low(low), high(high), isWindowVisible(false), action(action), CDialogEx(IDD_SELECT_POLY_DIALOG, pParent)
{
}

PolySelectionDialog::~PolySelectionDialog()
{
}

int PolySelectionDialog::getLeftPolyIndex() const
{
	return leftPolyIndex;
}

int PolySelectionDialog::getRightPolyIndex() const
{
	return rightPolyIndex;
}

void PolySelectionDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PolySelectionDialog, CDialogEx)
	//	ON_WM_ACTIVATE()
	ON_EN_CHANGE(IDC_EDITLEFTPOLY, &PolySelectionDialog::OnEnChangeEditleftpoly)
	ON_EN_CHANGE(IDC_EDITRIGHTPOLY, &PolySelectionDialog::OnEnChangeEditrightpoly)
END_MESSAGE_MAP()


// PolySelectionDialog message handlers

BOOL PolySelectionDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetWindowText(std::wstring(L"Polynomials Selection (" + action + L")").c_str());

	// Set ranges based on list control
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPINLEFTPOLY))->SetRange(low, high);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPINRIGHTPOLY))->SetRange(low, high);

	isWindowVisible = true;

	char * buffer = new char[16];
	_itoa_s(low, buffer, 16, 10);
	std::string str(buffer);
	SetDlgItemText(IDC_EDITLEFTPOLY, std::wstring(str.begin(), str.end()).c_str());
	SetDlgItemText(IDC_EDITRIGHTPOLY, std::wstring(str.begin(), str.end()).c_str());

	return TRUE;  // return TRUE  unless you set the focus to a control
}


void PolySelectionDialog::OnEnChangeEditleftpoly()
{
	// Avoid of validating input when window is first displayed
	if (!isWindowVisible)
	{
		return;
	}

	CString val;
	GetDlgItemText(IDC_EDITLEFTPOLY, val);
	std::wstring wstr(val.GetString());
	int value = atoi(std::string(wstr.begin(), wstr.end()).c_str());

	if ((value < low) || (value > high))
	{
		AfxMessageBox(L"Input is out of range. Please select valid row index.", MB_ICONERROR | MB_OK);
		char * buffer = new char[16];
		_itoa_s(leftPolyIndex, buffer, 16, 10);
		std::string str(buffer);
		SetDlgItemText(IDC_EDITLEFTPOLY, std::wstring(str.begin(), str.end()).c_str());
		delete buffer;
	}
	else
	{
		leftPolyIndex = value;
	}
}


void PolySelectionDialog::OnEnChangeEditrightpoly()
{
	// Avoid of validating input when window is first displayed
	if (!isWindowVisible)
	{
		return;
	}

	CString val;
	GetDlgItemText(IDC_EDITRIGHTPOLY, val);
	std::wstring wstr(val.GetString());
	int value = atoi(std::string(wstr.begin(), wstr.end()).c_str());

	if ((value < low) || (value > high))
	{
		AfxMessageBox(L"Input is out of range. Please select valid row index.", MB_ICONERROR | MB_OK);
		char * buffer = new char[16];
		_itoa_s(rightPolyIndex, buffer, 16, 10);
		std::string str(buffer);
		SetDlgItemText(IDC_EDITRIGHTPOLY, std::wstring(str.begin(), str.end()).c_str());
		delete buffer;
	}
	else
	{
		rightPolyIndex = value;
	}
}
