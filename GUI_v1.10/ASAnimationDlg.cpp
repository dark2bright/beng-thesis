// ASAnimationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "thesis.h"
#include "ASAnimationDlg.h"
#include "GraphFactory.h"
#include "GraphBuilder.h"
#include "WeightedVertex.h"
#include "WeightedEdge.h"
#include "NullIterator.h"
#include "ListIterator.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CASAnimationDlg dialog
CASAnimationDlg::tagASTARSTRUCT::tagASTARSTRUCT()
{
	color = 0;
	p = -1;
	g = 0;
	f = INFINITY;
}

CASAnimationDlg::CAssoc::CAssoc (UINT p, CObjectEx&object)
	: CAssociation(priority,object),priority(p)
{
	rescindOwnership (); 
}
INT CASAnimationDlg::CAssoc::typeId() const
{
	return ASSOCID;
}
CString CASAnimationDlg::CAssoc::toString()const
{
	return "Assoc";
}

CASAnimationDlg::CASAnimationDlg(NUMBER start, NUMBER goal,CWnd* pParent /*=NULL*/)
	: CAnimationDlg(pParent)
{
	//{{AFX_DATA_INIT(CASAnimationDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_start = start;
	m_goal = goal;
}


void CASAnimationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CASAnimationDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CASAnimationDlg, CAnimationDlg)
	//{{AFX_MSG_MAP(CASAnimationDlg)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CASAnimationDlg message handlers

void CASAnimationDlg::init()
{
	CGraphFactory factory;
	CAbstractGraph* pModel = m_pGraphView->getModel();
	UINT numberOfVertices = pModel->numberOfVertices();
	CAbstractGraph& graph = *factory.buildGraphAsLists(numberOfVertices,pModel->isDirected());
	CGraphBuilder builder(graph);
	CGraphViewEx* pEx = (CGraphViewEx*)m_pGraphView;
	m_pGraphView = new CGraphView(numberOfVertices);
	COLORREF white = RGB(255,255,255);
	for(NUMBER v = 0; v < numberOfVertices; v++)
	{
		CVertexView* pVV = (CVertexView*)(&(pEx->vertexViews[v]->clone()));
		pVV->setColor(white);
		// CVertex*pV = builder.buildDefaultVertex();
		CVertex*pV = builder.buildWeightedVertex(*new Integer(INFINITY));
		pVV->attach(pV);
		m_pGraphView->addVertexView(pVV);
		graph.addVertex(*pV);
	}
	for(v = 0; v < numberOfVertices; v++)
		for(NUMBER w = 0; w < numberOfVertices; w++)
		{
			CEdgeView* pEV = pEx->edgeViews[v][w];
			if (pEV) 
			{
				// CEdgeView*pNEV = new CEdgeView(((CGraphViewEx*)m_pGraphView)->vertexViews[v]);
				CEdgeView*pNEV = (CEdgeView*)(&pEV->clone());
				pNEV->setFirstEnd(((CGraphViewEx*)m_pGraphView)->vertexViews[v]);
				pNEV->setSecondEnd(((CGraphViewEx*)m_pGraphView)->vertexViews[w]);
				CEdge* pE = builder.buildWeightedEdge(v,w,*new Integer(getDistance(v,w)));
				graph.addEdge(*pE);
				pNEV->attach(pE);
				m_pGraphView->addEdgeView(pNEV);
				// pNEV->reposition(DO_UPDATE);
			}
		}
	m_pGraphView->attach(&graph);
	((CGraphViewEx*)m_pGraphView)->vertexViews[m_start]->setColor(m_trackColor[0]);
	((CGraphViewEx*)m_pGraphView)->vertexViews[m_goal]->setColor(m_trackColor[0]);
	//////////////////////////////////////////////////////////////////////////
	m_pQueue = new CBinaryHeap(pModel->numberOfEdges());
	m_pArray = new CArrayEx<ASTARSTRUCT>(pModel->numberOfVertices());
	(*m_pArray)[m_start].color = 1; // set color to gray
	(*m_pArray)[m_start].g = 0;
	(*m_pArray)[m_start].f = getDistance(m_start,m_goal);
	((CWeightedVertex&)graph.selectVertex(m_start)).setWeight(*new Integer((*m_pArray)[m_start].f));
	m_pQueue->enqueue(*new CAssoc ((*m_pArray)[m_start].f, graph.selectVertex(m_start)));
	m_pIter = new CNullIterator;
}

