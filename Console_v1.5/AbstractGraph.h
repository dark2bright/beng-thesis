// AbstractGraph.h: interface for the CAbstractGraph class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ABSTRACTGRAPH_H__EA253EA4_2EB5_4C07_B04B_65E473233A0E__INCLUDED_)
#define AFX_ABSTRACTGRAPH_H__EA253EA4_2EB5_4C07_B04B_65E473233A0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Container.h"
#include "EdgeContainer.h"
#include "BArray.h"

class CGraphFactory;

class CAbstractGraph : public CContainer
{
protected:
	CAbstractGraph(UINT,CEdgeContainer&);	
public:
	void removeEdge(NUMBER,NUMBER);
	void removeVertex(NUMBER);
	BOOL isFull()const;
	void resize(UINT);
	VOID accept (CVisitor&) const;
	CIterator& getVertices() const;
	CIterator& getEdges()const;
	virtual BOOL isDirected()const = 0;
	virtual VOID purge ();
	VOID addVertex(CVertex& vertex);
	VOID addEdge (CEdge&);
	CVertex&  selectVertex(NUMBER) const;	
	CEdge& selectEdge(NUMBER from, NUMBER to)const;
	virtual UINT numberOfEdges()const;
	virtual UINT numberOfVertices()const;
	virtual CVertex& operator [] (NUMBER) const;
	CIterator& emanatingEdges(NUMBER) const;
	CIterator& incidentEdges(NUMBER) const;
	virtual ~CAbstractGraph();
protected: 
	CArrayEx<CVertex*> vertices;
	CEdgeContainer& edges;
	friend class CGraphFactory;
};

#endif // !defined(AFX_ABSTRACTGRAPH_H__EA253EA4_2EB5_4C07_B04B_65E473233A0E__INCLUDED_)
