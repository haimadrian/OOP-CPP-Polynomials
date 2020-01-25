/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

#pragma once

#ifndef POLYNOMIALS_DIALOGLAYOUTMANAGER_H
#define POLYNOMIALS_DIALOGLAYOUTMANAGER_H


#include "framework.h"
#include <vector>

 /*
 Dialog Layout Manager for MFC
 Copyright 2009 Adam Sawicki
 E-mail: sawickiap(at)poczta(dot)onet(dot)pl
 Homepage: http://regedit.gamedev.pl/
 License: Public Domain
 */
class DialogLayoutManager
{
public:
	static const unsigned ANCHOR_LEFT = 0x01;
	static const unsigned ANCHOR_TOP = 0x02;
	static const unsigned ANCHOR_RIGHT = 0x04;
	static const unsigned ANCHOR_BOTTOM = 0x08;

	DialogLayoutManager();
	~DialogLayoutManager();

	void SetControl(CWnd *wnd, unsigned anchorFlags);
	void RemoveControl(CWnd *wnd);

	bool IsSaved() { return SavedClientSizeX != -1; }
	void Save(CWnd *parentWindow);
	void Restore(CWnd *parentWindow);

private:
	struct SControlDesc
	{
		CWnd *Wnd;
		unsigned AnchorFlags;
		RECT Rect;
	};

	std::vector<SControlDesc> ControlDescs;
	int SavedClientSizeX, SavedClientSizeY;
};

#endif