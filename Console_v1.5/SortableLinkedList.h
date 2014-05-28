// SortableLinkedList.h: interface for the CSortableLinkedList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SORTABLELINKEDLIST_H__BA0A42D6_F19D_4963_A2D7_508198B87BA3__INCLUDED_)
#define AFX_SORTABLELINKEDLIST_H__BA0A42D6_F19D_4963_A2D7_508198B87BA3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LinkedList.h"

template<class T>
class CSortableLinkedList : public CLinkedList<T>
{
public:
	CSortableLinkedList(){}
	virtual ~CSortableLinkedList(){}
public:
	// sort this linked list using merge sort
	void sort(BOOL bAscendant = TRUE)
	{
		recursiveSort(m_pHead,bAscendant);
	}
protected:
	void recursiveSort(CListElement*&pSubList,BOOL bAscendant)
	{
		if (pSubList && pSubList->next)
		{
			CListElement*pSecondHalf = divideFrom(pSubList);
			recursiveSort(pSubList,bAscendant);
			recursiveSort(pSecondHalf,bAscendant);
			pSubList = merge(pSubList,pSecondHalf,bAscendant);
		}
	}

	CListElement*divideFrom(CListElement*pSubList)
	{
		CListElement* pPosition // traverse the entire list
					, *pMidPoint // moves at half speed of position to midpoint
					, *pSecondHalf;
		if (!(pMidPoint = pSubList)) return NULL; // list empty
		pPosition = pMidPoint->next;
		while (pPosition)
		{
			pPosition = pPosition->next;
			if (pPosition)
			{
				pMidPoint = pMidPoint->next;
				pPosition = pPosition->next;
			}
		}
		pSecondHalf = pMidPoint->next;
		pMidPoint->next = NULL;
		return pSecondHalf;
	}

	CListElement*merge(CListElement*pFirst,CListElement*pSecond,BOOL bAscendant)
	{
		CListElement combined;
		CListElement*pLastSorted = &combined;
		while (pFirst && pSecond)
		{
			CListElement*&pTmp = bAscendant ? (pFirst->datum <= pSecond->datum ? pFirst : pSecond)
											: (pFirst->datum >= pSecond->datum ? pFirst : pSecond);
			pLastSorted->next = pTmp;
			pLastSorted = pTmp;
			pTmp = pTmp->next;
		}
		// After one list ends, attach remainder of the other
		pLastSorted->next = pFirst ? pFirst : pSecond;
		return combined.next;
	}
};

#endif // !defined(AFX_SORTABLELINKEDLIST_H__BA0A42D6_F19D_4963_A2D7_508198B87BA3__INCLUDED_)
