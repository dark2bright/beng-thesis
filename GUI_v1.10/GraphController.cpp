// GraphController.cpp: implementation of the CGraphController class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thesis.h"
#include "GraphController.h"
#include "ThesisView.h"
#include "NewVertexDlg.h"
#include "NewEdgeDlg.h"
#include "OptionsDlg.h"
#include "OutputDlg.h"
#include "ResizeGraphDlg.h"
#include "GenerateDlg.h"
#include "PropertiesGDlg.h"
#include "WrapperUtilities.h"
#include "AnimationDlg.h"
#include "AnimationDlgEx.h"
#include "SearchDlg.h"
#include "EKAnimationDlg.h"
#include "ASAnimationDlg.h"
#include "GraphUtilities.h"
#include "InsertingVisitor.h"
#include "PreOrder.h"
#include "PostOrder.h"
#include "MainFrm.h"
#include "coloredvertex.h"
#include "GraphGenerator.h"
#include "GraphLayout.h"
#include "Wrapper.h"
#include "WeightedEdge.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGraphController::CGraphController(UINT MAXSIZE)
{
	m_pGraphView = new CGraphView(MAXSIZE);
	m_pTmpSel = m_pSelected = NULL;
}

CGraphController::~CGraphController()
{
	CAbstractGraph*pModel = m_pGraphView->getModel();
	delete m_pGraphView;
	delete pModel;
}

void CGraphController::OnLButtonDown(CThesisView *pView,UINT nFlags, CPoint point)
{
	CPoint local(point);
	pView->clientToDoc(local);	
	pView->SetCapture();
	pView->Invalidate(FALSE);
	// Now, do with tools
	UINT nHitTest;	
	switch (pView->getMode())
	{
	case CThesisView::SELECT: // select, drag and drop, resize
		m_pSelected = m_pTmpSel;
		if (m_pSelected)
			m_nHitTest = m_pSelected->hitTest(point);
		m_prevPoint = point;
		break;
	case CThesisView::REMOVE: // remove graph data
		m_pSelected = m_pGraphView->getAt(point,nHitTest);
		if (m_pSelected)
			removeSelected();
		else m_pSelected = NULL;
		pView->setModifiedFlag();
		break;
	case CThesisView::VERTEX: // add new vertex
		addVertex(point);
		pView->setModifiedFlag();
		break;
	case CThesisView::EDGE: // add new edge mode
		m_pSelected = NULL;
		m_pTmpSel = m_pGraphView->getAt(point,nHitTest);
		if (m_pTmpSel && nHitTest == DO_SELECT) {
			if(m_pTmpSel->typeId() == VERTEXVIEWID) // ==> correct
			{
				m_pSelected = new CEdgeView((CVertexView*)m_pTmpSel);
				m_pTmpSel = NULL;
				pView->setModifiedFlag();
			}
		}
		break;
	}
}

void CGraphController::OnMouseMove(CThesisView *pView,UINT nFlags, CPoint point)
{
	CPoint local(point);
	pView->clientToDoc(local);
	pView->Invalidate(FALSE);
	// if mouse is pressed
	if (pView->GetCapture() == pView)
	{
		if (!m_pSelected)
		{
			// Draw rect tracker here...
			return;
		}
		//* ...recalculate current object's size
		if (nFlags == MK_LBUTTON && m_pSelected)
			pView->setModifiedFlag();
		if (pView->getMode() == CThesisView::SELECT)
		{
			CPoint offset(local - m_prevPoint);
			if (m_pSelected->typeId() == EDGEVIEWID) {
				if (m_nHitTest == DO_SELECT)
					m_pSelected->offset(offset,DO_SELECT);
				else // m_nHitTest == DO_RESIZE_XXX
				{
					m_pSelected->offset(local,m_nHitTest);
					((CEdgeView*)m_pSelected)->reposition(m_nHitTest);
				}
			}
			else // m_pSelected->typeId() == VERTEXVIEWID
			{
				m_pSelected->offset(offset,m_nHitTest);
				m_prevPoint = local;
				m_pGraphView->updateEdgeViews((CVertexView*)m_pSelected);
			}
			return;
		}
		if (pView->getMode() == CThesisView::REMOVE)
			return;
		// Reach here => draw a new one...
		m_pSelected->offset(local,DO_DRAW_NEW);
		// If this obj is a Bezier line ...
		if (m_pSelected->typeId() == EDGEVIEWID)
		{
			CGraphics *pObj = m_pGraphView->getAt(local,m_nHitTest);
			if ( pObj && m_nHitTest == DO_SELECT && pObj->typeId() == VERTEXVIEWID)
			{
				((CEdgeView*)m_pSelected)->setSecondEnd((CVertexView*)pObj);
				((CEdgeView*)m_pSelected)->reposition(DO_DRAW_NEW);
				return;
			}
			((CEdgeView*)m_pSelected)->setSecondEnd(NULL);
			((CEdgeView*)m_pSelected)->reposition(DO_DRAW_NEW);
		}
		return;
	}
	// mouse is released
	if (pView->getMode() != CThesisView::SELECT) return;
	UINT nHitTest;
	m_pTmpSel = m_pGraphView->getAt(point,nHitTest);
	if (m_pTmpSel)
		if(m_pSelected == m_pTmpSel){
			m_nHitTest = nHitTest;
		}
		else{ // Remember to write more.....
		}
	else m_nHitTest = DO_NOTHING;
}

void CGraphController::OnLButtonUp(CThesisView *pView,UINT nFlags, CPoint point)
{
	if (pView->GetCapture() == pView)
	{
		ReleaseCapture();
		CPoint local(point);
		pView->clientToDoc(local);
		if (!m_pSelected) return; // neu khong select thi khong lam gi
		//*
		if (pView->getMode() != CThesisView::SELECT)
		{
			// m_pSelected->offset(local,DO_DRAW_NEW); // ?????????????????????????????
			// Only if edge is selected
			if (m_pSelected->typeId() == EDGEVIEWID)
			{
				UINT nHitTest;
				CGraphics *pObj = m_pGraphView->getAt(local,nHitTest);
				// If the object at this point is not vertex
				// if (!pObj || pObj->typeId() != VERTEXVIEWID || nHitTest != DO_SELECT)
				if (!pObj || pObj->typeId() != VERTEXVIEWID)
				{
					// remove it immediately !
					delete m_pSelected;
					m_pSelected = NULL;
					return;
				}
				// add new edge
				((CEdgeView*)m_pSelected)->setSecondEnd((CVertexView*)pObj);
				((CEdgeView*)m_pSelected)->reposition(DO_DRAW_NEW);
				addEdge((CEdgeView*&)m_pSelected);
			}
		}
	}
}

void CGraphController::OnLButtonDblClk(CThesisView *pView,UINT nFlags, CPoint point)
{
	CPoint local(point);
	pView->clientToDoc(local);
	pView->Invalidate(FALSE);
	// Click on an object ==> display  a properties dialog
	pView->setModifiedFlag();
	m_pSelected = m_pTmpSel;
	if (m_pTmpSel != NULL) 
		m_pTmpSel->displayProperties(&m_control);
}

void CGraphController::attachModelToView(CAbstractGraph *pModel)
{
	m_pGraphView->attach(pModel);
}

