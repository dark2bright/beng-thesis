// GMLPairList.h: interface for the CGMLPairList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GMLPAIRLIST_H__C4A83763_2C3E_41B4_88F4_233646B824EB__INCLUDED_)
#define AFX_GMLPAIRLIST_H__C4A83763_2C3E_41B4_88F4_233646B824EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GMLPair.h"

class CGMLPairList  
{
public:
	CGMLPairList(LPGMLPAIR&);
	virtual ~CGMLPairList();
public:
	void remove(LPGMLPAIR);
	LPGMLPAIR lookup(const char*);	
protected:
	LPGMLPAIR& m_head;
};

#endif // !defined(AFX_GMLPAIRLIST_H__C4A83763_2C3E_41B4_88F4_233646B824EB__INCLUDED_)
