// UndirectedGraph.cpp: implementation of the CUndirectedGraph class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thesis.h"
#include "UndirectedGraph.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUndirectedGraph::CUndirectedGraph(UINT MAXSIZE, CEdgeContainer &edges)
	: CAbstractGraph(MAXSIZE,edges) 
{
}

BOOL CUndirectedGraph::isDirected() const
{
	return FALSE;
}

INT CUndirectedGraph::typeId() const
{
	return UNDIRECTEDGRAPHID;
}

CString CUndirectedGraph::toString() const
{
	return "UndirectedGraph";
}
