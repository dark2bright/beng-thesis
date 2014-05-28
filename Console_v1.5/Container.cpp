// Container.cpp: implementation of the CContainer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thesis.h"
#include "Container.h"
#include "NullIterator.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CContainer::CContainer() : m_uCount(0)
{
}

BOOL CContainer::isFull() const
{
	return FALSE;
}

BOOL CContainer::isEmpty() const
{
	return m_uCount == 0;
}

UINT CContainer::count() const{
	return m_uCount;
}

CIterator& CContainer::newIterator() const
{
	return *new CNullIterator;
}
