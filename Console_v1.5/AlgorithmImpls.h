// Algorithms.h: interface for the CAlgorithms class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALGORITHMS_H__336C1A1F_2138_4663_BCD4_902E3109EAD4__INCLUDED_)
#define AFX_ALGORITHMS_H__336C1A1F_2138_4663_BCD4_902E3109EAD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// #include <limits>
#include "Association.h"
#include "Wrapper.h"
#include "GraphFactory.h"
#include "GraphBuilder.h"
#include "BinaryHeap.h"
#include "Algorithms.h"
#include "WeightedVertex.h"
#include "WeightedEdge.h"
#include "Array2D.h"
#include "PartitionAsForest.h"
#include "GraphUtilities.h"
#include "PreOrder.h"
#include "PostOrder.h"
#include "NetworkEdge.h"
#include "LinkedQueue.h"

#define		INFINITE_VALUE	SHRT_MAX

template<class EDGETYPE>
class CAlgorithmImpls : public CAlgorithms
{
#define		TYPE	CWrapper<EDGETYPE>
	//	const TYPE INFINITE_VALUE = numeric_limits<EDGETYPE>::max();
	struct CTableEntry
	{
		BOOL known;
		TYPE distance;
		NUMBER predecessor;
		CTableEntry () : known (FALSE),	distance (INFINITE_VALUE) {}
	};
	
	class CAssoc : public CAssociation
	{
		TYPE priority;
	public:
		CAssoc (CWrapper<EDGETYPE>p, CObjectEx&object)
			: CAssociation(priority,object),priority(p)
		{
			rescindOwnership (); 
		}
		INT typeId() const
		{
			return ASSOCID;
		}
		CString toString()const
		{
			return "Assoc";
		}
	};

	CAlgorithmImpls(){}

	friend class CWrapperUtilities;

	public:	
		virtual ~CAlgorithmImpls(){}
	public:
		CAbstractGraph* doKruskal(const CAbstractGraph&graph)
		{
			ASSERT(!graph.isDirected());
			UINT const numberOfVertices = graph.numberOfVertices ();
			CGraphFactory graphFactory;
			CAbstractGraph *pResult = graphFactory.buildGraphAsLists(numberOfVertices,FALSE);
			CGraphBuilder builder(*pResult);
			for (NUMBER v = 0; v < numberOfVertices; ++v)
				pResult->addVertex (*(builder.buildDefaultVertex()));
			
			CPriorityQueue& queue = *new CBinaryHeap (graph.numberOfEdges ());
			CIterator& p = graph.getEdges ();
			while (!p.isDone ()) {
				CWeightedEdge& edge = (CWeightedEdge&) (p.currentItem());
				TYPE& weight = (TYPE&)(edge.getWeight ());
				queue.enqueue (*new CAssoc (weight, edge));
				p.moveNext();
			}
			delete &p;
			
			CPartition& partition = *new CPartitionAsForest (numberOfVertices);
			while (!queue.isEmpty () && partition.count() > 1)
			{
				CAssoc& assoc =
					(CAssoc&) (queue.dequeueMin ());
				CEdge& edge = (CEdge&)(assoc.getValue ());
				NUMBER const v0 = edge.firstEndPoint();
				NUMBER const v1 = edge.secondEndPoint();
				CSet& s = partition.findEx(CSet::ELEMENT(v0));
				CSet& t = partition.findEx(CSet::ELEMENT(v1));
				if (s != t)
				{
					partition.join (s, t);
					CWeightedEdge*pE = (CWeightedEdge*)builder.buildWeightedEdge(v0,v1,((CWeightedEdge&)graph.selectEdge(v0,v1)).getWeight());
					pE->rescindOwnership();
					pResult->addEdge(*pE);
				}
				delete &assoc;
			}
			delete &partition;
			delete &queue;
			return pResult;
		}
		
