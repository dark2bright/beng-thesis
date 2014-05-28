// LinkedQueue.cpp: implementation of the CLinkedQueue class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thesis.h"
#include "LinkedQueue.h"
#include <stdexcept>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLinkedQueue::CLinkedQueue() : list()
{
}

CLinkedQueue::~CLinkedQueue()
{
	purge();
}

VOID CLinkedQueue::accept(CVisitor &visitor) const
{
	CLinkedList<CObjectEx*>::CListElement const* ptr;		
	for (ptr = list.head(); ptr != 0 && !visitor.isDone(); ptr = ptr->next)
		visitor.visit(*ptr->datum);
}

VOID CLinkedQueue::purge()
{
	if (isOwner ()){
		CLinkedList<CObjectEx*>::CListElement const* ptr;		
		for (ptr = list.head(); ptr != 0; ptr = ptr->next)
			delete ptr->datum;
	}
	list.purge ();
	m_uCount = 0;
}

INT CLinkedQueue::typeId() const
{
	return LINKEDQUEUEID;
}

CObjectEx& CLinkedQueue::head() const
{
	if (m_uCount == 0){ 
		throw std::domain_error ("Queue is empty");
		AfxMessageBox("Queue is empty");
	}
	return *list.first ();	
}

VOID CLinkedQueue::enqueue(CObjectEx &object)
{
	list.append (&object);
	++m_uCount;
}

CObjectEx& CLinkedQueue::dequeue()
{
	if (m_uCount == 0){
		throw std::domain_error ("Queue is empty");
		AfxMessageBox("Queue is empty");
	}
	CObjectEx& result = *list.first ();
	list.extract (&result);
	--m_uCount;
	return result;
}

CString CLinkedQueue::toString() const
{
	return "LinkedQueue";
}
