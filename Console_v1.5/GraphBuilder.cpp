// GraphDataFactory.cpp: implementation of the CGraphBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thesis.h"
#include "GraphBuilder.h"
#include "NetworkEdge.h"
#include "WeightedVertex.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGraphBuilder::CGraphBuilder(CAbstractGraph&_graph)
	: graph(_graph)
{
}

CEdge* CGraphBuilder::buildDefaultEdge(NUMBER from, NUMBER to)const
{
	CVertex& v1 = graph.selectVertex(from);
	CVertex& v2 = graph.selectVertex(to);
	if (v1.isNull() || v2.isNull()) return NULL;//(CEdge&)CNullObject::instance();
	return new CEdge(v1,v2);
}

CEdge* CGraphBuilder::buildWeightedEdge(NUMBER from, NUMBER to, CObjectEx &weight)const
{
	CVertex& v1 = graph.selectVertex(from);
	CVertex& v2 = graph.selectVertex(to);
	if (v1.isNull() || v2.isNull()) return NULL; //(CEdge&)CNullObject::instance();
	return new CWeightedEdge(v1,v2,weight);	
}

CVertex* CGraphBuilder::buildDefaultVertex() const
{
	if (graph.isFull())return NULL; // (CVertex&)CNullObject::instance();
	return new CVertex(graph.numberOfVertices());
}

CVertex* CGraphBuilder::buildWeightedVertex(CObjectEx &weight)const
{
	if (graph.isFull())return NULL; // (CVertex&)CNullObject::instance();
	return new CWeightedVertex(graph.numberOfVertices(),weight);
}

CEdge* CGraphBuilder::buildNetworkEdge(NUMBER from, NUMBER to, CObjectEx &weight, CObjectEx&capacity) const
{
	CVertex& v1 = graph.selectVertex(from);
	CVertex& v2 = graph.selectVertex(to);
	if (v1.isNull() || v2.isNull()) return NULL; //(CEdge&)CNullObject::instance();
	return new CNetworkEdge(v1,v2,weight,capacity);	
}
