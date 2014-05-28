// EdgeView.cpp: implementation of the CEdgeView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thesis.h"
#include "EdgeView.h"
#include "Vector2D.h"
#include <math.h>
#include "WeightedEdge.h"
#include "NetworkEdge.h"
#include "PropertiesEDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEdgeView::CEdgeView()
{	
}

CEdgeView::CEdgeView(CVertexView*pFirstEnd)
{
	m_pFirstEnd = pFirstEnd;
	m_pSecondEnd = NULL;
	m_pModel = NULL;
	CPoint center = pFirstEnd->getCenter();
	for(UINT u = 0; u < 4; u++ )
		ctrlPoint[u] = center;
}

CEdgeView::~CEdgeView()
{
}

VOID CEdgeView::setSecondEnd(CVertexView *pSecondEnd)
{
	m_pSecondEnd = pSecondEnd;
}

VOID CEdgeView::drawWithColor(CDC*pDC,const COLORREF& _color)
{
	CBezier::drawWithColor(pDC,_color);
	if (m_pModel) // new da co model
	{
		if (m_pModel->typeId() == EDGEID) return;
		CString strLabel;
		strLabel = ((CWeightedEdge*)m_pModel)->getWeight().toString();
		if (m_pModel->typeId() == NETWORKEDGEID) // neu la canh cua mang, draw
			strLabel += "/" + ((CNetworkEdge*)m_pModel)->getCapacity().toString();
		TEXTMETRIC textmetric;
		pDC->GetTextMetrics(&textmetric);
		int nWidth = textmetric.tmAveCharWidth*(strLabel.GetLength()+3);
		CRect rect;
		rect.SetRect(m_lpPt[m_nNumPoints/2],m_lpPt[m_nNumPoints/2+1]);
		rect.InflateRect(nWidth/2,20,nWidth/2,20);
		rect.OffsetRect(0,-10);
		rect.NormalizeRect();
		pDC->SetBkColor(RGB(255,255,255));
		pDC->DrawText(strLabel,&rect,DT_SINGLELINE|DT_VCENTER|DT_CENTER);
	}
}

// draw an arrow symbolizing directed edge
void CEdgeView::drawDirectedMarkWithColor(CDC *pDC,const COLORREF& _color) const
{
	const int length = 10; // lenght of arrow
	const double pi = 3.1416;
	const int angleInDegree = 20;
	const double angleInRadian = angleInDegree*pi/180;

	CPoint I,M1,M2;
	// the arrow has direction from second to end
	CVector2D MT(ctrlPoint[SECOND],ctrlPoint[END]);
	double nEdge = MT.magnitude();
	if (nEdge == 0) return;
	// Compute coordinates
	I.x = long(ctrlPoint[END].x - (length*MT.x/nEdge));
	I.y = long(ctrlPoint[END].y - (length*MT.y/nEdge));
	
	M1.x = I.x + long(length*tan(angleInRadian)*(-MT.y/nEdge));
	M1.y = I.y + long(length*tan(angleInRadian)*(MT.x/nEdge));
	M2.x = I.x + long(length*tan(angleInRadian)*(MT.y/nEdge));
	M2.y = I.y + long(length*tan(angleInRadian)*(-MT.x/nEdge));
	// Now, draw arrow
	CPoint arrows[3] = {ctrlPoint[END],M1,M2};
	CBrush brush(_color),
		*pOld = pDC->SelectObject(&brush);
	pDC->Polygon(arrows,3);
	pDC->SelectObject(pOld);
}

