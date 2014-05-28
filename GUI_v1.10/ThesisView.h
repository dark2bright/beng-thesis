// ThesisView.h : interface of the CThesisView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_THESISVIEW_H__4FE64D2B_D2F0_4286_8B6C_825675726B6F__INCLUDED_)
#define AFX_THESISVIEW_H__4FE64D2B_D2F0_4286_8B6C_825675726B6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Visitor.h"
#include "MenuEx.h"
#include "ThesisDoc.h"

class CThesisView : public CScrollView
{
protected: // create from serialization only
	CThesisView();
	DECLARE_DYNCREATE(CThesisView)

// Attributes
public:
	CThesisDoc* GetDocument();
	enum MODE {VERTEX,EDGE,SELECT,REMOVE};
// Operations
public:
	void docToClient(CRect&);
	void docToClient(CPoint&);
	void clientToDoc(CPoint&);
	void clientToDoc(CRect&);
	MODE getMode()const;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThesisView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	void setModifiedFlag(BOOL bModified = TRUE);
	virtual ~CThesisView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CMenuEx m_menuContext;
	MODE mode;
// Generated message map functions
protected:
	//{{AFX_MSG(CThesisView)
	afx_msg void OnGraphAddEdge();
	afx_msg void OnGraphRemove();
	afx_msg void OnGraphSelect();
	afx_msg void OnGraphAddVertex();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnGraphProperties();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnToolsOptions();
	afx_msg void OnEditDelete();
	afx_msg void OnTopologicalOrderTraversal();
	afx_msg void OnBreadthFirstTraversal();
	afx_msg void OnPrimAlgorithm();
	afx_msg void OnDijkstraAlgorithm();
	afx_msg void OnFloydAlgorithm();
	afx_msg void OnKruskalAlgorithm();
	afx_msg void OnEulerianCircuit();
	afx_msg void OnSearchCutVertices();
	afx_msg void OnColorGraph();
	afx_msg void OnBellmanFordAlgorithm();
	afx_msg void OnSearchCycles();
	afx_msg void OnSearchBridgeEdges();
	afx_msg void OnSearchConnectedComponents();
	afx_msg void OnSearchBiconnectedComponents();
	afx_msg void OnGenerateCompleteGraph();
	afx_msg void OnUpdateGenerateCompleteGraph(CCmdUI* pCmdUI);
	afx_msg void OnGetTransitiveClosure();
	afx_msg void OnSearchCriticalPath();
	afx_msg void OnSspDagAlgorithm();
	afx_msg void OnCheckNetwork();
	afx_msg void OnFordFulkersonAlgorithm();
	afx_msg void OnBuildResidualNetwork();
	afx_msg void OnSearchVertexCover();
	afx_msg void OnResizeGraph();
	afx_msg void OnGenerateRandomgraph();
	afx_msg void OnUpdateGenerateRandomgraph(CCmdUI* pCmdUI);
	afx_msg void OnLayoutEllipse();
	afx_msg void OnUpdateLayoutEllipse(CCmdUI* pCmdUI);
	afx_msg void OnDemoFordFulkerson();
	afx_msg void OnSearchMaximumBipartiteMatching();
	afx_msg void OnJohnsonAlgorithm();
	afx_msg void OnPreorderTraversal();
	afx_msg void OnPostorderTraversal();
	afx_msg void OnHamiltonCircuit();
	afx_msg void OnDemoAstar();
	afx_msg void OnAstarAlgorithm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CGraphController* getController();
};

#ifndef _DEBUG  // debug version in ThesisView.cpp
inline CThesisDoc* CThesisView::GetDocument()
   { return (CThesisDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THESISVIEW_H__4FE64D2B_D2F0_4286_8B6C_825675726B6F__INCLUDED_)
