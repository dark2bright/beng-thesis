// GraphUtilities.cpp: implementation of the CGraphUtilities class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thesis.h"
#include "GraphUtilities.h"
#include "LinkedQueue.h"
#include "PreOrder.h"
#include "Array2D.h"
#include "GraphFactory.h"
#include "NullIterator.h"
#include "NetworkEdge.h"
#include "SortableLinkedList.h"
#include "coloredvertex.h"
#include "GraphFactory.h"
#include "GraphBuilder.h"
#include "LinkedStack.h"
#include "StackAsArray.h"
#include "Wrapper.h"
#include "WrapperUtilities.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGraphUtilities::CCountingVisitor::CCountingVisitor () : m_uCount (0)
{
}

VOID CGraphUtilities::CCountingVisitor::visit (CObjectEx&) 
{
	++m_uCount; 
}

UINT CGraphUtilities::CCountingVisitor::count()const
{ 
	return m_uCount; 
}

CGraphUtilities::CSearchingVisitor::CSearchingVisitor(CObjectEx&object)
: target(object)
{
	found = FALSE;
}

void CGraphUtilities::CSearchingVisitor::visit (CObjectEx&object)
{
	if (object == target)found = TRUE;
}

BOOL CGraphUtilities::CSearchingVisitor::isDone()const
{
	return found;
}

CGraphUtilities::_tagDFSCUTVERTEX::_tagDFSCUTVERTEX()
{
	treeEdges = 0;
	separating = FALSE;
}

CGraphUtilities::_tagDFSBRIDGEEDGE::_tagDFSBRIDGEEDGE()
{
	discover = -1; // undiscovered
	predecessor = -1; // no predcessor
}

CGraphUtilities::CGraphUtilities()
{
}

VOID CGraphUtilities::depthFirstTraversal(const CAbstractGraph&graph,CPrePostVisitor &visitor, const CVertex &vertex, CArrayEx<BOOL>&visited) const
{
	if (visitor.isDone ())
		return;
	visitor.preVisit(const_cast<CVertex&>(vertex));
	visited [vertex] = TRUE;
	CIterator& p = graph.emanatingEdges (vertex);
	while (!p.isDone ()){
		CEdge& edge = (CEdge&)(p.currentItem());
		CVertex& to = edge.mate (vertex);
		if (!visited [to])
			depthFirstTraversal (graph,visitor, to, visited);
		p.moveNext();
	}
	delete &p;
	visitor.postVisit (const_cast<CVertex&>(vertex));
}

VOID CGraphUtilities::depthFirstTraversal(const CAbstractGraph &graph, CPrePostVisitor &visitor, NUMBER start) const
{
	UINT numberOfVertices = graph.numberOfVertices();
	CArrayEx<BOOL> visited (numberOfVertices);
	for (NUMBER v = 0; v < numberOfVertices; ++v)
		visited [v] = FALSE;
	depthFirstTraversal (graph,
		visitor, const_cast<CVertex&>(graph.selectVertex(start)), visited);
}

VOID CGraphUtilities::depthFirstTraversal(const CAbstractGraph &graph, CPrePostVisitor &visitor) const
{
	UINT numberOfVertices = graph.numberOfVertices();
	CArrayEx<BOOL> visited (numberOfVertices);
	for (NUMBER v = 0; v < numberOfVertices; ++v)
		visited [v] = FALSE;
	for (v = 0; v < numberOfVertices; ++v)
		if (!visited[v])
			depthFirstTraversal (graph,
				visitor, const_cast<CVertex&>(graph.selectVertex(v)), visited);
}
// non-recursive version of depthFirstTraversal
// can't implement preOrder with non-recursive recursion of depthFirstTraversal
// because don't know when all of child is visit.
VOID CGraphUtilities::depthFirstTraversalEx(const CAbstractGraph &graph, CPrePostVisitor &visitor, NUMBER start) const
{
	//* have logic error ???
	UINT numberOfVertices = graph.numberOfVertices();
	CArrayEx<BOOL> visited (numberOfVertices);
	for (NUMBER v = 0; v < numberOfVertices; ++v)
		visited[v] = FALSE;
	CVertex& s = graph.selectVertex(start);
	CStack&stack = *new CStackAsArray(numberOfVertices);
	stack.push(s);
	// visitor.preVisit(s); // => c'est faux
	visited[s] = TRUE;
	while (!stack.isEmpty() && !visitor.isDone())
	{
		CVertex&vertex = (CVertex&)stack.top();
		CIterator& p = graph.emanatingEdges(vertex);
		while (!p.isDone()) 
		{
			CVertex&target = ((CEdge&)p.currentItem()).secondEndPoint();
			if (!visited[target])
			{
				stack.push(target);
				// visitor.preVisit(target); // => c'est faux 
				visited[target] = TRUE;
			}
			p.moveNext();
		}
		delete&p;
		if (vertex == stack.top())
		{
			stack.pop();
			visitor.postVisit(vertex);
		}
	}
	delete &stack;
	//*/
}

// for directed graph => it is strongly connected
BOOL CGraphUtilities::isConnected(const CAbstractGraph &graph)const
{
	UINT numberOfVertices = graph.numberOfVertices();
	if (graph.isDirected())
	{
		for (NUMBER v = 0; v < numberOfVertices; ++v)
		{
			CCountingVisitor visitor;
			depthFirstTraversal (graph,
				CPreOrder (visitor), graph.selectVertex (v));
			if (visitor.count () != numberOfVertices)
				return FALSE;
		}
		return TRUE;
	}
	else
	{
		CCountingVisitor visitor;
		depthFirstTraversal (graph,CPreOrder (visitor), graph.selectVertex (0));
		return visitor.count() == numberOfVertices;
	}
	// Never reach here => Don't care return true or false
	return TRUE;
}

VOID CGraphUtilities::topologicalOrderTraversal(const CDirectedGraph &digraph, CVisitor &visitor)const
{
	UINT numberOfVertices = digraph.numberOfVertices();
	CArrayEx<UINT> inDegree (numberOfVertices);
	for (NUMBER v = 0; v < numberOfVertices; ++v)
		inDegree [v] = 0;
	// Calculate the inDegree of all vertex
	CIterator& p = digraph.getEdges ();
	while (!p.isDone ()) {
		CEdge& edge = (CEdge&)(p.currentItem());
		++inDegree [edge.secondEndPoint()];
		p.moveNext();
	}
	delete &p;
	// Enqueue all vertex having indegree = 0(i.e It's source)
	CQueue& queue = *new CLinkedQueue ();
	queue.rescindOwnership ();
	for (v = 0; v < numberOfVertices; ++v)
		if (inDegree [v] == 0)
			queue.enqueue (digraph.selectVertex (v));
	while (!queue.isEmpty () && !visitor.isDone ())
	{
		// Get the vertex from queue and find all of edge emanating from it. 
		CVertex& vertex = (CVertex&)(queue.dequeue ());
		visitor.visit (vertex);
		CIterator& q = digraph.emanatingEdges (vertex);
		while (!q.isDone ()) {
			CEdge& edge = (CEdge&)(q.currentItem());
			CVertex& to = edge.secondEndPoint();
			// Decrese indegree of it's mate
			if (--inDegree [to] == 0)
				queue.enqueue (to);
			q.moveNext();
		}
		delete &q;
	}
	delete &queue;
}

