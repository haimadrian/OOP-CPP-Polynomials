
// PolynomialsDlg.cpp : implementation file
//

#include <string>
#include <ctime>
#include "framework.h"
#include "Polynomials.h"
#include "PolynomialsDlg.h"
#include "AboutDlg.h"
#include "afxdialogex.h"
#include "PolynomialsApplication.h"
#include "Actions\\ActionContext.h"
#include "Actions\\AbstractInputTextKeeperAction.h"
#include "Utils\\StringUtils.h"
#include "PolySelectionDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


void showGeneralErrorToUser() {
	AfxMessageBox(L"Something went wrong... Sorry", MB_ICONERROR | MB_OK);
}

void showExceptionMessageToUser(std::exception & e) {
	WCHAR * text = StringUtils::charToWCHAR(e.what());
	AfxMessageBox(text, MB_ICONERROR | MB_OK);
	delete text;
}


// CPolynomialsDlg dialog


CPolynomialsDlg::CPolynomialsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_POLYNOMIALS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_MAIN_ICON);
	m_layoutManager = new DialogLayoutManager;
}

CPolynomialsDlg::~CPolynomialsDlg() {
	freeLayoutManager();
}

void CPolynomialsDlg::freeLayoutManager() {
	if (m_layoutManager) {
		delete m_layoutManager;
		m_layoutManager = nullptr;
	}
}

void CPolynomialsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPolynomialsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_FILE_QUIT, OnFileQuit)
	ON_COMMAND(ID_FILE_OPEN32771, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE32772, OnFileSave)
	ON_COMMAND(ID_EDIT_UNDO32774, OnEditUndo)
	ON_COMMAND(ID_EDIT_REDO32775, OnEditRedo)
	ON_COMMAND(ID_EDIT_ADD, OnEditAdd)
	ON_COMMAND(ID_EDIT_SUB, OnEditSub)
	ON_COMMAND(ID_EDIT_MUL, OnEditMul)
	ON_COMMAND(ID_EDIT_DIV, OnEditDiv)
	ON_COMMAND(ID_HELP_ABOUT, OnHelpAbout)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO32774, OnUpdateEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO32775, OnUpdateEditRedo)
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_MFCBUTTONX, &CPolynomialsDlg::OnBnClickedMfcbuttonx)
	ON_BN_CLICKED(IDC_MFCBUTTON0, &CPolynomialsDlg::OnBnClickedMfcbutton0)
	ON_BN_CLICKED(IDC_MFCBUTTON1, &CPolynomialsDlg::OnBnClickedMfcbutton1)
	ON_BN_CLICKED(IDC_MFCBUTTON2, &CPolynomialsDlg::OnBnClickedMfcbutton2)
	ON_BN_CLICKED(IDC_MFCBUTTON3, &CPolynomialsDlg::OnBnClickedMfcbutton3)
	ON_BN_CLICKED(IDC_MFCBUTTON4, &CPolynomialsDlg::OnBnClickedMfcbutton4)
	ON_BN_CLICKED(IDC_MFCBUTTON5, &CPolynomialsDlg::OnBnClickedMfcbutton5)
	ON_BN_CLICKED(IDC_MFCBUTTON6, &CPolynomialsDlg::OnBnClickedMfcbutton6)
	ON_BN_CLICKED(IDC_MFCBUTTON7, &CPolynomialsDlg::OnBnClickedMfcbutton7)
	ON_BN_CLICKED(IDC_MFCBUTTON8, &CPolynomialsDlg::OnBnClickedMfcbutton8)
	ON_BN_CLICKED(IDC_MFCBUTTON9, &CPolynomialsDlg::OnBnClickedMfcbutton9)
	ON_BN_CLICKED(IDC_MFCBUTTONADD, &CPolynomialsDlg::OnBnClickedMfcbuttonadd)
	ON_BN_CLICKED(IDC_MFCBUTTONSUB, &CPolynomialsDlg::OnBnClickedMfcbuttonsub)
	ON_BN_CLICKED(IDC_MFCBUTTONMUL, &CPolynomialsDlg::OnBnClickedMfcbuttonmul)
	ON_BN_CLICKED(IDC_MFCBUTTONDIV, &CPolynomialsDlg::OnBnClickedMfcbuttondiv)
	ON_BN_CLICKED(IDC_MFCBUTTONPOW, &CPolynomialsDlg::OnBnClickedMfcbuttonpow)
	ON_BN_CLICKED(IDC_MFCBUTTONDOT, &CPolynomialsDlg::OnBnClickedMfcbuttondot)
	ON_BN_CLICKED(IDC_MFCBUTTONDEL, &CPolynomialsDlg::OnBnClickedMfcbuttondel)
	ON_BN_CLICKED(IDC_MFCBUTTONCLEAR, &CPolynomialsDlg::OnBnClickedMfcbuttonclear)
	ON_BN_CLICKED(IDC_MFCBUTTONEQ, &CPolynomialsDlg::OnBnClickedMfcbuttoneq)
	ON_BN_CLICKED(IDC_MFCBUTTONREMOVE, &CPolynomialsDlg::OnBnClickedMfcbuttonremove)
	ON_BN_CLICKED(IDC_MFCBUTTONINSERT, &CPolynomialsDlg::OnBnClickedMfcbuttoninsert)
