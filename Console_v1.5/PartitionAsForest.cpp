// PartitionAsForest.cpp: implementation of the CPartitionAsForest class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PartitionAsForest.h"
#include "NullObject.h"
#include "Definitions.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPartitionAsForest::CPartitionTree::CPartitionTree(UINT _item,UINT universeSize)
:	CSet(universeSize),item(_item),parent(0),rank(0)
{
	m_uCount = 1;
}

INT CPartitionAsForest::CPartitionTree::typeId() const
{
	return PARTITIONTREEID;
}

CString CPartitionAsForest::CPartitionTree::toString() const
{
	return "PartitionTree";
}

VOID CPartitionAsForest::CPartitionTree::insert (CObjectEx&){}

VOID CPartitionAsForest::CPartitionTree::withdraw (CObjectEx&){}

BOOL CPartitionAsForest::CPartitionTree::isMember (CObjectEx const&)const
{
	return TRUE;
}

CObjectEx& CPartitionAsForest::CPartitionTree::find (const CObjectEx&)const
{
	return CNullObject::instance();
}

void CPartitionAsForest::CPartitionTree::accept(CVisitor&)const{}

void CPartitionAsForest::CPartitionTree::purge(){}

INT CPartitionAsForest::CPartitionTree::compareTo(const CObjectEx &target)const { 
	if(item == ((CPartitionTree&)target).item) return 0;
	return item > (((CPartitionTree&)target).item) ? 1 : -1;
}

CPartitionAsForest::CPartitionAsForest(UINT universeSize)
: CPartition(universeSize),array(universeSize)
{
	for (UINT item = 0; item < universeSize; ++item)
		array [item] = new CPartitionTree (item, universeSize);
    m_uCount = universeSize;	
}

CPartitionAsForest::~CPartitionAsForest()
{
	purge();
}

CSet& CPartitionAsForest::findEx(const CObjectEx&object)const
{
	UINT const item = (const CSet::ELEMENT&) (object);
	CPartitionTree* root = array [item];
	while (root->parent != 0)
		root = root->parent;
		CPartitionTree* ptr = array [item];
		while (ptr->parent != 0)
		{
			CPartitionTree* const tmp = ptr->parent;
			ptr->parent = root;
			ptr = tmp;
		}
	return *root;
}

INT CPartitionAsForest::typeId() const
{
	return PARTITIONASFORESTID;
}

CString CPartitionAsForest::toString() const
{
	return "PartitionAsForest";
}

void CPartitionAsForest::purge()
{
	for (UINT item = 0; item < universeSize; ++item)
		delete array[item];
}

void CPartitionAsForest::accept(CVisitor&)const{}

VOID CPartitionAsForest::insert (CObjectEx&){}

VOID CPartitionAsForest::withdraw (CObjectEx&){}

BOOL CPartitionAsForest::isMember (CObjectEx const&)const
{
	return TRUE;
	// remember to rewrite this
}

void CPartitionAsForest::join (CSet&s, CSet&t) 
{
	CPartitionTree& p = (CPartitionTree&)s;
	CPartitionTree& q = (CPartitionTree&)t;
	checkArguments (p, q);
	if (p.m_uCount > q.m_uCount){
		q.parent = &p;
		p.m_uCount += q.m_uCount;
	} else{
		p.parent = &q;
		q.m_uCount += p.m_uCount;
	}
	--m_uCount;
}	

VOID CPartitionAsForest::checkArguments (CPartitionTree const&s, CPartitionTree const&t)
{
	if (  !isMember(s) || s.parent != 0
		||!isMember(t) || t.parent !=0 || s == t){
		AfxMessageBox("Incompatible sets");
		throw std::invalid_argument("Incompatible sets");
	}
}