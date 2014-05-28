// UndirectedGraph.h: interface for the CUndirectedGraph class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UNDIRECTEDGRAPH_H__BC9BB91C_FC54_4944_8313_876D27A2A7A5__INCLUDED_)
#define AFX_UNDIRECTEDGRAPH_H__BC9BB91C_FC54_4944_8313_876D27A2A7A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AbstractGraph.h"

class CGraphFactory;

class CUndirectedGraph : public CAbstractGraph  
{
protected:
	CUndirectedGraph(UINT,CEdgeContainer&);
public:
	virtual CString toString()const;
	INT typeId()const;
	BOOL isDirected()const;
	friend class CGraphFactory;
};

#endif // !defined(AFX_UNDIRECTEDGRAPH_H__BC9BB91C_FC54_4944_8313_876D27A2A7A5__INCLUDED_)