END_MESSAGE_MAP()


// CPolynomialsDlg message handlers

BOOL CPolynomialsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//setCaption(L"Polynomials");

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	//SetIcon(m_hIcon, FALSE);		// Set small icon

	// Set anchors
	if (m_layoutManager) {
		m_layoutManager->SetControl(GetDlgItem(IDC_PolynomialsList), DialogLayoutManager::ANCHOR_LEFT | DialogLayoutManager::ANCHOR_RIGHT | DialogLayoutManager::ANCHOR_TOP);
		m_layoutManager->SetControl(GetDlgItem(IDC_MFCBUTTONINSERT), DialogLayoutManager::ANCHOR_RIGHT | DialogLayoutManager::ANCHOR_TOP);
		m_layoutManager->SetControl(GetDlgItem(IDC_MFCBUTTONREMOVE), DialogLayoutManager::ANCHOR_RIGHT | DialogLayoutManager::ANCHOR_TOP);
		m_layoutManager->SetControl(GetDlgItem(IDC_POLYNOMIALS_LABEL), DialogLayoutManager::ANCHOR_LEFT | DialogLayoutManager::ANCHOR_TOP);
		m_layoutManager->SetControl(GetDlgItem(IDC_INPUT_TEXT), DialogLayoutManager::ANCHOR_TOP | DialogLayoutManager::ANCHOR_RIGHT);

		m_layoutManager->SetControl(GetDlgItem(IDC_MFCBUTTONX), DialogLayoutManager::ANCHOR_RIGHT | DialogLayoutManager::ANCHOR_TOP);
		m_layoutManager->SetControl(GetDlgItem(IDC_MFCBUTTON0), DialogLayoutManager::ANCHOR_RIGHT | DialogLayoutManager::ANCHOR_TOP);
		m_layoutManager->SetControl(GetDlgItem(IDC_MFCBUTTON1), DialogLayoutManager::ANCHOR_RIGHT | DialogLayoutManager::ANCHOR_TOP);
		m_layoutManager->SetControl(GetDlgItem(IDC_MFCBUTTON2), DialogLayoutManager::ANCHOR_RIGHT | DialogLayoutManager::ANCHOR_TOP);
		m_layoutManager->SetControl(GetDlgItem(IDC_MFCBUTTON3), DialogLayoutManager::ANCHOR_RIGHT | DialogLayoutManager::ANCHOR_TOP);
		m_layoutManager->SetControl(GetDlgItem(IDC_MFCBUTTON4), DialogLayoutManager::ANCHOR_RIGHT | DialogLayoutManager::ANCHOR_TOP);
		m_layoutManager->SetControl(GetDlgItem(IDC_MFCBUTTON5), DialogLayoutManager::ANCHOR_RIGHT | DialogLayoutManager::ANCHOR_TOP);
		m_layoutManager->SetControl(GetDlgItem(IDC_MFCBUTTON6), DialogLayoutManager::ANCHOR_RIGHT | DialogLayoutManager::ANCHOR_TOP);
		m_layoutManager->SetControl(GetDlgItem(IDC_MFCBUTTON7), DialogLayoutManager::ANCHOR_RIGHT | DialogLayoutManager::ANCHOR_TOP);
		m_layoutManager->SetControl(GetDlgItem(IDC_MFCBUTTON8), DialogLayoutManager::ANCHOR_RIGHT | DialogLayoutManager::ANCHOR_TOP);
		m_layoutManager->SetControl(GetDlgItem(IDC_MFCBUTTON9), DialogLayoutManager::ANCHOR_RIGHT | DialogLayoutManager::ANCHOR_TOP);
		m_layoutManager->SetControl(GetDlgItem(IDC_MFCBUTTONDOT), DialogLayoutManager::ANCHOR_RIGHT | DialogLayoutManager::ANCHOR_TOP);
		m_layoutManager->SetControl(GetDlgItem(IDC_MFCBUTTONADD), DialogLayoutManager::ANCHOR_RIGHT | DialogLayoutManager::ANCHOR_TOP);
		m_layoutManager->SetControl(GetDlgItem(IDC_MFCBUTTONSUB), DialogLayoutManager::ANCHOR_RIGHT | DialogLayoutManager::ANCHOR_TOP);
		m_layoutManager->SetControl(GetDlgItem(IDC_MFCBUTTONMUL), DialogLayoutManager::ANCHOR_RIGHT | DialogLayoutManager::ANCHOR_TOP);
		m_layoutManager->SetControl(GetDlgItem(IDC_MFCBUTTONDIV), DialogLayoutManager::ANCHOR_RIGHT | DialogLayoutManager::ANCHOR_TOP);
		m_layoutManager->SetControl(GetDlgItem(IDC_MFCBUTTONPOW), DialogLayoutManager::ANCHOR_RIGHT | DialogLayoutManager::ANCHOR_TOP);
		m_layoutManager->SetControl(GetDlgItem(IDC_MFCBUTTONEQ), DialogLayoutManager::ANCHOR_RIGHT | DialogLayoutManager::ANCHOR_TOP);
		m_layoutManager->SetControl(GetDlgItem(IDC_MFCBUTTONDEL), DialogLayoutManager::ANCHOR_RIGHT | DialogLayoutManager::ANCHOR_TOP);
		m_layoutManager->SetControl(GetDlgItem(IDC_MFCBUTTONCLEAR), DialogLayoutManager::ANCHOR_RIGHT | DialogLayoutManager::ANCHOR_TOP);

		m_layoutManager->SetControl(GetDlgItem(IDC_CONSOLE), DialogLayoutManager::ANCHOR_LEFT | DialogLayoutManager::ANCHOR_RIGHT | DialogLayoutManager::ANCHOR_TOP | DialogLayoutManager::ANCHOR_BOTTOM);

		// Save layout so we will be able to restore it when window is resized.
		m_layoutManager->Save(this);
	}

	// Share handles of main controls among the application, so commands can access them.
	PolynomialsApplication::getInstance().setMainWindow(this);
	PolynomialsApplication::getInstance().setInputTextControl((CEdit *)GetDlgItem(IDC_INPUT_TEXT));
	PolynomialsApplication::getInstance().setPolyListControl((CListCtrl *)GetDlgItem(IDC_PolynomialsList));
	PolynomialsApplication::getInstance().setConsole((CEdit *)GetDlgItem(IDC_CONSOLE));

	// Create an invisible column so we will use the list control as a vertical list, instead of horizontal one.
	CListCtrl * list = (CListCtrl *)GetDlgItem(IDC_PolynomialsList);
	list->InsertColumn(0, L"");
	list->SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPolynomialsDlg::setCaption(const CString & caption) {
	m_strCaption = caption;
	SetWindowText(m_strCaption);
}