// heuristic function
UINT CASAnimationDlg::getDistance(NUMBER source, NUMBER target) const
{
	CPoint s = ((CGraphViewEx*)m_pGraphView)->vertexViews[source]->getCenter();
	CPoint t = ((CGraphViewEx*)m_pGraphView)->vertexViews[target]->getCenter();
	return (UINT)sqrt(sqr((s.x - t.x))+sqr((s.y - t.y)));
}

BOOL CASAnimationDlg::OnInitDialog() 
{
	CAnimationDlg::OnInitDialog();
	
	init();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CASAnimationDlg::OnDestroy() 
{
	CAbstractGraph* pModel = m_pGraphView->getModel();
	CAnimationDlg::OnDestroy();
	delete pModel;
	delete m_pQueue;
	delete m_pArray;
	delete m_pIter;
}

void CASAnimationDlg::drawAnimation(CDC*pDC)
{
	for (; !m_pIter->isDone(); m_pIter->moveNext()) 
	{
		CGraphics& g = (CGraphics&)m_pIter->currentItem();
		g.drawAsSelected(pDC);
		g.drawControlPoints(pDC);
	}
}

void CASAnimationDlg::changeState()
{
	if (m_bFinished) return;
	if (m_pQueue->isEmpty()) 
	{
		CString str;
		str.Format("Can not find path from vertex %d to vertex %d",m_start,m_goal);
		AfxMessageBox(str);
		m_bFinished = TRUE;
		return;
	}
	delete m_pIter;
	CLinkedList<CObjectEx*>& list = *new CLinkedList<CObjectEx*>;
	CAbstractGraph& graph = *m_pGraphView->getModel();
	CAssoc& assoc = (CAssoc&)(m_pQueue->dequeueMin ());
	CVertex& u = (CVertex&)(assoc.getValue ());
	list.append(((CGraphViewEx*)m_pGraphView)->vertexViews[u]);
	m_pIter = new CListIterator(list);
	//*
	if (u == m_goal) 
	{
		list.append(((CGraphViewEx*)m_pGraphView)->vertexViews[u]);
		m_bFinished = TRUE;
		delete &assoc;
		Invalidate(FALSE);
		return;
	}
	//*/
	COLORREF gray = RGB(0,255,255);
	COLORREF black = RGB(64,64,255);
	CIterator& p = graph.emanatingEdges(u);
	for (; !p.isDone(); p.moveNext())
	{
		CWeightedEdge& edge = (CWeightedEdge&) (p.currentItem());
		CVertex& v = edge.secondEndPoint();
		/*
		if (v == m_goal) 
		{
			list.append(((CGraphViewEx*)m_pGraphView)->vertexViews[v]);
			m_bFinished = TRUE;
			break;
		}
		//*/
		UINT weight = (UnsignedInt&) (edge.getWeight());
		UINT g = (*m_pArray)[u].g + weight;
		UINT f = (*m_pArray)[v].g + getDistance(v,m_goal);
		
		if ((*m_pArray)[v].color == 0)
		{
			(*m_pArray)[v].color = 1;
			((CGraphViewEx*)m_pGraphView)->vertexViews[v]->setColor(gray);
			(*m_pArray)[v].p = u;
			(*m_pArray)[v].g = g;
			(*m_pArray)[v].f = f;
			m_pQueue->enqueue(*new CAssoc(f,graph.selectVertex(v)));
			((CWeightedVertex&)graph.selectVertex(v)).setWeight(*new Integer(f));
		}
		else 
			if ((*m_pArray)[v].color > 0)
			{
				if ((*m_pArray)[v].f > f)
				{
					(*m_pArray)[v].p = u;
					(*m_pArray)[v].g = g;
					(*m_pArray)[v].f = f;
					((CWeightedVertex&)graph.selectVertex(v)).setWeight(*new Integer(f));
				}
			}
	}
	delete &p;
	delete &assoc;
	(*m_pArray)[m_start].color = 2; // finish vertex u	
	((CGraphViewEx*)m_pGraphView)->vertexViews[u]->setColor(black);
	Invalidate(FALSE);
}

void CASAnimationDlg::reset()
{
}
