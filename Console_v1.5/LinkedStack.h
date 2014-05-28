// LinkedStack.h: interface for the CLinkedStack class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINKEDSTACK_H__22D2D44C_B477_428D_8C60_C608C385FCF6__INCLUDED_)
#define AFX_LINKEDSTACK_H__22D2D44C_B477_428D_8C60_C608C385FCF6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Stack.h"
#include "LinkedList.h"

class CLinkedStack : public CStack  
{
public:
	CLinkedStack();
	virtual ~CLinkedStack();
public:	
	CString toString()const;
	INT typeId()const;
	void purge();
	void accept (CVisitor&visitor) const;
	void push (CObjectEx&);
	CObjectEx& top () const;
    CObjectEx& pop ();
protected:
	CLinkedList<CObjectEx*> list;
};

#endif // !defined(AFX_LINKEDSTACK_H__22D2D44C_B477_428D_8C60_C608C385FCF6__INCLUDED_)