		CAbstractGraph* doPrim(const CAbstractGraph& graph, NUMBER number)
		{
			ASSERT(!graph.isDirected());
			CVertex& start = graph.selectVertex(number);
			UINT const numberOfVertices = graph.numberOfVertices ();
			CArrayEx<CTableEntry> table (numberOfVertices);
			CPriorityQueue& queue = *new CBinaryHeap (graph.numberOfEdges ());
			table [start].distance = 0;
			queue.enqueue (*new CAssoc (0, const_cast<CVertex&> (start)));
			while (!queue.isEmpty ())
			{
				CAssoc& assoc = (CAssoc&)(queue.dequeueMin ());
				CVertex& v0 = (CVertex&)(assoc.getValue ());
				if (!table [v0].known)
				{
					table [v0].known = true;
					CIterator& p = graph.emanatingEdges (v0);
					while (!p.isDone ()) {
						CWeightedEdge& edge = (CWeightedEdge&)(p.currentItem());
						CVertex& v1 = edge.mate (v0);
						TYPE& weight = (TYPE&) (edge.getWeight ());
						const TYPE d = weight;
						if (!table[v1].known && table[v1].distance > d){
							table [v1].distance = d;
							table [v1].predecessor = v0;
							queue.enqueue (*new CAssoc (d, v1));
						}
						p.moveNext();
					}
					delete &p;
				}
				delete &assoc;
			}
			delete &queue;
			
			CGraphFactory graphFactory;
			CAbstractGraph* pResult = graphFactory.buildGraphAsLists(numberOfVertices,FALSE);
			for (NUMBER v = 0; v < numberOfVertices; ++v)
				pResult->addVertex ((CVertex&)(graph.selectVertex(v).clone()));
			CGraphBuilder builder(*pResult);
			for (v = 0; v < numberOfVertices; ++v)
				if (v != start){
					CEdge* pE = builder.buildWeightedEdge(
						v, table [v].predecessor,
						*new TYPE(table[v].distance));
					pResult->addEdge(*pE); 
				}
				return pResult;
		}
		
		CAbstractGraph* doFloyd(const CAbstractGraph&digraph)
		{
			// ASSERT(graph.isDirected());
			UINT const numberOfVertices = digraph.numberOfVertices ();
			CArray2D<TYPE> distance (numberOfVertices, numberOfVertices);
			for (NUMBER v = 0; v < numberOfVertices; ++v)
				for (NUMBER w = 0; w < numberOfVertices; ++w)
					distance [v][w] = INFINITE_VALUE;
			CIterator& p = digraph.getEdges ();
			while (!p.isDone ())
			{
				CWeightedEdge& edge = (CWeightedEdge&) (p.currentItem());
				TYPE& weight = (TYPE&)(edge.getWeight());
				distance [edge.firstEndPoint()][edge.secondEndPoint()] = (UINT)weight;
				p.moveNext();
			}
			delete &p;
			
			for (NUMBER i = 0; i < numberOfVertices; ++i)
				for (NUMBER v = 0; v < numberOfVertices; ++v)
					for (NUMBER w = 0; w < numberOfVertices; ++w)
						if (distance [v][i] != INFINITE_VALUE &&
							distance [i][w] != INFINITE_VALUE)
						{
							const TYPE d =
								distance [v][i] + distance [i][w];
							if (distance [v][w] > d)
								distance [v][w] = d;
						}
							
			
			return buildAllPairsShortestPathGraph(numberOfVertices,distance);
		}
		
