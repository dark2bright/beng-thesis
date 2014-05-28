// WeightedEdge.cpp: implementation of the CWeightedEdge class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thesis.h"
#include "WeightedEdge.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEdge& CWeightedEdge::reverse() const
{
	CObjectEx& weight = *m_pWeight;
	CWeightedEdge*p = new CWeightedEdge(m_vEP2,m_vEP1,weight);
	// do weight khong phai cua thang p ma la cua thang this
	p->rescindOwnership();
	return *p;
}

CWeightedEdge::CWeightedEdge(CVertex &vEP1, CVertex &vEP2, CObjectEx &weight)
	: CEdge(vEP1,vEP2), CWeightedNode(weight)
{
}

CObjectEx& CWeightedEdge::clone() const
{
	return *new CWeightedEdge(m_vEP1,m_vEP2,m_pWeight->clone());
}

INT CWeightedEdge::typeId() const
{
	return WEIGHTEDEDGEID;
}

void CWeightedEdge::Serialize(CArchive &ar)
{
	if (ar.IsStoring())
	{
		CEdge::Serialize(ar);
		CString str;
		str.Format("weight %c%s%c\n",'"',getWeight().toString(),'"');
		ar.WriteString(str);
	}
}
