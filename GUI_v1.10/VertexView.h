// VertexView.h: interface for the CVertexView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VERTEXVIEW_H__79D4E4EF_296F_4482_8B53_6DC45B2B4141__INCLUDED_)
#define AFX_VERTEXVIEW_H__79D4E4EF_296F_4482_8B53_6DC45B2B4141__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shape.h"
#include "Vertex.h"

class CGraphLoader;

class CVertexView : public CShape  
{
public:
	CVertexView();
	CVertexView(CPoint);
	virtual ~CVertexView();
public:
	void Serialize(CArchive&);
	CObjectEx& clone()const;
	CString toString()const;
	NUMBER getModel()const;
	INT typeId()const;
	void displayProperties(LPCONTROLSTRUCT);
	VOID attach(CVertex*);
	void drawWithColor(CDC*,const COLORREF&);
protected:
	CVertex* m_pModel;
	friend class CGraphLoader;
};

#endif // !defined(AFX_VERTEXVIEW_H__79D4E4EF_296F_4482_8B53_6DC45B2B4141__INCLUDED_)
