// EKAnimationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "thesis.h"
#include "EKAnimationDlg.h"
#include "NetworkEdge.h"
#include "Wrapper.h"
#include "GraphUtilities.h"
#include "GraphFactory.h"
#include "InsertingVisitor.h"
#include "LinkedQueue.h"
#include "NullIterator.h"

#define	  Integer	CWrapper<int>	

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEKAnimationDlg dialog


CEKAnimationDlg::CEKAnimationDlg(CWnd* pParent,CGraphView* pView)
	: CAnimationDlg(pParent)
{
	//{{AFX_DATA_INIT(CEKAnimationDlg)
	//}}AFX_DATA_INIT
	ASSERT(m_pGraphView = pView);
	init();
}


void CEKAnimationDlg::DoDataExchange(CDataExchange* pDX)
{
	CAnimationDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEKAnimationDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEKAnimationDlg, CAnimationDlg)
	//{{AFX_MSG_MAP(CEKAnimationDlg)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEKAnimationDlg message handlers

void CEKAnimationDlg::changeState()
{
	if (m_bFinished) return;
	delete m_pIter;	
	COLORREF red = RGB(255,0,0),
			 blue = RGB(0,0,255),
			 yellow = RGB(255,255,0);
	CAbstractGraph& g = *(buildResidualNetwork());
	// use breadth first search to find augmenting paht
	UINT numberOfVertices = g.numberOfVertices();
	CArrayEx<BOOL> enqueued (numberOfVertices);
	CArrayEx<INT> predecessor(numberOfVertices);
	for (NUMBER v = 0; v < numberOfVertices; ++v)
	{
		enqueued[v] = FALSE;
		predecessor[v] = -1;
	}
	CQueue& queue = *new CLinkedQueue ();
	queue.rescindOwnership ();
	BOOL found = FALSE;
	enqueued[m_uSource] = TRUE;
	queue.enqueue (const_cast<CVertex&>(g.selectVertex(m_uSource)));
	while (!queue.isEmpty () && !found)
	{
		CVertex& vertex = (CVertex&)queue.dequeue();
		// visit vertex
		if (vertex == m_uSink) found = TRUE;
		CIterator& p = g.emanatingEdges (vertex);
		while (!p.isDone ()) {
			CEdge& edge = (CEdge&)(p.currentItem());
			CVertex& to = edge.mate (vertex);
			if (!enqueued [to])
			{
				enqueued[to] = TRUE;
				predecessor[to] = vertex;
				queue.enqueue (to);
			}
			p.moveNext();
		}
		delete &p;
	}
	delete &queue;
	if (!found) 
	{
		m_bFinished = TRUE;
		CInsertingVisitor visitor(m_pGraphView);
		CGraphUtilities gu;
		gu.breadthFirstTraversal(g,visitor,m_uSource);
		m_pIter = &visitor.getGraphics();
		Invalidate(FALSE);
		delete &g;
		return;
	}
	// found augmenting path =. trace back
	INT tmpV = predecessor[m_uSink];
	INT cp = (Integer&)((CWeightedEdge&)g.selectEdge(tmpV,m_uSink)).getWeight();
	while (predecessor[tmpV] != -1)
	{
		INT cf = (Integer&)((CWeightedEdge&)g.selectEdge(predecessor[tmpV],tmpV)).getWeight();
		if (cf < cp)
			cp = cf;
		tmpV = predecessor[tmpV];
	}
	tmpV = m_uSink;
	CAbstractGraph& network = *m_pGraphView->getModel();
	CGraphViewEx* pViewEx = (CGraphViewEx*)m_pGraphView; 
	CLinkedList<CObjectEx*>& list = * new CLinkedList<CObjectEx*>;
	while (predecessor[tmpV] != -1)
	{
		list.append(pViewEx->vertexViews[tmpV]);
		CNetworkEdge& e = (CNetworkEdge&)network.selectEdge(predecessor[tmpV],tmpV);
		if (e.isNull())
		{
			CNetworkEdge& e1 = (CNetworkEdge&)network.selectEdge(tmpV,predecessor[v]);
			INT w = (Integer&)e1.getWeight();
			e1.setWeight(*new Integer( w - cp));
			// add to graph view
			list.append(pViewEx->edgeViews[tmpV][predecessor[tmpV]]);
			pViewEx->edgeViews[tmpV][predecessor[tmpV]]->setColor(yellow);
		}
		else
		{
			INT w = (Integer&)e.getWeight();
			e.setWeight(*new Integer( w + cp));
			list.append(pViewEx->edgeViews[predecessor[tmpV]][tmpV]);
			// set color
			INT c = (Integer&)e.getCapacity();
			if (w + cp == c)
				pViewEx->edgeViews[predecessor[tmpV]][tmpV]->setColor(red);
			else pViewEx->edgeViews[predecessor[tmpV]][tmpV]->setColor(blue);
		}
		tmpV = predecessor[tmpV];
	}
	delete &g;
	list.append(pViewEx->vertexViews[tmpV]);
	m_pIter = new CListIterator(list);
	Invalidate(FALSE);
}

