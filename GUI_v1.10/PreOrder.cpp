// PreOrder.cpp: implementation of the CPreOrder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thesis.h"
#include "PreOrder.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CPreOrder::CPreOrder(CVisitor &v) : visitor(v)
{
}

VOID CPreOrder::preVisit(CObjectEx &object)
{
	visitor.visit(object);
}
