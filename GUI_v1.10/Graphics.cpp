// CGraphics.cpp: implementation of the CGraphics class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thesis.h"
#include "Graphics.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

INT CGraphics::m_nSelCtrlPnt = NONE;

CGraphics::~CGraphics()
{
}

VOID CGraphics::setColor(COLORREF newColor)
{
	color = newColor;
}

VOID CGraphics::setName(CString newName)
{
	name = newName;
}

const CString& CGraphics::getName()const
{
	return name;
}

VOID CGraphics::drawMark(CDC *pDC, CPoint point) const
{
	CRect rect(point.x-3,point.y-3,point.x+3,point.y+3);
	//*
	CBrush yellowBrush(RGB(255,255,0));
	CBrush *pOldBrush = pDC->SelectObject(&yellowBrush);
	pDC->Ellipse(&rect);
	pDC->SelectObject(pOldBrush);
	//*/
//	pDC->Rectangle(rect);
}

void CGraphics::drawControlPoints(CDC *pDC) const
{
	for (int i = 0; i < 4; i++)
		drawMark(pDC,ctrlPoint[i]);
}

void CGraphics::getContiguousArea(CPoint center, INT nRadius,CRect&rect) const
{
	rect.left = center.x - nRadius;
	rect.right = rect.left + 2*nRadius;
	rect.top = center.y - nRadius;
	rect.bottom = rect.top + 2*nRadius;
}

void CGraphics::draw(CDC*pDC)
{
	drawWithColor(pDC,color);
}

void CGraphics::Serialize(CArchive &ar)
{
	if (ar.IsStoring())
	{
		CString str;
		str.Format("name %c%s%c\ncolor %ld\n",'"',name,'"',((long int)color));
		ar.WriteString(str);
		ar.WriteString("controlPoint [\n");
		for (int i = 0; i < 4; i++)
		{
			ar.WriteString("point [\n");
			str.Format("x %ld\ny %ld\n",ctrlPoint[i].x,ctrlPoint[i].y);
			ar.WriteString(str);
			ar.WriteString("]\n");
		}
		ar.WriteString("]\n");
	}
}
