// GraphFactory.cpp: implementation of the CGraphFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thesis.h"
#include "GraphFactory.h"
#include "EdgeContainerAsLists.h"
#include "EdgeContainerAsMatrix.h"
#include "DirectedGraph.h"
#include "UndirectedGraph.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGraphFactory::CGraphFactory()
{
}

CAbstractGraph* CGraphFactory::buildGraphAsLists(UINT MAXSIZE,BOOL directed) const
{
	CEdgeContainer* pEC = new CEdgeContainerAsLists(MAXSIZE);
	CAbstractGraph* pGraph;
	if (directed) pGraph = new CDirectedGraph(MAXSIZE,*pEC);
	else pGraph = new CUndirectedGraph(MAXSIZE,*pEC);
	pEC->setParent(pGraph);
	return pGraph;
}

CAbstractGraph* CGraphFactory::buildGraphAsMatrix(UINT MAXSIZE, BOOL directed) const
{
	CEdgeContainer* pEC = new CEdgeContainerAsMatrix(MAXSIZE);
	CAbstractGraph* pGraph;
	if (directed) pGraph = new CDirectedGraph(MAXSIZE,*pEC);
	else pGraph = new CUndirectedGraph(MAXSIZE,*pEC);
	pEC->setParent(pGraph);
	return pGraph;
}
