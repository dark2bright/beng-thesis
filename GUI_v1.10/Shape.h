// Shape.h: interface for the CShape class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHAPE_H__C07C2E35_FF25_4A18_B1DA_B348CD75B834__INCLUDED_)
#define AFX_SHAPE_H__C07C2E35_FF25_4A18_B1DA_B348CD75B834__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Graphics.h"

class CShape  : public CGraphics
{
public:
	enum SHAPEMODE{ELLIPSE,RECTANGLE,LOZENGE};
	CShape(CPoint);
	virtual ~CShape();
public:
	INT hitTest(CPoint)const;
	void offset(CPoint,UINT);	
	void drawAsSelected(CDC*);		
	CPoint getCenter()const;
	BOOL pointInShape(CPoint)const;
	CPoint getContactPoint(CPoint );
	virtual void drawWithColor(CDC*,const COLORREF&);
	long getHorizontalRadius()const;
	long getVerticalRadius()const;
protected:
	void reset(const CPoint&);
protected:
	SHAPEMODE mode;
};

#endif // !defined(AFX_SHAPE_H__C07C2E35_FF25_4A18_B1DA_B348CD75B834__INCLUDED_)