VOID CGraphUtilities::breadthFirstTraversal(const CAbstractGraph &graph, CVisitor &visitor, NUMBER start) const
{
	UINT numberOfVertices = graph.numberOfVertices();
	CArrayEx<BOOL> enqueued (numberOfVertices);
	for (NUMBER v = 0; v < numberOfVertices; ++v)
		enqueued [v] = FALSE;
	
	CQueue& queue = *new CLinkedQueue ();
	queue.rescindOwnership ();
	
	enqueued[start] = TRUE;
	queue.enqueue (graph.selectVertex(start));
	while (!queue.isEmpty () && !visitor.isDone ())
	{
		CVertex& vertex = (CVertex&)queue.dequeue();
		visitor.visit (vertex);
		CIterator& p = graph.emanatingEdges (vertex);
		while (!p.isDone ()) {
			CEdge& edge = (CEdge&)(p.currentItem());
			CVertex& to = edge.mate (vertex);
			if (!enqueued [to])
			{
				enqueued[to] = TRUE;
				queue.enqueue (to);
			}
			p.moveNext();
		}
		delete &p;
	}
	delete &queue;
}

VOID CGraphUtilities::breadthFirstTraversal(const CAbstractGraph &graph, CVisitor &visitor) const
{
	UINT numberOfVertices = graph.numberOfVertices();
	CArrayEx<BOOL> enqueued (numberOfVertices);
	for (NUMBER v = 0; v < numberOfVertices; ++v)
		enqueued [v] = FALSE;
	for (v = 0; v < numberOfVertices; ++v)
		if (!enqueued[v]) // v start a connected component
		{
			CQueue& queue = *new CLinkedQueue ();
			queue.rescindOwnership ();

			enqueued[v] = TRUE;
			queue.enqueue (graph.selectVertex(v));
			while (!queue.isEmpty () && !visitor.isDone ())
			{
				CVertex& vertex = (CVertex&)queue.dequeue();
				visitor.visit (vertex);
				CIterator& p = graph.emanatingEdges (vertex);
				while (!p.isDone ()) {
					CEdge& edge = (CEdge&)(p.currentItem());
					CVertex& to = edge.mate (vertex);
					if (!enqueued [to])
					{
						enqueued[to] = TRUE;
						queue.enqueue (to);
					}
					p.moveNext();
				}
				delete &p;
			}
			delete &queue;
		}
}

BOOL CGraphUtilities::isCyclic(const CAbstractGraph &graph)const
{
	CCountingVisitor visitor;
	if (graph.isDirected())
	{
		topologicalOrderTraversal (((const CDirectedGraph&)graph),visitor);
		return visitor.count () != graph.numberOfVertices();
	}
	else // use breadth first search to detect cycle.
	{
		UINT numberOfVertices = graph.numberOfVertices();
		CArrayEx<INT> depth(numberOfVertices);
		CArrayEx<INT> predecessor(numberOfVertices);
		for (NUMBER v = 0; v < numberOfVertices; ++v)
		{
			depth[v] = -1;
			predecessor[v] = -1;
		}
		BOOL bResult = FALSE;
		for (v = 0; !bResult && v < numberOfVertices; ++v)
		{
			if (depth[v] == -1) // v bat dau mot connected component
			{
				CVertex& start = graph.selectVertex(v);
				CQueue& queue = *new CLinkedQueue ();
				queue.rescindOwnership ();
				
				depth[v] = 0;
				queue.enqueue (const_cast<CVertex&> (start));
				while (!bResult && !queue.isEmpty ())
				{
					CVertex& vertex = (CVertex&)queue.dequeue();
					CIterator& p = graph.emanatingEdges (vertex);
					while (!p.isDone ()) {
						CEdge& edge = (CEdge&)(p.currentItem());
						CVertex& to = edge.mate (vertex);
						if (depth [to] == -1)
						{
							depth[to] = depth[vertex]+1;
							predecessor[to] = vertex;
							queue.enqueue (to);
						}
						else 
						{
							// if (predecessor[vertex] != to && depth[to] < depth[vertex]) 
							if (predecessor[vertex] != to) 
							{
								bResult = TRUE;
								break;
							}
						}
						p.moveNext();
					}
					delete &p;
				}
				delete &queue;
			}
		}
		return bResult;
	}
	// Never reach here
	return TRUE;
}

BOOL CGraphUtilities::isWeaklyConnected(const CAbstractGraph&graph)const
{
	if (!graph.isDirected()) return isConnected(graph);
	// for directed graph
	UINT numberOfVertices = graph.numberOfVertices();
	for (NUMBER v = 0; v < numberOfVertices; ++v)
	{
		CCountingVisitor visitor;
		depthFirstTraversal(graph,
			CPreOrder (visitor), graph.selectVertex (v));
		if (visitor.count () == numberOfVertices)
			return TRUE;
	}
	return FALSE;
}

BOOL CGraphUtilities::eulerianTraversal(const CAbstractGraph &graph, CVisitor &visitor) const
{
	
	INT current = isEulerian(graph);
	if (current == -1) return FALSE;
	CAbstractGraph& fake = copyGraph(graph);
	for(;;)
	{
		NUMBER mate = current;
		BOOL bChosen = FALSE;
		CEdge*tmpEdge = NULL;
		CIterator& emanatingEdges = fake.emanatingEdges(current);
		//* visit it
		CVertex& vertex = fake.selectVertex(current);
		visitor.visit(vertex);
		//*/
		for(;!emanatingEdges.isDone();emanatingEdges.moveNext()) 
		{
			CEdge& edge = (CEdge&)emanatingEdges.currentItem();
			if (!bChosen) 
			{
				bChosen = TRUE;
				tmpEdge = &((CEdge&)edge.clone());
				mate = edge.secondEndPoint();
				fake.removeEdge(current,mate);
				if (hasPath(fake,current,mate)) // this edge is not a bridge => select it
				{
					delete tmpEdge;
					tmpEdge = NULL;
					break;
				}else continue;
			}
			else // already chose a edge but it is bridge => test this one
			{
				fake.addEdge(*tmpEdge);
				tmpEdge = &((CEdge&)edge.clone());
				mate = edge.secondEndPoint();
				fake.removeEdge(current,mate);
				if (hasPath(fake,current,mate)) // this edge is not a bridge
				{
					delete tmpEdge;
					tmpEdge = NULL;
					break;
				}else continue;
			}
		}
		delete &emanatingEdges;
		if (!bChosen) 
		{
			delete &fake;
			return TRUE;
		}
		if (tmpEdge) delete tmpEdge;
		current = mate;
	}
}

