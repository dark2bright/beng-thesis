// Association.h: interface for the CAssociation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ASSOCIATION_H__01E3B453_02CA_4C2C_AA89_4810205955D6__INCLUDED_)
#define AFX_ASSOCIATION_H__01E3B453_02CA_4C2C_AA89_4810205955D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Ownership.h"
#include "BObject.h"

class CAssociation : 
	public CObjectEx, 
	public COwnership  
{
public:
	CAssociation (CObjectEx&);
	CAssociation (CObjectEx&,CObjectEx&);
	virtual ~CAssociation();
public:
	CObjectEx& getValue () const;
	CObjectEx& getKey () const;
	INT typeId() const;
	INT compareTo (CObjectEx const&object) const;
protected:
    CObjectEx* key;
    CObjectEx* value;
};

#endif // !defined(AFX_ASSOCIATION_H__01E3B453_02CA_4C2C_AA89_4810205955D6__INCLUDED_)
