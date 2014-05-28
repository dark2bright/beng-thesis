// GraphGenerator.cpp: implementation of the CGraphGenerator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "thesis.h"
#include "GraphGenerator.h"
#include "GraphBuilder.h"
#include "Wrapper.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGraphGenerator::CGraphGenerator(CGraphView&view) : graphView(view)
{
	vertexWeightUpperBound = INT_MAX;
	edgeWeightUpperBound = INT_MAX;
	capacityUpperBound = INT_MAX;
}

CGraphGenerator::~CGraphGenerator()
{
}

void CGraphGenerator::generateRandomGraph(UINT numberOfVertices,UINT numberOfEdges, INT vertexType,INT edgeType, BOOL isNetwork)
{
	CAbstractGraph&graph = *graphView.getModel();
	if (!graph.isEmpty()) return;
	CArray2D<BOOL> hashTable(numberOfVertices,numberOfVertices);
	for(NUMBER i = 0; i < numberOfVertices; i++)
		for(NUMBER j = 0; j < numberOfVertices; j++)
			hashTable[i][j] = 0;
	CGraphBuilder builder(graph);
	if (vertexType == None) 
		for(NUMBER v = 0; v < numberOfVertices; v++)
			graph.addVertex(*(builder.buildDefaultVertex()));
	else
		for(NUMBER v = 0; v < numberOfVertices; v++)
			graph.addVertex(*(builder.buildWeightedVertex(*new Integer(rand()%vertexWeightUpperBound))));
	if (graph.isDirected())
	{
		if (edgeType == None)
		{
			while (numberOfEdges > 0) 
			{
				NUMBER  source = rand() % numberOfVertices,
						target = rand() % numberOfVertices;
				if (source != target && hashTable[source][target] == FALSE)
				{ 
					graph.addEdge(*(builder.buildDefaultEdge(source,target)));
					hashTable[source][target] = TRUE;
					numberOfEdges--;
				}
			}
		}
		else
		{
			if (isNetwork) // absolutely fault for not sastify conversation condition
			{
				while (numberOfEdges > 0) 
				{
					NUMBER  source = rand() % numberOfVertices,
						target = rand() % numberOfVertices;
					if (source != target && hashTable[source][target] == FALSE)
					{ 
						INT capacity = rand() % capacityUpperBound;
						INT upperBound = capacity > edgeWeightUpperBound ? capacity : edgeWeightUpperBound;
						INT weight = rand() % upperBound;
						graph.addEdge(*(builder.buildNetworkEdge(source,target,*new Integer(weight),*new Integer(capacity))));
						hashTable[source][target] = TRUE;
						numberOfEdges--;
					}
				}
			}
			else
			{
				while (numberOfEdges > 0) 
				{
					NUMBER  source = rand() % numberOfVertices,
						target = rand() % numberOfVertices;
					if (source != target && hashTable[source][target] == FALSE)
					{ 
						graph.addEdge(*(builder.buildWeightedEdge(source,target,*new Integer(rand()%edgeWeightUpperBound))));
						hashTable[source][target] = TRUE;
						numberOfEdges--;
					}
				}
			}
		}	
	}
	else
	{
		// for undirected graph, only add edge having source < target
		if (edgeType == None)
		{
			while (numberOfEdges > 0) 
			{
				NUMBER  source = rand() % numberOfVertices,
					target = rand() % numberOfVertices;
				if (source != target && hashTable[source][target] == FALSE)
				{ 
					graph.addEdge(*(builder.buildDefaultEdge(source,target)));
					hashTable[source][target] = TRUE;
					hashTable[target][source] = TRUE;
					numberOfEdges--;
				}
			}
		}
		else
		{
			while (numberOfEdges > 0) 
			{
				NUMBER  source = rand() % numberOfVertices,
					target = rand() % numberOfVertices;
				if (source != target && hashTable[source][target] == FALSE)
				{ 
					graph.addEdge(*(builder.buildWeightedEdge(source,target,*new Integer(rand() % edgeWeightUpperBound))));
					hashTable[source][target] = TRUE;
					hashTable[target][source] = TRUE;
					numberOfEdges--;
				}
			}
		}
	}
	refreshView();
}

