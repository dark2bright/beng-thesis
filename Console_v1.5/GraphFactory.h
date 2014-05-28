// GraphFactory.h: interface for the CGraphFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHFACTORY_H__81D646A3_DE66_4D3C_9B1E_54D913928B7F__INCLUDED_)
#define AFX_GRAPHFACTORY_H__81D646A3_DE66_4D3C_9B1E_54D913928B7F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AbstractGraph.h"

class CGraphFactory  
{
public:
	CGraphFactory();
public:
	CAbstractGraph* buildGraphAsMatrix(UINT MAXSIZE,BOOL directed)const;
	// build Graph having edge container as lists 
	CAbstractGraph* buildGraphAsLists(UINT MAXSIZE,BOOL directed)const;
};

#endif // !defined(AFX_GRAPHFACTORY_H__81D646A3_DE66_4D3C_9B1E_54D913928B7F__INCLUDED_)
