// BObject.h: interface for the CObjectEx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOBJECT_H__330FD0A4_D9DE_458F_8C8A_3902A3A8440D__INCLUDED_)
#define AFX_BOBJECT_H__330FD0A4_D9DE_458F_8C8A_3902A3A8440D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Definitions.h"

class CObjectEx // : public CObject
{
public:
	virtual ~CObjectEx();
public:
	virtual CObjectEx& clone()const;
	virtual CString toString()const = 0;
	virtual INT typeId() const = 0;
	virtual BOOL isNull () const;
	BOOL operator == (const CObjectEx & target) const;
	BOOL operator != (const CObjectEx & target) const;
	BOOL operator <= (const CObjectEx & target) const;
	BOOL operator < (const CObjectEx & target) const;
	BOOL operator >= (const CObjectEx & target) const;
	BOOL operator > (const CObjectEx & target) const;
	INT compare(CObjectEx const& object) const;
protected:
	virtual INT compareTo(const CObjectEx &target)const;
};

#endif // !defined(AFX_BOBJECT_H__330FD0A4_D9DE_458F_8C8A_3902A3A8440D__INCLUDED_)