void CGraphController::draw(CDC *pDC)
{
	CAbstractGraph* pModel = m_pGraphView->getModel();
	m_pGraphView->draw(pDC);
	if (m_pSelected){
		m_pSelected->drawAsSelected(pDC);
		m_pSelected->drawControlPoints(pDC);
		if (m_pSelected->typeId() == EDGEVIEWID && pModel->isDirected()) 
			((CEdgeView*)m_pSelected)->drawDirectedMarkAsSelected(pDC);
	}
	if (m_pTmpSel && m_pTmpSel != m_pSelected){
		m_pTmpSel->drawAsSelected(pDC);
		if (m_pTmpSel->typeId() == EDGEVIEWID && pModel->isDirected()) 
			((CEdgeView*)m_pTmpSel)->drawDirectedMarkAsSelected(pDC);
	}
}

HCURSOR CGraphController::getCusorHandle() const
{
	//nHandle is hittest-return
	LPCTSTR lpsIDC = IDC_ARROW;
	switch (m_nHitTest) {
	case DO_SELECT	: lpsIDC = IDC_ARROW;break;
	case DO_RESIZE_HORZ		: lpsIDC = IDC_SIZEWE;break;
	case DO_RESIZE_VERT		: lpsIDC = IDC_SIZENS;break;
	case DO_RESIZE_NEWS		: lpsIDC = IDC_SIZEALL;break;
	case DO_NOTHING			: lpsIDC = IDC_ARROW;break;
	}
	return AfxGetApp()->LoadStandardCursor(lpsIDC);
}

void CGraphController::addVertex(CPoint center)
{
	if (isFull())return;
	CAbstractGraph* pModel = m_pGraphView->getModel();
	CGraphBuilder builder(*pModel);
	CVertex* pVertex = NULL;
	CVertexView* pVertexView = new CVertexView(center);
	if (m_control.vertexType == None) // unweighted vertex
	{
		if (m_control.fastInsertVertex)  // if fast insert => buid with default value
		{
			pVertex = builder.buildDefaultVertex();
			pVertexView->setColor(m_control.vertexColor);
		}
		else // show a dialog
		{
			CNewVertexDlg dlg;
			dlg.m_color = m_control.vertexColor;
			if (dlg.DoModal() == IDOK) {
				pVertexView->setColor(dlg.m_color);
				pVertexView->setName(dlg.m_strName);
				pVertex = builder.buildDefaultVertex();
			}else{
				delete pVertexView;
				return;
			}
		}
	}
	else
		if (m_control.fastInsertVertex) // if fast insert => build with default value
		{
			CObjectEx& weight = CWrapperUtilities::buildWrapper(m_control.vertexType,m_control.defaultWeightOfVertex);
			pVertex = builder.buildWeightedVertex(weight);
		}
		else // show a dialog for user
		{
			CNewVertexDlg dlg(NULL,TRUE);
			dlg.m_color = m_control.vertexColor;
			dlg.m_strWeight = m_control.defaultWeightOfVertex;
			if(dlg.DoModal() == IDOK){
				pVertexView->setColor(dlg.m_color);
				pVertexView->setName(dlg.m_strName);
				CObjectEx& weight = CWrapperUtilities::buildWrapper(m_control.vertexType,dlg.m_strWeight);
				pVertex = builder.buildWeightedVertex(weight);
			}else
			{
				delete pVertexView;
				return;
			}
		}
		if (!pVertex) {
			delete pVertexView;
			AfxMessageBox("Graph is full");
			return;
		}
		// Reach here ==> build vertex success ==> attach model to view
		pVertexView->attach(pVertex);
		pModel->addVertex(*pVertex);
		m_pGraphView->addVertexView(pVertexView);
		m_pSelected = pVertexView;
}

void CGraphController::showOptions()
{
	CAbstractGraph*pModel = m_pGraphView->getModel();
	COptionsDlg dlg(NULL,&m_control);
	dlg.setState(pModel->numberOfVertices() == 0,pModel->numberOfEdges() == 0);
	dlg.DoModal();
	// Nho viet them de kiem tra => mang phai la directed graph
}

void CGraphController::addEdge(CEdgeView *&pEdgeView)
{
	NUMBER	from = pEdgeView->getFirstEnd()->getModel(),
		to = pEdgeView->getSecondEnd()->getModel();
	CAbstractGraph*pModel = m_pGraphView->getModel();
	CEdge& e = pModel->selectEdge(from,to);
	if (!e.isNull()) {
		delete pEdgeView;
		pEdgeView = NULL;
		return;
	}
	//* Reach here e is NULL ==> can build new one
	CEdge* pEdge = NULL;
	CGraphBuilder builder(*pModel);
	if (m_control.edgeType == None) // unweighted vertex
	{
		if (m_control.fastInsertEdge)  // if fast insert => buid with default value
		{
			pEdge = builder.buildDefaultEdge(from,to);
			pEdgeView->setColor(m_control.edgeColor);
		}
		else // show a dialog
		{
			CNewEdgeDlg dlg;
			dlg.m_bWeighted = FALSE;
			dlg.m_bNetworkEdge = FALSE;
			dlg.m_color = m_control.edgeColor;
			if (dlg.DoModal() == IDOK) 
			{
				pEdgeView->setColor(dlg.m_color);
				pEdgeView->setName(dlg.m_strName);
				pEdge = builder.buildDefaultEdge(from,to);
			}else
			{
				delete pEdgeView;
				pEdgeView = NULL;
				return;
			}
		}
	}
	else
		if (!m_control.isNetWork) 
			if (m_control.fastInsertEdge) // if fast insert => build with default value
			{
				CObjectEx& weight = CWrapperUtilities::buildWrapper(m_control.edgeType,m_control.defaultWeightOfEdge);
				pEdge = builder.buildWeightedEdge(from,to,weight);
				pEdgeView->setColor(m_control.edgeColor);
			}
			else // show a dialog for user
			{
				CNewEdgeDlg dlg(NULL);
				dlg.m_color = m_control.edgeColor;
				dlg.m_bWeighted = TRUE;
				dlg.m_bNetworkEdge = FALSE;
				dlg.m_strWeight = m_control.defaultWeightOfEdge;
				if(dlg.DoModal() == IDOK){
					pEdgeView->setColor(dlg.m_color);
					pEdgeView->setName(dlg.m_strName);
					CObjectEx& weight = CWrapperUtilities::buildWrapper(m_control.edgeType,dlg.m_strWeight);
					pEdge = builder.buildWeightedEdge(from,to,weight);
				}
				else
				{
					delete pEdgeView;
					pEdgeView = NULL;
					return;
				}
			}
			else // is network
			{
				if (m_control.fastInsertEdge) // if fast insert => build with default value
				{
					CObjectEx& weight = CWrapperUtilities::buildWrapper(m_control.edgeType,m_control.defaultWeightOfEdge);
					CObjectEx& capacity = CWrapperUtilities::buildWrapper(m_control.edgeType,m_control.defaultCapacity);
					pEdge = builder.buildNetworkEdge(from,to,weight,capacity);
				}
				else // show a dialog for user
				{
					CNewEdgeDlg dlg(NULL);
					dlg.m_color = m_control.edgeColor;
					dlg.m_bWeighted = TRUE;
					dlg.m_bNetworkEdge = TRUE;
					dlg.m_strWeight = m_control.defaultWeightOfEdge;
					if(dlg.DoModal() == IDOK){
						pEdgeView->setColor(dlg.m_color);
						pEdgeView->setName(dlg.m_strName);
						CObjectEx& weight = CWrapperUtilities::buildWrapper(m_control.edgeType,dlg.m_strWeight);
						CObjectEx& capacity = CWrapperUtilities::buildWrapper(m_control.edgeType,dlg.m_strCapacity);
						pEdge = builder.buildNetworkEdge(from,to,weight,capacity);
					}
					else
					{
						delete pEdgeView;
						pEdgeView = NULL;
						return;
					}
				}
			}
			pModel->addEdge(*pEdge);
			pEdgeView->attach(pEdge);
			m_pGraphView->addEdgeView(pEdgeView);
}