		CAbstractGraph* doJohnson(const CAbstractGraph&graph)
		{
			CGraphUtilities gu;
			CAbstractGraph& fake = gu.copyGraph(graph);
			CGraphBuilder builder(fake);
			CVertex& dummy = *builder.buildDefaultVertex();
			fake.addVertex(dummy);
			UINT numberOfVertices = graph.numberOfVertices();
			for(UINT v = 0; v < numberOfVertices; v++)
				fake.addEdge(*builder.buildWeightedEdge(dummy,v,*new TYPE(0)));
			CAbstractGraph* pBellmanFord = doBellmanFord(fake,dummy);
			if (!pBellmanFord) return NULL;
			CIterator& p = fake.getEdges();
			for (; !p.isDone(); p.moveNext())
			{
				CWeightedEdge& e = (CWeightedEdge&)p.currentItem();
				NUMBER  from = e.firstEndPoint(),
						to = e.secondEndPoint();
				TYPE& w = (TYPE&) (e.getWeight());
				TYPE& hf = (TYPE&)((CWeightedVertex&)pBellmanFord->selectVertex(from)).getWeight();
				TYPE& ht = (TYPE&)((CWeightedVertex&)pBellmanFord->selectVertex(to)).getWeight();
				e.setWeight(*new TYPE(w + hf - ht));
			}
			delete &p;
			CArray2D<TYPE> distance (numberOfVertices, numberOfVertices);
			for (v = 0; v < numberOfVertices; ++v)
				for (NUMBER w = 0; w < numberOfVertices; ++w)
					distance [v][w] = INFINITE_VALUE;
			for(v = 0; v < numberOfVertices; v++)
			{
				CAbstractGraph* pDijkstra = doDijkstra(fake,v);
				for(UINT w = 0; w < numberOfVertices; w++)
					if (w != v)
					{
						TYPE& hf = (TYPE&)((CWeightedVertex&)pBellmanFord->selectVertex(v)).getWeight();
						TYPE& ht = (TYPE&)((CWeightedVertex&)pBellmanFord->selectVertex(w)).getWeight();
						TYPE& d = (TYPE&)((CWeightedVertex&)pDijkstra->selectVertex(w)).getWeight();
						distance[v][w] = d + ht -hf;
					}
				delete pDijkstra;
			}
			delete pBellmanFord;
			delete &fake;
			return buildAllPairsShortestPathGraph(numberOfVertices,distance);
		}

		CAbstractGraph* doDAGsShortestPath(const CDirectedGraph&dag,NUMBER source) // must be Directed Acyclic Graph
		{
			class CShortestPathVisitor : public CVisitor
			{
				const CDirectedGraph& graph;
				CArrayEx<CTableEntry>&table;
			public:
				CShortestPathVisitor(const CDirectedGraph&_graph,CArrayEx<CTableEntry>&_table)
					: graph(_graph),table(_table)
				{}
				
				void visit (CObjectEx& object)
				{	
					NUMBER v0 = (CVertex&) (object);
					CIterator& p = graph.emanatingEdges(v0);
					while (!p.isDone())
					{
						CWeightedEdge& edge = (CWeightedEdge&) (p.currentItem());
						CVertex& v1 = edge.secondEndPoint();
						TYPE& weight = (TYPE&) (edge.getWeight());
						const TYPE d = table [v0].distance + weight;
						if (table [v1].distance > d)
						{
							table [v1].distance = d;
							table [v1].predecessor = v0;
						}
						p.moveNext();
					}
					delete&p;
				}	
			};
			UINT const numberOfVertices = dag.numberOfVertices ();
			CArrayEx<CTableEntry> table (numberOfVertices);
			table [source].distance = 0;
			CGraphUtilities gu;
			gu.topologicalOrderTraversal(dag,CShortestPathVisitor(dag,table));
			return buildSingleSourceShortestPathGraph(numberOfVertices,numberOfVertices,table);
		}
		//////////////////////////////////////////////////////////////////////////
		CIterator& doAStar(const CAbstractGraph&, NUMBER, CAstarHeuristic<EDGETYPE>&)
		{
			// return *new CNullIterator;
		}
		//////////////////////////////////////////////////////////////////////////
		CAbstractGraph* doDijkstra(const CAbstractGraph&digraph,NUMBER vertex)
		{
			CVertex& source = digraph.selectVertex(vertex);
			UINT const numberOfVertices = digraph.numberOfVertices ();
			CArrayEx<CTableEntry> table (numberOfVertices);
			CPriorityQueue& queue = *new CBinaryHeap (digraph.numberOfEdges ());
			table [source].distance = 0;
			queue.enqueue (*new CAssoc (0, const_cast<CVertex&> (source)));
			while (!queue.isEmpty ())
			{
				CAssoc& assoc = (CAssoc&)(queue.dequeueMin ());
				CVertex& v0 = (CVertex&)(assoc.getValue ());
				if (!table [v0].known)
				{
					table [v0].known = true;
					CIterator& p = digraph.emanatingEdges (v0);
					while (!p.isDone ()) 
					{
						CWeightedEdge& edge = (CWeightedEdge&) (p.currentItem());
						CVertex& v1 = edge.secondEndPoint();
						TYPE& weight = (TYPE&) (edge.getWeight());
						const TYPE d = table [v0].distance + weight;
						if (table [v1].distance > d)
						{
							table [v1].distance = d;
							table [v1].predecessor = v0;
							queue.enqueue (*new CAssoc(d, v1));
						}
						p.moveNext();
					}
					delete &p;
				}
				delete &assoc;
			}
			delete &queue;
			return buildSingleSourceShortestPathGraph(numberOfVertices,source,table);
		}
		