void CEKAnimationDlg::init()
{
	COLORREF black = RGB(0,0,0);
	CGraphViewEx* pViewEx = (CGraphViewEx*)m_pGraphView; 
	CGraphUtilities gu;
	m_pIter = new CNullIterator;
	CAbstractGraph& network = *m_pGraphView->getModel();
	CIterator& iter = network.getEdges();
	for(; !iter.isDone(); iter.moveNext())
	{
		CNetworkEdge& e = (CNetworkEdge&)iter.currentItem();
		e.setWeight(*new Integer(0));
		UINT from = e.firstEndPoint(),
			 to = e.secondEndPoint();
		pViewEx->edgeViews[from][to]->setColor(black);
	}
	delete&iter;
}

void CEKAnimationDlg::drawAnimation(CDC*pDC)
{
	while(!m_pIter->isDone())
	{
		CGraphics& graphics = (CGraphics&)m_pIter->currentItem();
		graphics.drawWithColor(pDC,m_trackColor[1]);
		if (graphics.typeId() == EDGEVIEWID)
			((CEdgeView&)graphics).drawDirectedMarkWithColor(pDC,m_trackColor[1]);
		m_pIter->moveNext();
	}	
	m_pIter->reset();
}

CAbstractGraph* CEKAnimationDlg::buildResidualNetwork()
{
	CAbstractGraph& network = *m_pGraphView->getModel();
	UINT numberOfVertices = network.numberOfVertices();
	CGraphFactory graphFactory;
	CAbstractGraph* pResult = graphFactory.buildGraphAsMatrix(numberOfVertices,TRUE);
	CGraphBuilder builder(*pResult);
	for (NUMBER v = 0; v < numberOfVertices; ++v)
		pResult->addVertex(*(builder.buildDefaultVertex()));
	CIterator& iter = network.getEdges();
	for(; !iter.isDone(); iter.moveNext())
	{
		CNetworkEdge& e = (CNetworkEdge&)iter.currentItem();
		NUMBER  m_uSource = e.firstEndPoint(),
			target = e.secondEndPoint();
		if (!pResult->selectEdge(m_uSource,target).isNull()) continue;
		Integer& weight = (Integer&)e.getWeight();
		Integer& capacity = (Integer&)e.getCapacity();
		INT w = capacity - weight;
		CNetworkEdge& e1 = (CNetworkEdge&)network.selectEdge(target,m_uSource);
		if (e1.isNull())
		{
			if (w > 0) pResult->addEdge(*(builder.buildWeightedEdge(m_uSource,target,*new Integer(w))));
			if (weight > 0) pResult->addEdge(*(builder.buildWeightedEdge(target,m_uSource,*new Integer(weight))));
		}
		else
		{
			Integer& weight1 = (Integer&)e1.getWeight();
			w = w + weight1;
			if (w > 0) pResult->addEdge(*(builder.buildWeightedEdge(m_uSource,target,*new Integer(w))));
		}
	}
	delete&iter;
	return pResult;
}

void CEKAnimationDlg::setParas(NUMBER s, NUMBER t)
{
	m_uSource = s;
	m_uSink = t;
}

void CEKAnimationDlg::OnDestroy() 
{
	CAbstractGraph& network = *m_pGraphView->getModel();
	CAnimationDlg::OnDestroy();	
	delete &network;
	delete m_pIter;
}

void CEKAnimationDlg::reset()
{
	delete m_pIter;
	init();
	m_bFinished = FALSE;
}
