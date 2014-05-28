// GraphController.h: interface for the CGraphController class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHCONTROLLER_H__79E54E81_253A_4A49_ABDA_B2941CAC0DFA__INCLUDED_)
#define AFX_GRAPHCONTROLLER_H__79E54E81_253A_4A49_ABDA_B2941CAC0DFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GraphView.h"

class CThesisView;

class CGraphController  
{
	class CColoringVisitor : public CVisitor
	{
	public:
		CColoringVisitor(CGraphView*); 
		void visit(CObjectEx&);
	protected:
		CGraphView*m_pView;
		COLORREF color[5];
	};
	class CGraphViewEx : public CGraphView
	{
		friend class CGraphController;
		friend class CColoringVisitor;
	};
public:
	CGraphController(UINT);
	virtual ~CGraphController();
public:
	void Serialize(CArchive&);
	void doAStar();
	void doPrim();
	void doKruskal();
	void doFloyd();
	void doJohnson();
	void doFordFulkerson();
	void doFleury();
	void doDijkstra();
	void doBellmanFord();
	void doWarshall();
	void doWelchPowell(CThesisView*);
	void doDAGsShortestPath();
	void displayProperties();
	void OnSearchCutVertices(CThesisView*);
	void out(CString&)const;
	void OnLayoutEllipse(CThesisView*);
	void OnTopologicalOrderTraversal();
	void OnBreadthFirstTraversal();
	void OnDepthFirstTraversal(BOOL preorder = TRUE);
	void OnCheckNetwork(CThesisView*);
	void removeSelected();
	void showOptions();
	void attachModelToView(CAbstractGraph*);
	void draw(CDC*);
	void OnBuildResidualNetwork();
	void OnDemoAstar();
	void OnDemoFordFulkerson();
	BOOL OnResizeGraph();
	void OnSearchBridgeEdges();
	void OnSearchBiconnectedComponents();
	void OnSearchCycles();
	void OnSearchCriticalPath();
	void OnSearchConnectedComponents();
	void OnSearchHamiltonPath();
	void OnSearchMaximumBipartiteMatching();
	void OnSearchVertexCover();
	void OnLButtonDown(CThesisView *,UINT, CPoint);
	void OnMouseMove(CThesisView *,UINT, CPoint);
	void OnLButtonUp(CThesisView *,UINT , CPoint );
	void OnLButtonDblClk(CThesisView*, UINT, CPoint);
	void OnGenerateCompleteGraph(CThesisView*);
	void OnGenerateRandomgraph(CThesisView*);
	HCURSOR getCusorHandle()const;
	BOOL isEmpty()const;
protected:
	void addVertex(CPoint);
	void addEdge(CEdgeView*&);
	BOOL isFull();
	BOOL containPositiveWeightedEdge(CAbstractGraph*)const;
	CGraphView* buildNewGraphView(const CAbstractGraph&,INT)const;	
	CGraphView* copyGraphView(const CAbstractGraph&,INT)const;
	CIterator&getGraphics(CIterator&,CGraphView*,BOOL bVertex = TRUE);
public:
	CONTROLSTRUCT m_control;
protected:
	CGraphView* m_pGraphView;
private:
	CGraphics*m_pSelected;
	CGraphics*m_pTmpSel; // temporary selected by mouse move over
	UINT m_nHitTest;
	CPoint m_prevPoint;
};

#endif // !defined(AFX_GRAPHCONTROLLER_H__79E54E81_253A_4A49_ABDA_B2941CAC0DFA__INCLUDED_)
