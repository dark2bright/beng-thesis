// Shape.cpp: implementation of the CShape class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thesis.h"
#include "Shape.h"
#include "Vector2D.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShape::CShape(CPoint center)
{
	color = RGB(219,214,248);	
	mode = ELLIPSE;
	reset(center);
}

CShape::~CShape()
{
}

void CShape::drawWithColor(CDC *pDC,const COLORREF& _color)
{
	CRect rect(ctrlPoint[TOPLEFT],ctrlPoint[BOTTOMRIGHT]);
	CBrush brush(_color);
	CBrush* pOldBrush = pDC->SelectObject(&brush);
	switch(mode) {
	case ELLIPSE:
		pDC->Ellipse(rect);
		break;
	case RECTANGLE:
		pDC->Rectangle(rect);
		break;
	case LOZENGE:
		break;
	default:
		AfxMessageBox("Can't draw. Unknown shape mode");
		break;
	}
	pDC->SelectObject(pOldBrush);
}

// get contact point between shape and line created by aPoint and center of shape
CPoint CShape::getContactPoint(CPoint aPoint)
{
	CPoint result;
	CPoint center = getCenter();
	if (mode == ELLIPSE) {
		CVector2D v(center,aPoint);
		v.normalize();
		result.x = long((getHorizontalRadius()*v.x)+center.x);
		result.y = long((getVerticalRadius()*v.y)+center.y);
	}
	/* RECTANGLE mode of this function is under construction
	if (mode == RECTANGLE) {
	}
	// LOZENGE mode of this function is under construction
	//*/
	return result;
}

BOOL CShape::pointInShape(CPoint point) const
{
	CRect rect(ctrlPoint[TOPLEFT],ctrlPoint[BOTTOMRIGHT]);
	if (mode == ELLIPSE) {
		CRgn ellipse;
		ellipse.CreateEllipticRgnIndirect(&rect);
		return ellipse.PtInRegion(point);
	}
	if (mode == RECTANGLE) {
		return rect.PtInRect(point);
	}
	// LOZENGE mode of this function is under construction
	return FALSE;
}

CPoint CShape::getCenter() const
{
	return CPoint
	(
		(ctrlPoint[TOPRIGHT].x+ctrlPoint[TOPLEFT].x)/2,
		(ctrlPoint[BOTTOMLEFT].y+ctrlPoint[TOPLEFT].y)/2
	);
}

long CShape::getVerticalRadius() const
{
	return abs((ctrlPoint[BOTTOMLEFT].y-ctrlPoint[TOPLEFT].y)/2);	
}

long CShape::getHorizontalRadius() const
{
	return abs((ctrlPoint[TOPRIGHT].x-ctrlPoint[TOPLEFT].x)/2);
}

INT CShape::hitTest(CPoint point)const
{
	int nRadius = 5;
	CPoint border[4];
	for(UINT u = 0 ; u < 4 ; u++)
		border[u] = ctrlPoint[u];
	border[TOPLEFT].Offset(getHorizontalRadius(),0);
	border[TOPRIGHT].Offset(0,getVerticalRadius());
	border[BOTTOMLEFT].Offset(0,-getVerticalRadius());
	border[BOTTOMRIGHT].Offset(-getHorizontalRadius(),0);
	CRect rect;
	getContiguousArea(border[TOPLEFT],nRadius,rect); // top
	if (rect.PtInRect(point)) {
		m_nSelCtrlPnt = TOP;
		return DO_RESIZE_VERT;
	}
	getContiguousArea(border[BOTTOMRIGHT],nRadius,rect);
	if (rect.PtInRect(point)) {
		m_nSelCtrlPnt = BOTTOM;
		return DO_RESIZE_VERT;
	}
	getContiguousArea(border[TOPRIGHT],nRadius,rect);
	if (rect.PtInRect(point)) {
		m_nSelCtrlPnt = RIGHT;
		return DO_RESIZE_HORZ;
	}
	getContiguousArea(border[BOTTOMLEFT],nRadius,rect);
	if (rect.PtInRect(point)) {
		m_nSelCtrlPnt = LEFT;
		return DO_RESIZE_HORZ;
	}
	// check if select
	CRect shapeRect(ctrlPoint[TOPLEFT],ctrlPoint[BOTTOMRIGHT]);
	if (mode == ELLIPSE) {
		CRgn ellipse;
		ellipse.CreateEllipticRgnIndirect(&shapeRect);
		if (ellipse.PtInRegion(point)) return DO_SELECT;
	}
	if (mode == RECTANGLE)
		if (shapeRect.PtInRect(point))return DO_SELECT;
	/* LOZENGE mode of this version is under construction
	if (mode == LOZENGE){
	}
	//*/
	return DO_NOTHING;
}

void CShape::drawAsSelected(CDC *pDC)
{
	COLORREF _color = RGB(255,255,0);
	drawWithColor(pDC,_color);
}

void CShape::offset(CPoint point, UINT nFlags)
{
	// call by layout algorithm
	if (nFlags == DO_LAYOUT)
	{
		reset(point);
		return;
	}
	if (nFlags == DO_SELECT){
		for(UINT u = 0; u < 4; u++)
			ctrlPoint[u].Offset(point);
		return;
	}
	if (nFlags == DO_RESIZE_HORZ) {
		if (m_nSelCtrlPnt == LEFT) {
			ctrlPoint[TOPLEFT].Offset(point.x,0);
			ctrlPoint[BOTTOMLEFT].Offset(point.x,0);
		}
		else // m_nSelCtrlPnt == RIGHT
		{
			ctrlPoint[TOPRIGHT].Offset(point.x,0);
			ctrlPoint[BOTTOMRIGHT].Offset(point.x,0);
		}
		return;
	}	
	if (nFlags == DO_RESIZE_VERT) {
		if (m_nSelCtrlPnt == TOP) {
			ctrlPoint[TOPLEFT].Offset(0,point.y);
			ctrlPoint[TOPRIGHT].Offset(0,point.y);
		}
		else // m_nSelCtrlPnt == BOTTOM
		{
			ctrlPoint[BOTTOMLEFT].Offset(0,point.y);
			ctrlPoint[BOTTOMRIGHT].Offset(0,point.y);
		}
	}
}

void CShape::reset(const CPoint&center)
{
	ctrlPoint[TOPLEFT].x = center.x - MIN_RADIUS;
	ctrlPoint[TOPLEFT].y = center.y - MIN_RADIUS;
	ctrlPoint[TOPRIGHT].x = center.x + MIN_RADIUS;
	ctrlPoint[TOPRIGHT].y = center.y - MIN_RADIUS;
	ctrlPoint[BOTTOMLEFT].x = center.x - MIN_RADIUS;
	ctrlPoint[BOTTOMLEFT].y = center.y + MIN_RADIUS;
	ctrlPoint[BOTTOMRIGHT].x = center.x + MIN_RADIUS;
	ctrlPoint[BOTTOMRIGHT].y = center.y + MIN_RADIUS;
}