void CGraphController::removeSelected()
{
	// When removing ==> Always remove all views of a model before removing it
	// to avoid displaying view without model
	if (!m_pSelected) return;
	CAbstractGraph* pModel = m_pGraphView->getModel();
	if (m_pSelected->typeId() == EDGEVIEWID) // remove edge
	{
		CEdgeView* pEV = (CEdgeView*)m_pSelected;
		NUMBER from = pEV->getFirstEnd()->getModel();
		NUMBER to = pEV->getSecondEnd()->getModel();
		m_pGraphView->removeEdgeView(from,to);
		pModel->removeEdge(from,to);
	}
	else // remove vertex
	{
		CVertexView* pVV = (CVertexView*)m_pSelected;
		NUMBER vertex = pVV->getModel();
		m_pGraphView->removeVertexView(vertex);
		pModel->removeVertex(vertex);
	}
	m_pSelected = NULL; // After being removed => set to NULL
}

void CGraphController::OnDepthFirstTraversal(BOOL preorder)
{
	CVertexView*pVertexView = (CVertexView*)m_pSelected;
	CAbstractGraph*pModel = m_pGraphView->getModel();
	NUMBER start = 0;
	CGraphView*pGraphView = copyGraphView(*pModel,-1);
	CInsertingVisitor insertingVisitor(pGraphView);
	CPrePostVisitor* pVisitor;
	if (preorder) 
		pVisitor = new CPreOrder(insertingVisitor);
	else pVisitor = new CPostOrder(insertingVisitor);
	CGraphUtilities gu;
	// execute algorithm and count time
	DWORD startTime = GetTickCount();
	if (!m_pSelected || m_pSelected->typeId() != VERTEXVIEWID)
		gu.depthFirstTraversal(*pModel,*pVisitor);	
	else
	{
		start = pVertexView->getModel();
		gu.depthFirstTraversal(*pModel,*pVisitor,start);
	}
	// gu.depthFirstTraversalEx(*pModel,prepost,start);
	// show time
	DWORD runningTime = GetTickCount() - startTime;
	CString strOut;
	strOut.Format("Depth first traversal start from vertex %d complete after %d miliseconds",start,runningTime);
	out(strOut);
	delete pVisitor;
	// show animation
	CIterator& iterator = insertingVisitor.getGraphics();
	CAnimationDlg dlg(NULL,iterator);
	dlg.m_strCaption = "DEPTH FIRST TRAVERSAL";
	dlg.m_pGraphView = pGraphView;
	dlg.DoModal();
}

void CGraphController::OnBreadthFirstTraversal()
{
	CVertexView*pVertexView = (CVertexView*)m_pSelected;
	CAbstractGraph*pModel = m_pGraphView->getModel();
	NUMBER start = 0;
	CGraphView*pGraphView = copyGraphView(*pModel,-1);
	CInsertingVisitor insertingVisitor(pGraphView);
	CGraphUtilities gu;
	// execute algorithm and count time
	DWORD startTime = GetTickCount();
	if (!m_pSelected || m_pSelected->typeId() != VERTEXVIEWID)
		gu.breadthFirstTraversal(*pModel,insertingVisitor);	
	else
	{
		start = pVertexView->getModel();
		gu.breadthFirstTraversal(*pModel,insertingVisitor,start);
	}
	// show time
	DWORD runningTime = GetTickCount() - startTime;
	CString strOut;
	strOut.Format("Breadth first traversal start from vertex %d complete after %d miliseconds",start,runningTime);
	out(strOut);
	// show animation
	CIterator& iterator = insertingVisitor.getGraphics();
	CAnimationDlg dlg(NULL,iterator);
	dlg.m_strCaption = "BREADTH FIRST TRAVERSAL";
	dlg.m_pGraphView = pGraphView;
	dlg.DoModal();
}

void CGraphController::OnTopologicalOrderTraversal()
{
	CAbstractGraph*pModel = m_pGraphView->getModel();
	CGraphUtilities gu;
	// Topological Order Traversal can only apply for dag (directed acyclic graph)
	if(gu.isCyclic(*pModel))
	{
		AfxMessageBox("This graph is not a Directed Acyclic Graph");
		return;
	}
	CGraphView*pGraphView = copyGraphView(*pModel,-1);
	CInsertingVisitor insertingVisitor(pGraphView);
	// execute algorithm and count time
	DWORD startTime = GetTickCount();
	gu.topologicalOrderTraversal(((const CDirectedGraph&)*pModel),insertingVisitor);
	// show time
	DWORD runningTime = GetTickCount() - startTime;
	CString strOut;
	strOut.Format("Topological order traversal complete after %d miliseconds",runningTime);
	out(strOut);
	// show animation
	CIterator& iterator = insertingVisitor.getGraphics();
	CAnimationDlg dlg(NULL,iterator);
	dlg.m_strCaption = "TOPOLOGICAL ORDER TRAVERSAL";
	dlg.m_pGraphView = pGraphView;
	dlg.DoModal();
}

void CGraphController::out(CString &str) const
{
	str = ">> " + str + "\n";
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	pMain->m_wndOutputBar.append(str);
}


void CGraphController::doPrim()
{
	if (!m_pSelected || m_pSelected->typeId() != VERTEXVIEWID)
	{
		AfxMessageBox("Select a vertex to start");
		return;
	}
	CAbstractGraph* pModel = m_pGraphView->getModel();
	CGraphUtilities gu;
	if (pModel->isDirected() 
		|| !gu.isConnected(*pModel)) 
	{
		AfxMessageBox("Graph to be applied Prim's algorithm has to be undirected,edge-weighted, connected");
		return;
	}
	// if (!containPositiveWeightedEdge(pModel)) return;
	CAlgorithms* pAl = CWrapperUtilities::buildAlgorithmImpl(m_control.edgeType);
	NUMBER start = ((CVertexView*)m_pSelected)->getModel();
	// run algorithm and count timer
	DWORD startTime = GetTickCount();
	CAbstractGraph* pResult = pAl->doPrim((const CUndirectedGraph&)*pModel,start);
	// show time
	DWORD runningTime = GetTickCount() - startTime;
	CString strOut;
	strOut.Format("Run Prim's algorithm on this graph. Complete after %d miliseconds",runningTime);
	out(strOut);
	delete pAl;
	CGraphView* pGraphView = copyGraphView(*pResult,start);
	COutputDlg dlg(NULL,pGraphView);
	dlg.m_strCaption = "PRIM's algorithm : Find minimum-cost spanning tree";
	dlg.DoModal();
}

