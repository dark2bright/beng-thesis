// GraphUtilities.h: interface for the CGraphUtilities class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHUTILITIES_H__8603FBCC_07C6_41A1_A770_F1762ACD3F84__INCLUDED_)
#define AFX_GRAPHUTILITIES_H__8603FBCC_07C6_41A1_A770_F1762ACD3F84__INCLUDED_

#include "Iterator.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DirectedGraph.h"
#include "UndirectedGraph.h"
#include "PrePostVisitor.h"
#include "ListIterator.h"
#include "Stack.h"

class CGraphUtilities  
{
	class CCountingVisitor : public CVisitor
	{
		UINT m_uCount;
	public:
		CCountingVisitor();
		void visit (CObjectEx&);
		UINT count ()const;
	};
	class CSearchingVisitor : public CVisitor
	{
	public:
		CSearchingVisitor(CObjectEx&);
		void visit (CObjectEx&);
		BOOL isDone()const;
	protected:
		CObjectEx&target;
		BOOL found;
	};
	typedef struct _tagDFSBRIDGEEDGE
	{
		INT discover;
		INT low;
		INT predecessor;
		_tagDFSBRIDGEEDGE();
	}DFSBRIDGEEDGE;
	typedef struct _tagDFSCUTVERTEX : public _tagDFSBRIDGEEDGE
	{
		UINT treeEdges;	// number of emanating edges
		BOOL separating;
		_tagDFSCUTVERTEX();
	}DFSCUTVERTEX;
public:
	CGraphUtilities();
public:
	INT isEulerian(const CAbstractGraph&)const;
	UINT colorGraph(const CAbstractGraph&,CVisitor&)const;	
	BOOL hasPath(const CAbstractGraph&,NUMBER,NUMBER)const;
	BOOL isWeaklyConnected(const CAbstractGraph&)const;
	BOOL isConnected(const CAbstractGraph&)const;
	BOOL isCyclic(const CAbstractGraph&)const;
	BOOL eulerianTraversal(const CAbstractGraph&,CVisitor&)const;
	VOID breadthFirstTraversal(const CAbstractGraph&,CVisitor&, NUMBER)const;
	VOID breadthFirstTraversal(const CAbstractGraph&,CVisitor&)const;
	VOID topologicalOrderTraversal(const CDirectedGraph&,CVisitor&)const;
	VOID depthFirstTraversal(CAbstractGraph const&,CPrePostVisitor&,NUMBER)const;
	VOID depthFirstTraversal(CAbstractGraph const&,CPrePostVisitor&)const;
	VOID depthFirstTraversalEx(CAbstractGraph const&,CPrePostVisitor&,NUMBER)const;
	CIterator& isBipartite(const CAbstractGraph&)const;
	CIterator& getPath(const CAbstractGraph&,NUMBER,NUMBER)const;
	CIterator& getArticulationPoints(const CAbstractGraph&)const;
	CIterator& getBiconnectedComponents(const CAbstractGraph&)const;
	CIterator& getBridgeEdges(const CAbstractGraph&)const;
	CIterator& getConnectedComponents(const CAbstractGraph&)const;
	CIterator& getCycle(const CAbstractGraph&,NUMBER)const;
	CIterator& getCycles(const CAbstractGraph&)const;
	CIterator& getMaximumMatching(const CAbstractGraph&)const;
	CIterator& getVertexCover(const CAbstractGraph&)const;
	CIterator& getHamiltonPath(const CAbstractGraph&, NUMBER,NUMBER)const;
	CAbstractGraph* getTransitiveClosure(const CAbstractGraph&)const;
	CAbstractGraph& copyGraph(const CAbstractGraph&)const;
protected:
	void popStackUntil(CStack&, NUMBER ,NUMBER, CLinkedList<CListIterator*> &) const;
	void dfsArticulationPoint(const CAbstractGraph&,NUMBER,UINT&,CArrayEx<DFSCUTVERTEX>&,CLinkedList<CObjectEx*>&)const;
	void dfsBiconnectedComponent(const CAbstractGraph&,NUMBER,UINT&,CArrayEx<DFSCUTVERTEX>&,CStack&,CLinkedList<CListIterator*>&)const;
	void dfsBridgeEdge(const CAbstractGraph&,NUMBER,UINT&,CArrayEx<DFSBRIDGEEDGE>&,CLinkedList<CListIterator*>&)const;
	void dfsConnectedComponent(const CAbstractGraph&,NUMBER,UINT&,UINT&,CArrayEx<INT>&,CArrayEx<INT>&,CStack&,CStack&)const;
	BOOL dfsHamilton(const CAbstractGraph&,CStack&,CLinkedList<CObjectEx*>&,CArrayEx<BOOL>&,NUMBER, NUMBER, UINT)const;
	VOID depthFirstTraversal(const CAbstractGraph&,CPrePostVisitor&, const CVertex&,CArrayEx<BOOL>&)const;
};

#endif // !defined(AFX_GRAPHUTILITIES_H__8603FBCC_07C6_41A1_A770_F1762ACD3F84__INCLUDED_)
