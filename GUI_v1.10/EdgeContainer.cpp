// EdgeContainer.cpp: implementation of the CEdgeContainer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thesis.h"
#include "EdgeContainer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

UINT CEdgeContainer::numberOfEdges() const
{
	return m_uCount;
}

BOOL CEdgeContainer::isEdge(NUMBER from, NUMBER to) const
{
	CEdge& e = selectEdge(from, to);
	if (e.isNull()) return FALSE;
	return TRUE;
}

VOID CEdgeContainer::setParent(CAbstractGraph *pParent)
{
	m_pGraph = pParent;
}

VOID CEdgeContainer::accept(CVisitor &visitor) const
{
	CIterator& iter = getEdges();
	while (!iter.isDone()) {
		CEdge& e = (CEdge&)iter.currentItem();
		visitor.visit(e);
	}
	delete &iter;
}

CEdgeContainer::~CEdgeContainer()
{

}