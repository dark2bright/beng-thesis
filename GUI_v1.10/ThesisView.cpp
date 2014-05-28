// ThesisView.cpp : implementation of the CThesisView class
//

#include "stdafx.h"
#include "Thesis.h"

#include "ThesisDoc.h"
#include "ThesisView.h"
//////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThesisView

IMPLEMENT_DYNCREATE(CThesisView, CScrollView)

BEGIN_MESSAGE_MAP(CThesisView, CScrollView)
	//{{AFX_MSG_MAP(CThesisView)
	ON_COMMAND(ID_GRAPH_EDGE, OnGraphAddEdge)
	ON_COMMAND(ID_GRAPH_REMOVE, OnGraphRemove)
	ON_COMMAND(ID_GRAPH_SELECT, OnGraphSelect)
	ON_COMMAND(ID_GRAPH_VERTEX, OnGraphAddVertex)
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_SETCURSOR()
	ON_WM_CONTEXTMENU()
	ON_WM_MEASUREITEM()
	ON_WM_DRAWITEM()
	ON_COMMAND(ID_GRAPH_PROPERTIES, OnGraphProperties)
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_TOOLS_OPTIONS, OnToolsOptions)
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	ON_COMMAND(ID_UTILITIES_TOPO, OnTopologicalOrderTraversal)
	ON_COMMAND(ID_UTILITIES_BFT, OnBreadthFirstTraversal)
	ON_COMMAND(ID_ALGORITHM_PRIM, OnPrimAlgorithm)
	ON_COMMAND(ID_ALGORITHM_DIJKSTRA, OnDijkstraAlgorithm)
	ON_COMMAND(ID_ALGORITHM_FLOYD, OnFloydAlgorithm)
	ON_COMMAND(ID_ALGORITHM_KRUSKAL, OnKruskalAlgorithm)
	ON_COMMAND(ID_UTILITIES_EULER, OnEulerianCircuit)
	ON_COMMAND(ID_UTILITIES_CUT_VERTEX, OnSearchCutVertices)
	ON_COMMAND(ID_UTILITIES_COLOR, OnColorGraph)
	ON_COMMAND(ID_ALGORITHM_BELLMAN_FORD, OnBellmanFordAlgorithm)
	ON_COMMAND(ID_UTILITIES_CYCLE, OnSearchCycles)
	ON_COMMAND(ID_UTILITIES_BRIDGE_EDGE, OnSearchBridgeEdges)
	ON_COMMAND(ID_UTILITIES_CONNECTED_COMPONENT, OnSearchConnectedComponents)
	ON_COMMAND(ID_UTILITIES_BICONNECTED_COMPONENT, OnSearchBiconnectedComponents)
	ON_COMMAND(ID_GRAPH_GENERATE_COMPLETEGRAPH, OnGenerateCompleteGraph)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_GENERATE_COMPLETEGRAPH, OnUpdateGenerateCompleteGraph)
	ON_COMMAND(ID_UTILITIES_TRANSITIVE_CLOSURE, OnGetTransitiveClosure)
	ON_COMMAND(ID_ALGORITHM_CRITICAL_PATH, OnSearchCriticalPath)
	ON_COMMAND(ID_ALGORITHM_SSP_DAG, OnSspDagAlgorithm)
	ON_COMMAND(ID_NETWORK_CHECK, OnCheckNetwork)
	ON_COMMAND(ID_NETWORK_FORD_FULKERSON, OnFordFulkersonAlgorithm)
	ON_COMMAND(ID_NETWORK_RESIDUAL, OnBuildResidualNetwork)
	ON_COMMAND(ID_UTILITIES_VERTEX_COVER, OnSearchVertexCover)
	ON_COMMAND(ID_GRAPH_RESIZE, OnResizeGraph)
	ON_COMMAND(ID_GRAPH_GENERATE_RANDOMGRAPH, OnGenerateRandomgraph)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_GENERATE_RANDOMGRAPH, OnUpdateGenerateRandomgraph)
	ON_COMMAND(ID_LAYOUT_ELLIPSE, OnLayoutEllipse)
	ON_UPDATE_COMMAND_UI(ID_LAYOUT_ELLIPSE, OnUpdateLayoutEllipse)
	ON_COMMAND(ID_DEMO_FORD_FULKERSON, OnDemoFordFulkerson)
	ON_COMMAND(ID_NETWORK_MAXIMUM_BIPARTITE_MATCHING, OnSearchMaximumBipartiteMatching)
	ON_COMMAND(ID_ALGORITHM_JOHNSON, OnJohnsonAlgorithm)
	ON_COMMAND(ID_UTILITIES_PREORDER, OnPreorderTraversal)
	ON_COMMAND(ID_UTILITIES_POSTORDER, OnPostorderTraversal)
	ON_COMMAND(ID_UTILITIES_HAMILTON, OnHamiltonCircuit)
	ON_COMMAND(ID_DEMO_ASTAR, OnDemoAstar)
	ON_COMMAND(ID_ALGORITHM_ASTAR, OnAstarAlgorithm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThesisView construction/destruction

CThesisView::CThesisView()
{
	// TODO: add construction code here
	m_menuContext.Initialize(IDR_GRAPH,NULL);
	mode = SELECT;
}

CThesisView::~CThesisView()
{
}

BOOL CThesisView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CScrollView::PreCreateWindow(cs);	
}

