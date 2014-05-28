// BObject.cpp: implementation of the CObjectEx class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thesis.h"
#include "BObject.h"
#include "NullObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BOOL CObjectEx::isNull () const { 
	return FALSE; 
}

BOOL CObjectEx::operator == (const CObjectEx & target) const {
	return compareTo(target) == 0; 
}

BOOL CObjectEx::operator != (const CObjectEx & target) const { 
	return compareTo(target) != 0; 
}

BOOL CObjectEx::operator <= (const CObjectEx & target) const { 
	return compareTo(target) <= 0; 
}

BOOL CObjectEx::operator < (const CObjectEx & target) const { 
	return compareTo(target) < 0; 
}

BOOL CObjectEx::operator >= (const CObjectEx & target) const { 
	return compareTo(target) >= 0; 
}

BOOL CObjectEx::operator > (const CObjectEx & target) const { 
	return compareTo(target) > 0; 
}

INT CObjectEx::compare(CObjectEx const& object) const
{
	if (this->typeId() == object.typeId())
		return compareTo (object);
	else if (this->typeId() < object.typeId())
		return -1;
	else
		return 1;
}

INT CObjectEx::compareTo(const CObjectEx &target)const { 
	return 0; 
}

CString CObjectEx::toString() const
{
	return "Object";
}

CObjectEx& CObjectEx::clone() const
{
	return CNullObject::instance();
}

CObjectEx::~CObjectEx()
{
}