void CPolynomialsDlg::setUnsavedChangesState() {
	PolynomialsApplication::getInstance().setUnsavedChanges(true);
	setCaption(L"* Polynomials");
}

void CPolynomialsDlg::removeUnsavedChangesState() {
	PolynomialsApplication::getInstance().setUnsavedChanges(false);
	setCaption(L"Polynomials");
}

void CPolynomialsDlg::logMessage(const std::wstring & message)
{
	CEdit * edit = (CEdit *)GetDlgItem(IDC_CONSOLE);
	
	time_t rawtime;
	struct tm timeinfo;
	char buffer[128];

	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);

	strftime(buffer, sizeof(buffer), "[%d/%m/%Y %H:%M:%S] INFO: ", &timeinfo);
	std::string str(buffer);
	std::wstring timeStr(str.begin(), str.end());

	int length = edit->GetWindowTextLengthW();
	edit->SetSel(length, length);
	edit->ReplaceSel((timeStr + message + L"\r\n").c_str());
}

void CPolynomialsDlg::logMessageWithInputText(const std::wstring & message)
{
	CEdit * edit = (CEdit *)GetDlgItem(IDC_INPUT_TEXT);
	WCHAR * txt = AbstractInputTextKeeperAction::getWholeText(edit);
	logMessage(message + std::wstring(txt));
	delete txt;
}

