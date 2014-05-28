// GMLPairList.cpp: implementation of the CGMLPairList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "thesis.h"
#include "GMLPairList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGMLPairList::CGMLPairList(LPGMLPAIR& head)
: m_head(head)
{
}

CGMLPairList::~CGMLPairList()
{
}

LPGMLPAIR CGMLPairList::lookup(const char *szKey)
{
	LPGMLPAIR tmp = m_head;
	while (tmp) 
	{
		if(strcmp(szKey,tmp->key)==0)
		{
			return tmp;
		}
		tmp = tmp->next;
	}
	return NULL;
}

// This method is only used to remove pair having kind != GML_LIST
// With pair having kind == GML_LIST uses CGMLParser::freeList() instead
void CGMLPairList::remove(LPGMLPAIR pair)
{
	if(!pair) return; // do nothing with NULL 
	if (m_head == pair)
	{
		m_head = pair->next;
		if (pair->kind == GML_STRING) free(pair->value.string);
		free(pair);
		return;
	}
	// pair differ from head
	LPGMLPAIR tmp = m_head;
	while (tmp && tmp->next != pair) 
		tmp = tmp->next;
	tmp->next = pair->next;
	if (pair->kind == GML_STRING) free(pair->value.string);
	free(pair);
}