CAbstractGraph& CGraphUtilities::copyGraph(const CAbstractGraph &graph) const
{
	UINT numberOfVertices = graph.numberOfVertices();
	CGraphFactory factory;
	CAbstractGraph* pResult = factory.buildGraphAsMatrix(numberOfVertices + 2,graph.isDirected());
	CIterator& vertexIter = graph.getVertices();
	while (!vertexIter.isDone()) 
	{
		CVertex& vertex = (CVertex&)vertexIter.currentItem().clone();
		pResult->addVertex(vertex);
		vertexIter.moveNext();
	}
	delete &vertexIter;
	CIterator& edgeIter = graph.getEdges();
	for (;!edgeIter.isDone();edgeIter.moveNext()) 
	{
		CEdge& edge = (CEdge&)edgeIter.currentItem().clone();
		NUMBER  from = edge.firstEndPoint(),
				to = edge.secondEndPoint();
		CEdge& oldedge = pResult->selectEdge(from,to);
		if (!oldedge.isNull()) 
		{
			delete &edge;
			continue;
		}
		edge.setEndPoints(pResult->selectVertex(from),pResult->selectVertex(to));
		pResult->addEdge(edge);
	}
	delete &edgeIter;
	return *pResult;
}

BOOL CGraphUtilities::hasPath(const CAbstractGraph &graph, NUMBER from, NUMBER to)const
{
	CVertex& source = graph.selectVertex(to);
	CSearchingVisitor visitor(source);
	breadthFirstTraversal(graph,visitor,from);
	return visitor.isDone();
}

CIterator& CGraphUtilities::getPath(const CAbstractGraph &graph, NUMBER from, NUMBER to)const
{
	if (from == to)return *new CNullIterator;
	UINT numberOfVertices = graph.numberOfVertices();
	CArrayEx<BOOL> enqueued (numberOfVertices);
	CArrayEx<BOOL> predecessor(numberOfVertices);
	for (NUMBER v = 0; v < numberOfVertices; ++v)
	{
		enqueued [v] = FALSE;
		predecessor [v] = -1;
	}
	CQueue& queue = *new CLinkedQueue ();
	queue.rescindOwnership ();
	enqueued[from] = TRUE;
	queue.enqueue (const_cast<CVertex&> (graph.selectVertex(from)));
	while (!queue.isEmpty ())
	{
		CVertex& vertex = (CVertex&)queue.dequeue();
		if (vertex == to) 
		{
			CLinkedList<CObjectEx*>& list = *new CLinkedList<CObjectEx*>;
			UINT tmp = vertex;
			while (tmp != -1)
			{
				list.prepend(&graph.selectVertex(tmp));
				tmp = predecessor[tmp];
			}
			delete &queue;
			return *new CListIterator(list);
		}
		CIterator& p = graph.emanatingEdges (vertex);
		while (!p.isDone ()) {
			CEdge& edge = (CEdge&)(p.currentItem());
			CVertex& to = edge.mate (vertex);
			if (!enqueued [to])
			{
				enqueued[to] = TRUE;
				queue.enqueue (to);
				predecessor[to] = vertex;
			}
			p.moveNext();
		}
		delete &p;
	}
	delete &queue;
	return *new CNullIterator;
}


// return -1 if not an Eulerian graph else return start vertex
INT CGraphUtilities::isEulerian(const CAbstractGraph &graph) const
{
	if (!isWeaklyConnected(graph))
	{
		AfxMessageBox("This is not an eulerian graph");
		return -1;
	}
	// calculate in and out degree of graph
	UINT numberOfVertices = graph.numberOfVertices();
	CArrayEx<UINT> inDegree(numberOfVertices),outDegree(numberOfVertices);
	for(UINT j = 0; j < numberOfVertices; j++)
		inDegree[j] = outDegree[j] = 0;
	CIterator& edgeIter = graph.getEdges();
	while (!edgeIter.isDone()) 
	{
		CEdge& edge = (CEdge&)edgeIter.currentItem();
		NUMBER  from = edge.firstEndPoint(),
			to = edge.secondEndPoint();
		outDegree[from]++;
		inDegree[to]++;
		edgeIter.moveNext();
	}
	delete &edgeIter;
	UINT ends[3], nIndex = 0;
	// test if this graph is eulerian graph
	if (graph.isDirected()) 
		for(UINT i = 0; i < numberOfVertices; i++)
		{
			if (inDegree[i] != outDegree[i])
			{
				ends[nIndex] = i;
				nIndex++;
				if (nIndex > 2)
				{
					AfxMessageBox("This is not an eulerian graph");
					return -1;
				}
			}
		}
		else // inDegree == outDegree = valance of undirected graph
			for(UINT i = 0; i < numberOfVertices; i++)
				if (inDegree[i] %2 != 0)
				{
					ends[nIndex] = i;
					nIndex++;
					if (nIndex > 2)
					{
						AfxMessageBox("This is not an eulerian graph");
						return -1;
					}
				}
	return (nIndex == 2) ? ends[0] : 0; // if circuit start at a abitrary vertex ( 0 )				
}

CIterator& CGraphUtilities::getArticulationPoints(const CAbstractGraph &graph) const
{
	UINT numberOfVertices = graph.numberOfVertices();
	CArrayEx<DFSCUTVERTEX> data(numberOfVertices);
	UINT time;
	CLinkedList<CObjectEx*>&list = *new CLinkedList<CObjectEx*>;
	for(UINT i = 0; i < numberOfVertices; i++)
		if (data[i].discover < 0) // undiscover
		{
			time = 0; // i is root of an DFS tree
			dfsArticulationPoint(graph,i,time,data,list);
		}
	return *new CListIterator(list);
}

