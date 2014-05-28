// LinkedQueue.h: interface for the CLinkedQueue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINKEDQUEUE_H__69F0C9A8_58F8_4571_96A5_10DFA58CA01A__INCLUDED_)
#define AFX_LINKEDQUEUE_H__69F0C9A8_58F8_4571_96A5_10DFA58CA01A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Queue.h"
#include "LinkedList.h"

class CLinkedQueue : public virtual CQueue  
{
public:
	CLinkedQueue();
	virtual ~CLinkedQueue();
public:
	CString toString()const;
	CObjectEx& dequeue ();
	VOID enqueue (CObjectEx&object);
	CObjectEx& head() const;
	INT typeId() const;
	VOID purge();
	VOID accept (CVisitor&visitor) const;
protected:
	CLinkedList<CObjectEx*> list;
};

#endif // !defined(AFX_LINKEDQUEUE_H__69F0C9A8_58F8_4571_96A5_10DFA58CA01A__INCLUDED_)
