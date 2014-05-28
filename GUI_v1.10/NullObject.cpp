// NullObject.cpp: implementation of the CNullObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thesis.h"
#include "NullObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CNullObject CNullObject::m_instance;

CNullObject::CNullObject()
{
}

CNullObject& CNullObject::instance() 
{ 
	return m_instance;
}

INT CNullObject::typeId() const
{
	return NULLOBJECTID;
}

BOOL CNullObject::isNull() const
{
	return TRUE;
}

CString CNullObject::toString() const
{
	return "NullObject";
}
