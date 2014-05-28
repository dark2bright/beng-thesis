// PostOrder.h: interface for the CPostOrder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POSTORDER_H__78B6658E_86F1_4F2A_9976_EEBE14282E32__INCLUDED_)
#define AFX_POSTORDER_H__78B6658E_86F1_4F2A_9976_EEBE14282E32__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PrePostVisitor.h"

class CPostOrder : public CPrePostVisitor  
{
	CVisitor& visitor;
public:
	VOID postVisit(CObjectEx&);
	CPostOrder(CVisitor&);

};

#endif // !defined(AFX_POSTORDER_H__78B6658E_86F1_4F2A_9976_EEBE14282E32__INCLUDED_)
