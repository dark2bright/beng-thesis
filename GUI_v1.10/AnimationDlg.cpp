// AnimationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "thesis.h"
#include "AnimationDlg.h"
#include "DelayTimeDlg.h"
#include "NullIterator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnimationDlg dialog

CAnimationDlg::CAnimationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAnimationDlg::IDD, pParent),m_graphicsIterator(*new CNullIterator)
{
	//{{AFX_DATA_INIT(CAnimationDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bFinished = FALSE;
	m_state = MANUAL;
	m_currentColor = 0;
	m_trackColor[0] = RGB(255,0,0);
	m_trackColor[1] = RGB(0,255,0);
	m_delayTime = 500; // miliseconds
}

CAnimationDlg::CAnimationDlg(CWnd* pParent /*=NULL*/,CIterator&graphicsIterator)
	: CDialog(CAnimationDlg::IDD, pParent),m_graphicsIterator(graphicsIterator)
{
	//{{AFX_DATA_INIT(CAnimationDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bFinished = FALSE;
	m_mode = TRACK_VERTEX;
	m_state = MANUAL;
	m_currentColor = 0;	
	m_trackColor[0] = RGB(255,0,0);
	m_trackColor[1] = RGB(0,255,0);
	m_delayTime = 500; // miliseconds
}


void CAnimationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAnimationDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAnimationDlg, CDialog)
	//{{AFX_MSG_MAP(CAnimationDlg)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_COMMAND(ID_OPTIONS_DELAYTIME, OnOptionsDelaytime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnimationDlg message handlers

void CAnimationDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: add draw code for native data here
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
	drawAnimation(pDrawDC);

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

BOOL CAnimationDlg::PreTranslateMessage(MSG* pMsg) 
{
	switch(pMsg->message) {
	case WM_LBUTTONDOWN:
		changeState();
		break;
	case WM_LBUTTONDBLCLK:
		changeState();
		break;
	case WM_COMMAND:
		switch(pMsg->wParam) {
		case ID_ANIMATION_NEXT:
			changeState();
			break;
		case ID_ANIMATION_RESET:
			reset();
			if (m_state == AUTOMATIC) 
			{
				m_state = MANUAL;
				KillTimer(WM_CHANGE_STATE);
			}
			Invalidate(FALSE);
			updateMenuUI();
			break;
		case ID_OPTIONS_AUTOMATIC:
			if (m_state == AUTOMATIC) break;
			m_state = AUTOMATIC;
			SetTimer(WM_CHANGE_STATE,m_delayTime,NULL);
			updateMenuUI();
			break;
		case ID_OPTIONS_MANUAL:
			if (m_state == MANUAL)break;
			m_state = MANUAL;
			KillTimer(WM_CHANGE_STATE);
			updateMenuUI();
			break;
		default:
			break;
		}
		break;
	case WM_TIMER:
		if (pMsg->wParam == WM_CHANGE_STATE) changeState();
		break;
	case WM_KEYDOWN:
		if (pMsg->wParam == VK_DOWN) changeState();
		break;
	default:
		break;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CAnimationDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	SetWindowText(m_strCaption);
	CMenu* pMenu = GetMenu();
	pMenu->CheckMenuItem(ID_OPTIONS_MANUAL,MF_CHECKED);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAnimationDlg::changeState()
{
	if (m_bFinished) return;
	NUMBER oldVertex = ((CVertexView&)m_graphicsIterator.currentItem()).getModel();
	if (m_mode == TRACK_VERTEX) // use in Halmiltonian traversal
		((CVertexView&)m_graphicsIterator.currentItem()).setColor(m_trackColor[m_currentColor]);
	// normal traversal (ex Depth First, Breadth First, Topological Order....just move next
	m_graphicsIterator.moveNext();
	// if done ==> reset iterator and color
	if (m_graphicsIterator.isDone())
	{
		m_graphicsIterator.reset();
		m_currentColor++;
		if (m_currentColor >= MAXCOLOR) m_currentColor = 0; // reset color
		m_bFinished = TRUE;
	}
	// complex traversal => track edge
	if (m_mode == TRACK_EDGE && !m_bFinished) // use in Eulerian traversal
	{
		class CGraphViewEx : public CGraphView
		{
			friend class CAnimationDlg;
		};
		CGraphViewEx *pGraphView = (CGraphViewEx*)m_pGraphView;
		NUMBER currentVertex = ((CVertexView&)m_graphicsIterator.currentItem()).getModel();
		CEdgeView* pE = pGraphView->edgeViews[oldVertex][currentVertex];
		if (!pE) pE = pGraphView->edgeViews[currentVertex][oldVertex];
		if (pE) pE->setColor(m_trackColor[m_currentColor]);
	}	
	Invalidate(FALSE);
}

void CAnimationDlg::drawAnimation(CDC *pDC)
{
	if (m_bFinished) return;
	CGraphics& graphics = (CGraphics&)m_graphicsIterator.currentItem();
	if (!graphics.isNull()) 
	{
		graphics.drawAsSelected(pDC);
		graphics.drawControlPoints(pDC);
	}
}

void CAnimationDlg::updateMenuUI()
{
	CMenu* pMenu = GetMenu();
	pMenu->CheckMenuItem(ID_OPTIONS_AUTOMATIC, m_state == AUTOMATIC ? MF_CHECKED : MF_UNCHECKED);
	pMenu->CheckMenuItem(ID_OPTIONS_MANUAL,m_state == MANUAL ? MF_CHECKED : MF_UNCHECKED);
}

void CAnimationDlg::OnDestroy() 
{
	delete m_pGraphView;
	delete &m_graphicsIterator;
	CDialog::OnDestroy();	
}

void CAnimationDlg::OnOptionsDelaytime() 
{
	CDelayTimeDlg dlg;
	dlg.m_oldTimeDelay = m_delayTime;
	if (dlg.DoModal() == IDOK)
	{
		m_delayTime = dlg.m_newDelayTime;
		if (m_state == AUTOMATIC)
		{
			KillTimer(WM_CHANGE_STATE);
			SetTimer(WM_CHANGE_STATE,m_delayTime,NULL);
		}

	}
}

void CAnimationDlg::reset()
{
	m_graphicsIterator.reset();
	m_bFinished = FALSE;
}
