?// Bezier.cpp: implementation of the CBezier class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thesis.h"
#include "Bezier.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBezier::CBezier()
{
	m_lpPt = new CPoint[1];
	m_nNumPoints = 0;
}

CBezier::~CBezier()
{
	delete [] m_lpPt;	
}

INT CBezier::hitTest(CPoint point) const
{
	INT nRadius = 5; // radius of cotiguous area
	INT nReturn = DO_NOTHING;
	CRect rect;
	m_nSelCtrlPnt = NONE;
	getContiguousArea(ctrlPoint[FIRST],nRadius,rect);
	if (rect.PtInRect(point))
	{
		m_nSelCtrlPnt = FIRST;
		return DO_RESIZE_NEWS;
	}
	getContiguousArea(ctrlPoint[SECOND],nRadius,rect);
	if (rect.PtInRect(point))
	{
		m_nSelCtrlPnt = SECOND;
		return DO_RESIZE_NEWS;
	}
	if (isSelect(point))
		return DO_SELECT; 
	return DO_NOTHING;
}

BOOL CBezier::hitTestLine(CPoint ptStart, CPoint ptEnd, CPoint ptMouse, int nWidth) const
{
	CRect rect(ptStart,ptEnd);
	rect.NormalizeRect();
	rect.InflateRect(nWidth/2,nWidth/2);
	return (rect.PtInRect(ptMouse));
}

BOOL CBezier::isSelect(CPoint point) const
{
	for (UINT nPt = 0; nPt < m_nNumPoints-1; nPt++)
		if (hitTestLine(m_lpPt[nPt],m_lpPt[nPt+1],point,6)) // mo rong vung select > 6
			return TRUE;
	return FALSE;
}

void CBezier::drawWithColor(CDC *pDC,const COLORREF&_color)
{
	CPen pen(PS_COSMETIC,1,_color);
	CPen* pOldPen = pDC->SelectObject(&pen);
	pDC->PolyBezier(ctrlPoint,4);
	calcSegments(pDC);
	pDC->SelectObject(pOldPen);
}

// recalculate bezier segments
void CBezier::calcSegments(CDC *pDC)
{
	BYTE *lpB;
	if (pDC->BeginPath()) {
		pDC->PolyBezier(ctrlPoint,4);
		if (pDC->EndPath())	{
			if (pDC->FlattenPath())
				m_nNumPoints = pDC->GetPath((LPPOINT)NULL,(LPBYTE)NULL,0);
			if (m_nNumPoints > 0)
			{
				if (m_lpPt) delete [] m_lpPt;
				m_lpPt = new CPoint[m_nNumPoints];
				lpB  = new BYTE[m_nNumPoints];
				m_nNumPoints = pDC->GetPath(m_lpPt, lpB, m_nNumPoints);
				delete [] lpB;
			}
		}
	}
}

void CBezier::drawAsSelected(CDC *pDC)
{
	COLORREF _color = RGB(0,255,0);
	drawWithColor(pDC,_color);
}