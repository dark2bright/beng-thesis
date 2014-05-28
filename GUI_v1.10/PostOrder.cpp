// PostOrder.cpp: implementation of the CPostOrder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thesis.h"
#include "PostOrder.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPostOrder::CPostOrder(CVisitor &v) : visitor(v)
{
}

VOID CPostOrder::postVisit(CObjectEx &object)
{
	visitor.visit(object);
}
