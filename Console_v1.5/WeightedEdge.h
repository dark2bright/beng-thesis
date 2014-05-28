// WeightedEdge.h: interface for the CWeightedEdge class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WEIGHTEDEDGE_H__2DC3BC0B_FE27_41D8_BAD9_55B4B0962318__INCLUDED_)
#define AFX_WEIGHTEDEDGE_H__2DC3BC0B_FE27_41D8_BAD9_55B4B0962318__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Edge.h"
#include "WeightedNode.h"

class CGraphBuilder;
class CGraphLoader;

class CWeightedEdge : public CEdge, public CWeightedNode
{
protected:
	CWeightedEdge (CVertex&, CVertex&, CObjectEx&);
public:
	virtual void Serialize(CArchive&ar);
	virtual INT typeId()const;
	virtual CEdge& reverse()const;
	friend class CGraphBuilder;
	friend class CGraphLoader;
};

#endif // !defined(AFX_WEIGHTEDEDGE_H__2DC3BC0B_FE27_41D8_BAD9_55B4B0962318__INCLUDED_)