		CAbstractGraph* doCriticalPathAnalysis (const CDirectedGraph& graph)
		{
			class CEarliestTimeVisitor : public CVisitor
			{
				const CDirectedGraph& graph;
				CArrayEx<TYPE>& earliestTime;
			public:
				CEarliestTimeVisitor (const CDirectedGraph& _graph, CArrayEx<TYPE>& e) 
					: graph (_graph), earliestTime (e) {}
				
				void visit (CObjectEx& object)
				{
					NUMBER w = (CVertex&) (object);
					TYPE max = earliestTime [0];
					CIterator& p = graph.incidentEdges (w);
					while (!p.isDone ()) 
					{
						CWeightedEdge& edge = (CWeightedEdge&) (p.currentItem());
						TYPE& weight = (TYPE&)(edge.getWeight ());
						// CVertex& v = edge.secondEndPoint();
						CVertex& v = edge.firstEndPoint();
						const TYPE t = earliestTime [v] + weight;
						if (t > max) max = t;
						p.moveNext();
					}
					delete &p;
					earliestTime[w] = max;
				}
			};
			class CLatestTimeVisitor : public CVisitor
			{
				const CDirectedGraph& graph;
				CArrayEx<TYPE>& latestTime;
			public:
				CLatestTimeVisitor (const CDirectedGraph& _graph, CArrayEx<TYPE>& l) 
					: graph (_graph), latestTime (l) {}
				
				void visit (CObjectEx& object)
				{
					UINT numberOfVertices = graph.numberOfVertices();
					NUMBER w = (CVertex&) (object);
					TYPE min = latestTime[numberOfVertices -1];
					CIterator& p = graph.emanatingEdges(w);
					while (!p.isDone ()) 
					{
						CWeightedEdge& edge = (CWeightedEdge&) (p.currentItem());
						TYPE& weight = (TYPE&)(edge.getWeight ());
						CVertex& v = edge.secondEndPoint();
						const TYPE t = latestTime [v] - weight;
						if (t < min) min = t;
						p.moveNext();
					}
					delete &p;
					latestTime[w] = min;
				}
			};
			ASSERT(graph.isDirected());
			UINT const numberOfVertices = graph.numberOfVertices ();
			
			CArrayEx<TYPE> earliestTime (numberOfVertices);
			earliestTime [0] = 0;
			CGraphUtilities gu;
			
			gu.topologicalOrderTraversal (graph,CEarliestTimeVisitor(graph, earliestTime));
			CArrayEx<TYPE> latestTime (numberOfVertices);
			latestTime [numberOfVertices - 1] = earliestTime [numberOfVertices - 1];
			
			gu.depthFirstTraversal (graph,CPostOrder(CLatestTimeVisitor(graph,latestTime)),0);
			CGraphFactory graphFactory;
			CAbstractGraph& slackGraph = *(graphFactory.buildGraphAsLists(numberOfVertices,TRUE));
			CGraphBuilder builder(slackGraph);
			for (NUMBER v = 0; v < numberOfVertices; ++v)
				slackGraph.addVertex (*(builder.buildDefaultVertex()));
			CIterator& p = graph.getEdges ();
			while (!p.isDone ()) 
			{
				CWeightedEdge& edge = (CWeightedEdge&) (p.currentItem());
				TYPE& weight =(TYPE&) (edge.getWeight ());
				CVertex& v0 = edge.firstEndPoint() ;
				CVertex& v1 = edge.secondEndPoint();
				const TYPE slack = latestTime [v1] - earliestTime [v0] - weight; // maximum delay time
				slackGraph.addEdge(*(builder.buildWeightedEdge(v0, v1, *new TYPE(slack))));
				p.moveNext();
			}
			delete &p;
			CAbstractGraph*pResult = doDijkstra((const CDirectedGraph&)slackGraph,0);
			delete &slackGraph;
			return pResult;
		}
		
