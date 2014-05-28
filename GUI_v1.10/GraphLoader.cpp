// GraphLoader.cpp: implementation of the CGraphLoader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "thesis.h"
#include "GraphLoader.h"
#include "GraphFactory.h"
#include "GraphBuilder.h"
#include "GMLPairList.h"
#include "WrapperUtilities.h"
#include "WeightedVertex.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGraphLoader::CGraphLoader()
{
}

CGraphLoader::~CGraphLoader()
{
}

// Load graph from file
CGraphController* CGraphLoader::load(const char *szFileName)
{
	CGMLParser parser(szFileName);
	if(!parser.parse())return NULL;
	CGMLParserEx* pParser = (CGMLParserEx*)(&parser);
	CGMLPairList list(pParser->list->value.list); // for list->key == graph => kind == list
	// prepare variable for loading and initialize with default value
	INT directed = 1, // default value
		maxSize  = 10,
		edgeStorage = 0,
		graphics = 1,
		vertexType = 0,
		edgeType = 0,
		isNetwork = 0;
	LPGMLPAIR pair = list.lookup("maxSize");
	if(pair){
		maxSize = pair->value.integer;
		list.remove(pair);
	}
	pair = list.lookup("directed");
	if(pair) {
		directed = pair->value.integer;
		list.remove(pair);
	}

	pair = list.lookup("edgeStorage");
	if(pair) {
		edgeStorage = pair->value.integer;
		list.remove(pair);
	}

	// build model, view, controller
	CGraphControllerEx* pController = (CGraphControllerEx*) new CGraphController(maxSize);
	CAbstractGraph* pGraph;
	CGraphFactory graphFactory;
	CString strOut;
	if (edgeStorage == 0)
	{
		pGraph = graphFactory.buildGraphAsMatrix(maxSize,directed == 1);
		if (directed == 1)
			strOut.Format("Directed graph as matrix\n>> Maximum number of vertices : %d",maxSize);
		else
			strOut.Format("Undirected graph as matrix\n>> Maximum number of vertices : %d",maxSize);
	}
	else
	{
		pGraph = graphFactory.buildGraphAsLists(maxSize,directed == 1);
		if (directed)
			strOut.Format("Directed graph as lists\n>> Maximum number of vertices : %d",maxSize);
		else
			strOut.Format("Undirected graph as lists\n>> Maximum number of vertices : %d",maxSize);
	}
	pController->out(strOut);
	pController->attachModelToView(pGraph);
	pController->m_control.maxSize = maxSize;
	pController->m_control.edgeStorage = edgeStorage;

	pair = list.lookup("graphics");
	if(pair) {
		graphics = pair->value.integer;
		list.remove(pair);
	}
	pair = list.lookup("vertexType");
	if(pair) {
		pController->m_control.vertexType = vertexType = pair->value.integer;
		list.remove(pair);
	}
	pair = list.lookup("edgeType");
	if(pair) {
		pController->m_control.edgeType = edgeType = pair->value.integer;
		list.remove(pair);
	}
	pair = list.lookup("isNetwork");
	if(pair) {
		isNetwork = pair->value.integer;
		pController->m_control.isNetWork = (isNetwork == 1);
		list.remove(pair);
	}
	
	pController->m_control.vertexType = vertexType;
	pController->m_control.edgeType = edgeType;
	// build vertices
	// prepare variables with default value
	UINT id;
	CString weight;
	LPGMLPAIR nodePair;
	while (nodePair = list.lookup("node"))
	{
		CGMLPairList nodeList(nodePair->value.list); // for node has type == List
		pair = nodeList.lookup("id");
		id = pair->value.integer;
		nodeList.remove(pair);
		CVertex* pV;
		if (vertexType == 0) // unweighted vertex
			pV = new CVertex(id);
		else
		{
			pair = nodeList.lookup("weight");
			weight = pair->value.string;
			nodeList.remove(pair);
			CObjectEx&vertexWeight = CWrapperUtilities::buildWrapper(vertexType,weight);
			pV = new CWeightedVertex(id,vertexWeight);
		}
		// if graphics => build view
		CVertexView* pVV = new CVertexView;
		pair = nodeList.lookup("name");
		pVV->name = pair->value.string;
		nodeList.remove(pair);
		pair = nodeList.lookup("color");
		pVV->color = (COLORREF)pair->value.integer;
		nodeList.remove(pair);
		LPGMLPAIR ctrlPair;
		if (ctrlPair = nodeList.lookup("controlPoint"))
		{
			CGMLPairList ctrlPntList(ctrlPair->value.list);
			int index = 0;
			LPGMLPAIR pntPair;
			while ((pntPair = ctrlPntList.lookup("point")) && index < 4) 
			{
				CGMLPairList pntList(pntPair->value.list);
				pair = pntList.lookup("x");
				pVV->ctrlPoint[index].x = pair->value.integer;
				pair = pntList.lookup("y");
				pVV->ctrlPoint[index].y = pair->value.integer;
				index++;
				pParser->freeList(pntPair->value.list);
				ctrlPntList.remove(pntPair);
			}

		}
		nodeList.remove(ctrlPair);
		pGraph->addVertex(*pV);
		pVV->attach(pV);
		pController->m_pGraphView->addVertexView(pVV);
		list.remove(nodePair);
	}
	// build edges
	// prepare variables with default value
	UINT source, target;
	CString capacity;
	LPGMLPAIR edgePair;
	CGraphBuilder builder(*pGraph);
	while (edgePair = list.lookup("edge"))
	{
		CGMLPairList edgeList(edgePair->value.list); // for edge has type == List
		pair = edgeList.lookup("source");
		source = pair->value.integer;
		edgeList.remove(pair);
		pair = edgeList.lookup("target");
		target = pair->value.integer;
		edgeList.remove(pair);
		CEdge*pE;
		if (edgeType == 0) // unweighted edge
			pE = builder.buildDefaultEdge(source,target);
		else
		{
			pair = edgeList.lookup("weight");
			weight = pair->value.string;
			edgeList.remove(pair);
			CObjectEx&edgeWeight = CWrapperUtilities::buildWrapper(edgeType,weight);
			if (isNetwork == 0) 
				pE = builder.buildWeightedEdge(source,target,edgeWeight);
			else
			{
				pair = edgeList.lookup("capacity");
				capacity = pair->value.string;
				edgeList.remove(pair);
				CObjectEx&edgeCapacity = CWrapperUtilities::buildWrapper(edgeType,capacity);
				pE = builder.buildNetworkEdge(source,target,edgeWeight,edgeCapacity);
			}
		}
		// if graphics => build view
		CEdgeView* pEV = new CEdgeView;
		pair = edgeList.lookup("name");
		pEV->name = pair->value.string;
		edgeList.remove(pair);
		pair = edgeList.lookup("color");
		pEV->color = pair->value.integer;
		edgeList.remove(pair);
		LPGMLPAIR ctrlPair;
		if (ctrlPair = edgeList.lookup("controlPoint"))
		{
			CGMLPairList ctrlPntList(ctrlPair->value.list);
			int index = 0;
			LPGMLPAIR pntPair;
			while ((pntPair = ctrlPntList.lookup("point")) && index < 4) 
			{
				CGMLPairList pntList(pntPair->value.list);
				pair = pntList.lookup("x");
				pEV->ctrlPoint[index].x = pair->value.integer;
				pair = pntList.lookup("y");
				pEV->ctrlPoint[index].y = pair->value.integer;
				index++;
				pParser->freeList(pntPair->value.list);
				ctrlPntList.remove(pntPair);
			}
			
		}
		edgeList.remove(ctrlPair);
		pGraph->addEdge(*pE);
		pEV->attach(pE);
		pEV->setFirstEnd(pController->m_pGraphView->vertexViews[pE->firstEndPoint()]);
		pEV->setSecondEnd(pController->m_pGraphView->vertexViews[pE->secondEndPoint()]);
		pController->m_pGraphView->addEdgeView(pEV);
		pParser->freeList(edgePair->value.list);
		list.remove(edgePair);
	}
	return pController;
}
