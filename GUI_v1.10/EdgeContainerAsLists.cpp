// EdgeContainerAsLists.cpp: implementation of the CEdgeContainerAsLists class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thesis.h"
#include "EdgeContainerAsLists.h"
#include "AbstractGraph.h"
#include "NullIterator.h"
#include "NullObject.h"
#include "ListIterator.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEdgeContainerAsLists::CEdgeContainerAsLists(UINT MAXSIZE)
	: adjacencyLists(MAXSIZE)
{
}

CEdgeContainerAsLists::~CEdgeContainerAsLists()
{
	purge();
}

VOID CEdgeContainerAsLists::addEdge(CEdge &edge)
{
	NUMBER firstEndPoint = edge.firstEndPoint();
	NUMBER secondEndPoint = edge.secondEndPoint();
	if(edge.isNull()){
		throw std::invalid_argument("Endpoint doesn't exist");
		AfxMessageBox("Endpoint doesn't exist");
		return;
	}
	// co can phai kiem tra canh them vao cung kieu voi cac canh truoc do ???

	const CLinkedList<CEdge*>::CListElement *ptr = adjacencyLists[firstEndPoint].head();
	while (ptr!=0) {
		if(ptr->datum->secondEndPoint() == secondEndPoint){
		//	throw std::invalid_argument("Edge existed");
			AfxMessageBox("Edge existed");
			return;
		}
		ptr = ptr->next;
	}
	adjacencyLists[firstEndPoint].append(&edge);
	m_uCount++;
}

VOID CEdgeContainerAsLists::purge()
{
	for(UINT i = 0; i < m_pGraph->numberOfVertices(); i++ ){
		const CLinkedList<CEdge*>::CListElement* pE = adjacencyLists[i].head();
		while(pE != 0){
			delete pE->datum;
			pE = pE->next;
		}
	}
}

CIterator& CEdgeContainerAsLists::emanatingEdges(NUMBER vertex) const
{
	// check if this vertex is contained by graph
	CVertex& v = m_pGraph->selectVertex(vertex);
	if (v.isNull()) return *new CNullIterator;
	CLinkedList<CEdge*>* pList = new 
		CLinkedList<CEdge*>((CLinkedList<CEdge*>&)adjacencyLists[v]);
	return *new CListIterator((CLinkedList<CObjectEx*>&)*pList);
}

CIterator& CEdgeContainerAsLists::incidentEdges(NUMBER v) const
{
	CVertex& vertex = m_pGraph->selectVertex(v);
	if (vertex.isNull()) return *new CNullIterator;
	// create a linked list and then create a iterator from this list
	CLinkedList<CEdge*>* pList = new CLinkedList<CEdge*>;
	for(UINT i = 0; i < m_pGraph->numberOfVertices(); i++ ){
		const CLinkedList<CEdge*>::CListElement* pE = adjacencyLists[i].head();
		while (pE != 0){ 
			CEdge& e = *pE->datum;
			if (e.secondEndPoint() == v)
				pList->append(pE->datum);
			pE = pE->next;
		}
	}
	return *new CListIterator((CLinkedList<CObjectEx*>&)*pList);
}

CIterator& CEdgeContainerAsLists::getEdges() const
{
	UINT uNumberOfVertices = m_pGraph->numberOfVertices();
	if (uNumberOfVertices == 0) return *new CNullIterator;
	CLinkedList<CEdge*>* pList = new CLinkedList<CEdge*>;
	for(UINT i = 0; i < uNumberOfVertices; i++ ){
		const CLinkedList<CEdge*>::CListElement* pE = adjacencyLists[i].head();
		while (pE != 0){ 
			pList->append(pE->datum);
			pE = pE->next;
		}
	}
	return *new CListIterator((CLinkedList<CObjectEx*>&)*pList);
}

INT CEdgeContainerAsLists::typeId() const
{
	return EDGECONTAINERASLISTSID;
}

CEdge& CEdgeContainerAsLists::selectEdge(NUMBER from, NUMBER to) const
{
	UINT uNumberOfVertices = m_pGraph->numberOfVertices();
	if (from >= uNumberOfVertices) return (CEdge&)CNullObject::instance();
	const CLinkedList<CEdge*>::CListElement* ptr = adjacencyLists[from].head();
	while (ptr!=0){ 
		if((*ptr->datum).secondEndPoint() == to)
			return *ptr->datum;
		ptr = ptr->next;
	}
	// if can't find return NULL
	return (CEdge&)CNullObject::instance();
}

CString CEdgeContainerAsLists::toString() const
{
	return "EdgeContainerAsLists";
}

void CEdgeContainerAsLists::removeEdge(NUMBER from, NUMBER to)
{
	CEdge& e = selectEdge(from,to);
	if (e.isNull()) {
//		AfxMessageBox("Edge doesn't exist");
		return;
	}
	// if existed, delete it and set to NULL
	adjacencyLists[from].extract(&e);
	delete &e;
	m_uCount--;
}

void CEdgeContainerAsLists::adjustBeforeRemove(NUMBER vertex)
{
	// delete emanating edges
	const CLinkedList<CEdge*>::CListElement* ptr = adjacencyLists[vertex].head();
	while (ptr!=0){ 
		delete ptr->datum;
		ptr = ptr->next;
		m_uCount--;
	}
	adjacencyLists[vertex].purge();
	// delete incident edges
	UINT bound = m_pGraph->numberOfVertices() - 1;
	for(UINT i = 0; i <= bound; i++ )
		removeEdge(i,vertex);
	// adjust
	for(i = vertex; i < bound; i++)
		adjacencyLists[i] = adjacencyLists[i+1];
	adjacencyLists[bound].purge();
}

void CEdgeContainerAsLists::resize(UINT newSize)
{
	adjacencyLists.setLength(newSize);
	// chua xu li truong hop lam nho graph, phai xoa cac du lieu du thua.
}
