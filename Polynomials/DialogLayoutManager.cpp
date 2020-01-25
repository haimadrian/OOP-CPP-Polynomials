
#include "DialogLayoutManager.h"

DialogLayoutManager::DialogLayoutManager()
	: SavedClientSizeX(-1)
	, SavedClientSizeY(-1)
{
}

DialogLayoutManager::~DialogLayoutManager()
{
	ControlDescs.clear();
}

void DialogLayoutManager::SetControl(CWnd *wnd, unsigned anchorFlags)
{
	size_t count = ControlDescs.size();
	size_t index;
	for (index = 0; index < count; index++)
		if (ControlDescs[index].Wnd == wnd)
			break;
	if (index == count) {
		ControlDescs.push_back(SControlDesc());
	}

	ControlDescs[index].Wnd = wnd;
	ControlDescs[index].AnchorFlags = anchorFlags;
	ControlDescs[index].Rect.left = -1;
	ControlDescs[index].Rect.top = -1;
	ControlDescs[index].Rect.right = -1;
	ControlDescs[index].Rect.bottom = -1;
}

void DialogLayoutManager::RemoveControl(CWnd *wnd)
{
	if (wnd == NULL) return;

	size_t count = ControlDescs.size();
	for (size_t index = 0; index < count; index++)
	{
		if (ControlDescs[index].Wnd == wnd)
		{
			ControlDescs.erase(ControlDescs.begin() + index);
			break;
		}
	}
}

void DialogLayoutManager::Save(CWnd *parentWindow)
{
	RECT wndClientRect;
	parentWindow->GetClientRect(&wndClientRect);
	SavedClientSizeX = wndClientRect.right - wndClientRect.left;
	SavedClientSizeY = wndClientRect.bottom - wndClientRect.top;

	size_t count = ControlDescs.size();
	for (size_t i = 0; i < count; i++)
	{
		ControlDescs[i].Wnd->GetWindowRect(&ControlDescs[i].Rect);
		parentWindow->ScreenToClient(&ControlDescs[i].Rect);
	}
}

void DialogLayoutManager::Restore(CWnd *parentWindow)
{
	RECT wndClientRect;
	parentWindow->GetClientRect(&wndClientRect);
	int newClientSizeX = wndClientRect.right - wndClientRect.left;
	int newClientSizeY = wndClientRect.bottom - wndClientRect.top;

	size_t count = ControlDescs.size();
	RECT newRect;
	long savedControlSizeX, savedControlSizeY;

	for (size_t i = 0; i < count; i++)
	{
		const SControlDesc &desc = ControlDescs[i];
		savedControlSizeX = desc.Rect.right - desc.Rect.left;
		savedControlSizeY = desc.Rect.bottom - desc.Rect.top;

		if ((desc.AnchorFlags & ANCHOR_LEFT) != 0 && (desc.AnchorFlags & ANCHOR_RIGHT) != 0)
		{
			newRect.left = desc.Rect.left;
			newRect.right = newClientSizeX - (SavedClientSizeX - desc.Rect.right);
		}
		else if ((desc.AnchorFlags & ANCHOR_RIGHT) != 0)
		{
			newRect.right = newClientSizeX - (SavedClientSizeX - desc.Rect.right);
			newRect.left = newRect.right - savedControlSizeX;
		}
		else
		{
			newRect.left = desc.Rect.left;
			newRect.right = newRect.left + savedControlSizeX;
		}

		if ((desc.AnchorFlags & ANCHOR_TOP) != 0 && (desc.AnchorFlags & ANCHOR_BOTTOM) != 0)
		{
			newRect.top = desc.Rect.top;
			newRect.bottom = newClientSizeY - (SavedClientSizeY - desc.Rect.bottom);
		}
		else if ((desc.AnchorFlags & ANCHOR_BOTTOM) != 0)
		{
			newRect.bottom = newClientSizeY - (SavedClientSizeY - desc.Rect.bottom);
			newRect.top = newRect.bottom - savedControlSizeY;
		}
		else
		{
			newRect.top = desc.Rect.top;
			newRect.bottom = newRect.top + savedControlSizeY;
		}

		desc.Wnd->SetWindowPos(
			NULL,
			newRect.left, newRect.top,
			newRect.right - newRect.left, newRect.bottom - newRect.top,
			SWP_NOOWNERZORDER | SWP_NOACTIVATE);
		desc.Wnd->Invalidate(1);//RedrawWindow(); 
	}
}
