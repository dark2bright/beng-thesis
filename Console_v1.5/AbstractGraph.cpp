// AbstractGraph.cpp: implementation of the CAbstractGraph class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thesis.h"
#include "AbstractGraph.h"
#include "NullObject.h"
#include "NullIterator.h"
#include "PreOrder.h"
#include "LinkedQueue.h"
#include "ArrayIterator.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAbstractGraph::~CAbstractGraph()
{
	purge();
	delete &edges;
}

CAbstractGraph::CAbstractGraph(UINT MAXSIZE,CEdgeContainer& _edges)
	: vertices(MAXSIZE), edges(_edges)
{
}

UINT CAbstractGraph::numberOfVertices()const
{
	return m_uCount;
}

UINT CAbstractGraph::numberOfEdges()const
{
	return edges.numberOfEdges();
}

CVertex& CAbstractGraph::selectVertex(NUMBER number) const
{
	if(number >= m_uCount){
		AfxMessageBox("Can't seclect. Invalid Vertex");
		return (CVertex&)CNullObject::instance();
	}
	return *vertices[number];
}

CVertex& CAbstractGraph::operator [] (NUMBER number) const{
	return selectVertex(number);
}

VOID CAbstractGraph::addEdge (CEdge&edge){
	edges.addEdge(edge);
	if (!isDirected() && !edge.isLoop()) edges.addEdge(edge.reverse());
}


VOID CAbstractGraph::addVertex(CVertex &vertex)
{
	if(isFull() || vertex.isNull()){
		// throw std::domain_error("Graph is full");
		AfxMessageBox("Either graph is full or vertex is null");
		return;
	}
	// vertex.setNumber(m_uCount); // Number of vertex must be from 0 to N
	// Khong can thiet do vertex duoc build tu factory luon thoa dieu kien
	vertices[m_uCount++] = &vertex;
}

CEdge& CAbstractGraph::selectEdge(NUMBER from, NUMBER to) const
{
	return edges.selectEdge(from,to);
}

VOID CAbstractGraph::purge()
{
	for(UINT i = 0 ; i < m_uCount; i++){
		delete vertices[i];
	}
}

CIterator& CAbstractGraph::getEdges() const
{
	return edges.getEdges();
}

CIterator& CAbstractGraph::getVertices() const
{
	int nNumberOfVertices = numberOfVertices();
//	if (nNumberOfVertices == 0) return *new CNullIterator;
	return *new CArrayIterator((const CArrayEx<CObjectEx*>&)vertices,nNumberOfVertices);
}

CIterator& CAbstractGraph::incidentEdges(NUMBER vertex) const
{
	return edges.incidentEdges(vertex);
}

CIterator& CAbstractGraph::emanatingEdges(NUMBER vertex) const
{
	return edges.emanatingEdges(vertex);
}

VOID CAbstractGraph::accept(CVisitor &visitor) const
{
	for(UINT u = 0; u < m_uCount; u++)
		visitor.visit(selectVertex(u));
	edges.accept(visitor);
}

BOOL CAbstractGraph::isFull() const
{
	return m_uCount >= vertices.getLength();
}

void CAbstractGraph::removeVertex(NUMBER vertex)
{
	if (vertex >= m_uCount) {
		AfxMessageBox("Invalid Vertex");
		return;
	}
	edges.adjustBeforeRemove(vertex);
	delete vertices[vertex];
	m_uCount--;
	// adjust vertices after remove
	for(UINT i = vertex; i < m_uCount; i++){
		vertices[i] = vertices[i+1];
		vertices[i]->setNumber(i);
	}
	vertices[m_uCount] = NULL;
}

void CAbstractGraph::removeEdge(NUMBER from, NUMBER to)
{
	edges.removeEdge(from,to);
	if (!isDirected()) edges.removeEdge(to,from);
}

void CAbstractGraph::resize(UINT newSize)
{
	vertices.setLength(newSize);
	edges.resize(newSize);
}
