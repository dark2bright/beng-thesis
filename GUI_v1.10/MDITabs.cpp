/****************************************************************************\
Datei  : MDITabs.h
Projekt: MDITabs, a tabcontrol for switching between MDI-views
Inhalt : CMDITabs implementation
Datum  : 03.10.2001
Autor  : Christian Rodemeyer
Hinweis: © 2001 by Christian Rodemeyer
\****************************************************************************/

#include "stdafx.h"
#include "MDITabs.h"
#include <AFXPRIV.H>
#include <algorithm>
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMDITabs

CMDITabs::CMDITabs()
{
	m_mdiClient = NULL;
	m_bImages = false;
}

BEGIN_MESSAGE_MAP(CMDITabs, CTabCtrl)
	//{{AFX_MSG_MAP(CMDITabs)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, OnSelChange)
	ON_WM_PAINT()
	ON_WM_NCPAINT()
	//}}AFX_MSG_MAP
ON_MESSAGE(WM_SIZEPARENT, OnSizeParent)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMDITabs message handlers

afx_msg LRESULT CMDITabs::OnSizeParent(WPARAM, LPARAM lParam)
{
	AFX_SIZEPARENTPARAMS* pParams = reinterpret_cast<AFX_SIZEPARENTPARAMS*>(lParam);
	
	const int height = 26 + (m_bImages ? 1 : 0);
	const int offset = 2;
	
	m_height = height + offset;
	m_width  = pParams->rect.right - pParams->rect.left;
	pParams->rect.bottom -= height;
	
	MoveWindow(pParams->rect.left, pParams->rect.bottom - offset, pParams->rect.right, height + offset, true);
	
	return 0;
}

void CMDITabs::OnSelChange(NMHDR* pNMHDR, LRESULT* pResult)
{
	TCITEM item;
	item.mask = TCIF_PARAM;
	GetItem(GetCurSel(), &item);
	::BringWindowToTop(HWND(item.lParam));
	*pResult = 0;
}

void CMDITabs::Update()
{
	SetRedraw(false);
	
	HWND active = ::GetTopWindow(m_mdiClient); // get active view window (actually the frame of the view)
	
	typedef std::vector<HWND> TWndVec;
	typedef TWndVec::iterator TWndIter;
	
	TWndVec vChild; // put all child windows in a list (actually a vector)
	for (HWND child = active; child; child = ::GetNextWindow(child, GW_HWNDNEXT))
	{
		vChild.push_back(child);
	}
	
	TCITEM item;
	char text[256];
	item.pszText = text;
	
	for (int i = GetItemCount(); i--;)  // for each tab
	{
		item.mask = TCIF_PARAM;
		GetItem(i, &item);
		
		TWndIter it = std::find(vChild.begin(), vChild.end(), HWND(item.lParam));
		if (it == vChild.end()) // associatete view does no longer exist, so delete the tab
		{
			DeleteItem(i);
			if (m_bImages) RemoveImage(i);
		}
		else // update the tab's text, image and selection state
		{
			item.mask = TCIF_TEXT;
			::GetWindowText(*it, text, 256);
			if (m_bImages) m_images.Replace(i, (HICON)::GetClassLong(*it, GCL_HICONSM));
			SetItem(i, &item);
			if (*it == active) SetCurSel(i); // associatet view is active => make it the current selection
			vChild.erase(it);                // remove view from list
		}
	}
	
	// all remaining views in vChild have to be added as new tabs
	i = GetItemCount();
	for (TWndIter it = vChild.begin(), end = vChild.end(); it != end; ++it)
	{
		item.mask = TCIF_TEXT|TCIF_PARAM|TCIF_IMAGE;
		::GetWindowText(*it, text, 256);
		if (m_bImages) m_images.Add((HICON)::GetClassLong(*it, GCL_HICONSM));
		item.iImage = i;
		item.lParam = LPARAM(*it);
		InsertItem(i, &item);
		if (*it == active) SetCurSel(i);
		++i;
	}
	
	RedrawWindow(NULL, NULL, RDW_FRAME|RDW_INVALIDATE|RDW_ERASE);
	SetRedraw(true);
}

