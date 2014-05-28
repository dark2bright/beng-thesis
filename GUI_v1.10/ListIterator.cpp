// ListIterator.cpp: implementation of the CListIterator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ListIterator.h"
#include "NullObject.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListIterator::CListIterator(CLinkedList<CObjectEx*> &aList) : list(aList){
	reset();
}

VOID CListIterator::reset ()
{
	m_pCurrent = list.head();
}

BOOL ::CListIterator::isDone () const
{
	return m_pCurrent == NULL;
}

CObjectEx& CListIterator::currentItem() const
{
	if (m_pCurrent != 0)
		return *m_pCurrent->datum;
	else
		return CNullObject::instance ();
}

VOID CListIterator::moveNext()
{
	m_pCurrent = m_pCurrent->next;
}

CListIterator::~CListIterator(){
	reset();
	delete &list;
}