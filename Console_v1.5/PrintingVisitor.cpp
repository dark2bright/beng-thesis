// PrintingVisitor.cpp: implementation of the CPrintingVisitor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PrintingVisitor.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include "Vertex.h"
#include <iostream.h>

CPrintingVisitor::CPrintingVisitor()
{
}

CPrintingVisitor::~CPrintingVisitor()
{
}

void CPrintingVisitor::visit(CObjectEx&oe)
{
	CVertex& v = (CVertex&) oe;
	cout << ((NUMBER)v) << endl;
}
