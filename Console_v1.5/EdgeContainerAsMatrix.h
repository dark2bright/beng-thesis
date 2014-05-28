// EdgeContainerAsMatrix.h: interface for the CEdgeContainerAsMatrix class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EDGECONTAINERASMATRIX_H__7B77C1F0_0F68_43F1_8D4D_8C2CD774204B__INCLUDED_)
#define AFX_EDGECONTAINERASMATRIX_H__7B77C1F0_0F68_43F1_8D4D_8C2CD774204B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Array2D.h"
#include "EdgeContainer.h"

class CGraphFactory;

class CEdgeContainerAsMatrix  : public CEdgeContainer
{
protected:
	CEdgeContainerAsMatrix(UINT);
	virtual ~CEdgeContainerAsMatrix();
protected:
	virtual void adjustBeforeRemove(NUMBER);
	virtual void removeEdge(NUMBER,NUMBER);
	virtual CString toString()const;
	CEdge& selectEdge(NUMBER,NUMBER) const;
	CIterator& emanatingEdges(NUMBER) const;
	CIterator& getEdges() const;
	CIterator& incidentEdges(NUMBER) const;
	INT typeId()const;
	VOID addEdge (CEdge&);
	VOID purge();
private:
    CArray2D<CEdge*> adjacencyMatrix;
protected:
	void resize(UINT);
	friend class CGraphFactory;
};

#endif // !defined(AFX_EDGECONTAINERASMATRIX_H__7B77C1F0_0F68_43F1_8D4D_8C2CD774204B__INCLUDED_)
