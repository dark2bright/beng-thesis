// OutputDlg.cpp : implementation file
//

#include "stdafx.h"
#include "thesis.h"
#include "OutputDlg.h"
#include "AbstractGraph.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputDlg dialog


COutputDlg::COutputDlg(CWnd* pParent,CGraphView*pGraphView)
	: CDialogEx(COutputDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COutputDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	ASSERT(pGraphView);
	m_drawTool.m_pGraphView = m_pGraphView = pGraphView;
}


void COutputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COutputDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COutputDlg, CDialog)
	//{{AFX_MSG_MAP(COutputDlg)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutputDlg message handlers

void COutputDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CDC MemDC; // double buffer
	CDC* pDC = &dc;
	CDC *pDrawDC = pDC;
	CBitmap bitmap,*pOldBitmap = NULL;
	
	// Only paint the visble cliping
	CRect client;
	pDC->GetClipBox(client);
	
	CRect rect = client;
	
	
	// Fast repaint by draw alls to a compatible bitmap 
	if (MemDC.CreateCompatibleDC(pDC))
	{
		if (bitmap.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height())){
			pDrawDC = &MemDC;
			MemDC.OffsetViewportOrg(-rect.left,-rect.top);
			pOldBitmap = MemDC.SelectObject(&bitmap);
			MemDC.SetBrushOrg(rect.left % 8, rect.top % 8);
		}
	}
	
	// Repaint background with White brush...
	CBrush brush;
	
	if (!brush.CreateSolidBrush(RGB(255,255,255)))
		return;
	brush.UnrealizeObject();
	pDrawDC->FillRect(client,&brush);
	
	// Draw all objects on screen
	m_pGraphView->draw(pDrawDC);
	m_drawTool.draw(pDrawDC);
	if (pDrawDC != pDC)
	{
		pDC->SetViewportOrg(0, 0);
		pDC->SetWindowOrg(0,0);
		pDC->SetMapMode(MM_TEXT);
		MemDC.SetViewportOrg(0,0);
		MemDC.SetWindowOrg(0,0);
		MemDC.SetMapMode(MM_TEXT);
		// Put everything out ...
		pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(),
			&MemDC, 0, 0, SRCCOPY);
		MemDC.SelectObject(pOldBitmap);
	}
	// Do not call CDialog::OnPaint() for painting messages
}

BOOL COutputDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetWindowText(m_strCaption);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COutputDlg::OnDestroy() 
{
	CAbstractGraph*pModel = m_pGraphView->getModel();
	delete m_pGraphView;
	if(pModel) delete pModel;
	CDialog::OnDestroy();
}

void COutputDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CDialogEx::OnLButtonDown(nFlags, point);
}

void COutputDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{	
	CDialogEx::OnLButtonUp(nFlags, point);
}

void COutputDlg::OnMouseMove(UINT nFlags, CPoint point) 
{	
	CDialogEx::OnMouseMove(nFlags, point);
}
BOOL COutputDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{	
	return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}
