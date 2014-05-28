// Bezier.h: interface for the CBezier class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BEZIER_H__65C62338_66AC_4C5A_A90A_17133D5FF579__INCLUDED_)
#define AFX_BEZIER_H__65C62338_66AC_4C5A_A90A_17133D5FF579__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Graphics.h"

class CBezier : public CGraphics  
{
public:
	CBezier();
	virtual ~CBezier();
public:
	void drawWithColor(CDC*,const COLORREF&);
	INT hitTest(CPoint)const;
	void drawAsSelected(CDC*);	
protected:
	BOOL isSelect(CPoint)const;
	BOOL hitTestLine(CPoint,CPoint,CPoint,int)const;
	void calcSegments(CDC*);
	CPoint *m_lpPt;
	UINT m_nNumPoints; // number of segments
};

#endif // !defined(AFX_BEZIER_H__65C62338_66AC_4C5A_A90A_17133D5FF579__INCLUDED_)
