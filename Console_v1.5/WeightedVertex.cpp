// WeightedVertex.cpp: implementation of the CWeightedVertex class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thesis.h"
#include "WeightedVertex.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWeightedVertex::CWeightedVertex(NUMBER number, CObjectEx &weight)
	: CVertex(number), CWeightedNode(weight)
{
}

INT CWeightedVertex::typeId() const
{
	return WEIGHTEDVERTEXID;
}

CObjectEx& CWeightedVertex::clone() const
{
	CWeightedVertex* v = new CWeightedVertex(m_uNumber,*m_pWeight);
	v->rescindOwnership(); // so its weight belong to this
	return *v;
}

void CWeightedVertex::Serialize(CArchive &ar)
{
	if (ar.IsStoring()) 
	{
		CVertex::Serialize(ar);
		CString str;
		str.Format("weight %c%s%c\n",'"',getWeight().toString(),'"');
		ar.WriteString(str);
	}
}
