#pragma once

#ifndef POLYNOMIALS_ACTIONCONTEXT_H
#define POLYNOMIALS_ACTIONCONTEXT_H

#include "../framework.h"
#include <string>

class ActionContext
{
private:
	LPARAM messageLParam;
	WPARAM messageWParam;
	int selectedPolyIndex;
	int selectedPolyIndex2;
	double xValue;
	std::wstring filePath;
public:
	ActionContext() = default;
	ActionContext(int selectedPolyIndex) :selectedPolyIndex(selectedPolyIndex) {}
	ActionContext(int selectedPolyIndex, int selectedPolyIndex2) :selectedPolyIndex(selectedPolyIndex), selectedPolyIndex2(selectedPolyIndex2) {}
	ActionContext(LPARAM lParam, WPARAM wParam) :messageLParam(lParam), messageWParam(wParam) {}
	ActionContext(int selectedPolyIndex, double xValue) :selectedPolyIndex(selectedPolyIndex), xValue(xValue) {}
	ActionContext(std::wstring filePath) : filePath(filePath) {}
	LPARAM getLParam() const { return messageLParam; };
	WPARAM getWParam() const { return messageWParam; };
	int getSelectedPolyIndex() const { return selectedPolyIndex; };
	int getSelectedPolyIndex2() const { return selectedPolyIndex2; };
	double getXValue() const { return xValue; };
	std::wstring getFilePath() const { return filePath; };
};


#endif

