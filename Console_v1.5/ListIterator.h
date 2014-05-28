// ListIterator.h: interface for the CListIterator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTITERATOR_H__A7F7B494_ABBC_4F60_A5D3_E17392B34321__INCLUDED_)
#define AFX_LISTITERATOR_H__A7F7B494_ABBC_4F60_A5D3_E17392B34321__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Iterator.h"
#include "LinkedList.h"

class CListIterator : public CIterator
{
public:
	CListIterator(CLinkedList<CObjectEx*>&);
	virtual VOID reset ();
	virtual BOOL isDone () const;
	virtual CObjectEx& currentItem() const;
	virtual VOID moveNext();
	virtual ~CListIterator();
protected:
	CLinkedList<CObjectEx*>const & list;
	CLinkedList<CObjectEx*>::CListElement const* m_pCurrent;
};

#endif // !defined(AFX_LISTITERATOR_H__A7F7B494_ABBC_4F60_A5D3_E17392B34321__INCLUDED_)
