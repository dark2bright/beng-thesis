// EdgeView.h: interface for the CEdgeView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EDGEVIEW_H__77B19AC0_67A6_4AB8_AC4E_114E5C23A43C__INCLUDED_)
#define AFX_EDGEVIEW_H__77B19AC0_67A6_4AB8_AC4E_114E5C23A43C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VertexView.h"
#include "Bezier.h"
#include "Edge.h"

class CGraphLoader;

class CEdgeView : public CBezier
{
public:
	CEdgeView();
	CEdgeView(CVertexView*);
	virtual ~CEdgeView();
public:
	void reverse();
	virtual void Serialize(CArchive&);
	void setFirstEnd(CVertexView*);
	CObjectEx& clone()const;
	CString toString()const;
	void drawDirectedMarkWithColor(CDC*,const COLORREF&)const;
	void drawDirectedMarkAsSelected(CDC*)const;
	void drawDirectedMark(CDC*)const;
	void attach(CEdge*pModel);
	CVertexView* getSecondEnd()const;
	CVertexView* getFirstEnd()const;
	INT typeId()const;
	void displayProperties(LPCONTROLSTRUCT);
	void offset(CPoint,UINT);
	void reposition(UINT);
	void drawWithColor(CDC*,const COLORREF&);
	VOID setSecondEnd(CVertexView*);
protected:
	void resetLoop();
	CVertexView* m_pFirstEnd;
	CVertexView* m_pSecondEnd;
	CEdge* m_pModel;

	friend class CGraphLoader;
};

#endif // !defined(AFX_EDGEVIEW_H__77B19AC0_67A6_4AB8_AC4E_114E5C23A43C__INCLUDED_)