void CGraphUtilities::dfsArticulationPoint(const CAbstractGraph&graph,NUMBER vertex,UINT&time,CArrayEx<DFSCUTVERTEX>&data,CLinkedList<CObjectEx*>&list)const
{
	data[vertex].discover = data[vertex].low = time++;
	CIterator& emanatingEdges = graph.emanatingEdges(vertex);
	DFSCUTVERTEX &current = data[vertex];
	for(;!emanatingEdges.isDone(); emanatingEdges.moveNext())
	{
		NUMBER mate = ((CEdge&)emanatingEdges.currentItem()).secondEndPoint();
		DFSCUTVERTEX &child = data[mate];
		if (current.predecessor == mate)continue;
		if (child.discover < 0) // undiscover
		{
			child.predecessor = vertex;
			current.treeEdges++;
			dfsArticulationPoint(graph,mate,time,data,list);
			current.low = min(current.low,child.low);
			if (child.low >= current.discover)
				current.separating = TRUE;
		}
		else
			if (child.discover < current.discover)
				current.low = min(current.low,child.discover);
	}
	delete &emanatingEdges;
	if (data[vertex].discover == 0 // vertex is root
		&& data[vertex].treeEdges <= 1) // and has only one tree-edges
			data[vertex].separating = FALSE;
	if (data[vertex].separating == TRUE) list.append(&(graph.selectVertex(vertex)));
}

void CGraphUtilities::dfsBiconnectedComponent(const CAbstractGraph&graph,NUMBER vertex,UINT&time,CArrayEx<DFSCUTVERTEX>&data,CStack&stack,CLinkedList<CListIterator*>&result)const
{
	UINT mate;
	data[vertex].discover = data[vertex].low = time++;
	DFSCUTVERTEX &current = data[vertex];
	CIterator& emanatingEdges = graph.emanatingEdges(vertex);
	for(;!emanatingEdges.isDone(); emanatingEdges.moveNext())
	{
		CEdge& edge = (CEdge&)emanatingEdges.currentItem();
		NUMBER to = edge.secondEndPoint();
		DFSCUTVERTEX &child = data[to];
		if (current.predecessor == to)continue;
		if (child.discover < 0) // undiscover
		{
			stack.push(edge); // push tree edge
			child.predecessor = vertex;
			current.treeEdges++;
			dfsBiconnectedComponent(graph,to,time,data,stack,result);
			current.low = min(current.low,child.low);
			if (child.low >= current.discover)
			{
				current.separating = TRUE;
				mate = to;
				if (child.low > current.discover) // for bridge edge,just remove since it will not belong to any biconnected component
				{
					if (!stack.isEmpty()) stack.pop();
				}
				else
					if (data[vertex].discover > 0) // vertex is not a root of DFS tree so it is a cut vertex
						popStackUntil(stack,vertex,mate,result);
			}
		}
		else
			if (child.discover < current.discover)
			{
				current.low = min(current.low,child.discover);
				stack.push(edge); // push back edge
			}
	}
	delete &emanatingEdges;	
	if (data[vertex].discover == 0) // vertex is root
		if (data[vertex].treeEdges <= 1) // and has only one tree-edges
			data[vertex].separating = FALSE;
		else // this root is articulation point 
			popStackUntil(stack,vertex,mate,result);		
}

// find a cycle from source -> target
BOOL CGraphUtilities::dfsHamilton(const CAbstractGraph&graph,CStack&stack,CLinkedList<CObjectEx*>&list,CArrayEx<BOOL>&visited,NUMBER source, NUMBER target, UINT length)const
{
	if (source == target) 
		return (length == 0);
    visited[source] = TRUE;
    CIterator& p = graph.emanatingEdges(source);
    for (; !p.isDone(); p.moveNext())
	{
		CEdge& e = (CEdge&)p.currentItem();
		NUMBER tmp = e.secondEndPoint(); 
		if (!visited[tmp])
		{
			stack.push(graph.selectEdge(source,tmp));
			if (dfsHamilton(graph,stack,list,visited,tmp,target, length - 1)) 
			{
				while (!stack.isEmpty())
				{
					CEdge& edge = (CEdge&)stack.pop();
					list.append(&edge.secondEndPoint());
				}
				delete &p;
				return TRUE;
			}
			NUMBER s = graph.numberOfVertices(); // ==> there's no vertex having id == s
			while (!stack.isEmpty() && s != tmp)
			{
				CEdge& edge = (CEdge&)stack.pop();
				s = edge.secondEndPoint();
			}
		}
	}
	delete &p;
	visited[source] = FALSE;
	return FALSE;			
}

void CGraphUtilities::dfsConnectedComponent(const CAbstractGraph&graph,NUMBER v,UINT& cnt,UINT&scnt,CArrayEx<INT>&pre,CArrayEx<INT>&id,CStack&s,CStack&p)const
{
	pre[v] = cnt++;
	s.push(graph.selectVertex(v));
	p.push(graph.selectVertex(v));
	CIterator& iter = graph.emanatingEdges(v);
	for ( ; !iter.isDone(); iter.moveNext()) 
	{
		CEdge& e = (CEdge&)iter.currentItem();
		CVertex& w = e.secondEndPoint();
		if (pre[w] == -1) dfsConnectedComponent(graph,w,cnt,scnt,pre,id,s,p);
		else 
			if(id[w] == -1)
				while (pre[(CVertex&)p.top()] > pre[w]) p.pop();
	}
	delete &iter;
	if ((CVertex&)p.top() == v) 
		p.pop(); 
	else return;
	NUMBER top;
	do 
	{ 
		id[top = (CVertex&)s.pop()] = scnt; 
	} while (top != v);
	scnt++;
}

void CGraphUtilities::dfsBridgeEdge(const CAbstractGraph&graph,NUMBER vertex,UINT&time,CArrayEx<DFSBRIDGEEDGE>&data,CLinkedList<CListIterator*>&result)const
{
	data[vertex].discover = data[vertex].low = time++;
	CIterator& emanatingEdges = graph.emanatingEdges(vertex);
	DFSBRIDGEEDGE&current = data[vertex];
	for(;!emanatingEdges.isDone(); emanatingEdges.moveNext())
	{
		CEdge& edge = (CEdge&)emanatingEdges.currentItem();
		NUMBER mate = edge.secondEndPoint();
		DFSBRIDGEEDGE &child = data[mate];
		if (current.predecessor == mate)continue;
		if (child.discover < 0) // undiscover
		{
			child.predecessor = vertex;
			dfsBridgeEdge(graph,mate,time,data,result);
			current.low = min(current.low,child.low);
			// if (child.low >= current.discover) => C'est faux.
			if (child.low > current.discover)
			{
				CLinkedList<CObjectEx*>&list = *new CLinkedList<CObjectEx*>;
				list.append(&edge);
				result.append(new CListIterator(list));
			}	
		}
		else
			if (child.discover < current.discover)
				current.low = min(current.low,child.discover);
	}
	delete &emanatingEdges;
}

