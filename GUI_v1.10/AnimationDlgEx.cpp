// AnimationDlgEx.cpp : implementation file
//

#include "stdafx.h"
#include "thesis.h"
#include "AnimationDlgEx.h"
#include "ListIterator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnimationDlgEx dialog


CAnimationDlgEx::CAnimationDlgEx(CWnd* pParent,CIterator& graphicsIterator)
	: CAnimationDlg(pParent, graphicsIterator)
{
	//{{AFX_DATA_INIT(CAnimationDlgEx)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CAnimationDlgEx::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAnimationDlgEx)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAnimationDlgEx, CAnimationDlg)
	//{{AFX_MSG_MAP(CAnimationDlgEx)
	ON_WM_DESTROY()
	ON_COMMAND(ID_OPTIONS_DELAYTIME, OnOptionsDelaytime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnimationDlgEx message handlers

void CAnimationDlgEx::OnDestroy() 
{
	m_graphicsIterator.reset();
	while (!m_graphicsIterator.isDone()) 
	{
		CObjectEx& current = m_graphicsIterator.currentItem();
		delete &current;
		m_graphicsIterator.moveNext();
	}
	CAnimationDlg::OnDestroy();
}

void CAnimationDlgEx::changeState()
{
	m_graphicsIterator.moveNext();
	if (m_graphicsIterator.isDone()) 
		m_graphicsIterator.reset();
	Invalidate(FALSE);
}

void CAnimationDlgEx::drawAnimation(CDC *pDC)
{
	CListIterator& current = (CListIterator&)m_graphicsIterator.currentItem();
	while (!current.isDone())
	{
		CGraphics& graphics = (CGraphics&)current.currentItem();
		graphics.drawWithColor(pDC,m_trackColor[1]);
		current.moveNext();
	}
	current.reset();
}

void CAnimationDlgEx::OnOptionsDelaytime() 
{
	CAnimationDlg::OnOptionsDelaytime();
}

