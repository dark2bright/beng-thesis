// CStackAsArray.cpp: implementation of the CStackAsArray class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StackAsArray.h"
#include <stdexcept>
#include "Definitions.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStackAsArray::CStackAsArray(UINT MAXSIZE)
: array(MAXSIZE)
{
}

CStackAsArray::~CStackAsArray()
{
	purge();
}

void CStackAsArray::purge()
{
	if (isOwner ())
    {
		for (UINT i = 0; i < m_uCount; ++i)
			delete array [i];
    }
    m_uCount = 0;
}

void CStackAsArray::push (CObjectEx& object)
{
    if (m_uCount == array.getLength ())
		throw std::domain_error ("Stack is full");
    array [m_uCount++] = &object;
}

CObjectEx& CStackAsArray::pop ()
{
    if (m_uCount == 0)
		throw std::domain_error ("Stack is empty");
    return *array [--m_uCount];
}

CObjectEx& CStackAsArray::top() const
{
    if (m_uCount == 0)
		throw std::domain_error ("Stack is empty");
    return *array [m_uCount - 1];
}

void CStackAsArray::accept (CVisitor&visitor) const
{
	for (UINT i = 0; i < m_uCount; ++i)
		visitor.visit(*array[i]);
}

INT CStackAsArray::typeId() const
{
	return STACKASARRAYID;
}

CString CStackAsArray::toString() const
{
	return "StackAsArray";
}
