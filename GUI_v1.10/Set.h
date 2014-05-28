// Set.h: interface for the CSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SET_H__7D7A20F7_EA69_459C_A301_0077DF9A1300__INCLUDED_)
#define AFX_SET_H__7D7A20F7_EA69_459C_A301_0077DF9A1300__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SearchableContainer.h"
#include "Wrapper.h"

class CSet : public CSearchableContainer  
{
public:
	typedef CWrapper<UINT> ELEMENT;

    CSet (UINT n) : universeSize (n) {}
protected:
    UINT universeSize;
};

#endif // !defined(AFX_SET_H__7D7A20F7_EA69_459C_A301_0077DF9A1300__INCLUDED_)
