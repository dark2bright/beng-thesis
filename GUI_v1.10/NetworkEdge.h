// NetworkEdge.h: interface for the CNetworkEdge class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NETWORKEDGE_H__F14B7A7D_CF06_4390_AD29_08CB9A330606__INCLUDED_)
#define AFX_NETWORKEDGE_H__F14B7A7D_CF06_4390_AD29_08CB9A330606__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WeightedEdge.h"

class CGraphBuilder;
class CGraphLoader;

class CNetworkEdge : public CWeightedEdge  
{
	CNetworkEdge(CVertex&,CVertex&,CObjectEx&,CObjectEx&);
public:
	virtual ~CNetworkEdge();
public:
	CObjectEx& clone()const;
	virtual void Serialize(CArchive&);
	void setCapacity(CObjectEx&);
	CObjectEx& getCapacity()const;
	virtual INT typeId()const;
protected:
	CObjectEx* m_pCapacity;
	friend class CGraphBuilder;
	friend class CGraphLoader;
};

#endif // !defined(AFX_NETWORKEDGE_H__F14B7A7D_CF06_4390_AD29_08CB9A330606__INCLUDED_)
