// GraphView.cpp: implementation of the CGraphView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thesis.h"
#include "GraphView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGraphView::CGraphView(UINT MAXSIZE)
:	vertexViews(MAXSIZE),
	edgeViews(MAXSIZE,MAXSIZE)
{
	m_pModel = NULL;
	for(UINT i = 0; i < MAXSIZE; i++){
		vertexViews[i] = NULL;
		for(UINT j = 0; j < MAXSIZE; j++)
			edgeViews[i][j] = NULL;
	}
}

CGraphView::~CGraphView()
{
	purge();
}

void CGraphView::attach(CAbstractGraph *pModel)
{
	m_pModel = pModel;
}

void CGraphView::buildDefaultView()
{
	if (!m_pModel) return;
	// build circle graph layout
}

void CGraphView::purge()
{
	if (!m_pModel) return;
	UINT numberOfVertices = m_pModel->numberOfVertices();
	for(UINT i = 0; i < numberOfVertices; i++){
		delete vertexViews[i];
		for(UINT j = 0; j < numberOfVertices; j++){
			CEdgeView* pE = edgeViews[i][j];
			if (pE)delete pE;
		}
	}
}

void CGraphView::draw(CDC *pDC)
{
	if (!m_pModel) return;
	UINT numberOfVertices = m_pModel->numberOfVertices();	
	// draw vertices and edges
	for(UINT row = 0; row < numberOfVertices; row++)
	{
		vertexViews[row]->draw(pDC);
		for(UINT col = 0; col < numberOfVertices; col++){
			CEdgeView* pE = edgeViews[row][col];
			if (pE){
				pE->draw(pDC);
				if (m_pModel->isDirected())
					pE->drawDirectedMark(pDC);
			}
		}
	}
}


CGraphics* CGraphView::getAt(CPoint point,UINT& nHitTest) const
{
	if (!m_pModel) return NULL;
	UINT numberOfVertices = m_pModel->numberOfVertices();
	for (int i = 0; i < numberOfVertices; i++){
		CVertexView*p = vertexViews[i];
		if ((nHitTest = vertexViews[i]->hitTest(point)) != DO_NOTHING) // va phai khac DO_DRAW_NEW nhung khong can kiem tra
			return vertexViews[i];
		for(UINT j = 0; j < numberOfVertices; j++){
			CEdgeView* pE = const_cast<CArray2D<CEdgeView*>&>(edgeViews)[i][j];
			// if(pE && pE->hitTest(point) == DO_SELECT) return pE;
			if(pE && (nHitTest = pE->hitTest(point)) != DO_NOTHING) return pE;
		}
	}
	return NULL;
}

void CGraphView::addVertexView(CVertexView*pView)
{
	NUMBER vertex = pView->getModel();
	vertexViews[vertex] = pView;
}


void CGraphView::addEdgeView(CEdgeView *pEdgeView)
{
	NUMBER from = pEdgeView->getFirstEnd()->getModel();
	NUMBER to = pEdgeView->getSecondEnd()->getModel();
	edgeViews[from][to] = pEdgeView;
}

void CGraphView::updateEdgeViews(CVertexView *pVertexView)
{
	UINT numberOfVertices = m_pModel->numberOfVertices();
	NUMBER vertex = pVertexView->getModel();
	for(UINT mate = 0; mate < numberOfVertices; mate++){
		CEdgeView* pE = edgeViews[mate][vertex];
		if (pE)pE->reposition(DO_UPDATE);
		pE = edgeViews[vertex][mate];
		if (pE)pE->reposition(DO_UPDATE);
	}
}

CAbstractGraph* CGraphView::getModel()const{
	return m_pModel;
}

// remove edge view. Don't care about its model ==> It's controller's job.
void CGraphView::removeEdgeView(NUMBER from,NUMBER to)
{
	delete edgeViews[from][to];
	edgeViews[from][to] = NULL;
}


void CGraphView::removeVertexView(NUMBER vertex)
{
	UINT numberOfVertices = m_pModel->numberOfVertices();
	// remove associated edge views with vertex views
	for(UINT i = 0; i < numberOfVertices; i++)
	{
		CEdgeView* pE = edgeViews[vertex][i];
		if (pE) {
			delete pE;
			edgeViews[vertex][i] = NULL;
		}
		pE = edgeViews[i][vertex];
		if (pE) {
			delete pE;
			edgeViews[vertex][i] = NULL;
		}
	}
	delete vertexViews[vertex];
	vertexViews[vertex] = NULL;
	numberOfVertices--;
	// adjust edge views
	for(i = 0; i < numberOfVertices; i++)
		for(UINT j = 0; j < numberOfVertices; j++)
		{
			if (i < vertex && j >= vertex) 
				edgeViews[i][j] = edgeViews[i][j+1];
			if (i >= vertex && j < vertex)
				edgeViews[i][j] = edgeViews[i+1][j];
			if (i >= vertex && j >= vertex)
				edgeViews[i][j] = edgeViews[i+1][j+1];
		}
	for(i = 0; i < numberOfVertices; i++)
	{
		edgeViews[i][numberOfVertices] = NULL;
		edgeViews[numberOfVertices][i] = NULL;
	}
	// adjust vertex views
	for(i = vertex; i < numberOfVertices; i++)
		vertexViews[i] = vertexViews[i+1];
	vertexViews[numberOfVertices] = NULL;
}

void CGraphView::Serialize(CArchive &ar)
{
	if (ar.IsStoring())
	{
		UINT numberOfVertices = m_pModel->numberOfVertices();
		for(UINT i = 0 ; i < numberOfVertices; i++)
			vertexViews[i]->Serialize(ar);
		for(i = 0 ; i < numberOfVertices; i++)
			for(UINT j = 0 ; j < numberOfVertices; j++)
			{
				CEdgeView*pE = edgeViews[i][j];
				if (pE) pE->Serialize(ar);
			}
	}
}

void CGraphView::detach()
{
	m_pModel = NULL;
}

void CGraphView::resize(UINT newSize)
{
	UINT oldSize = vertexViews.getLength();
	vertexViews.setLength(newSize);
	edgeViews.setSize(newSize,newSize);
	m_pModel->resize(newSize);
	for(UINT i = oldSize; i < newSize; i++)
		for(UINT j = 0; j < newSize; j++)
			edgeViews[i][j] = 0;
	for(i = 0; i < oldSize; i++)
		for(UINT j = oldSize; j < newSize ; j++)
			edgeViews[i][j] = 0;
}
