// PrintingVisitor.h: interface for the CPrintingVisitor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRINTINGVISITOR_H__0B8F23A2_F175_476A_84D6_A48873C80A5D__INCLUDED_)
#define AFX_PRINTINGVISITOR_H__0B8F23A2_F175_476A_84D6_A48873C80A5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Visitor.h"

class CPrintingVisitor : public CVisitor  
{
public:
	void visit(CObjectEx&);
	CPrintingVisitor();
	virtual ~CPrintingVisitor();

};

#endif // !defined(AFX_PRINTINGVISITOR_H__0B8F23A2_F175_476A_84D6_A48873C80A5D__INCLUDED_)
