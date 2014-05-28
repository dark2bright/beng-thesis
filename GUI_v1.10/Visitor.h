// Visitor.h: interface for the CVisitor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VISITOR_H__488761B2_952C_4081_AA42_4494B57FBED0__INCLUDED_)
#define AFX_VISITOR_H__488761B2_952C_4081_AA42_4494B57FBED0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BObject.h"

class CVisitor  
{
public:
	virtual ~CVisitor();
	virtual BOOL isDone() const;
	virtual void visit(CObjectEx&) = 0;
};

#endif // !defined(AFX_VISITOR_H__488761B2_952C_4081_AA42_4494B57FBED0__INCLUDED_)
