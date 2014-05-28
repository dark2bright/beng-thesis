// DirectedGraph.cpp: implementation of the CDirectedGraph class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thesis.h"
#include "DirectedGraph.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDirectedGraph::CDirectedGraph(UINT MAXSIZE, CEdgeContainer &edges)
	: CAbstractGraph(MAXSIZE,edges) 
{
}

BOOL CDirectedGraph::isDirected() const
{
	return TRUE;
}

INT CDirectedGraph::typeId() const
{
	return DIRECTEDGRAPHID;
}

CString CDirectedGraph::toString() const
{
	return"DirectedGraph";
}
