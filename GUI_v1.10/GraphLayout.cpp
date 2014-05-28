// GraphLayout.cpp: implementation of the CGraphLayout class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "thesis.h"
#include "GraphLayout.h"
#include "Vector2D.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGraphLayout::CGraphLayout()
{
}

CGraphLayout::~CGraphLayout()
{
}

void CGraphLayout::doEllipse(CGraphView&view, CRect&rect)
{
	rect.NormalizeRect();
	rect.DeflateRect(2*MIN_RADIUS,2*MIN_RADIUS);
	CPoint center = rect.CenterPoint();
	UINT numberOfVertices = view.m_pModel->numberOfVertices();
	DOUBLE rad = 2*3.1415926536 / numberOfVertices;
	for(UINT vertex = 0; vertex < numberOfVertices; vertex++)
	{
		DOUBLE degree = vertex * rad; // goc cua dinh
		CPoint coordinate; // toa do cua dinh
		coordinate.x = long((rect.right - rect.left) / 2 * cos(degree) + center.x);
		coordinate.y = long((rect.bottom - rect.top) / 2 * sin(degree) + center.y);
		view.vertexViews[vertex]->offset(coordinate,DO_LAYOUT);
	}
	for(UINT source = 0; source < numberOfVertices; source++)
		for(UINT target = 0; target < numberOfVertices; target++)
		{
			CEdgeView*pE = view.edgeViews[source][target];
			if (pE) pE->reposition(DO_UPDATE); 
		}
}
