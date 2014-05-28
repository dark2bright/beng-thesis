// EuclideanHeuristic.h: interface for the CEuclideanHeuristic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EUCLIDEANHEURISTIC_H__6F2FAF96_7573_4B37_93F2_7D2974838292__INCLUDED_)
#define AFX_EUCLIDEANHEURISTIC_H__6F2FAF96_7573_4B37_93F2_7D2974838292__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AstarHeuristic.h"
// #include "GraphView.h"

class CEuclideanHeuristic : public CAstarHeuristic<int>  
{
public:
	CEuclideanHeuristic(NUMBER goal);
	virtual ~CEuclideanHeuristic();
protected:
//	CGraphView* m_pGraphView;
};

#endif // !defined(AFX_EUCLIDEANHEURISTIC_H__6F2FAF96_7573_4B37_93F2_7D2974838292__INCLUDED_)