CGraphView* CGraphController::copyGraphView(const CAbstractGraph &model,INT selected) const
{
	CGraphView* pGraphView = new CGraphView(model.numberOfVertices());
	CGraphViewEx* pOldView = (CGraphViewEx*)m_pGraphView;
	// create vertex views
	CIterator& vertexIter = model.getVertices();
	while (!vertexIter.isDone())
	{
		CVertex& vertex = (CVertex&)vertexIter.currentItem();
		CVertexView& vertexView = (CVertexView&)pOldView->vertexViews[vertex]->clone();
		vertexView.attach(&vertex);
		pGraphView->addVertexView(&vertexView);
		vertexIter.moveNext();
	}
	delete &vertexIter;
	// create edge views
	CGraphViewEx* pTmp = (CGraphViewEx*)pGraphView;
	if (selected > 0) pTmp->vertexViews[selected]->setColor(RGB(255,255,0));
	CIterator& edgeIter = model.getEdges();
	for (; !edgeIter.isDone(); edgeIter.moveNext())
	{
		CEdge& edge = (CEdge&)edgeIter.currentItem();
		NUMBER	from = edge.firstEndPoint(),
			to = edge.secondEndPoint();
		CEdgeView* pE = pOldView->edgeViews[from][to];
		CEdgeView* pNew = NULL;
		if(!pE)
		{
			if (model.isDirected())
			{
				pE = pOldView->edgeViews[to][from];
				if (pE)
				{
					pNew = &((CEdgeView&)pE->clone());
					pNew->reverse();
				} else continue;
			}
			else continue;
		}
		if (!pE) continue;
		if (!pNew) pNew = &((CEdgeView&)pE->clone());
		pNew->attach(&edge);
		pNew->setFirstEnd(pTmp->vertexViews[from]);
		pNew->setSecondEnd(pTmp->vertexViews[to]);
		pGraphView->addEdgeView(pNew);
	}
	delete &edgeIter;
	pGraphView->attach(const_cast<CAbstractGraph*>(&model));
	return pGraphView;
}

CGraphView* CGraphController::buildNewGraphView(const CAbstractGraph &model, INT selected) const
{
	CGraphView* pGraphView = new CGraphView(model.numberOfVertices());
	CGraphViewEx* pOldView = (CGraphViewEx*)m_pGraphView;
	// copy vertex views
	CIterator& vertexIter = model.getVertices();
	while (!vertexIter.isDone())
	{
		CVertex& vertex = (CVertex&)vertexIter.currentItem();
		CVertexView& vertexView = (CVertexView&)pOldView->vertexViews[vertex]->clone();
		vertexView.attach(&vertex);
		pGraphView->addVertexView(&vertexView);
		vertexIter.moveNext();
	}
	delete &vertexIter;
	// create edge views
	CGraphViewEx* pTmp = (CGraphViewEx*)pGraphView;
	if (selected > 0) pTmp->vertexViews[selected]->setColor(RGB(255,255,0));
	CIterator& edgeIter = model.getEdges();
	for (; !edgeIter.isDone(); edgeIter.moveNext())
	{
		CEdge& edge = (CEdge&)edgeIter.currentItem();
		CVertexView* pFirstEnd = pTmp->vertexViews[edge.firstEndPoint()],
			*pSecondEnd = pTmp->vertexViews[edge.secondEndPoint()];
		CEdgeView*pEV = new CEdgeView;
		pEV->setFirstEnd(pFirstEnd);
		pEV->setSecondEnd(pSecondEnd);
		pEV->attach(&edge);
		if (edge.isLoop()) pEV->reposition(DO_DRAW_NEW);
		else pEV->reposition(DO_UPDATE);
		pGraphView->addEdgeView(pEV);
	}
	delete &edgeIter;
	pGraphView->attach(const_cast<CAbstractGraph*>(&model));
	return pGraphView;
}

void CGraphController::doDijkstra()
{
	if (!m_pSelected || m_pSelected->typeId() != VERTEXVIEWID)
	{
		AfxMessageBox("Select a vertex to start");
		return;
	}
	CAbstractGraph* pModel = m_pGraphView->getModel();
	// if (!containPositiveWeightedEdge(pModel)) return;	
	CAlgorithms* pAl = CWrapperUtilities::buildAlgorithmImpl(m_control.edgeType);
	NUMBER start = ((CVertexView*)m_pSelected)->getModel();
	DWORD startTime = GetTickCount();
	CAbstractGraph* pResult = pAl->doDijkstra((const CDirectedGraph&)*pModel,start);
	// show time
	DWORD runningTime = GetTickCount() - startTime;
	CString strOut;
	strOut.Format("Run Dijkstra's algorithm on this graph with source : vertex %d. Complete after %d miliseconds",start,runningTime);
	out(strOut);
	delete pAl;
	CGraphView* pGraphView = copyGraphView(*pResult,start);
	COutputDlg dlg(NULL,pGraphView);
	dlg.m_strCaption = "DIJKSTRA's algorithm : Greedy algorithm for single source shortest path problem";	
	dlg.DoModal();
}

BOOL CGraphController::containPositiveWeightedEdge(CAbstractGraph *pGraph) const
{
	CIterator& edgeIter = pGraph->getEdges();
	// Make sure graph contains weighted edge
	CWeightedEdge& edge = (CWeightedEdge&)edgeIter.currentItem();
	// if (edge.typeId() != WEIGHTEDEDGEID)
	if (edge.typeId() == EDGEID)
	{
		AfxMessageBox("This graph doesn't contain weighted edge");
		delete &edgeIter;
		return FALSE;
	}
	// Make sure edges don't have negative weight
	while (!edgeIter.isDone()) 
	{
		CWeightedEdge& item = (CWeightedEdge&)edgeIter.currentItem();
		if (edge.getWeight() < CWrapper<int>(0)) 
		{
			AfxMessageBox("This graph contain negative weighted edge");
			delete &edgeIter;
			return FALSE;
		}
		edgeIter.moveNext();
	}
	delete &edgeIter;
	return TRUE;
}

void CGraphController::doFloyd()
{
	CAbstractGraph* pModel = m_pGraphView->getModel();
	// if (!containPositiveWeightedEdge(pModel)) return;
	CAlgorithms* pAl = CWrapperUtilities::buildAlgorithmImpl(m_control.edgeType);
	DWORD startTime = GetTickCount();
	CAbstractGraph* pResult = pAl->doFloyd((const CDirectedGraph&)*pModel);
	// show time
	DWORD runningTime = GetTickCount() - startTime;
	CString strOut;
	strOut.Format("Run Floyd's algorithm on this graph. Complete after %d miliseconds",runningTime);
	out(strOut);
	delete pAl;
	CGraphView* pGraphView = buildNewGraphView(*pResult,-1);
	COutputDlg dlg(NULL,pGraphView);
	dlg.m_strCaption = "FLOYD's algorithm : All-pairs shortest-path using Dynamic programing";
	dlg.DoModal();
}

void CGraphController::Serialize(CArchive &ar)
{
	if (ar.IsStoring())
	{
		ar.WriteString("graph [\n");
		// write graph attributes
		CAbstractGraph*pModel = m_pGraphView->getModel();
		int directed = pModel->isDirected() ? 1 : 0;
		int isNetwork = m_control.isNetWork ? 1 : 0;
		CString str;
		str.Format("directed %d\nmaxSize %d\nedgeStorage %d\ngraphics 1\nvertexType %d\nedgeType %d\nisNetwork %d\n",
			directed,m_control.maxSize,m_control.edgeStorage,m_control.vertexType,m_control.edgeType,m_control.isNetWork);
		ar.WriteString(str);
		m_pGraphView->Serialize(ar);
		ar.WriteString("]");
	}
}

