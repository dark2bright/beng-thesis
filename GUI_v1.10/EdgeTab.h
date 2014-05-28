#if !defined(AFX_EDGETAB_H__E767FD36_C8FD_4D10_9EDC_1728516CEF0F__INCLUDED_)
#define AFX_EDGETAB_H__E767FD36_C8FD_4D10_9EDC_1728516CEF0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EdgeTab.h : header file
//
#include "TabPageSSL.h"
/////////////////////////////////////////////////////////////////////////////
// CEdgeTab dialog

#include "controlstruct.h"

class CEdgeTab : public CTabPageSSL
{
// Construction
public:
	CEdgeTab(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEdgeTab)
	enum { IDD = IDD_EDGE_TAB };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEdgeTab)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CEdgeTab)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnChangeColor();
	afx_msg void OnApply();
	afx_msg void OnSelchangeCombo();
	afx_msg void OnNetworkEdgeCheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bEmptyE;
	LPCONTROLSTRUCT m_lpControlStruct;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDGETAB_H__E767FD36_C8FD_4D10_9EDC_1728516CEF0F__INCLUDED_)
