// EdgeContainerAsLists.h: interface for the CEdgeContainerAsLists class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EDGECONTAINERASLISTS_H__8C12A975_9735_4683_8FF3_45D5E74F8828__INCLUDED_)
#define AFX_EDGECONTAINERASLISTS_H__8C12A975_9735_4683_8FF3_45D5E74F8828__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EdgeContainer.h"
#include "BArray.h"

class CGraphFactory;

class CEdgeContainerAsLists  : CEdgeContainer
{
protected:
	CEdgeContainerAsLists(UINT);
	virtual ~CEdgeContainerAsLists();
protected:
	virtual void adjustBeforeRemove(NUMBER);
	virtual void removeEdge(NUMBER,NUMBER);
	void resize(UINT);
	virtual CString toString()const;
	VOID addEdge (CEdge&);
	CEdge& selectEdge(NUMBER,NUMBER) const;
	CIterator& getEdges() const;
	CIterator& incidentEdges(NUMBER) const;
	CIterator& emanatingEdges(NUMBER) const;
	INT typeId()const;
	VOID purge();
private:
    CArrayEx<CLinkedList<CEdge*> > adjacencyLists;
protected:
	friend class CGraphFactory;
};

#endif // !defined(AFX_EDGECONTAINERASLISTS_H__8C12A975_9735_4683_8FF3_45D5E74F8828__INCLUDED_)
