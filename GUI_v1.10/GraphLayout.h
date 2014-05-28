// GraphLayout.h: interface for the CGraphLayout class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHLAYOUT_H__39BBEF34_8B34_4D88_BE06_0CA06911899E__INCLUDED_)
#define AFX_GRAPHLAYOUT_H__39BBEF34_8B34_4D88_BE06_0CA06911899E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GraphView.h"

class CGraphLayout  
{
public:
	CGraphLayout();
	virtual ~CGraphLayout();
public:
	static void doEllipse(CGraphView&,CRect&);
};

#endif // !defined(AFX_GRAPHLAYOUT_H__39BBEF34_8B34_4D88_BE06_0CA06911899E__INCLUDED_)
