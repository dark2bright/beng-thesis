// NetworkEdge.cpp: implementation of the CNetworkEdge class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thesis.h"
#include "NetworkEdge.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNetworkEdge::CNetworkEdge(CVertex&vEP1,CVertex&vEP2,CObjectEx&weight,CObjectEx&capacity)
	: CWeightedEdge(vEP1,vEP2,weight),m_pCapacity(&capacity)
{
}

CNetworkEdge::~CNetworkEdge()
{
	delete m_pCapacity;
}

INT CNetworkEdge::typeId() const
{
	return NETWORKEDGEID;
}

CObjectEx& CNetworkEdge::getCapacity() const
{
	return *m_pCapacity;
}

void CNetworkEdge::setCapacity(CObjectEx &capacity)
{
	delete m_pCapacity;
	m_pCapacity = &capacity;
}

void CNetworkEdge::Serialize(CArchive &ar)
{
	if (ar.IsStoring()) 
	{
		CWeightedEdge::Serialize(ar);
		CString str;
		str.Format("capacity %c%s%c\n",'"',getWeight().toString(),'"');
		ar.WriteString(str);
	}
}