UINT CGraphUtilities::colorGraph(const CAbstractGraph&graph,CVisitor&visitor)const
{
	if (graph.isDirected()) return 0; 
	UINT numberOfVertices = graph.numberOfVertices();
	CArrayEx<CColoredVertexPtr> array(numberOfVertices);
	for(UINT i = 0; i < numberOfVertices; i++)
		array[i].create(i);
	CIterator& edgeIter = graph.getEdges();
	while (!edgeIter.isDone()) 
	{
		CEdge& edge = (CEdge&)edgeIter.currentItem();
		NUMBER  from = edge.firstEndPoint();
		array[from].datum->valance++;
		edgeIter.moveNext();
	}
	delete &edgeIter;
	UINT currentColor = 0;
	CSortableLinkedList<CColoredVertexPtr> list;
	for(i = 0; i < numberOfVertices; i++) list.append(array[i]);
	list.sort(FALSE); // sort descendant
	while (!list.isEmpty()) 
	{
		CLinkedList<UINT>lstTmp;
		const CLinkedList<CColoredVertexPtr>::CListElement* head = list.head();
		head->datum.datum->color = currentColor;
		visitor.visit(const_cast<CColoredVertexPtr&>(head->datum));
		list.extract(head);
		lstTmp.append(head->datum.datum->vertex);
		const CLinkedList<CColoredVertexPtr>::CListElement*pTmp = list.head();
		while (pTmp !=0)
		{
			LPCOLOREDVERTEX tmp = pTmp->datum.datum;
			BOOL bConnected = FALSE;
			CIterator& emanatingEdges = graph.emanatingEdges(tmp->vertex);
			for(; !emanatingEdges.isDone(); emanatingEdges.moveNext()) 
			{
				UINT target = ((CEdge&)emanatingEdges.currentItem()).secondEndPoint();
				if (lstTmp.contain(target))
				{
					bConnected = TRUE;
					break;
				}
			}
			delete &emanatingEdges;
			if (!bConnected){
				tmp->color = currentColor;
				visitor.visit((CColoredVertexPtr&)pTmp->datum);
				list.extract(pTmp);
				lstTmp.append(pTmp->datum.datum->vertex);
				const CLinkedList<CColoredVertexPtr>::CListElement*pNext = pTmp->next;
				delete pTmp;
				pTmp = pNext;
				continue;			
			}
			pTmp = pTmp->next;
		}
		currentColor++;
		delete head;
	}
	return currentColor;
}

CIterator& CGraphUtilities::getCycle(const CAbstractGraph&graph,NUMBER start)const
{
	UINT numberOfVertices = graph.numberOfVertices();
	CArrayEx<BOOL> enqueued (numberOfVertices);
	CArrayEx<BOOL> predecessor(numberOfVertices);
	for (NUMBER v = 0; v < numberOfVertices; ++v)
	{
		enqueued [v] = FALSE;
		predecessor [v] = -1;
	}
	UINT length = 0; // length of cycle
	CQueue& queue = *new CLinkedQueue ();
	queue.rescindOwnership ();
	enqueued[start] = TRUE;
	queue.enqueue (const_cast<CVertex&> (graph.selectVertex(start)));
	while (!queue.isEmpty ())
	{
		CVertex& vertex = (CVertex&)queue.dequeue();
		CIterator& p = graph.emanatingEdges (vertex);
		while (!p.isDone ()) {
			CEdge& edge = (CEdge&)(p.currentItem());
			CVertex& to = edge.mate (vertex);
			if (!enqueued [to])
			{
				enqueued[to] = TRUE;
				queue.enqueue (to);
				predecessor[to] = vertex;
			}
			else 
				if (to == start) 
				{
					CLinkedList<CObjectEx*>& list = *new CLinkedList<CObjectEx*>;
					list.append(&graph.selectEdge(vertex,start));
					UINT tmp = vertex;
					while (predecessor[tmp] != -1)
					{
						list.prepend(&graph.selectEdge(predecessor[tmp],tmp));
						tmp = predecessor[tmp];
					}
					delete &p;
					delete &queue;
					return *new CListIterator(list);
				}
			p.moveNext();
		}
		delete &p;
	}
	delete &queue;
	return *new CNullIterator;
}	

