// InOrder.h: interface for the CInOrder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INORDER_H__48B99FF1_E2FF_4FB6_9D70_A9B6074E0E3D__INCLUDED_)
#define AFX_INORDER_H__48B99FF1_E2FF_4FB6_9D70_A9B6074E0E3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PrePostVisitor.h"

class CInOrder : public CPrePostVisitor  
{
	CVisitor& visitor;
public:
	void visit(CObjectEx&);
	CInOrder(CVisitor&);
};

#endif // !defined(AFX_INORDER_H__48B99FF1_E2FF_4FB6_9D70_A9B6074E0E3D__INCLUDED_)