void CMDITabs::OnPaint()
{
	CPaintDC dc(this);
	
	if (GetItemCount() == 0) return; // do nothing
	
	// get some system colors
	DWORD face   = ::GetSysColor(COLOR_3DFACE);
	DWORD shadow = ::GetSysColor(COLOR_3DSHADOW);
	DWORD dark   = ::GetSysColor(COLOR_3DDKSHADOW);
	
	::ExcludeClipRect(dc, 0, 0, m_width, 2); // prevent system from drawing upper border
	
	// windows should draw the control as usual
	_AFX_THREAD_STATE* pThreadState = AfxGetThreadState();
	pThreadState->m_lastSentMsg.wParam = WPARAM(HDC(dc));
	Default();
	
	// now we retouch the drawing to make it look nice
	::SetPixel(dc, 0, 2, face);
	::SetPixel(dc, 0, 2, shadow);
	
	CRect rect;
	GetItemRect(GetCurSel(), rect);
	if (rect.left == 2) // is at the leftmost position a tab selected?
	{
		// if yes, remove the leftmost white line and extend the bottom border of the tab
		int j = m_bImages ? 1 : 0;
		
		HPEN pen = ::CreatePen(PS_SOLID, 1, face);
		HGDIOBJ old = ::SelectObject(dc, pen);
		::MoveToEx(dc, 0, 2, NULL);
		::LineTo(dc, 0, 22 + j);
		::MoveToEx(dc, 1, 2, NULL); // patch for Win98
		::LineTo(dc, 1, 22 + j);    // patch for Win98
		::SetPixel(dc, 0, 22 + j, shadow); ::SetPixel(dc, 1, 22 + j, shadow);
		::SetPixel(dc, 0, 23 + j, dark);   ::SetPixel(dc, 1, 23 + j, dark);
		
		::SelectObject(dc, old);
		::DeleteObject(pen);
	}
	
	// extend the top border to the right margin
	::SetPixel(dc, m_width - 5, 2, shadow);
	::SetPixel(dc, m_width - 5, 3, dark);
}

void CMDITabs::OnNcPaint()
{
	HDC hdc = ::GetWindowDC(m_hWnd);
	
	CRect rect;
	rect.left = 0;
	rect.top = -2;
	rect.right = m_width;
	rect.bottom = m_height;
	DrawEdge(hdc, rect, EDGE_SUNKEN, BF_LEFT|BF_RIGHT|BF_BOTTOM);
	
	HPEN pen = ::CreatePen(PS_SOLID, 0, ::GetSysColor(COLOR_3DFACE));
	HGDIOBJ old = ::SelectObject(hdc, pen);
	
	::MoveToEx(hdc, 2, 0, NULL);
	::LineTo(hdc, m_width - 2, 0);
	::MoveToEx(hdc, 2, 1, NULL);
	::LineTo(hdc, m_width - 2, 1);
	
	::SelectObject(hdc, old);
	::DeleteObject(pen);
	::ReleaseDC(m_hWnd, hdc);
}

void CMDITabs::Create(CFrameWnd* pMainFrame, bool bImages)
{
	CTabCtrl::Create(WS_CHILD|WS_VISIBLE|TCS_BOTTOM|TCS_SINGLELINE|TCS_FOCUSNEVER|TCS_FORCEICONLEFT|WS_CLIPSIBLINGS, CRect(0, 0, 0, 0), pMainFrame, 42);
	ModifyStyleEx(0, WS_EX_CLIENTEDGE);
	SendMessage(WM_SETFONT, WPARAM(GetStockObject(DEFAULT_GUI_FONT)), 0);
	
	m_mdiClient = ::GetTopWindow(*pMainFrame);
	
#ifdef _DEBUG
	char wndClass[32];
	::GetClassName(m_mdiClient, wndClass, 32);
	ASSERT(strncmp(wndClass, "MDIClient", 32) == 0); // MDI
#endif
	
	// manipulate Z-order so, that our tabctrl is above the mdi client, but below any status bar
	::SetWindowPos(m_hWnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
	::SetWindowPos(m_mdiClient, m_hWnd, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
	m_bImages = bImages;
	if (bImages)
	{
		m_images.Create(16, 16, ILC_COLORDDB|ILC_MASK, 5, 5);
		SetImageList(&m_images);
	}
}
