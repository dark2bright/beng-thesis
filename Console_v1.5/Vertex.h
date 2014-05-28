// Vertex.h: interface for the CVertex class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VERTEX_H__AA3ECF92_677F_4DAC_B6F5_93BE464BB250__INCLUDED_)
#define AFX_VERTEX_H__AA3ECF92_677F_4DAC_B6F5_93BE464BB250__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BObject.h"

// typedef UINT NUMBER;

class CGraphBuilder;
class CGraphLoader;

class CVertex : public CObjectEx  
{
protected:
	CVertex(NUMBER number);
public:
	virtual ~CVertex();
public:
	virtual void Serialize(CArchive&);
	operator NUMBER() const;
	VOID setNumber(NUMBER);
	virtual CString toString()const;
	virtual CObjectEx& clone()const;
	virtual INT typeId()const;
	virtual INT compareTo(const CObjectEx&) const;
protected:
	NUMBER m_uNumber;
	friend class CGraphBuilder;
	friend class CGraphLoader;
};

#endif // !defined(AFX_VERTEX_H__AA3ECF92_677F_4DAC_B6F5_93BE464BB250__INCLUDED_)
