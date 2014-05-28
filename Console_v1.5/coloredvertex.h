// coloredvertex.h: interface for the COLOREDVERTEX class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLOREDVERTEX_H__22A64922_3E5B_4A9C_96AE_02FFFE7FE19D__INCLUDED_)
#define AFX_COLOREDVERTEX_H__22A64922_3E5B_4A9C_96AE_02FFFE7FE19D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Ownership.h"
#include "BObject.h"

typedef struct tagCOLOREDVERTEX  
{
	UINT vertex;
	UINT valance;
	INT color;
}COLOREDVERTEX,*LPCOLOREDVERTEX;

class CColoredVertexPtr : public CObjectEx, public COwnership
{
public:
	CColoredVertexPtr();
	CColoredVertexPtr(const CColoredVertexPtr&);
	~CColoredVertexPtr();
public:
	void create(UINT);
	INT compareTo(const CObjectEx &) const;
	CString toString()const;
	INT typeId()const;
public:
	LPCOLOREDVERTEX datum;
};

#endif // !defined(AFX_COLOREDVERTEX_H__22A64922_3E5B_4A9C_96AE_02FFFE7FE19D__INCLUDED_)
