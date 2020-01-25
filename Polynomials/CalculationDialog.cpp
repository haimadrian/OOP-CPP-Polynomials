/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

#include "Polynomials.h"
#include "CalculationDialog.h"
#include "afxdialogex.h"


// CalculationDialog dialog

IMPLEMENT_DYNAMIC(CalculationDialog, CDialogEx)

CalculationDialog::CalculationDialog(CWnd* pParent /*=nullptr*/)
	: xValue(0), CDialogEx(IDD_CALCULATE_DIALOG, pParent)
{

}

CalculationDialog::~CalculationDialog()
{
}

void CalculationDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CalculationDialog, CDialogEx)
	ON_EN_CHANGE(IDC_EDITXVALUE, &CalculationDialog::OnEnChangeEditxvalue)
END_MESSAGE_MAP()


// CalculationDialog message handlers


void CalculationDialog::OnEnChangeEditxvalue()
{
	try {
		CString val;
		GetDlgItemText(IDC_EDITXVALUE, val);
		std::wstring wstr(val.GetString());
		xValue = atof(std::string(wstr.begin(), wstr.end()).c_str());
	}
	catch (...) {
		AfxMessageBox(L"Illegal input. Only numbers are accepted.", MB_ICONERROR | MB_OK);
		xValue = 0;
		SetDlgItemText(IDC_EDITXVALUE, L"0");
	}
}

double CalculationDialog::getXValue() {
	return xValue;
}

BOOL isNavigation(WPARAM key) {
	switch (key) {
		case VK_LEFT:
		case VK_RIGHT:
		case VK_UP:
		case VK_DOWN:
		case VK_SHIFT:
		case LVKF_SHIFT:
		case VK_CAPITAL:
		case VK_CONTROL:
		case LVKF_CONTROL:
		case VK_OEM_WSCTRL:
		case VK_MENU:
		case LVKF_ALT:
		case VK_DELETE:
		case VK_BACK:
			return true;
		default: return false;
	}
}

BOOL CalculationDialog::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN) {
		if (pMsg->wParam == VK_RETURN) {
			EndDialog(IDOK);
			return TRUE;
		}
		else if (pMsg->wParam == VK_ESCAPE) {
			EndDialog(IDCANCEL);
			return TRUE;
		} else if (isNavigation(pMsg->wParam)) {
			return CDialogEx::PreTranslateMessage(pMsg);
		}

		const WPARAM wParam = pMsg->wParam; // Virtual key, e.g. DEL
		const LPARAM lParam = pMsg->lParam;
		const LPARAM keyboardScanCode = (lParam >> 16) & 0x00ff;
		WPARAM virtualKey = wParam;

		BYTE keyboardState[256];
		GetKeyboardState(keyboardState);

		WORD ascii = 0;
		const int len = ToAscii((UINT)virtualKey, (UINT)keyboardScanCode, keyboardState, &ascii, 0);
		if (len == 0) {
			ascii = (WORD)wParam; // Just take the key as is
		}

		if (!(isdigit(ascii)) && (ascii != '-') && (ascii != '.')) {
			AfxMessageBox(L"Illegal input. Only numbers are accepted.", MB_ICONERROR | MB_OK);
			return TRUE;
		}
		else {
			CEdit * edit = (CEdit *)GetDlgItem(IDC_EDITXVALUE);
			WCHAR * text = new WCHAR[2]{ (WCHAR)ascii, '\0' };
			int length = edit->GetWindowTextLengthW();
			edit->SetSel(length, length);
			edit->ReplaceSel(text);
			delete text;

			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
