// GraphView.h: interface for the CGraphView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHVIEW_H__FFC55654_2A09_42BD_B9F4_6AA8E255FB09__INCLUDED_)
#define AFX_GRAPHVIEW_H__FFC55654_2A09_42BD_B9F4_6AA8E255FB09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AbstractGraph.h"
#include "EdgeView.h"
#include "GraphBuilder.h"
#include "Array2D.h"

class CGraphLoader;
class CGraphLayout;
// composite pattern
class CGraphView
{
public:
	CGraphView(UINT);
	virtual ~CGraphView();
public:
	void resize(UINT);
	void detach();
	void Serialize(CArchive&);
	void removeVertexView(NUMBER);
	void removeEdgeView(NUMBER,NUMBER);
	void updateEdgeViews(CVertexView*);
	void addEdgeView(CEdgeView*);
	void addVertexView(CVertexView*);
	CGraphics* getAt(CPoint,UINT &)const;
	CAbstractGraph*getModel()const;
	void draw(CDC*);
	void purge();
	void buildDefaultView();
	void attach(CAbstractGraph*);
protected:
	CArrayEx<CVertexView*> vertexViews;
	CArray2D<CEdgeView*> edgeViews; // adjacency matrix
	CAbstractGraph* m_pModel;
	friend class CGraphLoader;
	friend class CGraphLayout;
};

#endif // !defined(AFX_GRAPHVIEW_H__FFC55654_2A09_42BD_B9F4_6AA8E255FB09__INCLUDED_)
