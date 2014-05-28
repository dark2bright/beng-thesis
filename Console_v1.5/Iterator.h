// Iterator.h: interface for the CIterator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ITERATOR_H__C29CE05C_C71F_4EB4_A3E9_7A1F899E6C15__INCLUDED_)
#define AFX_ITERATOR_H__C29CE05C_C71F_4EB4_A3E9_7A1F899E6C15__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BObject.h"

class CIterator  
{
public:
    virtual ~CIterator (){}
    virtual VOID reset () = 0;
    virtual BOOL isDone () const = 0;
    virtual CObjectEx& currentItem() const = 0;
    virtual VOID moveNext() = 0;
};

#endif // !defined(AFX_ITERATOR_H__C29CE05C_C71F_4EB4_A3E9_7A1F899E6C15__INCLUDED_)