BOOL isNavigationKey(WPARAM key) {
	switch (key) {
		case VK_LEFT:
		case VK_RIGHT:
		case VK_UP:
		case VK_SHIFT:
		case LVKF_SHIFT:
		case VK_CAPITAL:
		case VK_CONTROL:
		case LVKF_CONTROL:
		case VK_OEM_WSCTRL:
		case VK_MENU:
		case LVKF_ALT:
			return true;
		default: return false;
	}
}

void redirectMessage(HWND sender, MSG* pMsg) {
	if (sender != pMsg->hwnd) {
		SendMessage(pMsg->hwnd, pMsg->message, pMsg->wParam, pMsg->lParam);
	}
}

BOOL CPolynomialsDlg::PreTranslateMessage(MSG* pMsg)
{
	try {
		// Globally catch key down message to redirect it to the input.
		if (pMsg->message == WM_KEYDOWN)
		{
			// Do not redirect event if sender is the console or list control, to let user copy text.
			if ((pMsg->hwnd != GetDlgItem(IDC_CONSOLE)->GetSafeHwnd()) && (pMsg->hwnd != GetDlgItem(IDC_PolynomialsList)->GetSafeHwnd())) {
				if (pMsg->wParam == VK_RETURN) {
					OnBnClickedMfcbuttoneq();
				}
				// If it is a navigation key, and current handle is the input edit, redirect it
				else if (isNavigationKey(pMsg->wParam)) {
					redirectMessage(GetSafeHwnd(), pMsg);
				}
				else {
					try {
						ActionContext context(pMsg->lParam, pMsg->wParam);
						PolynomialsApplication::getInstance().getActionExecutor()->execute(Action::KeyDown, context);
					}
					catch (ExecuteActionException & e) {
						showExceptionMessageToUser(e);
					}
				}

				return true;
			}
		}
		else if ((pMsg->message == WM_RBUTTONDOWN) || (pMsg->message == WM_RBUTTONUP)) {
			// Ignore it so user cannot open CEdit right click menu
			return true;
		}
	}
	catch (...) {
		showGeneralErrorToUser();
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CPolynomialsDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPolynomialsDlg::OnPaint()
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
HCURSOR CPolynomialsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPolynomialsDlg::OnUpdateEditUndo(CCmdUI* pCmdUI) {
	pCmdUI->Enable(PolynomialsApplication::getInstance().getActionExecutor()->canUndo() ? TRUE : FALSE);
}

void CPolynomialsDlg::OnUpdateEditRedo(CCmdUI* pCmdUI) {
	pCmdUI->Enable(PolynomialsApplication::getInstance().getActionExecutor()->canRedo() ? TRUE : FALSE);
}

void CPolynomialsDlg::OnFileOpen() {
	try {
	}
	catch (...) {
		showGeneralErrorToUser();
	}
}

void CPolynomialsDlg::OnFileSave() {
	try {
		removeUnsavedChangesState();
	}
	catch (...) {
		showGeneralErrorToUser();
	}
}

void CPolynomialsDlg::OnFileQuit() {
	SendMessage(WM_CLOSE);
}

void CPolynomialsDlg::OnEditUndo() {
	try {
		if (PolynomialsApplication::getInstance().getActionExecutor()->canUndo()) {
			PolynomialsApplication::getInstance().getActionExecutor()->undo();
		}
		else {
			logMessage(L"There is nothing to undo.");
		}
	}
	catch (...) {
		showGeneralErrorToUser();
	}
}

void CPolynomialsDlg::OnEditRedo() {
	try {
		if (PolynomialsApplication::getInstance().getActionExecutor()->canRedo()) {
			PolynomialsApplication::getInstance().getActionExecutor()->redo();
		}
		else {
			logMessage(L"There is nothing to redo.");
		}
	}
	catch (...) {
		showGeneralErrorToUser();
	}
}

bool CPolynomialsDlg::canExecuteArithmeticAction() {
	bool isPossible = ((CListCtrl *)GetDlgItem(IDC_PolynomialsList))->GetItemCount() > 0;

	if (!isPossible) {
		AfxMessageBox(L"Unable to execute arithmetic actions. Insert polynomials to the list first.", MB_ICONASTERISK | MB_OK);
	}

	return isPossible;
}

void CPolynomialsDlg::OnEditAdd() {
	if (!canExecuteArithmeticAction()) {
		return;
	}

	try {
		PolySelectionDialog dlg(1, ((CListCtrl *)GetDlgItem(IDC_PolynomialsList))->GetItemCount(), L"Add", this);
		INT_PTR response = dlg.DoModal();
		if (response == IDOK)
		{
			int left = dlg.getLeftPolyIndex() - 1;
			int right = dlg.getRightPolyIndex() - 1;

			try {
				PolynomialsApplication::getInstance().getActionExecutor()->execute(Action::Add, ActionContext(left, right));
			}
			catch (ExecuteActionException & e) {
				showExceptionMessageToUser(e);
			}
		}
	}
	catch (...) {
		showGeneralErrorToUser();
	}
}

void CPolynomialsDlg::OnEditSub() {
	if (!canExecuteArithmeticAction()) {
		return;
	}

	try {
		PolySelectionDialog dlg(1, ((CListCtrl *)GetDlgItem(IDC_PolynomialsList))->GetItemCount(), L"Sub", this);
		INT_PTR response = dlg.DoModal();
		if (response == IDOK)
		{
			int left = dlg.getLeftPolyIndex() - 1;
			int right = dlg.getRightPolyIndex() - 1;

			try {
				PolynomialsApplication::getInstance().getActionExecutor()->execute(Action::Sub, ActionContext(left, right));
			}
			catch (ExecuteActionException & e) {
				showExceptionMessageToUser(e);
			}
		}
	}
	catch (...) {
		showGeneralErrorToUser();
	}
}

void CPolynomialsDlg::OnEditMul() {
	if (!canExecuteArithmeticAction()) {
		return;
	}

	try {
		PolySelectionDialog dlg(1, ((CListCtrl *)GetDlgItem(IDC_PolynomialsList))->GetItemCount(), L"Mul", this);
		INT_PTR response = dlg.DoModal();
		if (response == IDOK)
		{
			int left = dlg.getLeftPolyIndex() - 1;
			int right = dlg.getRightPolyIndex() - 1;

			try {
				PolynomialsApplication::getInstance().getActionExecutor()->execute(Action::Mul, ActionContext(left, right));
			}
			catch (ExecuteActionException & e) {
				showExceptionMessageToUser(e);
			}
		}
	}
	catch (...) {
		showGeneralErrorToUser();
	}
}

void CPolynomialsDlg::OnEditDiv() {
	if (!canExecuteArithmeticAction()) {
		return;
	}

	try {
		PolySelectionDialog dlg(1, ((CListCtrl *)GetDlgItem(IDC_PolynomialsList))->GetItemCount(), L"Div", this);
		INT_PTR response = dlg.DoModal();
		if (response == IDOK)
		{
			int left = dlg.getLeftPolyIndex() - 1;
			int right = dlg.getRightPolyIndex() - 1;

			try {
				PolynomialsApplication::getInstance().getActionExecutor()->execute(Action::Div, ActionContext(left, right));
			}
			catch (ExecuteActionException & e) {
				showExceptionMessageToUser(e);
			}
		}
	}
	catch (...) {
		showGeneralErrorToUser();
	}
}

void CPolynomialsDlg::OnHelpAbout() {
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}


void CPolynomialsDlg::OnClose()
{
	// If there are unsaved changes, prompt to ask user if he wants to exit without saving.
	if (PolynomialsApplication::getInstance().anyUnsavedChanges()) 
	{
		int answer = AfxMessageBox(L"There are unsaved changes. Are you sure you want to exit?", MB_ICONEXCLAMATION | MB_YESNO);

		if (answer == IDYES)
		{
			TRACE(traceAppMsg, 0, "Information: exit approved. Closing application.\n");
			freeLayoutManager();
			CDialogEx::OnClose();
		}
		else if (answer == IDNO)
		{
			TRACE(traceAppMsg, 0, "Information: exit cancelled.\n");
		}
	}
	// If there is nothing to save, just exit.
	else 
	{
		freeLayoutManager();
		CDialogEx::OnClose();
	}
}

void CPolynomialsDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// Restore layout only after window initialized and components location is saved in layout manager.
	if (m_layoutManager && m_layoutManager->IsSaved()) {
		m_layoutManager->Restore(this);
	}

	CListCtrl * list = (CListCtrl *)GetDlgItem(IDC_PolynomialsList);
	if (list) {
		list->SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	}
}


void CPolynomialsDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x = 550;
	lpMMI->ptMinTrackSize.y = 450;

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}


