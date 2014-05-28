// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Thesis.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_GRAPH, OnViewGraph)
	ON_UPDATE_COMMAND_UI(ID_VIEW_GRAPH, OnUpdateViewGraph)
	ON_COMMAND(ID_VIEW_OUTPUT, OnViewOutput)
	ON_UPDATE_COMMAND_UI(ID_VIEW_OUTPUT, OnUpdateViewOutput)
	ON_COMMAND(ID_VIEW_UTILITIES, OnViewUtilities)
	ON_UPDATE_COMMAND_UI(ID_VIEW_UTILITIES, OnUpdateViewUtilities)
	ON_COMMAND(ID_VIEW_ALGORITHMS, OnViewAlgorithms)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ALGORITHMS, OnUpdateViewAlgorithms)
	ON_COMMAND(ID_VIEW_NETWORK, OnViewNetwork)
	ON_UPDATE_COMMAND_UI(ID_VIEW_NETWORK, OnUpdateViewNetwork)
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CMDIFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CMDIFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CMDIFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CMDIFrameWnd::OnHelpFinder)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar,AFX_IDW_DOCKBAR_TOP);
	//* [My code start here]
	// Graph ToolBar
	if (!m_wndGraphBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndGraphBar.LoadToolBar(IDR_GRAPH))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	m_wndGraphBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndGraphBar,AFX_IDW_DOCKBAR_RIGHT);
	// DockControlBar(&m_wndGraphBar,AFX_IDW_DOCKBAR_LEFT);
	// Utilities ToolBar
	// if (!m_wndUtilBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | /*WS_VISIBLE | */CBRS_TOP
	if (!m_wndUtilBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndUtilBar.LoadToolBar(IDR_UTILITIES))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	m_wndUtilBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndUtilBar,AFX_IDW_DOCKBAR_LEFT);
	// Algorithm ToolBar
	// if (!m_wndAlgorithmBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | /*WS_VISIBLE | */ CBRS_BOTTOM
	if (!m_wndAlgorithmBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_BOTTOM
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndAlgorithmBar.LoadToolBar(IDR_ALGORITHMS))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	m_wndAlgorithmBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndAlgorithmBar,AFX_IDW_DOCKBAR_LEFT);
	// Network ToolBar
	// if (!m_wndNetworkBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | /*WS_VISIBLE | */ CBRS_BOTTOM
	if (!m_wndNetworkBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_BOTTOM
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndNetworkBar.LoadToolBar(IDR_NETWORK))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	m_wndNetworkBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndNetworkBar,AFX_IDW_DOCKBAR_LEFT);
	
	// Output (edit bar)
	if(!m_wndOutputBar.Create(_T("Output"),this,0))
	{
		TRACE0("Failed to create output bar\n");
		return -1;		// fail to create
	}
	m_wndOutputBar.SetBarStyle(m_wndOutputBar.GetBarStyle()|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_SIZE_DYNAMIC);
	m_wndOutputBar.EnableDocking(CBRS_ALIGN_BOTTOM);
	DockControlBar(&m_wndOutputBar,AFX_IDW_DOCKBAR_BOTTOM);
	
	// RepositionBars(IDR_UTILITIES,IDR_NP_COMPLETES,IDR_NP_COMPLETES);

	// CMDITabs must be createt at last to ensure correct layout!!!
	// ------------------------------------------------------------
	m_wndMDITabs.Create(this);
	/* Set application icon
	SetIcon(
		AfxGetApp()->LoadIcon(IDR_MAINFRAME),
		FALSE
	);
	//*/
	// [My code end here] 
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	CMDIFrameWnd::OnUpdateFrameTitle(bAddToTitle);
	
	m_wndMDITabs.Update(); // sync the mditabctrl with all views
}

void CMainFrame::OnViewGraph() 
{
	ShowControlBar(&m_wndGraphBar,! m_wndGraphBar.IsWindowVisible(),FALSE);
}

void CMainFrame::OnUpdateViewGraph(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndGraphBar.IsWindowVisible() ? 1 : 0);
}

void CMainFrame::OnViewOutput() 
{
	ShowControlBar(&m_wndOutputBar,! m_wndOutputBar.IsWindowVisible(),FALSE);
}

void CMainFrame::OnUpdateViewOutput(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndOutputBar.IsWindowVisible() ? 1 : 0);
}

void CMainFrame::OnViewUtilities() 
{
	ShowControlBar(&m_wndUtilBar,! m_wndUtilBar.IsWindowVisible(),FALSE);
}

void CMainFrame::OnUpdateViewUtilities(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndUtilBar.IsWindowVisible() ? 1 : 0);
}

void CMainFrame::OnViewAlgorithms() 
{
	ShowControlBar(&m_wndAlgorithmBar,! m_wndAlgorithmBar.IsWindowVisible(),FALSE);
}

void CMainFrame::OnUpdateViewAlgorithms(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndAlgorithmBar.IsWindowVisible() ? 1 : 0);
}

void CMainFrame::OnViewNetwork() 
{
	ShowControlBar(&m_wndNetworkBar,! m_wndNetworkBar.IsWindowVisible(),FALSE);
}

void CMainFrame::OnUpdateViewNetwork(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndNetworkBar.IsWindowVisible() ? 1 : 0);
}