/////////////////////////////////////////////////////////////////////////////
// CThesisView drawing

void CThesisView::OnDraw(CDC* pDC)
{
	CThesisDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	CDC MemDC; // double buffer
	CDC *pDrawDC = pDC;
	CBitmap bitmap,*pOldBitmap = NULL;
	
	// Only paint the visble cliping
	CRect client;
	pDC->GetClipBox(client);
	
	CRect rect = client;
	docToClient(rect);
	
	// Fast repaint by draw alls to a compatible bitmap 
	if (MemDC.CreateCompatibleDC(pDC))
	{
		if (bitmap.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height())){
			OnPrepareDC(&MemDC,NULL);
			pDrawDC = &MemDC;
			MemDC.OffsetViewportOrg(-rect.left,-rect.top);
			pOldBitmap = MemDC.SelectObject(&bitmap);
			MemDC.SetBrushOrg(rect.left % 8, rect.top % 8);
		}
	}
	
	// Repaint background with White brush...
	CBrush brush;
	
	if (!brush.CreateSolidBrush(RGB(255,255,255)))
		return;
	brush.UnrealizeObject();
	pDrawDC->FillRect(client,&brush);
	
	// Draw all objects on screen
	CGraphController*pController = getController();
	if (pController) pController->draw(pDrawDC);
	
	if (pDrawDC != pDC)
	{
		pDC->SetViewportOrg(0, 0);
		pDC->SetWindowOrg(0,0);
		pDC->SetMapMode(MM_TEXT);
		MemDC.SetViewportOrg(0,0);
		MemDC.SetWindowOrg(0,0);
		MemDC.SetMapMode(MM_TEXT);
		// Put everything out ...
		pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(),
			&MemDC, 0, 0, SRCCOPY);
		MemDC.SelectObject(pOldBitmap);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CThesisView diagnostics

#ifdef _DEBUG
void CThesisView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CThesisView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CThesisDoc* CThesisView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CThesisDoc)));
	return (CThesisDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CThesisView message handlers

void CThesisView::OnGraphAddEdge() 
{
	mode = EDGE;
}

void CThesisView::OnGraphRemove() 
{
	mode = REMOVE;
}

void CThesisView::OnGraphSelect() 
{
	mode = SELECT;
}

void CThesisView::OnGraphAddVertex() 
{
	mode = VERTEX;
}

int CThesisView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

void CThesisView::OnInitialUpdate() 
{
	CScrollView::OnInitialUpdate();
	
	CSize sizeTotal;
	// TODO: calculate the total size of this view
	// sizeTotal.cx = sizeTotal.cy = 100;
	/*
	CRect rect;
	GetClientRect(rect);
	sizeTotal.cx = rect.bottom - rect.top;
	sizeTotal.cy = rect.right - rect.left;
	//*/
	sizeTotal.cx = sizeTotal.cy = 10000;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

BOOL CThesisView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	if (nHitTest == HTCLIENT) {		
		switch(mode) {
		case SELECT:
			SetCursor(
				getController()->getCusorHandle()
			);
			break;
		case REMOVE:
			SetCursor(
				AfxGetApp()->LoadCursor(IDC_REMOVE_CURSOR)
			);
			break;
		case VERTEX:
			SetCursor(
				AfxGetApp()->LoadCursor(IDC_VERTEX_CURSOR)
			);
			break;
		case EDGE:
			SetCursor(
				AfxGetApp()->LoadCursor(IDC_EDGE_CURSOR)
			);
			break;
		default:
			break;
		}
	}
	return TRUE;
	// return CScrollView::OnSetCursor(pWnd, nHitTest, message);
}

void CThesisView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CMenu *pSubMenu = m_menuContext.GetSubMenu(0);
	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);	
}

void CThesisView::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	m_menuContext.DrawItem(lpDrawItemStruct);	
	CScrollView::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CThesisView::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	m_menuContext.MeasureItem(this, lpMeasureItemStruct);	
	CScrollView::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void CThesisView::OnGraphProperties() 
{	
	getController()->displayProperties();
}

void CThesisView::clientToDoc(CPoint& point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc, NULL);
	dc.DPtoLP(&point);
}

void CThesisView::clientToDoc(CRect& rect)
{
	CClientDC dc(this);
	OnPrepareDC(&dc, NULL);
	dc.DPtoLP(rect);
	ASSERT(rect.left <= rect.right);
	ASSERT(rect.bottom <= rect.top);
}

void CThesisView::docToClient(CPoint& point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc, NULL);
	dc.LPtoDP(&point);
}

void CThesisView::docToClient(CRect& rect)
{
	CClientDC dc(this);
	OnPrepareDC(&dc, NULL);
	dc.LPtoDP(rect);
	rect.NormalizeRect();
}