// ####################### Calculator buttons ############
void CPolynomialsDlg::OnBnClickedMfcbuttonx()
{
	MSG msg;
	msg.hwnd = GetSafeHwnd();
	msg.message = WM_KEYDOWN;
	msg.wParam = 'x';
	PreTranslateMessage(&msg);
}


void CPolynomialsDlg::OnBnClickedMfcbutton0()
{
	MSG msg;
	msg.hwnd = GetSafeHwnd();
	msg.message = WM_KEYDOWN;
	msg.wParam = '0';
	PreTranslateMessage(&msg);
}


void CPolynomialsDlg::OnBnClickedMfcbutton1()
{
	MSG msg;
	msg.hwnd = GetSafeHwnd();
	msg.message = WM_KEYDOWN;
	msg.wParam = '1';
	PreTranslateMessage(&msg);
}


void CPolynomialsDlg::OnBnClickedMfcbutton2()
{
	MSG msg;
	msg.hwnd = GetSafeHwnd();
	msg.message = WM_KEYDOWN;
	msg.wParam = '2';
	PreTranslateMessage(&msg);
}


void CPolynomialsDlg::OnBnClickedMfcbutton3()
{
	MSG msg;
	msg.hwnd = GetSafeHwnd();
	msg.message = WM_KEYDOWN;
	msg.wParam = '3';
	PreTranslateMessage(&msg);
}