// Search for cycles base on BFS
CIterator& CGraphUtilities::getCycles(const CAbstractGraph&graph)const
{
	CLinkedList<CListIterator*>&result = *new CLinkedList<CListIterator*>;
	UINT numberOfVertices = graph.numberOfVertices();
	// for directed graph
	if (graph.isDirected()) 
	{
		CArrayEx<UINT> inDegree (numberOfVertices);
		CArrayEx<UINT> outDegree (numberOfVertices);
		for (NUMBER v = 0; v < numberOfVertices; ++v)
		{
			inDegree[v] = 0;
			outDegree[v] = 0;
		}
		// Calculate the inDegree of all vertex
		CIterator& p = graph.getEdges ();
		while (!p.isDone ()) {
			CEdge& edge = (CEdge&)(p.currentItem());
			++inDegree[edge.secondEndPoint()];
			++outDegree[edge.firstEndPoint()];
			p.moveNext();
		}
		delete &p;
		// Enqueue all vertex having indegree = 0(i.e It's source)
		CQueue& queue = *new CLinkedQueue ();
		queue.rescindOwnership ();
		for (v = 0; v < numberOfVertices; ++v)
			if (inDegree [v] == 0)
				queue.enqueue (graph.selectVertex (v));
		UINT count = 0;
		while (!queue.isEmpty ())
		{
			// Get the vertex from queue and find all of edge emanating from it. 
			CVertex& vertex = (CVertex&)(queue.dequeue ());
			count++;
			CIterator& q = graph.emanatingEdges (vertex);
			while (!q.isDone ()) {
				CEdge& edge = (CEdge&)(q.currentItem());
				CVertex& to = edge.secondEndPoint();
				// Decrese indegree of it's mate
				if (--inDegree [to] == 0)
					queue.enqueue (to);
				q.moveNext();
			}
			delete &q;
		}
		if (count < numberOfVertices) // cyclic
		{
			for (v = 0; v < numberOfVertices; ++v)
				if (outDegree [v] == 0)
					queue.enqueue (graph.selectVertex (v));
			while (!queue.isEmpty ())
			{
				// Get the vertex from queue and find all of edge emanating from it. 
				CVertex& vertex = (CVertex&)(queue.dequeue ());
				count++;
				CIterator& q = graph.incidentEdges(vertex);
				while (!q.isDone ()) {
					CEdge& edge = (CEdge&)(q.currentItem());
					CVertex& from = edge.firstEndPoint();
					// Decrese indegree of it's mate
					if (--outDegree [from] == 0)
						queue.enqueue (from);
					q.moveNext();
				}
				delete &q;
			}
			delete &queue;
			for (v = 0; v < numberOfVertices; ++v)
				if (outDegree [v] > 0 && inDegree[v] > 0 )
				{
					CIterator& cycle = getCycle(graph,v);
					result.append((CListIterator*)&cycle);
					break;
				}
			return *new CListIterator((CLinkedList<CObjectEx*>&)result);
		}
		delete &queue;
		delete &result;
		return *new CNullIterator;
	}
	// for undirected graph
	CArrayEx<INT> depth(numberOfVertices);
	CArrayEx<INT> predecessor(numberOfVertices);
	for (NUMBER v = 0; v < numberOfVertices; ++v)
	{
		depth[v] = -1;
		predecessor[v] = -1;
	}
	BOOL bResult = FALSE;
	for (v = 0; v < numberOfVertices; ++v)
	{
		if (depth[v] < 0) // v bat dau mot connected component
		{
			CQueue& queue = *new CLinkedQueue ();
			queue.rescindOwnership ();
			depth[v] = 0;
			queue.enqueue (const_cast<CVertex&> (graph.selectVertex(v)));
			while (!queue.isEmpty ())
			{
				CVertex& vertex = (CVertex&)queue.dequeue();
				CIterator& p = graph.emanatingEdges (vertex);
				for (; !p.isDone (); p.moveNext()) {
					CEdge& edge = (CEdge&)(p.currentItem());
					CVertex& to = edge.mate (vertex);
					if (depth [to] == -1)
					{
						depth[to] = depth[vertex]+1;
						predecessor[to] = vertex;
						queue.enqueue (to);
					}
					else 
					{
						if (predecessor[vertex] != to) 
						{
							NUMBER  tmp1 = vertex, 
								tmp2 = to;
							if  ( depth[tmp2] < depth[tmp1] ||
								 (depth[tmp1] == depth[tmp2] && tmp1 > tmp2)
								) 
								continue; // if not continue => redundancy
							CLinkedList<CObjectEx*>&cycleList = *new CLinkedList<CObjectEx*>;
							cycleList.append(&graph.selectEdge(vertex,to));
							int count = 0;
							while (depth[tmp1] < depth[tmp2])
							{
								cycleList.prepend(&graph.selectEdge(predecessor[tmp2],tmp2));
								tmp2 = predecessor[tmp2];
								count++;
							}
							// reach here => depth[tmp1] == depth[tmp2]
							CEdge&e = graph.selectEdge(tmp1,tmp2);
							if (!e.isNull() && count > 0) // if count == 0 ==> only have an edge
							{
								cycleList.append(&e);
							}
							else
								while (tmp1 != tmp2) 
								{
									cycleList.append(&graph.selectEdge(predecessor[tmp1],tmp1));
									cycleList.prepend(&graph.selectEdge(predecessor[tmp2],tmp2));
									tmp1 = predecessor[tmp1];
									tmp2 = predecessor[tmp2];
								}
							result.append(new CListIterator(cycleList));
						}
					}
				}
				delete &p;
			}
			delete &queue;
		}
	}
	return *new CListIterator((CLinkedList<CObjectEx*>&)result);
}

CIterator& CGraphUtilities::getHamiltonPath(const CAbstractGraph&graph, NUMBER source,NUMBER target)const
{
	UINT numberOfVertices = graph.numberOfVertices();
	CArrayEx<BOOL> visited(numberOfVertices);
	for(UINT  v = 0 ; v < numberOfVertices; v++)
		visited[v] = FALSE;
	CLinkedList<CObjectEx*>& list = * new CLinkedList<CObjectEx*>;
	CStack& stack = *new CLinkedStack;
	if (source == target)
	{
		for(UINT  v = 1 ; v < numberOfVertices; v++)
		{
			list.append(&graph.selectVertex(0));
			if (dfsHamilton(graph,stack,list,visited,0,v,numberOfVertices - 1)) 
			{
				delete &stack;
				list.append(&graph.selectVertex(0));
				return *new CListIterator(list);
			}
			for(UINT  w = 0 ; w < numberOfVertices; w++)
				visited[w] = FALSE;
		}
		delete &stack;
		delete &list;
		return *new CNullIterator;
	}
	BOOL found = dfsHamilton(graph,stack,list,visited,source,target,numberOfVertices - 1);
	delete &stack;
	if (found)
		return *new CListIterator(list);
	delete &list;
	return *new CNullIterator;
}

CIterator& CGraphUtilities::getMaximumMatching(const CAbstractGraph&graph)const
{
	// build a network from graph
	CIterator& iter = isBipartite(graph);
	if (iter.isDone())
	{
		AfxMessageBox("This graph is not a bipartite graph");
		return *new CNullIterator;
	}
	CLinkedList<CListIterator*>&result = *new CLinkedList<CListIterator*>;
	UINT numberOfVertices = graph.numberOfVertices();
	// source has id == numberOfVertices and sink has id == numberOfVertices + 1
	CGraphFactory factory;
	CAbstractGraph& network = *factory.buildGraphAsLists(numberOfVertices + 2,TRUE);
	CGraphBuilder builder(network);
	for(UINT v = 0; v < numberOfVertices + 2; v++)
		network.addVertex(*builder.buildDefaultVertex());
	// add links from source to left
	NUMBER  source = numberOfVertices,
			sink = source + 1;
	CListIterator& left = (CListIterator&)iter.currentItem();
	for(; !left.isDone(); left.moveNext())
	{
		NUMBER v = (CVertex&)left.currentItem();
		network.addEdge(*builder.buildNetworkEdge(source,v,*new Integer(0),*new Integer(1)));

		// add links from left to right. A vertex in left side only connect to vertices in right side
		CIterator& p = graph.emanatingEdges(v);
		for(; !p.isDone(); p.moveNext())
		{
			CEdge& e = (CEdge&)p.currentItem();
			NUMBER r = e.secondEndPoint();
			network.addEdge(*builder.buildNetworkEdge(v,r,*new Integer(0),*new Integer(1)));
		}
		delete &p;
	}
	delete &left;
	iter.moveNext();
	// add links from right to sink
	CListIterator& right = (CListIterator&)iter.currentItem();
	for (; !right.isDone(); right.moveNext())
	{
		NUMBER v = (CVertex&)right.currentItem();
		network.addEdge(*builder.buildNetworkEdge(v,sink,*new Integer(0),*new Integer(1)));
	}
	delete &right;
	delete &iter;
	// use max-flow min-cut to find maximum-matching
	// CAlgorithmImpls<int> algorithm;
	CAlgorithms& algorithm = *CWrapperUtilities::buildAlgorithmImpl(Int);
	CIterator& mincut = algorithm.doEdmondsKarp((CDirectedGraph&)network,source,sink);
	delete &mincut;
	delete &algorithm;
	CLinkedList<CObjectEx*>& list = * new CLinkedList<CObjectEx*>;
	CIterator& edges = network.getEdges();
	while (!edges.isDone())
	{
		CNetworkEdge& e = (CNetworkEdge&)edges.currentItem();
		NUMBER  from = e.firstEndPoint(),
				to = e.secondEndPoint();
		INT w = (Integer&)e.getWeight();
		if ( w > 0 && from < numberOfVertices && to < numberOfVertices) 
			list.append(&graph.selectEdge(from,to));
		edges.moveNext();
	}
	delete &edges;
	result.append(new CListIterator(list));
	delete &network;
	return *new CListIterator((CLinkedList<CObjectEx*>&)result);
}

