// GraphGenerator.h: interface for the CGraphGenerator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHGENERATOR_H__3B4221A6_18EB_41C4_9F1B_9AF511C9D04F__INCLUDED_)
#define AFX_GRAPHGENERATOR_H__3B4221A6_18EB_41C4_9F1B_9AF511C9D04F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GraphBuilder.h"
#include "GraphView.h"

class CGraphGenerator  
{
	class CGraphViewEx : public CGraphView
	{
		friend class CGraphGenerator;
	};
public:
	CGraphGenerator(CGraphView&);
	virtual ~CGraphGenerator();
public:
	void setUpperBounds(INT vertexWeightUpperBound = INT_MAX, INT edgeWeightUpperBound = INT_MAX, INT capacityUpperBound = INT_MAX);
	void generateRandomGraph(UINT numberOfVertices,UINT numberOfEdges, INT vertexType,INT edgeType, BOOL isNetwork);
	void generateCompleteGraph(UINT numberOfVertices,INT vertexType, INT edgeType,BOOL isNetwork);
protected:
	void refreshView();
protected:
	CGraphView& graphView;
	INT vertexWeightUpperBound;
	INT edgeWeightUpperBound;
	INT capacityUpperBound;
};

#endif // !defined(AFX_GRAPHGENERATOR_H__3B4221A6_18EB_41C4_9F1B_9AF511C9D04F__INCLUDED_)
