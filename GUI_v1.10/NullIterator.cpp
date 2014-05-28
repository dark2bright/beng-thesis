// NullIterator.cpp: implementation of the CNullIterator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thesis.h"
#include "NullIterator.h"
#include "NullObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNullIterator::CNullIterator()
{

}

VOID CNullIterator::reset()
{

}

BOOL CNullIterator::isDone() const
{
	return TRUE;
}

VOID CNullIterator::moveNext()
{
}

CObjectEx& CNullIterator::currentItem() const
{
	return CNullObject::instance();
}
