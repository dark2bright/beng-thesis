// PreOrder.h: interface for the CPreOrder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PREORDER_H__5B4BCF2C_1DF4_430D_B6E7_08566813B993__INCLUDED_)
#define AFX_PREORDER_H__5B4BCF2C_1DF4_430D_B6E7_08566813B993__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PrePostVisitor.h"

class CPreOrder : public CPrePostVisitor  
{
	CVisitor& visitor;
public:
	virtual void preVisit(CObjectEx&);
	CPreOrder(CVisitor&);

};

#endif // !defined(AFX_PREORDER_H__5B4BCF2C_1DF4_430D_B6E7_08566813B993__INCLUDED_)
