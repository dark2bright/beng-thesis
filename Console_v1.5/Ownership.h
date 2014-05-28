// Ownership.h: interface for the COwnership class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OWNERSHIP_H__D3FAE1A3_620A_4511_9220_D8DD360B0C19__INCLUDED_)
#define AFX_OWNERSHIP_H__D3FAE1A3_620A_4511_9220_D8DD360B0C19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class COwnership  
{
public:
	COwnership();
public:
	COwnership (COwnership&);
	BOOL isOwner()const;
	VOID rescindOwnership();
	VOID assertOwnership();
protected:
	BOOL m_bIsOwner;
};

#endif // !defined(AFX_OWNERSHIP_H__D3FAE1A3_620A_4511_9220_D8DD360B0C19__INCLUDED_)
