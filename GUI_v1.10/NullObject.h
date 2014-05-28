// NullObject.h: interface for the CNullObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NULLOBJECT_H__C977A05B_CB97_4082_9356_311B95693537__INCLUDED_)
#define AFX_NULLOBJECT_H__C977A05B_CB97_4082_9356_311B95693537__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BObject.h"

class CNullObject : public CObjectEx  
{
	CNullObject();
	static CNullObject m_instance;
public:
	CString toString()const;
	static CNullObject& instance();
	BOOL isNull()const;
	INT typeId()const;
};

#endif // !defined(AFX_NULLOBJECT_H__C977A05B_CB97_4082_9356_311B95693537__INCLUDED_)