void CEdgeView::reposition(UINT nFlags)
{
	if (nFlags == DO_DRAW_NEW && m_pFirstEnd == m_pSecondEnd)
		resetLoop();
	// if (m_pFirstEnd == m_pSecondEnd) return; // do nothing with loop
	// is called in CGraphView->updateAllViews()
	if (nFlags == DO_UPDATE) 
	{
		if (m_pFirstEnd == m_pSecondEnd)
			resetLoop();
		else
		{
			CPoint  firstCenter = m_pFirstEnd->getCenter(),
					secondCenter = m_pSecondEnd->getCenter();
			ctrlPoint[FIRST].x = (firstCenter.x+secondCenter.x)/2;
			ctrlPoint[FIRST].y = (firstCenter.y+secondCenter.y)/2;
			ctrlPoint[SECOND] = ctrlPoint[FIRST];
		}
	}
	ctrlPoint[START] = m_pFirstEnd->getContactPoint(ctrlPoint[FIRST]);
	if (m_pSecondEnd) ctrlPoint[END] = m_pSecondEnd->getContactPoint(ctrlPoint[SECOND]);
}

void CEdgeView::offset(CPoint newCoordinate, UINT nFlags)
{
	if (nFlags == DO_DRAW_NEW)
	{
		ctrlPoint[END] = newCoordinate;
		if (m_pFirstEnd != m_pSecondEnd)
		{
			ctrlPoint[FIRST].x = (ctrlPoint[START].x+ctrlPoint[END].x)/2;
			ctrlPoint[FIRST].y = (ctrlPoint[START].y+ctrlPoint[END].y)/2;
			ctrlPoint[SECOND] = ctrlPoint[FIRST];
		}
	}
	else // DO_RESIZE_XXX
		if (m_nSelCtrlPnt == FIRST || m_nSelCtrlPnt == SECOND)
			ctrlPoint[m_nSelCtrlPnt] = newCoordinate;
}

void CEdgeView::displayProperties(LPCONTROLSTRUCT lpControlStruct)
{
	CPropertiesEDlg dlg(NULL,m_pModel);
	dlg.m_color = color;
	dlg.m_strName = name;
	dlg.m_lpControlStruct = lpControlStruct;
	if (dlg.DoModal() == IDOK) {
		color = dlg.m_color;
		name = dlg.m_strName;
	}
}

INT CEdgeView::typeId() const
{
	return EDGEVIEWID;
}

CVertexView* CEdgeView::getFirstEnd() const
{
	return m_pFirstEnd;
}

CVertexView* CEdgeView::getSecondEnd() const
{
	return m_pSecondEnd;
}

void CEdgeView::attach(CEdge *pModel)
{
	m_pModel = pModel;
}

void CEdgeView::drawDirectedMark(CDC *pDC) const
{
	drawDirectedMarkWithColor(pDC,color);
}

void CEdgeView::drawDirectedMarkAsSelected(CDC *pDC) const
{
	COLORREF _color = RGB(0,255,0);
	drawDirectedMarkWithColor(pDC,_color);
}

CString CEdgeView::toString() const
{
	return "EdgeView";
}

CObjectEx& CEdgeView::clone() const
{
	CEdgeView*pNew = new CEdgeView;
	for(UINT i = 0; i < 4; i++)
		pNew->ctrlPoint[i] = ctrlPoint[i];
	pNew->color = color;
	pNew->name = name;
	return *pNew;
}

void CEdgeView::setFirstEnd(CVertexView *pFirstEnd)
{
	m_pFirstEnd = pFirstEnd;
}

void CEdgeView::Serialize(CArchive &ar)
{
	if (ar.IsStoring()) 
	{
		ar.WriteString("edge [\n");
		m_pModel->Serialize(ar);
		CGraphics::Serialize(ar);
		ar.WriteString("]\n");
	}
}

void CEdgeView::reverse()
{
	CPoint pntTmp = ctrlPoint[START];
	ctrlPoint[START] = ctrlPoint[END];
	ctrlPoint[END] = pntTmp;
}

void CEdgeView::resetLoop()
{
	ctrlPoint[START] = ctrlPoint[END] = m_pFirstEnd->getCenter();
	ctrlPoint[FIRST].y = ctrlPoint[SECOND].y = ctrlPoint[0].y + 2*MAX_RADIUS;
	ctrlPoint[FIRST].x = ctrlPoint[START].x + MIN_RADIUS;
	ctrlPoint[SECOND].x = ctrlPoint[START].x - MIN_RADIUS;
}