void CGraphController::doFleury()
{
	CVertexView*pVertexView = (CVertexView*)m_pSelected;
	CAbstractGraph*pModel = m_pGraphView->getModel();
	CGraphView* pGraphView = copyGraphView(*pModel,-1);
	CInsertingVisitor insertingVisitor(pGraphView);
	CGraphUtilities gu;
	// execute algorithm and count time
	DWORD startTime = GetTickCount();
	BOOL success = gu.eulerianTraversal(*pModel,insertingVisitor);
	// show time
	DWORD runningTime = GetTickCount() - startTime;
	CString strOut;
	strOut.Format("Find Eulerian path. complete after %d miliseconds",runningTime);
	out(strOut);
	// show animation
	if (!success) 
	{
		delete pGraphView;
		delete &(insertingVisitor.getGraphics());
		return;
	}
	CIterator& iterator = insertingVisitor.getGraphics();
	CAnimationDlg dlg(NULL,iterator);
	dlg.m_strCaption = "EULERIAN TRAVERSAL";
	dlg.m_pGraphView = pGraphView;
	dlg.m_mode = CAnimationDlg::TRACK_EDGE;
	dlg.DoModal();
}

void CGraphController::OnSearchCutVertices(CThesisView*pView)
{
	COLORREF markColor = RGB(255,0,0);
	CAbstractGraph*pModel = m_pGraphView->getModel();
	CGraphViewEx* pViewEx = (CGraphViewEx*)m_pGraphView;
	CGraphUtilities gu;
	// execute algorithm and count time
	DWORD startTime = GetTickCount();
	CIterator& separationVertices = gu.getArticulationPoints(*pModel);
	// show time
	DWORD runningTime = GetTickCount() - startTime;
	CString strOut;
	strOut.Format("Find Articulation points. complete after %d miliseconds",runningTime);
	out(strOut);
	for(; !separationVertices.isDone(); separationVertices.moveNext()) 
	{
		NUMBER vertex = (CVertex&)separationVertices.currentItem();
		pViewEx->vertexViews[vertex]->setColor(markColor);
	}
	delete &separationVertices;
	pView->Invalidate(FALSE);
}

CGraphController::CColoringVisitor::CColoringVisitor(CGraphView*pGraphView)
{
	m_pView = pGraphView;
	color[0] = RGB(255,0,0);
	color[1] = RGB(0,255,0);
	color[2] = RGB(0,0,255);
	color[3] = RGB(255,255,0);
	color[4] = RGB(255,0,255);
}

void CGraphController::CColoringVisitor::visit(CObjectEx&object)
{
	CGraphViewEx*pView = (CGraphViewEx*)m_pView;
	CColoredVertexPtr& coloredvertex = (CColoredVertexPtr&)object;
	NUMBER vertex = coloredvertex.datum->vertex;
	UINT colorIndex = coloredvertex.datum->color;
	pView->vertexViews[vertex]->setColor(color[colorIndex]);
}

void CGraphController::doWelchPowell(CThesisView *pView)
{
	CColoringVisitor visitor(m_pGraphView);
	CAbstractGraph*pModel = m_pGraphView->getModel();
	CGraphUtilities gu;
	UINT numberOfColors = gu.colorGraph(*pModel,visitor);
	CString str;
	str.Format("Color graph. Number of color is used : %d",numberOfColors);
	out(str);
	pView->Invalidate(FALSE);
}

void CGraphController::doKruskal()
{
	CAbstractGraph* pModel = m_pGraphView->getModel();
	if (pModel->isDirected())
	{
		AfxMessageBox("Can't apply on directed graph");
		return;
	}
	// if (!containPositiveWeightedEdge(pModel)) return;
	CAlgorithms* pAl = CWrapperUtilities::buildAlgorithmImpl(m_control.edgeType);
	// run algorithm and count timer
	DWORD startTime = GetTickCount();
	CAbstractGraph* pResult = pAl->doKruskal((const CUndirectedGraph&)*pModel);
	// show time
	DWORD runningTime = GetTickCount() - startTime;
	CString strOut;
	strOut.Format("Run Kruskal's algorithm on this graph. Complete after %d miliseconds",runningTime);
	out(strOut);
	delete pAl;
	CGraphView* pGraphView = copyGraphView(*pResult,-1);
	COutputDlg dlg(NULL,pGraphView);
	dlg.m_strCaption = "KRUSKAL's algorithm : Find minimum-cost spanning forest";
	dlg.DoModal();
}

void CGraphController::doBellmanFord()
{
	if (!m_pSelected || m_pSelected->typeId() != VERTEXVIEWID)
	{
		AfxMessageBox("Select a vertex to start");
		return;
	}
	CAbstractGraph* pModel = m_pGraphView->getModel();
	CAlgorithms* pAl = CWrapperUtilities::buildAlgorithmImpl(m_control.edgeType);
	NUMBER start = ((CVertexView*)m_pSelected)->getModel();
	DWORD startTime = GetTickCount();
	CAbstractGraph* pResult = pAl->doBellmanFord((const CDirectedGraph&)*pModel,start);
	// show time
	DWORD runningTime = GetTickCount() - startTime;
	CString strOut;
	strOut.Format("Run Bellman-Ford's algorithm on this graph with source : vertex %d. Complete after %d miliseconds",start,runningTime);
	out(strOut);
	delete pAl;
	if (!pResult)
	{
		AfxMessageBox("This graph contain negative weight cycle");
		return;
	}
	CGraphView* pGraphView = copyGraphView(*pResult,start);
	COutputDlg dlg(NULL,pGraphView);
	dlg.m_strCaption = "BELLMAN-FORD's algorithm : Greedy algorithm for single source shortest path problem";	
	dlg.DoModal();
}

void CGraphController::OnSearchCycles()
{
	CAbstractGraph*pModel = m_pGraphView->getModel();
	CGraphUtilities gu;
	/*
	if (pModel->isDirected()) 
	{
		AfxMessageBox("This algorithm apply for undirected graph only");
		return;
	}
	//*/
	if (!gu.isCyclic(*pModel)) 
	{
		AfxMessageBox("This graph contains no cycle");
		return;
	}
	CIterator& iter = gu.getCycles(*pModel);
	CGraphView* pView = copyGraphView(*pModel,-1);
	CIterator& graphicsIter = getGraphics(iter,pView,FALSE);
	CAnimationDlgEx dlg(NULL,graphicsIter);
	dlg.m_pGraphView = pView;
	dlg.m_strCaption = "FIND CYCLES";
	dlg.DoModal();
}


void CGraphController::OnSearchBridgeEdges()
{
	CAbstractGraph*pModel = m_pGraphView->getModel();
	CGraphUtilities gu;
	if (pModel->isDirected()) 
	{
		AfxMessageBox("This algorithm apply for undirected graph only");
		return;
	}
	CIterator& iter = gu.getBridgeEdges(*pModel);
	if (iter.isDone())
	{
		AfxMessageBox("This graph contains no bridge edge");
		delete &iter;
		return;
	}
	CGraphView* pView = copyGraphView(*pModel,-1);
	CIterator& graphicsIter = getGraphics(iter,pView,FALSE);
	CAnimationDlgEx dlg(NULL,graphicsIter);
	dlg.m_pGraphView = pView;
	dlg.m_strCaption = "FIND BRIDGE EDGES";
	dlg.DoModal();
}

