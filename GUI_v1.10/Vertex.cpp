// Vertex.cpp: implementation of the CVertex class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thesis.h"
#include "Vertex.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVertex::CVertex(NUMBER number) : m_uNumber(number)
{
}

CVertex::~CVertex()
{
}

CVertex::operator NUMBER() const
{
	return m_uNumber;
}

INT CVertex::compareTo(const CObjectEx &target) const
{
	if(m_uNumber == ((CVertex&)target).m_uNumber) return 0;
	return m_uNumber > (((CVertex&)target).m_uNumber) ? 1 : -1;
}

INT CVertex::typeId() const
{
	return VERTEXID;
}

VOID CVertex::setNumber(NUMBER _uNumber)
{
	m_uNumber = _uNumber;
}

CString CVertex::toString() const
{
	return "Vertex";
}

CObjectEx& CVertex::clone() const
{
	return *new CVertex(m_uNumber);
}

void CVertex::Serialize(CArchive &ar)
{
	if (ar.IsStoring()) 
	{
		CString str;
		str.Format("id %d\n",m_uNumber);
		ar.WriteString(str);
	}
}
