// coloredvertex.cpp: implementation of the COLOREDVERTEX class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "coloredvertex.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CColoredVertexPtr::CColoredVertexPtr()
{
	datum = NULL;
}

CColoredVertexPtr::CColoredVertexPtr(const CColoredVertexPtr &target)
{
	assertOwnership();
	(const_cast<CColoredVertexPtr&>(target)).rescindOwnership();
	datum = target.datum;
}

CColoredVertexPtr::~CColoredVertexPtr()
{
	if (isOwner()) free(datum);
}

INT CColoredVertexPtr::typeId() const
{
	return COLOREDVERTEXPTRID;
}

CString CColoredVertexPtr::toString() const
{
	return "ColoredVertexPointer";
}

INT CColoredVertexPtr::compareTo(const CObjectEx &object) const
{
	const CColoredVertexPtr& target = (const CColoredVertexPtr&) object;
	if (datum->valance == target.datum->valance) return 0;
	return datum->valance > target.datum->valance ? 1 : -1;
}

void CColoredVertexPtr::create(UINT vertex)
{
	datum = (LPCOLOREDVERTEX)malloc(sizeof(COLOREDVERTEX));
	datum->vertex = vertex;
	datum->color = -1; // uncolored
	datum->valance = 0;
}