		CAbstractGraph* doBellmanFord(const CAbstractGraph&digraph,NUMBER vertex)
		{
			CVertex& source = digraph.selectVertex(vertex);
			UINT const numberOfVertices = digraph.numberOfVertices ();
			CArrayEx<CTableEntry> table (numberOfVertices);
			table[source].distance = 0;
			CIterator& edges = digraph.getEdges();
			for(UINT i = 1; i < numberOfVertices; i++)
			{
				edges.reset();
				while (!edges.isDone())
				{
					CWeightedEdge& e = (CWeightedEdge&) (edges.currentItem());
					NUMBER  source = e.firstEndPoint(),
						target = e.secondEndPoint();
					TYPE& weight = (TYPE&) (e.getWeight());
					const TYPE d = table [source].distance + weight;
					if (table [target].distance > d)
					{
						table [target].distance = d;
						table [target].predecessor = source;
					}
					edges.moveNext();
				}
			}
			edges.reset();
			while (!edges.isDone())
			{
				CWeightedEdge& e = (CWeightedEdge&) (edges.currentItem());
				TYPE& weight = (TYPE&) (e.getWeight());
				NUMBER  source = e.firstEndPoint(),
					target = e.secondEndPoint();
				const TYPE d = table[source].distance + weight;
				if (table [target].distance > d)
				{
					AfxMessageBox("Graph contains negative weight cycle");
					delete &edges;
					return NULL; // graph contains negative weight cycle
				}
				edges.moveNext();
			}
			return buildSingleSourceShortestPathGraph(numberOfVertices,source,table);
		}
		
