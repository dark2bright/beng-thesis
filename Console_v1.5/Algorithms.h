// Algorithms.h: interface for the CAlgorithm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALGORITHM_H__023113C6_3A7E_4376_BB8D_C6BEA929599C__INCLUDED_)
#define AFX_ALGORITHM_H__023113C6_3A7E_4376_BB8D_C6BEA929599C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UndirectedGraph.h"
#include "DirectedGraph.h"
#include "AstarHeuristic.h"

interface CAlgorithms
{
	//////////////////////////////////////////////////////////////////////////
	// weighted graph algorithms
	//////////////////////////////////////////////////////////////////////////

	// finds a minimum-cost spanning tree of an edge-weighted, connected, undirected graph 
	virtual CAbstractGraph* doPrim(const CAbstractGraph&, NUMBER) = 0;		
	// finds a minimum-cost spanning tree
	virtual CAbstractGraph* doKruskal(const CAbstractGraph&) = 0;
	// dynamic programming method to solve the all-pairs shortest-path problem on a dense graph
	virtual CAbstractGraph* doFloyd(const CAbstractGraph&) = 0;
	virtual CAbstractGraph* doJohnson(const CAbstractGraph&) = 0;
	// algorithm to solve single-source, shortest-path problem on DAGs
	virtual CAbstractGraph* doDAGsShortestPath(const CDirectedGraph&,NUMBER) = 0;
	// greedy algorithm for solving the single-source, shortest-path problem on an edge-weighted graph in which all the weights are non-negative
	virtual CAbstractGraph* doDijkstra(const CAbstractGraph&,NUMBER) = 0;
	// greedy algorithm for solving the single-source, shortest-path problem , can handle negative-weight cycle
	virtual CAbstractGraph* doBellmanFord(const CAbstractGraph&,NUMBER) = 0;
	// critical path in scheduling problem ( perl diagram )
	virtual CAbstractGraph* doCriticalPathAnalysis (const CDirectedGraph&) = 0;
	
	virtual CIterator& doAStar(const CAbstractGraph&, NUMBER, CAstarHeuristic&) = 0;
	//////////////////////////////////////////////////////////////////////////
	// Network flow's alorithms
	//////////////////////////////////////////////////////////////////////////
	
	// return	VALID if graph is valid network and return source and sink of it
	//			REDUCED if graph is multi-source and sink network, automatic reduced to single-source and sink
	//			INVALID if graph is invalid ( don't sastify contraints )
	virtual INT checkValidNetwork(CDirectedGraph&,NUMBER&,NUMBER&) = 0;
	virtual CDirectedGraph* buildResidualNetwork(const CDirectedGraph&) = 0;
	// max-flow algorithm base on Ford-Fulkerson => return a set of mincut
	virtual CIterator& doEdmondsKarp(CDirectedGraph&,NUMBER,NUMBER) = 0;
};

#endif // !defined(AFX_ALGORITHM_H__023113C6_3A7E_4376_BB8D_C6BEA929599C__INCLUDED_)