void CThesisView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CScrollView::OnLButtonDown(nFlags, point);
	getController()->OnLButtonDown(this,nFlags,point);
}

void CThesisView::OnLButtonUp(UINT nFlags, CPoint point) 
{	
	CScrollView::OnLButtonUp(nFlags, point);
	getController()->OnLButtonUp(this,nFlags,point);
}

void CThesisView::OnMouseMove(UINT nFlags, CPoint point) 
{	
	CScrollView::OnMouseMove(nFlags, point);
	getController()->OnMouseMove(this,nFlags,point);
}

void CThesisView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{	
	CScrollView::OnLButtonDblClk(nFlags, point);
	getController()->OnLButtonDblClk(this,nFlags,point);
}

void CThesisView::setModifiedFlag(BOOL bModified)
{
	GetDocument()->SetModifiedFlag(bModified);
}

CThesisView::MODE CThesisView::getMode()const{
	return mode;
}
void CThesisView::OnToolsOptions() 
{
	getController()->showOptions();
}

void CThesisView::OnEditDelete() 
{
	getController()->removeSelected();
	setModifiedFlag();
	Invalidate(FALSE);
}

void CThesisView::OnTopologicalOrderTraversal() 
{
	getController()->OnTopologicalOrderTraversal();
}

void CThesisView::OnBreadthFirstTraversal() 
{
	getController()->OnBreadthFirstTraversal();
}

void CThesisView::OnPrimAlgorithm() 
{	
	getController()->doPrim();
}

void CThesisView::OnDijkstraAlgorithm() 
{	
	getController()->doDijkstra();
}

void CThesisView::OnFloydAlgorithm() 
{
	getController()->doFloyd();
}

void CThesisView::OnKruskalAlgorithm() 
{	
	getController()->doKruskal();	
}

CGraphController* CThesisView::getController()
{
	return (GetDocument()->m_pController);
}

void CThesisView::OnEulerianCircuit() 
{
	getController()->doFleury();
}

void CThesisView::OnSearchCutVertices() 
{
	getController()->OnSearchCutVertices(this);
}

void CThesisView::OnColorGraph() 
{
	getController()->doWelchPowell(this);	
}

void CThesisView::OnBellmanFordAlgorithm() 
{
	getController()->doBellmanFord();	
}

void CThesisView::OnSearchCycles() 
{
	getController()->OnSearchCycles();
}

void CThesisView::OnSearchBridgeEdges() 
{
	getController()->OnSearchBridgeEdges();
}

void CThesisView::OnSearchConnectedComponents() 
{
	getController()->OnSearchConnectedComponents();
}

void CThesisView::OnSearchBiconnectedComponents() 
{
	getController()->OnSearchBiconnectedComponents();
}

void CThesisView::OnGenerateCompleteGraph() 
{
	getController()->OnGenerateCompleteGraph(this);
}

void CThesisView::OnUpdateGenerateCompleteGraph(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(getController()->isEmpty());
}

void CThesisView::OnGetTransitiveClosure() 
{
	getController()->doWarshall();
}

void CThesisView::OnSearchCriticalPath() 
{
	getController()->OnSearchCriticalPath();
}

// single-source shortest path in DAGs
void CThesisView::OnSspDagAlgorithm() 
{
	getController()->doDAGsShortestPath();
}

void CThesisView::OnCheckNetwork() 
{
	getController()->OnCheckNetwork(this);
}

void CThesisView::OnFordFulkersonAlgorithm() 
{
	getController()->doFordFulkerson();
}

void CThesisView::OnBuildResidualNetwork() 
{
	getController()->OnBuildResidualNetwork();
}

void CThesisView::OnSearchVertexCover() 
{
	getController()->OnSearchVertexCover();
	Invalidate(FALSE);
}

void CThesisView::OnResizeGraph() 
{
	getController()->OnResizeGraph();
}

void CThesisView::OnGenerateRandomgraph() 
{
	getController()->OnGenerateRandomgraph(this);
}

void CThesisView::OnUpdateGenerateRandomgraph(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(getController()->isEmpty());
}

void CThesisView::OnLayoutEllipse() 
{
	getController()->OnLayoutEllipse(this);
}

void CThesisView::OnUpdateLayoutEllipse(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!getController()->isEmpty());	
}

void CThesisView::OnDemoFordFulkerson() 
{
	getController()->OnDemoFordFulkerson();
}

void CThesisView::OnSearchMaximumBipartiteMatching() 
{
	getController()->OnSearchMaximumBipartiteMatching();
}

void CThesisView::OnJohnsonAlgorithm() 
{
	getController()->doJohnson();
}

void CThesisView::OnPreorderTraversal() 
{
	getController()->OnDepthFirstTraversal();
}

void CThesisView::OnPostorderTraversal() 
{
	getController()->OnDepthFirstTraversal(FALSE);
}

void CThesisView::OnHamiltonCircuit() 
{
	getController()->OnSearchHamiltonPath();
}

void CThesisView::OnDemoAstar() 
{
	getController()->OnDemoAstar();
}

void CThesisView::OnAstarAlgorithm() 
{
	getController()->doAStar();
}
