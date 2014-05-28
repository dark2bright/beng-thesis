// DrawTool.cpp: implementation of the CDrawTool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "thesis.h"
#include "DrawTool.h"
#include "DialogEx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawTool::CDrawTool()
{
	m_pSelected = 0;
	m_pTmpSel = 0;
}

CDrawTool::~CDrawTool()
{
}

void CDrawTool::OnLButtonDown(CDialogEx*pView,UINT nFlags, CPoint point)
{
	CPoint local(point);
	pView->clientToDoc(local);	
	pView->SetCapture();
	pView->Invalidate(FALSE);
	m_pSelected = m_pTmpSel;
	if (m_pSelected)
		m_nHitTest = m_pSelected->hitTest(point);
	m_prevPoint = point;
}

void CDrawTool::OnMouseMove(CDialogEx *pView,UINT nFlags, CPoint point)
{
	CPoint local(point);
	pView->clientToDoc(local);
	pView->Invalidate(FALSE);
	// if mouse is pressed
	if (pView->GetCapture() == pView)
	{
		if (!m_pSelected)
		{
			// Draw rect tracker here...
			return;
		}
		//* ...recalculate current object's size
		CPoint offset(local - m_prevPoint);
		if (m_pSelected->typeId() == EDGEVIEWID) {
			if (m_nHitTest == DO_SELECT)
				m_pSelected->offset(offset,DO_SELECT);
			else // m_nHitTest == DO_RESIZE_XXX
			{
				m_pSelected->offset(local,m_nHitTest);
				((CEdgeView*)m_pSelected)->reposition(m_nHitTest);
			}
		}
		else // m_pSelected->typeId() == VERTEXVIEWID
		{
			m_pSelected->offset(offset,m_nHitTest);
			m_prevPoint = local;
			m_pGraphView->updateEdgeViews((CVertexView*)m_pSelected);
		}
		return;
	}
	// mouse is released
	UINT nHitTest;
	m_pTmpSel = m_pGraphView->getAt(point,nHitTest);
	if (m_pTmpSel)
		if(m_pSelected == m_pTmpSel)
			m_nHitTest = nHitTest;
		else{}
	else m_nHitTest = DO_NOTHING;
}

void CDrawTool::OnLButtonUp(CDialogEx *pView,UINT nFlags, CPoint point)
{
	if (pView->GetCapture() == pView)
 	{
		ReleaseCapture();
		CPoint local(point);
		pView->clientToDoc(local);
	}
}

void CDrawTool::draw(CDC *pDC)
{
	CAbstractGraph* pModel = m_pGraphView->getModel();
	if (m_pSelected)
	{
		m_pSelected->drawAsSelected(pDC);
		m_pSelected->drawControlPoints(pDC);
		if (m_pSelected->typeId() == EDGEVIEWID && pModel->isDirected()) 
			((CEdgeView*)m_pSelected)->drawDirectedMarkAsSelected(pDC);
	}
	if (m_pTmpSel && m_pTmpSel != m_pSelected)
	{
		m_pTmpSel->drawAsSelected(pDC);
		if (m_pTmpSel->typeId() == EDGEVIEWID && pModel->isDirected()) 
			((CEdgeView*)m_pTmpSel)->drawDirectedMarkAsSelected(pDC);
	}
}

HCURSOR CDrawTool::getCusorHandle() const
{
	//nHandle is hittest-return
	LPCTSTR lpsIDC = IDC_ARROW;
	switch (m_nHitTest) {
	case DO_SELECT			: lpsIDC = IDC_ARROW;break;
	case DO_RESIZE_HORZ		: lpsIDC = IDC_SIZEWE;break;
	case DO_RESIZE_VERT		: lpsIDC = IDC_SIZENS;break;
	case DO_RESIZE_NEWS		: lpsIDC = IDC_SIZEALL;break;
	case DO_NOTHING			: lpsIDC = IDC_ARROW;break;
	}
	return AfxGetApp()->LoadStandardCursor(lpsIDC);
}
