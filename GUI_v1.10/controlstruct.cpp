#include "stdafx.h"
#include "controlstruct.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

tagCONTROLSTRUCT::tagCONTROLSTRUCT()
{
	// edgeStorage = 0; // adjacency matrix
	vertexType = None; // graph with unweighted vertex
	edgeType = None; // graph with unweighted edge
	fastInsertVertex = TRUE; // create vertex with mouse only
	fastInsertEdge = TRUE; // create edge with mouse only
	isNetWork = FALSE;
	defaultWeightOfVertex = "10";
	defaultWeightOfEdge = "10";
	defaultCapacity = "100";
	vertexColor = RGB(219,214,248);
	edgeColor = RGB(0,0,0);
}