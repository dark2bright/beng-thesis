// Container.h: interface for the CContainer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONTAINER_H__F0812ED9_09BC_4B28_9100_8E65285C5751__INCLUDED_)
#define AFX_CONTAINER_H__F0812ED9_09BC_4B28_9100_8E65285C5751__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BObject.h"
#include "Ownership.h"
#include "Iterator.h"
#include "Visitor.h"

class CContainer : public CObjectEx, public COwnership  
{
protected:
	CContainer();
public:
	CIterator& newIterator()const;
	UINT count()const;
	BOOL isEmpty()const;
	virtual BOOL isFull()const;
	// pure virtual function
	virtual VOID purge () = 0;
    virtual VOID accept (CVisitor&) const = 0;
protected:
    UINT m_uCount;
};

#endif // !defined(AFX_CONTAINER_H__F0812ED9_09BC_4B28_9100_8E65285C5751__INCLUDED_)