void CGraphController::OnSearchConnectedComponents()
{
	CAbstractGraph*pModel = m_pGraphView->getModel();
	CGraphUtilities gu;
	CIterator& iter = gu.getConnectedComponents(*pModel);
	CGraphView* pView = copyGraphView(*pModel,-1);
	CIterator& graphicsIter = getGraphics(iter,pView);
	CAnimationDlgEx dlg(NULL,graphicsIter);
	dlg.m_pGraphView = pView;
	dlg.m_strCaption = "FIND CONNECTED COMPONENTS";
	dlg.DoModal();
}

CIterator&CGraphController::getGraphics(CIterator&iter,CGraphView*pView,BOOL bVertex)
{
	CLinkedList<CListIterator*>&result = *new CLinkedList<CListIterator*>;
	CGraphViewEx*pEx = (CGraphViewEx*)pView;
	if (bVertex)
	{
		while (!iter.isDone()) 
		{
			CListIterator& current = (CListIterator&)iter.currentItem();
			CLinkedList<CObjectEx*>& list = *new CLinkedList<CObjectEx*>;
			while (!current.isDone())
			{
				UINT vertex = (CVertex&)current.currentItem();
				list.append(pEx->vertexViews[vertex]);
				current.moveNext();
			}
			delete&current;
			result.append(new CListIterator(list));
			iter.moveNext();
		}
		delete&iter;
		return *new CListIterator((CLinkedList<CObjectEx*>&)result);
	}
	// Reach here ==> get edge's graphics
	while (!iter.isDone()) 
	{
		CListIterator& current = (CListIterator&)iter.currentItem();
		CLinkedList<CObjectEx*>& list = *new CLinkedList<CObjectEx*>;
		CArrayEx<BOOL> unAppended(pEx->m_pModel->numberOfVertices()); // default = true
		while (!current.isDone())
		{
			CEdge& edge = (CEdge&)current.currentItem();
			UINT source = (NUMBER)edge.firstEndPoint(),
				 target = (NUMBER)edge.secondEndPoint();
			CEdgeView*pE = pEx->edgeViews[source][target];
			if (!pE) pE = pEx->edgeViews[target][source];
			list.append(pE);
			if (unAppended[source]) 
			{
				list.append(pEx->vertexViews[source]);
				unAppended[source] = FALSE;
			}
			if (unAppended[target]) 
			{
				list.append(pEx->vertexViews[target]);
				unAppended[target] = FALSE;
			}
			current.moveNext();
		}
		delete&current;
		result.append(new CListIterator(list));
		iter.moveNext();
	}
	delete&iter;
	return *new CListIterator((CLinkedList<CObjectEx*>&)result);
}

void CGraphController::OnSearchBiconnectedComponents()
{
	CAbstractGraph*pModel = m_pGraphView->getModel();
	if (pModel->isDirected()) 
	{
		AfxMessageBox("This algorithm apply to undirected graph only");
		return;
	}
	CGraphUtilities gu;
	CIterator& iter = gu.getBiconnectedComponents(*pModel);
	if (iter.isDone())
	{
		AfxMessageBox("This graph has no biconnected components because all edges are bridges");
		delete &iter;
		return;
	}
	CGraphView* pView = copyGraphView(*pModel,-1);
	CIterator& graphicsIter = getGraphics(iter,pView,FALSE);
	CAnimationDlgEx dlg(NULL,graphicsIter);
	dlg.m_pGraphView = pView;
	dlg.m_strCaption = "FIND BICONNECTED COMPONENTS";
	dlg.DoModal();
}

BOOL CGraphController::isEmpty()const
{
	CAbstractGraph*pModel = m_pGraphView->getModel();
	return pModel->isEmpty();
}

BOOL CGraphController::isFull()
{
	CAbstractGraph*pModel = m_pGraphView->getModel();
	if (pModel->isFull())
	{
		if(AfxMessageBox("Graph is full. Do you want to enlarge it ",MB_YESNO)==IDYES)
			return OnResizeGraph();
		return TRUE; // graph is full but user don't want to enlarge it.
	}
	return FALSE;
}

void CGraphController::OnGenerateCompleteGraph(CThesisView*pView)
{
	// remember to write more => show a dialog to get user option
	// this code for unweighted graph only
	CGenerateDlg dlg;
	dlg.m_bDirected = m_pGraphView->getModel()->isDirected();
	dlg.m_lpControlStruct = &m_control;
	if (dlg.DoModal() == IDOK) 
	{
		CGraphGenerator generator(*m_pGraphView);
		generator.setUpperBounds(	dlg.m_generateStruct.vertexWeightUpperBound,
									dlg.m_generateStruct.edgeWeightUpperBound,
									dlg.m_generateStruct.capacityUpperBound);
		generator.generateCompleteGraph(dlg.m_generateStruct.numberOfVertices,
										dlg.m_generateStruct.vertexType,
										dlg.m_generateStruct.edgeType,
										// dlg.m_generateStruct.networkEdge);
										FALSE);
		CRect rect;
		pView->GetClientRect(&rect);
		CGraphLayout::doEllipse(*m_pGraphView,rect);
		pView->Invalidate(FALSE);
		m_control.vertexType = dlg.m_generateStruct.vertexType;
		m_control.edgeType = dlg.m_generateStruct.edgeType;
		pView->setModifiedFlag();
	}
}

void CGraphController::doWarshall()
{
	CAbstractGraph*pModel = m_pGraphView->getModel();
	CGraphUtilities gu;
	if (!pModel->isDirected()) 
	{
		AfxMessageBox("Warshall's algorithm appy to directed graph only");
		return;
	}
	CAbstractGraph*pResult = gu.getTransitiveClosure(*pModel);
	CGraphView*pView = buildNewGraphView(*pResult,-1);
	COutputDlg dlg(NULL,pView);
	dlg.m_strCaption = "WARSHALL'S ALGORITHM : TRANSITIVE CLOSURE";
	dlg.DoModal();
}

void CGraphController::OnSearchCriticalPath()
{
	CAbstractGraph* pModel = m_pGraphView->getModel();
	CGraphUtilities gu;
	if(gu.isCyclic(*pModel))
	{
		AfxMessageBox("This graph is not a Directed Acyclic Graph");
		return;
	}
	if (!containPositiveWeightedEdge(pModel)) return;	
	CAlgorithms* pAl = CWrapperUtilities::buildAlgorithmImpl(m_control.edgeType);
	DWORD startTime = GetTickCount();
	CAbstractGraph* pResult = pAl->doCriticalPathAnalysis((const CDirectedGraph&)*pModel);
	// show time
	DWORD runningTime = GetTickCount() - startTime;
	CString strOut;
	strOut.Format("Search critical path. Complete after %d miliseconds",runningTime);
	out(strOut);
	delete pAl;
	CGraphView* pGraphView = copyGraphView(*pResult,-1);
	COutputDlg dlg(NULL,pGraphView);
	dlg.m_strCaption = "CRITICAL PATH'S ANALYSIS";	
	dlg.DoModal();
}

