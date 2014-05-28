// Edge.h: interface for the CEdge class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EDGE_H__5C6380C0_5250_46E4_B655_ACFA773B7E02__INCLUDED_)
#define AFX_EDGE_H__5C6380C0_5250_46E4_B655_ACFA773B7E02__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BObject.h"
#include "Vertex.h"

class CGraphBuilder;
class CGraphLoader;

class CEdge : public CObjectEx  
{
protected:
	CEdge(CVertex&,CVertex&);
public:
	virtual  ~CEdge();
public:
	BOOL isLoop();
	CObjectEx& clone()const;
	void setEndPoints(CVertex&,CVertex&);
	virtual void Serialize(CArchive&ar);
	virtual CString toString()const;
	virtual CEdge& reverse()const;
	virtual CVertex& mate(const CVertex&)const;
	virtual CVertex& secondEndPoint()const;
	virtual CVertex& firstEndPoint()const;
	virtual INT typeId()const;
protected:
	CVertex &m_vEP1;
	CVertex &m_vEP2;
	friend class CGraphBuilder;
	friend class CGraphLoader;
};

#endif // !defined(AFX_EDGE_H__5C6380C0_5250_46E4_B655_ACFA773B7E02__INCLUDED_)
