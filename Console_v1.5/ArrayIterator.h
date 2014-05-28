// ArrayIterator.h: interface for the CArrayIterator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VERTEXITERATOR_H__61BEF6C5_A56D_4504_AB61_A1E7D7681EB1__INCLUDED_)
#define AFX_VERTEXITERATOR_H__61BEF6C5_A56D_4504_AB61_A1E7D7681EB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Vertex.h"
#include "Iterator.h"
#include "BArray.h"

class CArrayIterator : public CIterator
{
public:
	CArrayIterator (const CArrayEx<CObjectEx*>&,UINT);
	~CArrayIterator ();
public:
	BOOL isDone () const;
	CObjectEx& currentItem() const;
	VOID reset();
	VOID moveNext();
protected:
	const CArrayEx<CObjectEx*>& array;
	UINT current;
	UINT count;
};

#endif // !defined(AFX_VERTEXITERATOR_H__61BEF6C5_A56D_4504_AB61_A1E7D7681EB1__INCLUDED_)