void CPolynomialsDlg::OnBnClickedMfcbutton4()
{
	MSG msg;
	msg.hwnd = GetSafeHwnd();
	msg.message = WM_KEYDOWN;
	msg.wParam = '4';
	PreTranslateMessage(&msg);
}


void CPolynomialsDlg::OnBnClickedMfcbutton5()
{
	MSG msg;
	msg.hwnd = GetSafeHwnd();
	msg.message = WM_KEYDOWN;
	msg.wParam = '5';
	PreTranslateMessage(&msg);
}


void CPolynomialsDlg::OnBnClickedMfcbutton6()
{
	MSG msg;
	msg.hwnd = GetSafeHwnd();
	msg.message = WM_KEYDOWN;
	msg.wParam = '6';
	PreTranslateMessage(&msg);
}


void CPolynomialsDlg::OnBnClickedMfcbutton7()
{
	MSG msg;
	msg.hwnd = GetSafeHwnd();
	msg.message = WM_KEYDOWN;
	msg.wParam = '7';
	PreTranslateMessage(&msg);
}


void CPolynomialsDlg::OnBnClickedMfcbutton8()
{
	MSG msg;
	msg.hwnd = GetSafeHwnd();
	msg.message = WM_KEYDOWN;
	msg.wParam = '8';
	PreTranslateMessage(&msg);
}