void CGraphGenerator::generateCompleteGraph(UINT numberOfVertices,INT vertexType, INT edgeType,BOOL isNetwork)
{
	CAbstractGraph&graph = *graphView.getModel();
	if (!graph.isEmpty()) return;
	CGraphBuilder builder(graph);
	if (vertexType == None) // unweighted vertex
		for(NUMBER v = 0; v < numberOfVertices; v++)
			graph.addVertex(*(builder.buildDefaultVertex()));
	else
		graph.addVertex(*(builder.buildWeightedVertex(*new Integer(rand()%vertexWeightUpperBound))));
	if (graph.isDirected())
	{
		if (edgeType == None) // unweighted edge
		{
			for(NUMBER source = 0; source < numberOfVertices; source++)
				for(NUMBER target = 0; target < numberOfVertices; target++)
					if (source != target) 
						graph.addEdge(*(builder.buildDefaultEdge(source,target)));
		}
		else
		{
			if (isNetwork) // absolutely fault for not sastify conversation condition
			{
				for(NUMBER source = 0; source < numberOfVertices; source++)
					for(NUMBER target = 0; target < numberOfVertices; target++)
						if (source != target) 
						{
							INT capacity = rand() % capacityUpperBound;
							INT upperBound = capacity > edgeWeightUpperBound ? capacity : edgeWeightUpperBound;
							INT weight = rand() % upperBound;
							graph.addEdge(*(builder.buildNetworkEdge(source,target,*new Integer(weight),*new Integer(capacity))));
						}
			}
			else
			{
				for(NUMBER source = 0; source < numberOfVertices; source++)
					for(NUMBER target = 0; target < numberOfVertices; target++)
						if (source != target) 
							graph.addEdge(*(builder.buildWeightedEdge(source,target,*new Integer(rand()%edgeWeightUpperBound))));
			}
		}	
	}
	else
	{
		// for undirected graph, only add edge having source < target
		if (edgeType == None)
		{
			for(NUMBER source = 0; source < numberOfVertices; source++)
				for(NUMBER target = source + 1; target < numberOfVertices; target++)
					graph.addEdge(*(builder.buildDefaultEdge(source,target)));
		}
		else
		{
			for(NUMBER source = 0; source < numberOfVertices; source++)
				for(NUMBER target = source + 1; target < numberOfVertices; target++)
					graph.addEdge(*(builder.buildWeightedEdge(source,target,*new Integer(rand()%edgeWeightUpperBound))));
		}
	}
	refreshView();
}

void CGraphGenerator::refreshView()
{
	CAbstractGraph&graph = *(graphView.getModel());
	CIterator& vertices = graph.getVertices();
	while (!vertices.isDone())
	{
		CVertex& vertex = (CVertex&)vertices.currentItem();
		CVertexView& vertexView = *new CVertexView;
		vertexView.attach(&vertex);
		graphView.addVertexView(&vertexView);
		vertices.moveNext();
	}
	delete &vertices;
	CIterator& edges = graph.getEdges();
	for (; !edges.isDone(); edges.moveNext())
	{
		CEdge& edge = (CEdge&)edges.currentItem();
		NUMBER  source = (CVertex&)edge.firstEndPoint(),
			target = (CVertex&)edge.secondEndPoint();
		if (!graph.isDirected() && source > target) continue;
		CEdgeView*pE = new CEdgeView(((CGraphViewEx&)graphView).vertexViews[source]);
		pE->setSecondEnd(((CGraphViewEx&)graphView).vertexViews[target]);
		pE->attach(&edge);
		graphView.addEdgeView(pE);
	}
	delete &edges;
}

void CGraphGenerator::setUpperBounds(INT _vertexWeightUpperBound, INT _edgeWeightUpperBound, INT _capacityUpperBound)
{
	vertexWeightUpperBound = _vertexWeightUpperBound;
	edgeWeightUpperBound = _edgeWeightUpperBound;
	capacityUpperBound = _capacityUpperBound;
}
