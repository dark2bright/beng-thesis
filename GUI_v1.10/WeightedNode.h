// WeightedNode.h: interface for the CWeightedNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WEIGHTEDNODE_H__EE2EA0B6_51F1_48BC_83B7_4F17D155D4A9__INCLUDED_)
#define AFX_WEIGHTEDNODE_H__EE2EA0B6_51F1_48BC_83B7_4F17D155D4A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BObject.h"
#include "Ownership.h"

class CWeightedNode : public COwnership
{
public:
	void setWeight(CObjectEx&);
	CObjectEx& getWeight()const;
	CWeightedNode(CObjectEx&);
	virtual ~CWeightedNode();
protected:
	CObjectEx* m_pWeight;
};

#endif // !defined(AFX_WEIGHTEDNODE_H__EE2EA0B6_51F1_48BC_83B7_4F17D155D4A9__INCLUDED_)
