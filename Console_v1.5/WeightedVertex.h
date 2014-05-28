// WeightedVertex.h: interface for the CWeightedVertex class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WEIGHTEDVERTEX_H__04C4F458_0DFD_4401_A556_F56DB2557BD2__INCLUDED_)
#define AFX_WEIGHTEDVERTEX_H__04C4F458_0DFD_4401_A556_F56DB2557BD2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Vertex.h"
#include "WeightedNode.h"
#include "BObject.h"	// Added by ClassView

class CGraphBuilder;
class CGraphLoader;

class CWeightedVertex : public CVertex , public CWeightedNode
{
protected:
	CWeightedVertex (NUMBER, CObjectEx&);
	friend	class CGraphBuilder;
	friend class CGraphLoader;
public:
	virtual void Serialize(CArchive&ar);
	virtual CObjectEx& clone()const;
	virtual INT typeId()const;
};

#endif // !defined(AFX_WEIGHTEDVERTEX_H__04C4F458_0DFD_4401_A556_F56DB2557BD2__INCLUDED_)
