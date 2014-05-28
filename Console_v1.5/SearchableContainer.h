// SearchableContainer.h: interface for the CSearchableContainer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEARCHABLECONTAINER_H__CD1E006A_D45F_4928_BB61_259A86CA84E1__INCLUDED_)
#define AFX_SEARCHABLECONTAINER_H__CD1E006A_D45F_4928_BB61_259A86CA84E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Container.h"

class CSearchableContainer : public CContainer  
{
public:
    virtual VOID insert (CObjectEx&) = 0;
    virtual VOID withdraw (CObjectEx&) = 0;
	virtual BOOL isMember (CObjectEx const&) const = 0;
	virtual CObjectEx& find (const CObjectEx&) const = 0;
};

#endif // !defined(AFX_SEARCHABLECONTAINER_H__CD1E006A_D45F_4928_BB61_259A86CA84E1__INCLUDED_)
