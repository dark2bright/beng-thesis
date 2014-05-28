// EdgeContainerAsMatrix.cpp: implementation of the CEdgeContainerAsMatrix class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thesis.h"
#include "EdgeContainerAsMatrix.h"
#include "AbstractGraph.h"
#include "NullObject.h"
#include "NullIterator.h"
#include "ListIterator.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEdgeContainerAsMatrix::CEdgeContainerAsMatrix(UINT MAXSIZE)
	: adjacencyMatrix(MAXSIZE,MAXSIZE)  
{
	for(UINT i = 0; i < MAXSIZE; i++)
		for(UINT j = 0; j < MAXSIZE; j++)
			adjacencyMatrix[i][j] = NULL;
}

CEdgeContainerAsMatrix::~CEdgeContainerAsMatrix()
{
	purge();
}

VOID CEdgeContainerAsMatrix::purge()
{
	UINT uNumberOfVertices = m_pGraph->numberOfVertices();
	for(UINT i = 0; i < uNumberOfVertices; i++)
		for(UINT j = 0; j < uNumberOfVertices; j++)
		{
			CEdge* pE = adjacencyMatrix[i][j];
			if (pE) delete pE;
		}
}

VOID CEdgeContainerAsMatrix::addEdge(CEdge &edge)
{
	NUMBER firstEndPoint = edge.firstEndPoint();
	NUMBER secondEndPoint = edge.secondEndPoint();
	if(edge.isNull()){
		throw std::invalid_argument("Can't add new edge. Invalid Edge");
		AfxMessageBox("Can't add new edge. Invalid Edge");
		return;
	}
	CEdge* pE = adjacencyMatrix[firstEndPoint][secondEndPoint];
	if (pE) 
	{
		AfxMessageBox("Edge existed");
		return;
	}
	adjacencyMatrix[firstEndPoint][secondEndPoint] = &edge;
	m_uCount++;
}

INT CEdgeContainerAsMatrix::typeId() const
{
	return EDGECONTAINERASMATRIXID;
}

CIterator& CEdgeContainerAsMatrix::incidentEdges(NUMBER v) const
{
	CVertex& vertex = m_pGraph->selectVertex(v);
	if (vertex.isNull()) return *new CNullIterator;
	// create a linked list and then create a iterator from this list
	CLinkedList<CEdge*>* pList = new CLinkedList<CEdge*>;
	for(UINT i = 0; i < m_pGraph->numberOfVertices(); i++ )
	{
		CEdge* pE = const_cast<CArray2D<CEdge*>&>(adjacencyMatrix)[i][vertex];
		if (pE)pList->append(pE);
	}
	return *new CListIterator((CLinkedList<CObjectEx*>&)*pList);
}

CIterator& CEdgeContainerAsMatrix::getEdges() const
{
	UINT uNumberOfVertices = m_pGraph->numberOfVertices();
	if (uNumberOfVertices == 0) return *new CNullIterator;
	CLinkedList<CEdge*>* pList = new CLinkedList<CEdge*>;
	for(UINT i = 0; i < uNumberOfVertices; i++ )
		for(UINT j = 0; j < uNumberOfVertices; j++ )
		{
			CEdge* pE = const_cast<CArray2D<CEdge*>&>(adjacencyMatrix)[i][j];
			if (pE)pList->append(pE);
		}
	return *new CListIterator((CLinkedList<CObjectEx*>&)*pList);
}

CIterator& CEdgeContainerAsMatrix::emanatingEdges(NUMBER v) const
{
	CVertex& vertex = m_pGraph->selectVertex(v);
	if (vertex.isNull()) return *new CNullIterator;
	// create a linked list and then create a iterator from this list
	CLinkedList<CEdge*>* pList = new CLinkedList<CEdge*>;
	for(UINT i = 0; i < m_pGraph->numberOfVertices(); i++ )
	{
		CEdge* pE = const_cast<CArray2D<CEdge*>&>(adjacencyMatrix)[vertex][i];
		if (pE)pList->append(pE);
	}
	return *new CListIterator((CLinkedList<CObjectEx*>&)*pList);
}

CEdge& CEdgeContainerAsMatrix::selectEdge(NUMBER from, NUMBER to) const
{
	UINT uNumberOfVertices = m_pGraph->numberOfVertices();
	if(from >= uNumberOfVertices || to >= uNumberOfVertices ){
		AfxMessageBox("EndPoint doesn't exist");
		return (CEdge&)CNullObject::instance();
	}
	CEdge* pE = const_cast<CArray2D<CEdge*>&>(adjacencyMatrix)[from][to];
	if (pE != 0) return *pE;
	return (CEdge&)CNullObject::instance();
}

CString CEdgeContainerAsMatrix::toString() const
{
	return "EdgeContainerAsMatrix";
}

void CEdgeContainerAsMatrix::removeEdge(NUMBER from, NUMBER to)
{
	CEdge& e = selectEdge(from,to);
	if (e.isNull()) {
		AfxMessageBox("Edge doesn't exist");
		return;
	}
	// if existed, delete it and set to NULL
	delete &e;
	adjacencyMatrix[from][to] = NULL;
	m_uCount--;
}

void CEdgeContainerAsMatrix::adjustBeforeRemove(NUMBER vertex)
{
	UINT numberOfVertices = m_pGraph->numberOfVertices();
	// delete all emanating edges and incident edges of this vertex
	for(UINT i = 0; i < numberOfVertices; i++){
		CEdge* pE = adjacencyMatrix[vertex][i];
		if (pE) {
			delete pE;
			adjacencyMatrix[vertex][i] = NULL;
			m_uCount--;
		}
		pE = adjacencyMatrix[i][vertex];
		if (pE) {
			delete pE;
			adjacencyMatrix[vertex][i] = NULL;
			m_uCount--;
		}
	}
	numberOfVertices--;
	// adjust adjacencyMatrix
	for(i = 0; i < numberOfVertices; i++)
		for(UINT j = 0; j < numberOfVertices; j++)
		{
			if (i < vertex && j >= vertex) 
				adjacencyMatrix[i][j] = adjacencyMatrix[i][j+1];
			if (i >= vertex && j < vertex)
				adjacencyMatrix[i][j] = adjacencyMatrix[i+1][j];
			if (i >= vertex && j >= vertex)
				adjacencyMatrix[i][j] = adjacencyMatrix[i+1][j+1];
		}
	// set to NULL
	for(i = 0; i < numberOfVertices; i++)
	{
		adjacencyMatrix[i][numberOfVertices] = NULL;
		adjacencyMatrix[numberOfVertices][i] = NULL;
	}
}

void CEdgeContainerAsMatrix::resize(UINT newSize)
{
	UINT oldSize;
	adjacencyMatrix.getSize(oldSize,oldSize);
	adjacencyMatrix.setSize(newSize,newSize);
	// truong hop lam lon
	for(UINT i = oldSize; i < newSize; i++)
		for(UINT j = 0; j < newSize; j++)
			adjacencyMatrix[i][j] = 0;
	for(i = 0; i < oldSize; i++)
		for(UINT j = oldSize; j < newSize ; j++)
			adjacencyMatrix[i][j] = 0;
	// chua xu li truong hop lam nho graph.
}
