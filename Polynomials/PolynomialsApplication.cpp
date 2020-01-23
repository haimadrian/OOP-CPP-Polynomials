
#include "PolynomialsApplication.h"

PolynomialsApplication & PolynomialsApplication::getInstance() {
	static PolynomialsApplication instance; // Unique instance
	return instance;
}

PolynomialsApplication::PolynomialsApplication():unsavedChanges(false){
	
}

CPolynomialsDlg * PolynomialsApplication::getMainWindow() const {
	return mainWindow;
}

void PolynomialsApplication::setMainWindow(CPolynomialsDlg * handle) {
	mainWindow = handle;
}

CEdit * PolynomialsApplication::getInputTextControl() const {
	return inputTextControl;
}

void PolynomialsApplication::setInputTextControl(CEdit * handle) {
	inputTextControl = handle;
}

CListCtrl * PolynomialsApplication::getPolyListControl() const {
	return polyListControl;
}

void PolynomialsApplication::setPolyListControl(CListCtrl * handle) {
	polyListControl = handle;
}

CEdit * PolynomialsApplication::getConsole() const {
	return console;
}

void PolynomialsApplication::setConsole(CEdit * handle) {
	console = handle;
}

bool PolynomialsApplication::anyUnsavedChanges() const {
	return unsavedChanges;
}

void PolynomialsApplication::setUnsavedChanges(bool value) {
	unsavedChanges = value;
}

ActionExecutor * PolynomialsApplication::getActionExecutor()
{
	return &actionExecutor;
}