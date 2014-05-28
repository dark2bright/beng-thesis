// Edge.cpp: implementation of the CEdge class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thesis.h"
#include "Edge.h"
#include "NullObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEdge::CEdge(CVertex &vEP1, CVertex &vEP2):m_vEP1(vEP1),m_vEP2(vEP2) 
{
}

INT CEdge::typeId() const
{
	return EDGEID;
}

CVertex& CEdge::firstEndPoint() const
{
	return m_vEP1;
}

CVertex& CEdge::secondEndPoint() const
{
	return m_vEP2;
}

CVertex& CEdge::mate(const CVertex &vEndPoint) const
{
	if (vEndPoint != m_vEP1 && vEndPoint != m_vEP2) 
		return (CVertex&)CNullObject::instance();
	return vEndPoint == m_vEP1 ? m_vEP2 : m_vEP1;
}

CEdge& CEdge::reverse() const
{
	return *new CEdge(m_vEP2,m_vEP1);
}

CEdge::~CEdge()
{
}

CString CEdge::toString() const
{
	return "Edge";
}

void CEdge::Serialize(CArchive &ar)
{
	if (ar.IsStoring())
	{
		NUMBER source = m_vEP1;
		NUMBER target = m_vEP2;
		CString str;
		str.Format("source %d\n target %d\n",source,target);
		ar.WriteString(str);
	}
}

void CEdge::setEndPoints(CVertex &vEP1, CVertex &vEP2)
{
	m_vEP1 = vEP1;
	m_vEP2 = vEP2;
}

CObjectEx& CEdge::clone() const
{
	return *new CEdge(m_vEP1,m_vEP2);
}

BOOL CEdge::isLoop()
{
	NUMBER  from = m_vEP1,
			to = m_vEP2;
	return (from == to);
}
