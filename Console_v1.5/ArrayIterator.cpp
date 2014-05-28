// ArrayIterator.cpp: implementation of the CArrayIterator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "thesis.h"
#include "ArrayIterator.h"
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

CArrayIterator::CArrayIterator (const CArrayEx<CObjectEx*>& _array,UINT _count)
: array(_array),count(_count)
{ 
	count = _count;
	reset(); 
}

CArrayIterator::~CArrayIterator (){}

VOID CArrayIterator::reset () 
{ 
	current = 0; 
}

BOOL CArrayIterator::isDone () const 
{ 
	return current >= count; 
}

CObjectEx& CArrayIterator::currentItem() const
{
	if (current < count)
		return *array[current];
	else
		return CNullObject::instance ();
}

VOID CArrayIterator::moveNext() 
{ 
	if(current < count) current++;
}