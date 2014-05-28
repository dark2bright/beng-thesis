// EdgeContainer.h: interface for the CEdgeContainer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EDGECONTAINER_H__EB482E73_918B_464B_AAE4_386A91030413__INCLUDED_)
#define AFX_EDGECONTAINER_H__EB482E73_918B_464B_AAE4_386A91030413__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Container.h"
#include "Vertex.h"
#include "Edge.h"
#include "LinkedList.h"

class CAbstractGraph;

class CEdgeContainer : public CContainer  
{
public:
	VOID setParent(CAbstractGraph*pParent);
protected: // pure virtual function
	virtual void adjustBeforeRemove(NUMBER) = 0;
	virtual VOID addEdge (CEdge&) = 0;
	virtual void removeEdge(NUMBER,NUMBER) = 0;
	virtual void resize(UINT) = 0;
	virtual CEdge& selectEdge(NUMBER,NUMBER) const = 0;
	virtual CIterator& getEdges() const = 0;
	virtual CIterator& incidentEdges(NUMBER) const = 0;  // in-degree
	virtual CIterator& emanatingEdges(NUMBER) const = 0; // out-degree
protected:
	UINT numberOfEdges()const;
	BOOL isEdge (NUMBER, NUMBER) const;
	VOID accept (CVisitor&) const;
	virtual  ~CEdgeContainer();
protected:
	CAbstractGraph*m_pGraph;
protected:
	friend class CAbstractGraph;
};

#endif // !defined(AFX_EDGECONTAINER_H__EB482E73_918B_464B_AAE4_386A91030413__INCLUDED_)