// for directed graph this method search for strongly connected components
// This algorithm is based on BFS
CIterator& CGraphUtilities::getConnectedComponents(const CAbstractGraph&graph)const
{
	CLinkedList<CListIterator*>&result = *new CLinkedList<CListIterator*>;
	UINT numberOfVertices = graph.numberOfVertices();
	if (graph.isDirected()) // if directed ==> Gabow's algorithm
	{
		CArrayEx<INT> pre(numberOfVertices);
		CArrayEx<INT> id(numberOfVertices);
		CStack& s = *new CStackAsArray(numberOfVertices);
		CStack& p = *new CStackAsArray(numberOfVertices);
		UINT cnt = 0, scnt = 0;
		for (INT v = 0; v < numberOfVertices; ++v)
			pre[v] = id[v] = -1;
		for (v = numberOfVertices - 1; v >= 0; v--)
			if (pre[v] == -1)
				dfsConnectedComponent(graph,v,cnt,scnt,pre,id,s,p);
		//////////////////////////////////////////////////////////////////////////
		// for debug only
		TRACE("number of connected component %d\n",scnt);
		for (v = 0; v < numberOfVertices; v++)
			TRACE("vertex %d in components %d\n",v,id[v]);
		//////////////////////////////////////////////////////////////////////////
		delete &s;
		delete &p;
		CArrayEx<CLinkedList<CObjectEx*>*> list(cnt);
		for (v = 0; v < scnt; v++)
			list[v] = new CLinkedList<CObjectEx*>;
		for (v = 0; v < numberOfVertices; ++v)
			list[id[v]]->append(&graph.selectVertex(v));
		for (v= 0; v < scnt; v++)
			result.append(new CListIterator(*list[v]));
		return *new CListIterator((CLinkedList<CObjectEx*>&)result);
	}
	// reach here => undirected graph
	CArrayEx<INT> depth(numberOfVertices);
	for (NUMBER v = 0; v < numberOfVertices; ++v) depth[v] = -1;
	BOOL bResult = FALSE;
	for (v = 0; v < numberOfVertices; ++v)
	{
		if (depth[v] < 0) // v bat dau mot connected component
		{
			CQueue& queue = *new CLinkedQueue ();
			queue.rescindOwnership ();
			CLinkedList<CObjectEx*>&componentList = *new CLinkedList<CObjectEx*>;
			depth[v] = 0;
			queue.enqueue (const_cast<CVertex&> (graph.selectVertex(v)));
			while (!queue.isEmpty ())
			{
				CVertex& vertex = (CVertex&)queue.dequeue();
				componentList.append(&vertex);
				CIterator& p = graph.emanatingEdges(vertex);
				for (; !p.isDone (); p.moveNext()) {
					CEdge& edge = (CEdge&)(p.currentItem());
					CVertex& to = edge.mate (vertex);
					if (depth [to] == -1)
					{
						depth[to] = depth[vertex]+1;
						queue.enqueue (to);
					}
				}
				delete &p;
			}
			delete &queue;
			result.append(new CListIterator(componentList));
		}
	}
	return *new CListIterator((CLinkedList<CObjectEx*>&)result);
}

// Search for bridge edges base on DFS
CIterator& CGraphUtilities::getBridgeEdges(const CAbstractGraph&graph)const
{
	// if (graph.isDirected()) return *new CNullIterator;
	CLinkedList<CListIterator*>&result = *new CLinkedList<CListIterator*>;
	UINT numberOfVertices = graph.numberOfVertices();
	CArrayEx<DFSBRIDGEEDGE> data(numberOfVertices);
	UINT time = 0;
	for (UINT v = 0; v < numberOfVertices; ++v)
		if (data[v].discover < 0) 
			dfsBridgeEdge(graph,v,time,data,result);
	return *new CListIterator((CLinkedList<CObjectEx*>&)result);
}

CIterator& CGraphUtilities::getBiconnectedComponents(const CAbstractGraph&graph)const
{
	if (graph.isDirected()) return *new CNullIterator;
	CLinkedList<CListIterator*>&result = *new CLinkedList<CListIterator*>;
	UINT numberOfVertices = graph.numberOfVertices();
	CStack&stack = *new CLinkedStack;
	// CStack&stack = *new CStackAsArray(numberOfVertices*numberOfVertices);
	stack.rescindOwnership();
	CArrayEx<DFSCUTVERTEX> data(numberOfVertices);
	UINT time;
	for (UINT v = 0; v < numberOfVertices; ++v)
		if (data[v].discover < 0)
		{
			time = 0;
			dfsBiconnectedComponent(graph,v,time,data,stack,result);
		}
	// if stack contain any edge left, these edges will make the last biconnected component
	CLinkedList<CObjectEx*>&list = *new CLinkedList<CObjectEx*>;
	while (!stack.isEmpty())
	{
		CEdge& edge = (CEdge&)stack.pop();
		list.append(&edge);
	}
	if (!list.isEmpty()) 
		result.append(new CListIterator((CLinkedList<CObjectEx*>&)list));
	else delete &list;
	delete&stack;
	return *new CListIterator((CLinkedList<CObjectEx*>&)result);
}

// pop stack until edge(vertex->mate) is found and also pop edge(vertex->mate)
void CGraphUtilities::popStackUntil(CStack &stack, NUMBER vertex, NUMBER mate, CLinkedList<CListIterator*> &result) const
{
	CLinkedList<CObjectEx*>&list = *new CLinkedList<CObjectEx*>;
	// pop stack until edge (vertex -> mate) is found
	while (!stack.isEmpty())
	{
		CEdge&edge = (CEdge&)stack.top();
		NUMBER source = edge.firstEndPoint();
		NUMBER target = edge.secondEndPoint();
		if (edge.firstEndPoint() != vertex || edge.secondEndPoint() != mate)
		{
			list.append(&edge);
			stack.pop();
		}
		else break;
	}
	// also pop edge (vertex -> mate)
	if(!stack.isEmpty()) 
		list.append(&(stack.pop()));
	if (!list.isEmpty()) 
		result.append(new CListIterator((CLinkedList<CObjectEx*>&)list));
	else delete &list;
}

