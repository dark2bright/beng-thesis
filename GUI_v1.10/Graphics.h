// CGraphics.h: interface for the CGraphics class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHICALOBJECT_H__1B7EA2B2_4B15_4F26_B848_95A2CC26A583__INCLUDED_)
#define AFX_GRAPHICALOBJECT_H__1B7EA2B2_4B15_4F26_B848_95A2CC26A583__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BObject.h"
#include "controlstruct.h"

class CGraphics : public CObjectEx
{
public:
	virtual~CGraphics();
	// pure virtual function
	virtual INT hitTest(CPoint)const = 0;
	virtual void drawAsSelected(CDC*) = 0;
	virtual void drawWithColor(CDC*,const COLORREF&) = 0;
	virtual void displayProperties(LPCONTROLSTRUCT) = 0;
	virtual void offset(CPoint,UINT) = 0;
	virtual INT typeId()const = 0;
public:
	virtual void Serialize(CArchive&);
	virtual void draw(CDC*pDC);;
	void getContiguousArea(CPoint,INT,CRect&)const;
	const CString& getName()const;
	VOID setName(CString );
	VOID setColor(COLORREF);
	void drawControlPoints(CDC*)const;
protected:
	VOID drawMark(CDC*,CPoint)const;
	CString name;
	COLORREF color;
	CPoint ctrlPoint[4];
	static INT m_nSelCtrlPnt; // selected control point
};

#endif // !defined(AFX_GRAPHICALOBJECT_H__1B7EA2B2_4B15_4F26_B848_95A2CC26A583__INCLUDED_)