void CPolynomialsDlg::OnBnClickedMfcbutton9()
{
	MSG msg;
	msg.hwnd = GetSafeHwnd();
	msg.message = WM_KEYDOWN;
	msg.wParam = '9';
	PreTranslateMessage(&msg);
}


void CPolynomialsDlg::OnBnClickedMfcbuttonadd()
{
	MSG msg;
	msg.hwnd = GetSafeHwnd();
	msg.message = WM_KEYDOWN;
	msg.wParam = '+';
	PreTranslateMessage(&msg);
}


void CPolynomialsDlg::OnBnClickedMfcbuttonsub()
{
	MSG msg;
	msg.hwnd = GetSafeHwnd();
	msg.message = WM_KEYDOWN;
	msg.wParam = '-';
	PreTranslateMessage(&msg);
}


void CPolynomialsDlg::OnBnClickedMfcbuttonmul()
{
	MSG msg;
	msg.hwnd = GetSafeHwnd();
	msg.message = WM_KEYDOWN;
	msg.wParam = '*';
	PreTranslateMessage(&msg);
}


void CPolynomialsDlg::OnBnClickedMfcbuttondiv()
{
	MSG msg;
	msg.hwnd = GetSafeHwnd();
	msg.message = WM_KEYDOWN;
	msg.wParam = '/';
	PreTranslateMessage(&msg);
}


void CPolynomialsDlg::OnBnClickedMfcbuttonpow()
{
	MSG msg;
	msg.hwnd = GetSafeHwnd();
	msg.message = WM_KEYDOWN;
	msg.wParam = '^';
	PreTranslateMessage(&msg);
}


void CPolynomialsDlg::OnBnClickedMfcbuttondot()
{
	MSG msg;
	msg.hwnd = GetSafeHwnd();
	msg.message = WM_KEYDOWN;
	msg.wParam = VK_DECIMAL;
	PreTranslateMessage(&msg);
}


void CPolynomialsDlg::OnBnClickedMfcbuttondel()
{
	MSG msg;
	msg.hwnd = GetSafeHwnd();
	msg.message = WM_KEYDOWN;
	msg.wParam = VK_DELETE;
	PreTranslateMessage(&msg);
}


void CPolynomialsDlg::OnBnClickedMfcbuttonclear()
{
	try {
		// Select all text
		CEdit * edit = (CEdit *)GetDlgItem(IDC_INPUT_TEXT);
		edit->SetSel(0, edit->GetWindowTextLengthW());

		// Generate a DELETE message so it will be handled as an edit action
		OnBnClickedMfcbuttondel();
	} 
	catch (...) {
		showGeneralErrorToUser();
	}
}

void CPolynomialsDlg::OnBnClickedMfcbuttoneq()
{
	try {
		PolynomialsApplication::getInstance().getActionExecutor()->execute(Action::Evaluate, ActionContext());
	}
	catch (ExecuteActionException & e) {
		showExceptionMessageToUser(e);
	}
	catch (...) {
		showGeneralErrorToUser();
	}
}


void CPolynomialsDlg::OnBnClickedMfcbuttoninsert()
{
	try {
		PolynomialsApplication::getInstance().getActionExecutor()->execute(Action::InsertPoly, ActionContext());
		setUnsavedChangesState();
	}
	catch (ExecuteActionException & e) {
		showExceptionMessageToUser(e);
	}
	catch (...) {
		showGeneralErrorToUser();
	}
}


void CPolynomialsDlg::OnBnClickedMfcbuttonremove()
{
	try {
		CListCtrl * list = (CListCtrl *)GetDlgItem(IDC_PolynomialsList);
		int selectedIndex = list->GetSelectionMark();

		if (selectedIndex >= 0) {
			try {
				PolynomialsApplication::getInstance().getActionExecutor()->execute(Action::RemovePoly, ActionContext(selectedIndex));
				setUnsavedChangesState();
			}
			catch (ExecuteActionException & e) {
				showExceptionMessageToUser(e);
			}
		}
		else {
			AfxMessageBox(L"Please select a polynomial first.", MB_ICONINFORMATION | MB_OK);
		}
	}
	catch (...) {
		showGeneralErrorToUser();
	}
}