void CGraphController::doDAGsShortestPath()
{
	if (!m_pSelected || m_pSelected->typeId() != VERTEXVIEWID)
	{
		AfxMessageBox("Select a vertex to start");
		return;
	}
	CAbstractGraph*pModel = m_pGraphView->getModel();
	CGraphUtilities gu;
	// Topological Order Traversal can only apply for dag (directed acyclic graph)
	if(gu.isCyclic(*pModel))
	{
		AfxMessageBox("This graph is not a Directed Acyclic Graph");
		return;
	}
	// if (!containPositiveWeightedEdge(pModel)) return;	
	CAlgorithms* pAl = CWrapperUtilities::buildAlgorithmImpl(m_control.edgeType);
	NUMBER start = ((CVertexView*)m_pSelected)->getModel();	
	DWORD startTime = GetTickCount();
	CAbstractGraph* pResult = pAl->doDAGsShortestPath((const CDirectedGraph&)*pModel,start);
	// show time
	DWORD runningTime = GetTickCount() - startTime;
	CString strOut;
	strOut.Format("Run Single Source Shortest Pahs in DAGs's algorithm on this graph with source. Complete after %d miliseconds",runningTime);
	out(strOut);
	delete pAl;
	CGraphView* pGraphView = copyGraphView(*pResult,start);
	COutputDlg dlg(NULL,pGraphView);
	dlg.m_strCaption = "SINGLE-SOURCE SHORTEST PATHS IN DAGS";	
	dlg.DoModal();
}

void CGraphController::OnCheckNetwork(CThesisView*pView)
{
	CAbstractGraph*pModel = m_pGraphView->getModel();
	CAlgorithms* pAl = CWrapperUtilities::buildAlgorithmImpl(m_control.edgeType);
	DWORD startTime = GetTickCount();
	UINT source,sink;
	INT ret = pAl->checkValidNetwork((CDirectedGraph&)*pModel,source,sink);
	// show time
	DWORD runningTime = GetTickCount() - startTime;
	CString strOut;
	strOut.Format("Validate network. Complete after %d miliseconds",runningTime);
	out(strOut);
	delete pAl;
	CGraphViewEx* pGV = (CGraphViewEx*)m_pGraphView;
	COLORREF sourceColor = RGB(255,0,0), sinkColor = RGB(0,0,255);
	if (ret == INVALID) return;
	CPoint pnt(MIN_RADIUS,MIN_RADIUS);
	if ((ret & REDUCE_SOURCE || ret & REDUCE_SINK)) m_control.maxSize += 2;
	if (ret & REDUCE_SOURCE)
	{
		CVertexView* pV = new CVertexView(pnt);
		pV->attach(&(pModel->selectVertex(source)));
		m_pGraphView->addVertexView(pV);
		CIterator& iter = pModel->emanatingEdges(source);
		for(; !iter.isDone(); iter.moveNext()) 
		{
			CEdge& e = (CEdge&)iter.currentItem();
			NUMBER subSource = e.secondEndPoint();
			CEdgeView* pE = new CEdgeView(pGV->vertexViews[source]);
			pE->setSecondEnd(pGV->vertexViews[subSource]);
			pE->attach(&e);
			pE->reposition(DO_UPDATE);
			m_pGraphView->addEdgeView(pE);
		}
		delete&iter;
	}
	if (ret & REDUCE_SINK)
	{
		CVertexView* pV = new CVertexView(pnt);
		pV->attach(&(pModel->selectVertex(sink)));
		m_pGraphView->addVertexView(pV);
		CIterator& iter = pModel->incidentEdges(sink);
		for(; !iter.isDone(); iter.moveNext()) 
		{
			CEdge& e = (CEdge&)iter.currentItem();
			NUMBER subSink = e.firstEndPoint();
			CEdgeView* pE = new CEdgeView(pGV->vertexViews[subSink]);
			pE->setSecondEnd(pGV->vertexViews[sink]);
			pE->attach(&e);
			pE->reposition(DO_UPDATE);
			m_pGraphView->addEdgeView(pE);			
		}
		delete&iter;
	}
	pGV->vertexViews[source]->setColor(sourceColor);
	pGV->vertexViews[source]->setName("source");
	pGV->vertexViews[sink]->setColor(sinkColor);
	pGV->vertexViews[sink]->setName("sink");
	pView->Invalidate(FALSE);
}

void CGraphController::doFordFulkerson()
{
	CAbstractGraph* pModel = m_pGraphView->getModel();
	CGraphUtilities gu;
	CAbstractGraph& graph = gu.copyGraph(*pModel);
	CAlgorithms* pAl = CWrapperUtilities::buildAlgorithmImpl(m_control.edgeType);
	UINT source,sink;
	if(pAl->checkValidNetwork((CDirectedGraph&)graph,source,sink) != VALID)
	{
		AfxMessageBox("This is not a valid single source-sink network");
		delete pAl;
		delete &graph;
		return;
	}
	DWORD startTime = GetTickCount();
	CIterator& iter = pAl->doEdmondsKarp((CDirectedGraph&)graph,source,sink);
	// show time
	DWORD runningTime = GetTickCount() - startTime;
	CString strOut;
	strOut.Format("Run Edmonds-Karp's algorithm . Complete after %d miliseconds",runningTime);
	out(strOut);
	delete pAl;
	CGraphView* pGraphView = copyGraphView(graph,-1);
	COLORREF markColor = RGB(0,255,255);
	while (!iter.isDone())
	{
		NUMBER vertex = (CVertex&)iter.currentItem();
		((CGraphViewEx*)pGraphView)->vertexViews[vertex]->setColor(markColor);
		iter.moveNext();
	}
	delete&iter;
	COutputDlg dlg(NULL,pGraphView);
	dlg.m_strCaption = "EDMONDS-KARP'S ALGORITHM : FIND MAX-FLOW MIN-CUT";	
	dlg.DoModal();
}

void CGraphController::OnBuildResidualNetwork()
{
	CAbstractGraph* pModel = m_pGraphView->getModel();
	CAlgorithms* pAl = CWrapperUtilities::buildAlgorithmImpl(m_control.edgeType);
	DWORD startTime = GetTickCount();
	CDirectedGraph* pResult = pAl->buildResidualNetwork((const CDirectedGraph&)*pModel);
	// show time
	DWORD runningTime = GetTickCount() - startTime;
	CString strOut;
	strOut.Format("Construct residual network. Complete after %d miliseconds",runningTime);
	out(strOut);
	delete pAl;
	CGraphView* pGraphView = copyGraphView(*pResult,-1);
	COutputDlg dlg(NULL,pGraphView);
	dlg.m_strCaption = "RESIDUAL NETWORK";	
	dlg.DoModal();
}

void CGraphController::OnSearchVertexCover()
{
	COLORREF markColor = RGB(255,0,0);
	CAbstractGraph*pModel = m_pGraphView->getModel();
	CGraphViewEx* pViewEx = (CGraphViewEx*)m_pGraphView;
	CGraphUtilities gu;
	// execute algorithm and count time
	DWORD startTime = GetTickCount();
	CIterator& vertexCover = gu.getVertexCover(*pModel);
	// show time
	DWORD runningTime = GetTickCount() - startTime;
	CString strOut;
	strOut.Format("Find Vertex Cover. complete after %d miliseconds",runningTime);
	out(strOut);
	for(; !vertexCover.isDone(); vertexCover.moveNext()) 
	{
		NUMBER vertex = (CVertex&)vertexCover.currentItem();
		pViewEx->vertexViews[vertex]->setColor(markColor);
	}
	delete &vertexCover;
}

