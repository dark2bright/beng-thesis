// InsertingVisitor.cpp: implementation of the CInsertingVisitor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "thesis.h"
#include "InsertingVisitor.h"
#include "NullObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInsertingVisitor::CGraphicsIterator::CGraphicsIterator(CLinkedList<CGraphics*> &aList) : list(aList){
	reset();
}

VOID CInsertingVisitor::CGraphicsIterator::reset ()
{
	m_pCurrent = list.head();
}

BOOL CInsertingVisitor::CGraphicsIterator::isDone () const
{
	return m_pCurrent == NULL;
}

CObjectEx& CInsertingVisitor::CGraphicsIterator::currentItem() const
{
	if (m_pCurrent != 0)
		return *m_pCurrent->datum;
	else
		return CNullObject::instance ();
}

VOID CInsertingVisitor::CGraphicsIterator::moveNext()
{
	if (m_pCurrent)
		m_pCurrent = m_pCurrent->next;
}

CInsertingVisitor::CGraphicsIterator::~CGraphicsIterator(){
	reset();
	delete &list;
}

CInsertingVisitor::CInsertingVisitor(CGraphView*pGraphView)
{
	ASSERT(pGraphView);
	m_pGraphView = pGraphView;
	m_pList = new CLinkedList<CGraphics*>;
}

CInsertingVisitor::~CInsertingVisitor()
{
}

void CInsertingVisitor::visit(CObjectEx &node)
{
	INT typeId = node.typeId();
	CGraphViewEx* pGraphView = (CGraphViewEx*)m_pGraphView;
	NUMBER num = ((CVertex&)node);
	CVertexView* pV = pGraphView->vertexViews[num];
	m_pList->append(pV);
}

CIterator& CInsertingVisitor::getGraphics()const
{
	return *new CGraphicsIterator(*m_pList);
}
