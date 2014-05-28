// Partition.h: interface for the CPartition class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARTITION_H__7507D5E2_D70B_45D4_AFFD_CAA308CC8FE5__INCLUDED_)
#define AFX_PARTITION_H__7507D5E2_D70B_45D4_AFFD_CAA308CC8FE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Set.h"

class CPartition : public CSet
{
public:
	CPartition (UINT);
public:
	CObjectEx& find(const CObjectEx&)const;
    virtual CSet& findEx (const CObjectEx&) const = 0;
    virtual VOID join (CSet&, CSet&) = 0;
};

#endif // !defined(AFX_PARTITION_H__7507D5E2_D70B_45D4_AFFD_CAA308CC8FE5__INCLUDED_)
