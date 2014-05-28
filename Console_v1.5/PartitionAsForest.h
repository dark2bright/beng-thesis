// PartitionAsForest.h: interface for the CPartitionAsForest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARTITIONASFOREST_H__CC6C7AFC_8745_4768_BA68_3D168A5C478F__INCLUDED_)
#define AFX_PARTITIONASFOREST_H__CC6C7AFC_8745_4768_BA68_3D168A5C478F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Partition.h"
#include "BArray.h"

class CPartitionAsForest : public CPartition  
{
	class CPartitionTree : public CSet
	{
		CPartitionTree (UINT,UINT);
	private: // dummy methods inherited from CContainer
		void accept(CVisitor&)const;
		void purge();
	private: // dummy methods inherited from CSearchableContainer
		virtual VOID insert (CObjectEx&);
		virtual VOID withdraw (CObjectEx&);
		virtual BOOL isMember (CObjectEx const&)const;
		virtual CObjectEx& find (const CObjectEx&)const;
	private: // methods inherited from CObjectEx
		virtual INT compareTo(const CObjectEx &target)const;
		INT typeId()const;
		CString toString()const;
	private:
		UINT const item;
		UINT rank;
		CPartitionTree* parent;
		friend class CPartitionAsForest;
	};
public:
	CPartitionAsForest(UINT);
	virtual ~CPartitionAsForest();
public:	
	CSet& findEx (const CObjectEx&)const;
	void join (CSet&, CSet&);
	void accept (CVisitor&) const;
	void purge();
	CString toString()const;
	INT typeId()const;
private: // dummy methods inherited from CSearchableContainer
	virtual VOID insert (CObjectEx&);
	virtual VOID withdraw (CObjectEx&);
	virtual BOOL isMember (CObjectEx const&)const;
	VOID checkArguments (CPartitionTree const&,CPartitionTree const&);
private:
	CArrayEx<CPartitionTree*>array;
};

#endif // !defined(AFX_PARTITIONASFOREST_H__CC6C7AFC_8745_4768_BA68_3D168A5C478F__INCLUDED_)
