// Ownership.cpp: implementation of the COwnership class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thesis.h"
#include "Ownership.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COwnership::COwnership() : m_bIsOwner(TRUE)
{
}

VOID COwnership::assertOwnership()
{
	m_bIsOwner = TRUE;
}

VOID COwnership::rescindOwnership()
{
	m_bIsOwner = FALSE;
}

BOOL COwnership::isOwner() const
{
	return m_bIsOwner;
}

COwnership::COwnership(COwnership &arg) 
	: m_bIsOwner(arg.m_bIsOwner) 
{
	m_bIsOwner = FALSE;
}
