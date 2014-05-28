// BinaryHeap.cpp: implementation of the CBinaryHeap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thesis.h"
#include "BinaryHeap.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBinaryHeap::~CBinaryHeap()
{
	purge();
}

CBinaryHeap::CBinaryHeap(UINT length)
	: array (length, 1) 
{

}

VOID CBinaryHeap::accept(CVisitor &visitor) const
{
}

INT CBinaryHeap::typeId() const
{
	return BINARYHEAPID;
}

CObjectEx& CBinaryHeap::dequeueMin()
{
	if (m_uCount == 0)
		throw std::domain_error ("Priority queue is empty");
	CObjectEx& result = *array [1];
	CObjectEx& last = *array [m_uCount];
	--m_uCount;
	UINT i = 1;
	while (2 * i < m_uCount + 1){
		UINT child = 2 * i;
		if (child + 1 < m_uCount + 1
			&& *array [child + 1] < *array[child])
			child += 1;
		if (last <= *array [child])
			break;
		array [i] = array [child];
		i = child;
	}
	array[i] = &last;
	return result;
}

VOID CBinaryHeap::enqueue(CObjectEx &object)
{
	if (m_uCount == array.getLength ())
		throw std::domain_error ("Priority queue is full");
	++m_uCount;
	UINT i = m_uCount;
	while ((i > 1) && *array [i / 2] > object){
		array [i] = array [i / 2];
		i /= 2;
	}
	array [i] = &object;
}

CObjectEx& CBinaryHeap::findMin() const
{
	if (m_uCount == 0)
		throw std::domain_error ("Priority queue is empty");
	return *array [1];
}

VOID CBinaryHeap::purge()
{
	if (isOwner ())
		for (UINT i = 1; i < m_uCount + 1; ++i)
			delete array [i];
	m_uCount = 0;
}

CString CBinaryHeap::toString() const
{
	return "BinaryHeap";
}
