// NullIterator.h: interface for the CNullIterator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NULLITERATOR_H__7B5D93D5_5887_41A2_939B_C04CE20E6F3B__INCLUDED_)
#define AFX_NULLITERATOR_H__7B5D93D5_5887_41A2_939B_C04CE20E6F3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Iterator.h"

class CNullIterator : public CIterator  
{
public:
	CObjectEx& currentItem()const;
	VOID moveNext();
	BOOL isDone()const;
	VOID reset();
	CNullIterator();
};

#endif // !defined(AFX_NULLITERATOR_H__7B5D93D5_5887_41A2_939B_C04CE20E6F3B__INCLUDED_)
