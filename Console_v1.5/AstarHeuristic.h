// AstarHeuristic.h: interface for the CAstarHeuristic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ASTARHEURISTIC_H__4C151FE6_F0C5_409B_B443_F5B87726AEAB__INCLUDED_)
#define AFX_ASTARHEURISTIC_H__4C151FE6_F0C5_409B_B443_F5B87726AEAB__INCLUDED_

#include "definitions.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

template<class TYPE>
class CAstarHeuristic  
{
public:
	CAstarHeuristic(NUMBER goal)
	{
		m_goal = goal;
	}
	virtual ~CAstarHeuristic() {}
public:
	NUMBER getGoal()const
	{
		return m_goal;
	}

	virtual TYPE getHeuristicDistance()const = 0;
protected:
	NUMBER m_goal;
};

#endif // !defined(AFX_ASTARHEURISTIC_H__4C151FE6_F0C5_409B_B443_F5B87726AEAB__INCLUDED_)
