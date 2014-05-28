// WeightedNode.cpp: implementation of the CWeightedNode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thesis.h"
#include "WeightedNode.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWeightedNode::CWeightedNode(CObjectEx&weight) : m_pWeight(&weight) 
{
}

CWeightedNode::~CWeightedNode()
{
	if (isOwner())
		delete m_pWeight;
}

CObjectEx& CWeightedNode::getWeight() const
{	
	return *m_pWeight;
}

void CWeightedNode::setWeight(CObjectEx&weight)
{
	delete m_pWeight;
	m_pWeight = &weight;
}
