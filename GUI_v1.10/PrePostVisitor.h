// PrePostVisitor.h: interface for the CPrePostVisitor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PREPOSTVISITOR_H__590B0418_CECD_4204_8718_5A3864F1F70E__INCLUDED_)
#define AFX_PREPOSTVISITOR_H__590B0418_CECD_4204_8718_5A3864F1F70E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Visitor.h"

class CPrePostVisitor : public CVisitor  
{
public:
	virtual void preVisit(CObjectEx&);
	virtual void visit(CObjectEx&);
	virtual void postVisit(CObjectEx&);
};

#endif // !defined(AFX_PREPOSTVISITOR_H__590B0418_CECD_4204_8718_5A3864F1F70E__INCLUDED_)
