// StackAsArray.h: interface for the CStackAsArray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STACKASARRAY_H__4A350356_FC1E_4B1A_8EFC_5271A67376B5__INCLUDED_)
#define AFX_STACKASARRAY_H__4A350356_FC1E_4B1A_8EFC_5271A67376B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Stack.h"
#include "BArray.h"

class CStackAsArray : public CStack  
{
public:
	CStackAsArray(UINT);
	virtual ~CStackAsArray();
public:
	CString toString()const;
	INT typeId()const;
    CObjectEx& pop();
	CObjectEx& top() const;
	void push (CObjectEx&);
	void purge();
	void accept (CVisitor&) const;
protected:
	CArrayEx<CObjectEx*> array;
};

#endif // !defined(AFX_STACKASARRAY_H__4A350356_FC1E_4B1A_8EFC_5271A67376B5__INCLUDED_)