CAbstractGraph* CGraphUtilities::getTransitiveClosure(const CAbstractGraph &graph)const
{
	if (!graph.isDirected())return NULL; // this algorithm just use for directed graph
	UINT numberOfVertices = graph.numberOfVertices();
	CGraphFactory factory;
	CAbstractGraph* pResult = factory.buildGraphAsMatrix(numberOfVertices,TRUE);
	CGraphBuilder builder(*pResult);
	for(NUMBER v = 0; v < numberOfVertices; v++)
	{
		pResult->addVertex(*(builder.buildDefaultVertex()));
		pResult->addEdge(*(builder.buildDefaultEdge(v,v)));
	}
	CIterator& edges = graph.getEdges();
	while (!edges.isDone())
	{
		CEdge&edge = (CEdge&)edges.currentItem();
		NUMBER  source = edge.firstEndPoint(),
				target = edge.secondEndPoint();
		if (source != target) // becase all loop already add to pResult at previous loop
			pResult->addEdge(*(builder.buildDefaultEdge(source,target)));
		edges.moveNext();
	}
	delete&edges;
	for(v = 0; v < numberOfVertices; v++)
		for(NUMBER source = 0; source < numberOfVertices; source++)
			if (!pResult->selectEdge(source,v).isNull()) 
				for(NUMBER target = 0; target < numberOfVertices; target++)
					if (!pResult->selectEdge(v,target).isNull() && pResult->selectEdge(source,target).isNull())
						pResult->addEdge(*(builder.buildDefaultEdge(source,target)));
	return pResult;
}

CIterator& CGraphUtilities::getVertexCover(const CAbstractGraph &graph) const
{
	CLinkedList<CObjectEx*>&list = *new CLinkedList<CObjectEx*>;
	CAbstractGraph& fake = copyGraph(graph);
	CIterator*pIter = &fake.getEdges();
	while (!pIter->isDone())
	{
		CEdge& e = (CEdge&)pIter->currentItem();
		NUMBER  source = e.firstEndPoint(),
				target = e.secondEndPoint();
		list.append(&graph.selectVertex(source));
		list.append(&graph.selectVertex(target));
		fake.removeEdge(source,target);

		CIterator& iter1 = fake.emanatingEdges(source);
		while (!iter1.isDone())
		{
			CEdge& e1 = (CEdge&)iter1.currentItem();
			NUMBER  source1 = e1.firstEndPoint(),
					target1 = e1.secondEndPoint();
			fake.removeEdge(source1,target1);
			iter1.moveNext();
		}
		delete&iter1;
		CIterator& iter2 = fake.emanatingEdges(target);
		while (!iter2.isDone())
		{
			CEdge& e2 = (CEdge&)iter2.currentItem();
			NUMBER  source2 = e2.firstEndPoint(),
					target2 = e2.secondEndPoint();
			fake.removeEdge(source2,target2);
			iter2.moveNext();
		}
		delete&iter2;
		delete pIter;
		pIter = &fake.getEdges();
	}
	delete pIter;
	delete &fake;
	return *new CListIterator(list);
}

CIterator& CGraphUtilities::isBipartite(const CAbstractGraph&graph)const
{
	if (graph.isDirected() || !isConnected(graph))
	{
		AfxMessageBox("Apply this algorithm on connected undirected graph only");
		return *new CNullIterator;
	}
	CLinkedList<CListIterator*>&result = *new CLinkedList<CListIterator*>;
	CLinkedList<CObjectEx*>& left = *new CLinkedList<CObjectEx*>;
	CLinkedList<CObjectEx*>& right = *new CLinkedList<CObjectEx*>;
	UINT numberOfVertices = graph.numberOfVertices();
	// test if this graph is 2-colourability (i.e bipartite)
	CArrayEx<INT> color(numberOfVertices);
	// CArrayEx<INT> predecessor(numberOfVertices);
	for (NUMBER v = 0; v < numberOfVertices; ++v)
	{
		color [v] = -1; // un color
		// predecessor [v] = -1; // no predecessor
	}
	
	CStack& stack = *new CStackAsArray(numberOfVertices);
	stack.rescindOwnership ();
	
	color[0] = 1; // color temporary
	left.append(&graph.selectVertex(0));
	stack.push(graph.selectVertex(0));
	//////////////////////////////////////////////////////////////////////////
	// for debug only
	TRACE("Vertex 0 has no parent and color 1\n");
	TRACE("Push 0\n");
	//////////////////////////////////////////////////////////////////////////
	while (!stack.isEmpty ())
	{
		CVertex& vertex = (CVertex&)stack.top();
		CIterator& p = graph.emanatingEdges (vertex);
		INT count = 0;

		//////////////////////////////////////////////////////////////////////////
		TRACE("Process %d\n",(NUMBER)vertex);
		//////////////////////////////////////////////////////////////////////////

		for (; !p.isDone (); p.moveNext()) 
		{
			CEdge& edge = (CEdge&)(p.currentItem());
			CVertex& to = edge.mate (vertex);
			if (color [to] == -1) // un color
			{
				// predecessor[to] = vertex;
				stack.push (to);
				count++;
				//////////////////////////////////////////////////////////////////////////
				TRACE("Push %d\n",(NUMBER)to);
				//////////////////////////////////////////////////////////////////////////

				// visitor.visit (vertex);
				if (color[vertex] == 1) // parent has color == 1 ==> it has color == 1
				{
					color[to] = 2;
					right.append(&to);
				}
				else // parent has color == 2 ==> it has color == 1 
				{
					color[to] = 1;
					left.append(&to);
				}
				//////////////////////////////////////////////////////////////////////////
				// for debug only
				UINT n = to;
				// INT a = predecessor[to];
				INT b = color[to];
				TRACE("Vertex %d has parent and color %d\n",n,b);
				//////////////////////////////////////////////////////////////////////////
				//
			}
			//*
			else
			{
				if (color[to] == color[vertex]) // to and vertex are in the same side but are linked to each other
				{
					//////////////////////////////////////////////////////////////////////////
					// for debug only
					TRACE("Edge %d --> %d\n",(NUMBER)vertex,(NUMBER)to);
					//////////////////////////////////////////////////////////////////////////
					delete &p;
					delete &stack;
					delete &left;
					delete &right;
					delete & result;
					return *new CNullIterator; // it's not an bipartite
				}
			}
			//*/
		}
		delete &p;
		if (count == 0)
		{
			//////////////////////////////////////////////////////////////////////////
			TRACE("Pop %d\n",(NUMBER)vertex);
			//////////////////////////////////////////////////////////////////////////
			stack.pop();
			continue;
		}
	}
	delete &stack;
	result.append(new CListIterator(left));
	result.append(new CListIterator(right));
	return *new CListIterator((CLinkedList<CObjectEx*>&)result);
}