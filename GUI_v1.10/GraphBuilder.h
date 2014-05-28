// GraphDataFactory.h: interface for the CGraphDataFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHDATAFACTORY_H__DE85E251_AFD6_4A02_96D8_C921FD9242BB__INCLUDED_)
#define AFX_GRAPHDATAFACTORY_H__DE85E251_AFD6_4A02_96D8_C921FD9242BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AbstractGraph.h"
#include "Edge.h"
#include "Vertex.h"

class CGraphBuilder  
{
public:
	CGraphBuilder(CAbstractGraph&);
public:
	CVertex* buildDefaultVertex()const;
	CVertex* buildWeightedVertex(CObjectEx&)const;
	CEdge* buildDefaultEdge(NUMBER,NUMBER)const;
	CEdge* buildWeightedEdge(NUMBER,NUMBER,CObjectEx&)const;
	CEdge* buildNetworkEdge(NUMBER,NUMBER,CObjectEx&,CObjectEx&)const;
protected:
	CAbstractGraph& graph;
};

#endif // !defined(AFX_GRAPHDATAFACTORY_H__DE85E251_AFD6_4A02_96D8_C921FD9242BB__INCLUDED_)
