/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

#include <vector>
#include <sstream>
#include <string>
#include "framework.h"
#include "Polynomials.h"
#include "GraphDialog.h"
#include "afxdialogex.h"


// GraphDialog dialog

IMPLEMENT_DYNAMIC(GraphDialog, CDialogEx)

GraphDialog::GraphDialog(Polynomial & polynomial, CWnd* pParent /*=nullptr*/)
	: polynomial(polynomial), CDialogEx(IDD_GRAPH_DIALOG, pParent)
{

}

GraphDialog::~GraphDialog()
{
}

void GraphDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GraphDialog, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// GraphDialog message handlers
BOOL GraphDialog::OnInitDialog() {
	std::ostringstream out;
	out << "Graph of:   " << polynomial;

	std::string str = out.str();
	std::wstring wstr(str.begin(), str.end());

	SetWindowText(wstr.c_str());

	return TRUE;
}

void GraphDialog::OnPaint()
{
	CPaintDC dc(this); 

	RECT windowRect;
	GetClientRect(&windowRect);

	CBrush brush;
	brush.CreateSolidBrush((COLORREF)RGB(255, 255, 255));
	dc.FillRect(&windowRect, &brush);

	paintTableArea(dc);

	paintFunction(dc);
}

void GraphDialog::paintFunction(CPaintDC & dc) {
	RECT windowRect;
	GetClientRect(&windowRect);

	int middleHorizontal = (windowRect.right - windowRect.left) / 2;
	int middleVertical = (windowRect.bottom - windowRect.top) / 2;

	double funcValue;
	std::vector<CPoint> actualPoints;

	// If x=0 is illegal, e.g. 1/x, we separate the graph to 2.
	std::vector<CPoint> optionalActualPoints;
	bool redirectToOptional = false, isFirstOptionalMarked = false;

	double maxDeg = polynomial.getMaxEffectiveDegree();
	double minDeg = polynomial.getMinEffectiveDegree();
	double divideBy = 1;

	// In order to display a beutiful graph, normalize the function value
	if (((maxDeg < 0) || (maxDeg > 1)) && (polynomial.getEffectiveCount() == 1)) {
		divideBy = ((maxDeg != 1) && (maxDeg != 2)) ? 30.0 : 10.0;
	}

	// Run over axis
	for (int i = 0; i < windowRect.right; i++) {
		// Here we normalize the value of x in order to draw a more easier to see graph.
		double x = ((double)i - middleHorizontal) / divideBy;
		
		// Be careful not to divide by zero.
		// When we get to divide by zero, start filling in the other vector such that we will have
		// two lines with a vertical asymptote
		if ((minDeg >= 0) || (fabs(x) > 0.1)) {
			funcValue = polynomial(x);

			if (abs(funcValue) < SHORT_MAX) {
				if (!redirectToOptional) {
					actualPoints.push_back(CPoint(i, middleVertical - (int)funcValue));
				} else {
					// Define the "infinity" point of the line we are about to fill.
					if (!isFirstOptionalMarked) {
						x = ((double)i + 10 - middleHorizontal) / divideBy;
						optionalActualPoints.push_back(CPoint(i, (funcValue < 0) ? windowRect.bottom : windowRect.top));
						isFirstOptionalMarked = true;
					}
					else {
						optionalActualPoints.push_back(CPoint(i, middleVertical - (int)funcValue));
					}
				}
			}
		}
		else if (!redirectToOptional){
			// This means there are two lines.
			redirectToOptional = true;

			// Define the "infinity" point for the line we fill so far.
			actualPoints.push_back(CPoint(i - 1, (funcValue < 0) ? windowRect.bottom : windowRect.top));
		}
	}

	CPen pen;
	pen.CreatePen(PS_SOLID, 2, (COLORREF)RGB(255, 0, 0));
	dc.SelectObject(&pen);

	// Copy points to array, so we will pass it to the DC
	size_t amountOfPoints = actualPoints.size();
	CPoint * points = new CPoint[amountOfPoints];
	for (size_t i = 0; i < amountOfPoints; i++) {
		points[i] = actualPoints[i];
	}

	// In case there are two lines, add the second line to the array and use PolyPolyline instead of Polyline.
	if (redirectToOptional) {
		size_t amountOfPoints2 = optionalActualPoints.size();
		size_t newLen = amountOfPoints + amountOfPoints2;
		points = (CPoint *)realloc(points, newLen * sizeof(CPoint));

		for (size_t i = amountOfPoints; i < newLen; i++) {
			points[i] = optionalActualPoints[i - amountOfPoints];
		}

		DWORD  linesLength[2] = { (DWORD)amountOfPoints , (DWORD)amountOfPoints2 };
		dc.PolyPolyline(points, linesLength, 2);
	}
	else {
		dc.Polyline(points, (int)amountOfPoints);
	}

	delete points;
}

void GraphDialog::paintTableArea(CPaintDC & dc) {
	RECT windowRect;
	GetClientRect(&windowRect);

	int middleVertical = (windowRect.bottom - windowRect.top) / 2;
	int middleHorizontal = (windowRect.right - windowRect.left) / 2;

	const int amountOfPoints = 12, amountOfLines = 6;
	CPoint points[amountOfPoints];
	DWORD  linesLength[amountOfLines] = { 2, 2, 2, 2, 2, 2 };

	// X's
	int xStart = windowRect.right / 10, xEnd = windowRect.right - xStart, arrowLength = 30;
	int i = 0;

	points[i++] = CPoint(xStart, middleVertical);
	points[i++] = CPoint(xEnd, middleVertical);

	// X Arrow
	points[i++] = CPoint(xEnd, middleVertical);
	points[i++] = CPoint(xEnd - arrowLength, middleVertical - arrowLength);

	points[i++] = CPoint(xEnd, middleVertical);
	points[i++] = CPoint(xEnd - arrowLength, middleVertical + arrowLength);

	// Y's
	int yStart = windowRect.bottom / 10, yEnd = windowRect.bottom - yStart;
	points[i++] = CPoint(middleHorizontal, yStart);
	points[i++] = CPoint(middleHorizontal, yEnd);

	// Y Arrow
	points[i++] = CPoint(middleHorizontal, yStart);
	points[i++] = CPoint(middleHorizontal - arrowLength, yStart + arrowLength);

	points[i++] = CPoint(middleHorizontal, yStart);
	points[i++] = CPoint(middleHorizontal + arrowLength, yStart + arrowLength);

	CPen pen;
	pen.CreatePen(PS_SOLID, 7, (COLORREF)RGB(0, 0, 255));
	dc.SelectObject(&pen);

	dc.PolyPolyline(points, linesLength, amountOfLines);

	CFont font;
	font.CreateFontW(50, 20, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, 
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"Microsoft Sans Serif");
	dc.SelectObject(&font);

	UINT txtParams = DT_VCENTER | DT_SINGLELINE | DS_CENTER | TRANSPARENT;
	RECT xPos;
	xPos.top = middleVertical - 30;
	xPos.left = xEnd + 5;
	xPos.right = xPos.left + 50;
	xPos.bottom = xPos.top + 50;
	dc.DrawTextW(L"x", &xPos, txtParams);

	RECT yPos;
	yPos.top = yStart - 60;
	yPos.left = middleHorizontal - 25;
	yPos.right = yPos.left + 50;
	yPos.bottom = yPos.top + 50;
	dc.DrawTextW(L"y", &yPos, txtParams);
}
