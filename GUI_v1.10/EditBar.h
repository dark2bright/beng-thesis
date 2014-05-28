// EditBar.h: interface for the CEditBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EDITBAR_H__33FDCBF0_8A0E_4196_8988_4C5B20B3380F__INCLUDED_)
#define AFX_EDITBAR_H__33FDCBF0_8A0E_4196_8988_4C5B20B3380F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "scbarg.h"
#include "MenuEx.h"

class CEditBar : public CSizingControlBarG  
{
public:
	CEditBar();
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditBar)
	//}}AFX_VIRTUAL

	// Implementation
public:
	void append(const CString&);
	virtual ~CEditBar();
protected:
	CRichEditCtrl	m_wndEdit;
	// Generated message map functions
protected:
	//{{AFX_MSG(CEditBar)
	afx_msg void OnClear();
	afx_msg void OnCopy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	CMenuEx m_menuContext;
};

#endif // !defined(AFX_EDITBAR_H__33FDCBF0_8A0E_4196_8988_4C5B20B3380F__INCLUDED_)
