// LinkedStack.cpp: implementation of the CLinkedStack class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LinkedStack.h"
#include "Definitions.h"
#include <stdexcept>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLinkedStack::CLinkedStack()
: list()
{
}

CLinkedStack::~CLinkedStack()
{
	purge();
}

void CLinkedStack::purge()
{
	if (isOwner ())
		for (const CLinkedList<CObjectEx*>::CListElement*ptr = list.head(); ptr != 0; ptr = ptr->next)
			delete ptr->datum;
    list.purge ();
    m_uCount = 0;
}

INT CLinkedStack::typeId() const
{
	return LINKEDSTACKID;
}

CString CLinkedStack::toString() const
{
	return "LinkedStack";
}

void CLinkedStack::accept(CVisitor &visitor) const
{
	CLinkedList<CObjectEx*>::CListElement const* ptr;		
	for (ptr = list.head(); ptr != 0 && !visitor.isDone(); ptr = ptr->next)
		visitor.visit(*ptr->datum);
}

void CLinkedStack::push (CObjectEx& object)
{
    list.prepend (&object);
    ++m_uCount;
}

CObjectEx& CLinkedStack::pop()
{
    if (m_uCount == 0)
		throw std::domain_error ("Stack is empty");
    CObjectEx& result = *(list.first());
    list.extract (&result);
    --m_uCount;
    return result;
}

CObjectEx& CLinkedStack::top () const
{
    if (m_uCount == 0)
		throw std::domain_error ("Stack is empty");
    return *list.first ();
}
