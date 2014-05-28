// Thesis.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Thesis.h"
#include "Algorithms.h"
#include "GraphFactory.h"
#include "WeightedEdge.h"
#include "GraphBuilder.h"
#include "Wrapper.h"
#include "GraphUtilities.h"
#include "PrintingVisitor.h"
#include "PreOrder.h"
#include "PostOrder.h"
#include "InOrder.h"
#include <iostream.h>
#include "SortableLinkedList.h"
#include "ListIterator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;
	
	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
	}
	else
	{
		// TODO: code your application's behavior here.
		//[my code start here]
		//*
		CGraphFactory factory;
		CAbstractGraph*pG = factory.buildGraphAsLists(13,FALSE);
		CGraphBuilder builder(*pG);
		for(UINT i = 0; i < 7; i++)
			pG->addVertex(*(builder.buildDefaultVertex()));
		
		pG->addEdge(*(builder.buildDefaultEdge(0,1)));
		pG->addEdge(*(builder.buildDefaultEdge(0,2)));
		pG->addEdge(*(builder.buildDefaultEdge(0,5)));
		pG->addEdge(*(builder.buildDefaultEdge(0,6)));
		pG->addEdge(*(builder.buildDefaultEdge(1,2)));
		pG->addEdge(*(builder.buildDefaultEdge(2,3)));
		pG->addEdge(*(builder.buildDefaultEdge(2,4)));
		pG->addEdge(*(builder.buildDefaultEdge(3,4)));
		pG->addEdge(*(builder.buildDefaultEdge(4,5)));
		pG->addEdge(*(builder.buildDefaultEdge(4,6)));
		pG->addEdge(*(builder.buildDefaultEdge(5,6)));
		CGraphUtilities gu;
		
		CIterator& iter = gu.getHamiltonPath(*pG,0,0);
		for (; !iter.isDone(); iter.moveNext()) 
		{
			CEdge& edge = (CEdge&)iter.currentItem();
			//////////////////////////////////////////////////////////////////////////
			NUMBER  s = edge.firstEndPoint(),
					t = edge.secondEndPoint();
			TRACE("%d -> %d\n",s,t);
		}
		delete &iter;
		delete pG;		
		//[my code end here]
	}
	return nRetCode;
}
