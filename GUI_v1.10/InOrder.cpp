// InOrder.cpp: implementation of the CInOrder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thesis.h"
#include "InOrder.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInOrder::CInOrder(CVisitor &v) : visitor(v)
{
}

VOID CInOrder::visit(CObjectEx&object)
{
	visitor.visit(object);
}
