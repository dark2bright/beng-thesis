// EditBar.cpp: implementation of the CEditBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thesis.h"
#include "EditBar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEditBar::CEditBar()
{
	m_menuContext.Initialize(IDR_EDIT,NULL);
}

CEditBar::~CEditBar()
{
}

BEGIN_MESSAGE_MAP(CEditBar, CSizingControlBarG)
	//{{AFX_MSG_MAP(CEditBar)
	ON_WM_CREATE()
	ON_WM_CONTEXTMENU()
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	ON_COMMAND(ID_EDIT_COPY, OnCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CEditBar message handlers

int CEditBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CSizingControlBarG::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	SetSCBStyle(GetSCBStyle() | SCBS_SHOWEDGES | SCBS_SIZECHILD);
	
	if (!m_wndEdit.Create(WS_CHILD|WS_VISIBLE| WS_VSCROLL|WS_HSCROLL|
			ES_MULTILINE |ES_WANTRETURN|ES_AUTOVSCROLL | ES_AUTOHSCROLL |ES_READONLY,
			CRect(0,0,0,0), this, 123))
		return -1;
	CFont font;
	m_wndEdit.ModifyStyleEx(0, WS_EX_CLIENTEDGE);
	if (!font.CreatePointFont(110, "Tahoma"))
		return -1;
	m_wndEdit.SetFont(&font);
	return 0;
}

void CEditBar::append(const CString &str)
{
	long Length = m_wndEdit.GetTextLength();
	m_wndEdit.SetSel(Length, Length);
	m_wndEdit.ReplaceSel(str);
}

void CEditBar::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CMenu *pSubMenu = m_menuContext.GetSubMenu(0);
	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);	
}

void CEditBar::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	m_menuContext.DrawItem(lpDrawItemStruct);	
	CSizingControlBarG::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CEditBar::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	m_menuContext.MeasureItem(this, lpMeasureItemStruct);	
	CSizingControlBarG::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void CEditBar::OnCopy()
{
	m_wndEdit.Copy();
}

void CEditBar::OnClear()
{
	m_wndEdit.SetWindowText("");
}
