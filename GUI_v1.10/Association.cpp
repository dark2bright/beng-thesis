// Association.cpp: implementation of the CAssociation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thesis.h"
#include "Association.h"
#include "NullObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAssociation::CAssociation(CObjectEx &_key)
	: key(&_key), value(0)
{
}

CAssociation::CAssociation(CObjectEx &_key, CObjectEx &_value)
	: key(&_key), value(&_value)
{
}

CAssociation::~CAssociation()
{
	if (isOwner ()){
		delete key;
		delete value;
	}
}

INT CAssociation::compareTo(const CObjectEx &object) const
{
	CAssociation const& association = (CAssociation const&)(object);
	return getKey().compare (association.getKey());
}


INT CAssociation::typeId() const
{
	return ASSOCIATIONID;
}

CObjectEx& CAssociation::getKey() const
{
	return *key;
}

CObjectEx& CAssociation::getValue() const
{
	if (value == 0)
		return CNullObject::instance ();
	else
		return *value;	
}
