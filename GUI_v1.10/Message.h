// Message.h: interface for the CMessage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESSAGE_H__F8E0BE6C_0140_4BDA_A1C7_0B93CED35A30__INCLUDED_)
#define AFX_MESSAGE_H__F8E0BE6C_0140_4BDA_A1C7_0B93CED35A30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

interface CMessage  
{
public:
	virtual void show(CString) = 0;
};

#endif // !defined(AFX_MESSAGE_H__F8E0BE6C_0140_4BDA_A1C7_0B93CED35A30__INCLUDED_)
