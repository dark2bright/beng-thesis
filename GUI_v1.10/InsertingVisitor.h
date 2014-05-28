// InsertingVisitor.h: interface for the CInsertingVisitor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLORINGVISITOR_H__1800CE50_42EF_492F_90A1_4EC707D55410__INCLUDED_)
#define AFX_COLORINGVISITOR_H__1800CE50_42EF_492F_90A1_4EC707D55410__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Visitor.h"
#include "GraphView.h"

//////////////////////////////////////////////////////////////////////////
// InsertingVisitor : insert every object it visits and return an Iterator

class CInsertingVisitor : public CVisitor  
{
	class CGraphViewEx : public CGraphView
	{
		friend class CInsertingVisitor;
	};

	class CGraphicsIterator : public CIterator
	{
	public:
		CGraphicsIterator(CLinkedList<CGraphics*> &);
		virtual VOID reset ();
		virtual BOOL isDone () const;
		virtual CObjectEx& currentItem() const;
		virtual VOID moveNext();
		virtual ~CGraphicsIterator();
	protected:
		CLinkedList<CGraphics*>const & list;
		CLinkedList<CGraphics*>::CListElement const* m_pCurrent;
	};
public:
	CInsertingVisitor(CGraphView*);
	virtual ~CInsertingVisitor();
public:
	CIterator& getGraphics()const;
	void visit(CObjectEx&);
protected:
	CGraphView *m_pGraphView;
	CLinkedList<CGraphics*> *m_pList;
};

#endif // !defined(AFX_COLORINGVISITOR_H__1800CE50_42EF_492F_90A1_4EC707D55410__INCLUDED_)
