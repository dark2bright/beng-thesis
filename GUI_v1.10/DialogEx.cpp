// DialogEx.cpp : implementation file
//

#include "stdafx.h"
#include "thesis.h"
#include "DialogEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogEx dialog

BEGIN_MESSAGE_MAP(CDialogEx, CDialog)
	//{{AFX_MSG_MAP(CDialogEx)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogEx message handlers

CDialogEx::CDialogEx(UINT nIDTemplate,CWnd* pParent)
: CDialog(nIDTemplate, pParent)
{
	//{{AFX_DATA_INIT(CAnimationDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CDialogEx::clientToDoc(CPoint& point)
{
	CClientDC dc(this);
	// OnPrepareDC(&dc, NULL);
	dc.DPtoLP(&point);
}

void CDialogEx::clientToDoc(CRect& rect)
{
	CClientDC dc(this);
	// OnPrepareDC(&dc, NULL);
	dc.DPtoLP(rect);
	ASSERT(rect.left <= rect.right);
	ASSERT(rect.bottom <= rect.top);
}

void CDialogEx::docToClient(CPoint& point)
{
	CClientDC dc(this);
	// OnPrepareDC(&dc, NULL);
	dc.LPtoDP(&point);
}

void CDialogEx::docToClient(CRect& rect)
{
	CClientDC dc(this);
	// OnPrepareDC(&dc, NULL);
	dc.LPtoDP(rect);
	rect.NormalizeRect();
}

BOOL CDialogEx::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetWindowText(m_strCaption);
	m_drawTool.m_pGraphView = m_pGraphView;
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogEx::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CDialog::OnLButtonDown(nFlags, point);
	m_drawTool.OnLButtonDown(this,nFlags,point);
}

void CDialogEx::OnLButtonUp(UINT nFlags, CPoint point) 
{	
	CDialog::OnLButtonUp(nFlags, point);
	m_drawTool.OnLButtonUp(this,nFlags,point);
}

void CDialogEx::OnMouseMove(UINT nFlags, CPoint point) 
{	
	CDialog::OnMouseMove(nFlags, point);
	m_drawTool.OnMouseMove(this,nFlags,point);
}

BOOL CDialogEx::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	if (nHitTest == HTCLIENT)
		SetCursor(m_drawTool.getCusorHandle());		
	return TRUE;
}
