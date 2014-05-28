// Template.h: interface for the Template class.
//
//////////////////////////////////////////////////////////////////////
#include "StdAfx.h"

#if !defined(AFX_TEMPLATE_H__C4E74C52_C2CD_4F8E_935A_FDB742CD111B__INCLUDED_)
#define AFX_TEMPLATE_H__C4E74C52_C2CD_4F8E_935A_FDB742CD111B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

template <class T>
class CLinkedList
{
public:
	struct CListElement
	{
		T datum;
		CListElement* next;
		CListElement(): next(NULL){}
		CListElement (T const& _datum, CListElement*_next)
			: next(_next), datum(_datum){}
	};
public:
    CLinkedList ():m_pHead(0), m_pTail(0){}

	CLinkedList (CLinkedList const&linkedList):m_pHead(0), m_pTail(0)
	{
		CListElement const* ptr;
		for (ptr = linkedList.head(); ptr != 0; ptr = ptr->next)
			append (ptr->datum);
	}

    ~CLinkedList (){ purge(); }
public:
    CLinkedList& operator = (CLinkedList const&linkedList){
		if (&linkedList != this){
			purge ();
			CListElement const* ptr;
			for (ptr = linkedList.head(); ptr != 0; ptr = ptr->next)
				append (ptr->datum);
		}
		return *this;	
    }

    CListElement const* head () const { return m_pHead; }
    CListElement const* tail () const { return m_pTail; }

	BOOL contain(const T& item) const {
		if (!m_pHead) return FALSE;
		CListElement*ptr = m_pHead;
		do{
			if(ptr->datum == item) return TRUE;
			ptr = ptr->next;
		}
		while( ptr!= 0);
		return FALSE;
	}

    BOOL isEmpty () const {return m_pHead == 0; }

    T const& first () const{
		if (m_pHead == 0){
			throw std::domain_error ("List is empty");
			AfxMessageBox("List is empty");
		}
		return m_pHead->datum;		
    }
	
    T const& last () const{
		if (tail == 0)
			throw domain_error ("List is empty");
		return m_pTail->datum;		
    }
	
    VOID prepend (T const& item){
		CListElement* const tmp = new CListElement (item, m_pHead);
		if (m_pHead == 0)
			m_pTail = tmp;
		m_pHead = tmp;		
    }

    VOID append (T const& item){
		CListElement* const tmp = new CListElement (item, 0);
		if (m_pHead == 0)
			m_pHead = tmp;
		else
			m_pTail->next = tmp;
		m_pTail = tmp;	
    }

    VOID extract (T const& item){
		CListElement* ptr = m_pHead;
		CListElement* prevPtr = 0;
		while (ptr != 0 && ptr->datum != item)
		{
			prevPtr = ptr;
			ptr = ptr->next;
		}
		if (ptr == 0){
			throw std::invalid_argument ("Item not found");
			AfxMessageBox("Item not found");
		}
		if (ptr == m_pHead)
			m_pHead = ptr->next;
		else
			prevPtr->next = ptr->next;
		if (ptr == m_pTail)
			m_pTail = prevPtr;
		delete ptr;		
    }

	VOID extract(const CListElement*pLE)
	{
		if (m_pHead == pLE) 
		{
			m_pHead = m_pHead->next;
			if (!m_pHead) m_pTail = 0;
			return;
		}
		CListElement* ptr = m_pHead;
		while (ptr != 0 && ptr->next != pLE)
			ptr = ptr->next;
		if (ptr == 0)
		{
			throw std::invalid_argument ("Item not found");
			AfxMessageBox("Item not found");
		}
		if (pLE == m_pTail) 
			m_pTail = ptr;
		ptr->next = pLE->next;
	}

    VOID purge (){
		while (m_pHead != 0){
			CListElement* const tmp = m_pHead;
			m_pHead = m_pHead->next;
			delete tmp;
		}
		m_pTail = 0;		
	}

	UINT getCount()
	{
		if (!m_pHead) return 0;
		UINT nCount = 0;
		CListElement*ptr = m_pHead;
		do{
			nCount++;
			ptr = ptr->next;
		}
		while( ptr!= 0);
		return nCount;
	}

    VOID insertAfter (CListElement const*arg, T const&item){
		CListElement* ptr = const_cast<CListElement*> (arg);
		if (ptr == 0)
			throw invalid_argument ("Invalid position");
		CListElement* const tmp =
			new CListElement (item, ptr->next);
		ptr->next = tmp;
		if (m_pTail == ptr)
			m_pTail = tmp;		
    }

    VOID insertBefore (CListElement const*arg, T const&item){
		CListElement* ptr = const_cast<CListElement*> (arg);
		if (ptr == 0)
			throw invalid_argument ("Invalid position");
		CListElement* const tmp = new CListElement(item, ptr);
		if (m_pHead == ptr)
			m_pHead = tmp;
		else
		{
			CListElement* prevPtr = m_pHead;
			while (prevPtr != 0 && prevPtr->next != ptr)
				prevPtr = prevPtr->next;
			if (prevPtr == 0)
				throw invalid_argument ("Invalid position");
			prevPtr->next = tmp;
		}		
    }
protected:
	CListElement* m_pHead;
    CListElement* m_pTail;
};

#endif // !defined(AFX_TEMPLATE_H__C4E74C52_C2CD_4F8E_935A_FDB742CD111B__INCLUDED_)