BOOL CGraphController::OnResizeGraph()
{
	CResizeGraphDlg dlg;
	dlg.m_currentSize = m_control.maxSize;
	if (dlg.DoModal() == IDOK)
	{
		m_control.maxSize = dlg.m_newSize;
		m_pGraphView->resize(m_control.maxSize);
		return FALSE;
	}
	return TRUE; // user abort enlarging procedure
}

void CGraphController::OnGenerateRandomgraph(CThesisView *pView)
{
	// remember to write more => show a dialog to get user option
	// this code for unweighted graph only
	CGenerateDlg dlg;
	dlg.m_lpControlStruct = &m_control;
	dlg.m_bDirected = m_pGraphView->getModel()->isDirected();
	if (dlg.DoModal() == IDOK) 
	{
		CGraphGenerator generator(*m_pGraphView);
		generator.setUpperBounds(	dlg.m_generateStruct.vertexWeightUpperBound,
			dlg.m_generateStruct.edgeWeightUpperBound,
			dlg.m_generateStruct.capacityUpperBound);
		generator.generateRandomGraph(	dlg.m_generateStruct.numberOfVertices,
										dlg.m_generateStruct.numberOfEdges,
										dlg.m_generateStruct.vertexType,
										dlg.m_generateStruct.edgeType,
									//	dlg.m_generateStruct.networkEdge);
										FALSE);
		CRect rect;
		pView->GetClientRect(&rect);
		CGraphLayout::doEllipse(*m_pGraphView,rect);
		pView->Invalidate(FALSE);
		m_control.vertexType = dlg.m_generateStruct.vertexType;
		m_control.edgeType = dlg.m_generateStruct.edgeType;
		pView->setModifiedFlag();
	}
}

void CGraphController::displayProperties()
{
	if (m_pTmpSel)
	{
		m_pTmpSel->displayProperties(&m_control);
		return;
	}
	if (m_pSelected)
	{
		m_pSelected->displayProperties(&m_control);
		return;
	}
	CAbstractGraph* pModel = m_pGraphView->getModel();
	CPropertiesGDlg dlg(NULL,&m_control);
	dlg.m_bDirected = pModel->isDirected();
	dlg.m_uNumberOfVertices = pModel->numberOfVertices();
	dlg.m_uNumberOfEdges = pModel->numberOfEdges();
	dlg.DoModal();
}

void CGraphController::OnLayoutEllipse(CThesisView*pView)
{
	CRect rect;
	pView->GetClientRect(&rect);
	CGraphLayout::doEllipse(*m_pGraphView,rect);
	pView->setModifiedFlag();
	pView->Invalidate(FALSE);
}

void CGraphController::OnDemoFordFulkerson()
{
	CAbstractGraph* pModel = m_pGraphView->getModel();
	CGraphUtilities gu;
	CAbstractGraph& graph = gu.copyGraph(*pModel);
	CAlgorithms* pAl = CWrapperUtilities::buildAlgorithmImpl(m_control.edgeType);
	UINT source,sink;
	if(pAl->checkValidNetwork((CDirectedGraph&)graph,source,sink) != VALID)
	{
		AfxMessageBox("This is not a valid single source-sink network");
		delete pAl;
		delete &graph;
		return;
	}
	delete pAl;
	CGraphView* pGraphView = copyGraphView(graph,-1);
	CEKAnimationDlg dlg(NULL,pGraphView);
	dlg.m_strCaption = "EDMONDS-KARP's ALGORITHM : MAX-FLOW MIN-CUT";
	dlg.setParas(source,sink);
	dlg.DoModal();
}

void CGraphController::OnSearchMaximumBipartiteMatching()
{
	CAbstractGraph*pModel = m_pGraphView->getModel();
	CGraphUtilities gu;
	if (pModel->isDirected()) 
	{
		AfxMessageBox("This algorithm apply for undirected graph only");
		return;
	}
	DWORD startTime = GetTickCount();
	CIterator& iter = gu.getMaximumMatching(*pModel);
	DWORD runningTime = GetTickCount() - startTime;
	CString strOut;
	strOut.Format("Find Maximum Bipartite Matching on this graph. Complete after %d miliseconds",runningTime);
	out(strOut);
	CGraphView* pView = copyGraphView(*pModel,-1);
	CIterator& graphicsIter = getGraphics(iter,pView,FALSE);
	CAnimationDlgEx dlg(NULL,graphicsIter);
	dlg.m_pGraphView = pView;
	dlg.m_strCaption = "MAXIMUM BIPARTITE MATCHING";
	dlg.DoModal();
}

void CGraphController::doJohnson()
{
	CAbstractGraph* pModel = m_pGraphView->getModel();
	// if (!containPositiveWeightedEdge(pModel)) return;
	CAlgorithms* pAl = CWrapperUtilities::buildAlgorithmImpl(m_control.edgeType);
	DWORD startTime = GetTickCount();
	CAbstractGraph* pResult = pAl->doJohnson((const CDirectedGraph&)*pModel);
	// show time
	DWORD runningTime = GetTickCount() - startTime;
	CString strOut;
	strOut.Format("Run Johnson's algorithm on this graph. Complete after %d miliseconds",runningTime);
	out(strOut);
	delete pAl;
	if (pResult)
	{
		CGraphView* pGraphView = buildNewGraphView(*pResult,-1);
		COutputDlg dlg(NULL,pGraphView);
		dlg.m_strCaption = "JOHNSON's algorithm : All-pairs shortest-path using Dynamic programing";
		dlg.DoModal();
	}
}

void CGraphController::OnSearchHamiltonPath()
{
	CAbstractGraph*pModel = m_pGraphView->getModel();
	CGraphUtilities gu;
	// execute algorithm and count time
	DWORD startTime = GetTickCount();
	CIterator& iter = gu.getHamiltonPath(*pModel,0,0);
	// show time
	DWORD runningTime = GetTickCount() - startTime;
	CString strOut;
	strOut.Format("Find Hamiltonian path complete after %d miliseconds",runningTime);
	out(strOut);
	// show animation
	if (iter.isDone())
	{
		delete &iter;
		AfxMessageBox("This graph has no Hamiltonian circuit");
		return;
	}
	CGraphView*pGraphView = copyGraphView(*pModel,-1);
	CInsertingVisitor insertingVisitor(pGraphView);
	for(; !iter.isDone(); iter.moveNext())
		insertingVisitor.visit(iter.currentItem());
	delete &iter;
	CIterator& iterator = insertingVisitor.getGraphics();
	CAnimationDlg dlg(NULL,iterator);
	dlg.m_strCaption = "TOPOLOGICAL ORDER TRAVERSAL";
	dlg.m_mode = CAnimationDlg::TRACK_EDGE;
	dlg.m_pGraphView = pGraphView;
	dlg.DoModal();
}

void CGraphController::OnDemoAstar()
{
	CSearchDlg searchDlg;
	searchDlg.m_uGoal = m_pGraphView->getModel()->numberOfVertices() - 1;
	if (searchDlg.DoModal() == IDOK)
	{
		CASAnimationDlg dlg(searchDlg.m_uStart,searchDlg.m_uGoal);
		dlg.m_pGraphView = m_pGraphView;
		dlg.m_strCaption = "A-STAR ALGORITHM";
		dlg.DoModal();
	}
}

void CGraphController::doAStar()
{
}