		INT checkValidNetwork(CDirectedGraph&network,NUMBER&source,NUMBER&sink)
		{
			UINT numberOfVertices = network.numberOfVertices();
			CArrayEx<TYPE> flow(numberOfVertices);
			CArrayEx<UINT> inDegree(numberOfVertices);
			CArrayEx<UINT> outDegree(numberOfVertices);
			TYPE infiniteCapacity = 0;
			for(UINT v = 0; v < numberOfVertices; v++)
			{
				inDegree[v] = 0;
				outDegree[v] = 0;
				flow[v] = 0;
			}
			CLinkedList<NUMBER> sources;
			CLinkedList<NUMBER> sinks;
			CIterator& p = network.getEdges();
			for(; !p.isDone(); p.moveNext())
			{
				CNetworkEdge& e = (CNetworkEdge&)p.currentItem();
				NUMBER  from = e.firstEndPoint(),
						to = e.secondEndPoint();
				TYPE& weight = (TYPE&) (e.getWeight());
				TYPE& capacity = (TYPE&) (e.getCapacity());
				if (weight > capacity || weight < 0 || capacity < 0) 
				{
					delete&p;
					return INVALID;
				}
				infiniteCapacity = infiniteCapacity + capacity;
				flow[from] = flow[from] + weight;
				flow[to] = flow[to] - weight;
				inDegree[to]++; 
				outDegree[from]++;
			}
			delete&p;
			for(v = 0; v < numberOfVertices; v++)
			{
				if (inDegree[v] == 0)
				{
					if (outDegree[v] == 0) // isolated vertex
						continue;
					else //  a source
					{
						sources.append(v);
						continue;
					}
				}
				else // not a source and not an isolated vertex, check if it is a sink
					if (outDegree[v] == 0) 
					{
						sinks.append(v);
						continue;
					}
					else // it is a normal, check if it sastify conversation
						if ( flow[v] != 0)
							return INVALID;
			}
			// reach here ==> sastify conversation contraint
			UINT numberOfSources = sources.getCount(),
				 numberOfSinks = sinks.getCount();
			if (numberOfSources == 0) // iff numberOfSinks == 0
				return INVALID;
			UINT ret = VALID;
			CGraphBuilder builder(network);
			if ((numberOfSources > 1 || numberOfSinks > 1 && network.isFull())) 
				network.resize(numberOfVertices + 2);
			if (numberOfSources > 1) // multi source
			{
				ret |= REDUCE_SOURCE;
				network.addVertex(*(builder.buildDefaultVertex())); // build a super source with have id == numberOfVertices
				source = numberOfVertices++;
				for(const CLinkedList<NUMBER>::CListElement* pTmp = sources.head(); pTmp; pTmp = pTmp->next)
				{
					NUMBER s = pTmp->datum;
					network.addEdge(*(builder.buildNetworkEdge(source,s,*new TYPE(flow[s]),*new TYPE(infiniteCapacity))));
				}
			}
			else
				source = sources.first();
			if (numberOfSinks > 1)
			{
				ret |= REDUCE_SINK; // 1 | 2 == 3 ==>   REDUCE_SOURCE | REDUCE_SINK == REDUCE_BOTH
				network.addVertex(*(builder.buildDefaultVertex())); // build a super sink with have id == numberOfVertices
				sink = numberOfVertices++;
				for(const CLinkedList<NUMBER>::CListElement* pTmp = sinks.head(); pTmp; pTmp = pTmp->next)
				{
					NUMBER t = pTmp->datum;
					network.addEdge(*(builder.buildNetworkEdge(t,sink,*new TYPE(- flow[t]),*new TYPE(infiniteCapacity))));
				}
			}
			else
				sink = sinks.first();
			return ret;
		}

