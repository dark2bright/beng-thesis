// Stack.h: interface for the CStack class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STACK_H__38AF8208_E5BC_4B1E_A4DE_49FED4A4F6E9__INCLUDED_)
#define AFX_STACK_H__38AF8208_E5BC_4B1E_A4DE_49FED4A4F6E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Container.h"

class CStack  : public CContainer
{
public:
    virtual CObjectEx& top () const = 0;
    virtual void push (CObjectEx&) = 0;
    virtual CObjectEx& pop () = 0;
};

#endif // !defined(AFX_STACK_H__38AF8208_E5BC_4B1E_A4DE_49FED4A4F6E9__INCLUDED_)
