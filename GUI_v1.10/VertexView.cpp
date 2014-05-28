// VertexView.cpp: implementation of the CVertexView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thesis.h"
#include "VertexView.h"
#include "WeightedVertex.h"
#include "PropertiesVDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVertexView::CVertexView()
	: CShape(CPoint(0,0)) 
{	
}

CVertexView::CVertexView(CPoint center)
	: CShape(center)
{
}

CVertexView::~CVertexView()
{
}

void CVertexView::drawWithColor(CDC *pDC,const COLORREF& _color)
{
	CShape::drawWithColor(pDC,_color);
	//* draw number
	pDC->SetBkColor(_color);
	CString str;
	NUMBER number = *m_pModel;
	str.Format("%d",number);
	CRect rect(ctrlPoint[TOPLEFT],ctrlPoint[BOTTOMRIGHT]);
	pDC->DrawText(str,rect,DT_SINGLELINE|DT_VCENTER|DT_CENTER);
	//* draw weight of vertex (if available)
	if (m_pModel->typeId() == VERTEXID) return; // Unweighted vertex do nothing
	// Reach here draw weight of vertex
	pDC->SetBkColor(RGB(255,255,255));
	CString strWeight = ((CWeightedVertex*)m_pModel)->getWeight().toString();
	/*
	CPoint pnt = ctrlPoint[TOPLEFT];
	pnt.Offset(0, - getVerticalRadius());
	CRect wRect(pnt,ctrlPoint[TOPRIGHT]);
	//*/
	//*
	CPoint topLeft = ctrlPoint[TOPLEFT], topRight = ctrlPoint[TOPRIGHT];
	topLeft.Offset(getHorizontalRadius(), - getVerticalRadius());
	topRight.Offset(- getHorizontalRadius(), 0);
	CRect wRect(topLeft,topRight);
	// wRect.NormalizeRect();
	TEXTMETRIC textmetric;
	pDC->GetTextMetrics(&textmetric);
	int nWidth = textmetric.tmAveCharWidth*(strWeight.GetLength()+3);
	wRect.InflateRect(nWidth/2,0,nWidth/2,0);
	//*/
	//////////////////////////////////////////////////////////////////////////
	pDC->DrawText(strWeight,wRect,DT_SINGLELINE|DT_VCENTER|DT_CENTER);
}

VOID CVertexView::attach(CVertex *pModel)
{
	m_pModel = pModel;
}

void CVertexView::displayProperties(LPCONTROLSTRUCT lpControlStruct)
{
	CPropertiesVDlg dlg(NULL,m_pModel);
	dlg.m_color = color;
	dlg.m_strName = name;
	dlg.m_lpControlStruct = lpControlStruct;
	if (dlg.DoModal() == IDOK) {
		color = dlg.m_color;
		name = dlg.m_strName;
	}
}

INT CVertexView::typeId() const
{
	return VERTEXVIEWID;
}


NUMBER CVertexView::getModel() const
{
	NUMBER model = *m_pModel;
	return model;
}

CString CVertexView::toString() const
{
	return "VertexView";
}

CObjectEx& CVertexView::clone() const
{
	CVertexView* pNew = new CVertexView();
	for(UINT i = 0; i < 4; i++)
		pNew->ctrlPoint[i] = ctrlPoint[i];
	pNew->color = color;
	pNew->name = name;
	pNew->mode = mode;
	return *pNew;
}

void CVertexView::Serialize(CArchive &ar)
{
	if (ar.IsStoring()) 
	{
		ar.WriteString("node [\n");
		m_pModel->Serialize(ar);
		CGraphics::Serialize(ar);
		ar.WriteString("]\n");
	}
}
