// BinaryHeap.h: interface for the CBinaryHeap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BINARYHEAP_H__78989F34_AE83_4BC1_89A8_7976EFC0421A__INCLUDED_)
#define AFX_BINARYHEAP_H__78989F34_AE83_4BC1_89A8_7976EFC0421A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BObject.h"
#include "Container.h"
#include "BArray.h"

class CPriorityQueue : public virtual CContainer
{
public:
    virtual VOID enqueue (CObjectEx&) = 0;
    virtual CObjectEx& findMin () const = 0;
    virtual CObjectEx& dequeueMin () = 0;
};

class CBinaryHeap : public CPriorityQueue  
{
public:
	CBinaryHeap (UINT);
	virtual ~CBinaryHeap();
public:
	virtual CString toString()const;
	CObjectEx& findMin () const;
	CObjectEx& dequeueMin ();
	INT typeId() const;
	VOID accept(CVisitor&) const;		
	VOID purge ();
	VOID enqueue (CObjectEx&);
protected:
	CArrayEx<CObjectEx*> array;
};

#endif // !defined(AFX_BINARYHEAP_H__78989F34_AE83_4BC1_89A8_7976EFC0421A__INCLUDED_)