		CDirectedGraph* buildResidualNetwork(const CDirectedGraph&network)
		{
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
				NUMBER  source = e.firstEndPoint(),
						target = e.secondEndPoint();
				if (!pResult->selectEdge(source,target).isNull()) continue;
				TYPE& weight = (TYPE&)e.getWeight();
				TYPE& capacity = (TYPE&)e.getCapacity();
				EDGETYPE w = capacity - weight;
				CNetworkEdge& e1 = (CNetworkEdge&)network.selectEdge(target,source);
				if (e1.isNull())
				{
					if (w > 0) pResult->addEdge(*(builder.buildWeightedEdge(source,target,*new TYPE(w))));
					if (weight > 0) pResult->addEdge(*(builder.buildWeightedEdge(target,source,*new TYPE(weight))));
				}
				else
				{
					TYPE& weight1 = (TYPE&)e1.getWeight();
					w = w + weight1;
					if (w > 0) pResult->addEdge(*(builder.buildWeightedEdge(source,target,*new TYPE(w))));
				}
			}
			delete&iter;
			return (CDirectedGraph*)pResult;
		}

		CIterator& doEdmondsKarp(CDirectedGraph&network, NUMBER source, NUMBER sink)
		{
			class CMincutVisitor : public CVisitor
			{
				CLinkedList<CObjectEx*>& list;
				CDirectedGraph&network;
			public:
				CMincutVisitor(CDirectedGraph&g) 
					: network(g),list(*new CLinkedList<CObjectEx*>) {}
				void visit (CObjectEx& object) 
				{ 
					NUMBER vertex = (CVertex&)object;
					list.append(&network.selectVertex(vertex)); 
				}
				CIterator& getIterator() { return *new CListIterator(list); }
			};
			CMincutVisitor visitor(network);
			CIterator& iter = network.getEdges();
			for(; !iter.isDone(); iter.moveNext())
			{
				CNetworkEdge& e = (CNetworkEdge&)iter.currentItem();
				e.setWeight(*new TYPE(0));
			}
			delete&iter;
			// CDirectedGraph& g = *(buildResidualNetwork(network));
			for(;;) 
			{
				// use breadth first search to compute augmenting path
				CDirectedGraph& g = *(buildResidualNetwork(network));
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
				enqueued[source] = TRUE;
				queue.enqueue (const_cast<CVertex&> (g.selectVertex(source)));
				while (!queue.isEmpty () && !found)
				{
					CVertex& vertex = (CVertex&)queue.dequeue();
					// visit vertex
					if (vertex == sink) found = TRUE;
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
					CGraphUtilities gu;
					gu.breadthFirstTraversal(g,visitor,source);
					delete &g;
					break;
				}
				// found augmenting path => trace back
				INT tmpV = predecessor[sink];
				EDGETYPE cp = (TYPE&)((CWeightedEdge&)g.selectEdge(tmpV,sink)).getWeight();
				while (predecessor[tmpV] != -1)
				{
					EDGETYPE cf = (TYPE&)((CWeightedEdge&)g.selectEdge(predecessor[tmpV],tmpV)).getWeight();
					if (cf < cp)
						cp = cf;
					tmpV = predecessor[tmpV];
				}
				tmpV = sink;
				while (predecessor[tmpV] != -1)
				{
					CNetworkEdge& e = (CNetworkEdge&)network.selectEdge(predecessor[tmpV],tmpV);
					if (e.isNull())
					{
						CNetworkEdge& e1 = (CNetworkEdge&)network.selectEdge(tmpV,predecessor[v]);
						EDGETYPE w = (TYPE&)e1.getWeight();
						e1.setWeight(*new TYPE( w - cp));
					}
					else
					{
						EDGETYPE w = (TYPE&)e.getWeight();
						e.setWeight(*new TYPE( w + cp));
					}
					tmpV = predecessor[tmpV];
				}
				delete &g;
			}
			return visitor.getIterator();
		}
protected:
	CAbstractGraph* buildSingleSourceShortestPathGraph(UINT numberOfVertices,NUMBER source,const CArrayEx<CTableEntry>&table)
	{
		CGraphFactory graphFactory;
		CAbstractGraph* pResult = graphFactory.buildGraphAsLists(numberOfVertices,TRUE);
		CGraphBuilder builder(*pResult);
		for (NUMBER v = 0; v < numberOfVertices; ++v)
		{
			CVertex* pV = builder.buildWeightedVertex(*new TYPE(table [v].distance));
			pResult->addVertex(*pV);
		}
		for (v = 0; v < numberOfVertices; ++v)
			if (v != source)
			{
				NUMBER predecessor = table [v].predecessor;
				if (predecessor < numberOfVertices) 
				{
					CEdge* pE = builder.buildDefaultEdge(predecessor,v);
					pResult->addEdge(*pE);
				}
			}
		return pResult;
	}

	CAbstractGraph* buildAllPairsShortestPathGraph(UINT numberOfVertices,CArray2D<TYPE>&distance)
	{
		CGraphFactory graphFactory;
		CAbstractGraph* pResult = graphFactory.buildGraphAsMatrix(numberOfVertices,TRUE);
		CGraphBuilder builder(*pResult);
		for (UINT v = 0; v < numberOfVertices; ++v)
			pResult->addVertex (*builder.buildDefaultVertex());
		for (v = 0; v < numberOfVertices; ++v)
			for (NUMBER w = 0; w < numberOfVertices; ++w)
				if (distance [v][w] != INFINITE_VALUE)
				{
					CEdge*pE = builder.buildWeightedEdge(v, w,
						*new TYPE (distance[v][w]));
					pResult->addEdge(*pE);
				}
		return pResult;
	}
};

#endif // !defined(AFX_ALGORITHMS_H__336C1A1F_2138_4663_BCD4_902E3109EAD4__INCLUDED_)