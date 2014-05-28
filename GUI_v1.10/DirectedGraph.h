// DirectedGraph.h: interface for the CDirectedGraph class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIRECTEDGRAPH_H__05C797E9_8B03_44F2_A796_9BDE44C564D1__INCLUDED_)
#define AFX_DIRECTEDGRAPH_H__05C797E9_8B03_44F2_A796_9BDE44C564D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AbstractGraph.h"

class CGraphFactory;

class CDirectedGraph : public CAbstractGraph  
{
	CDirectedGraph(UINT,CEdgeContainer&);
public:
	virtual CString toString()const;
	INT typeId()const;
	BOOL isDirected()const;
	
	friend class CGraphFactory;
};

#endif // !defined(AFX_DIRECTEDGRAPH_H__05C797E9_8B03_44F2_A796_9BDE44C564D1__INCLUDED_)
