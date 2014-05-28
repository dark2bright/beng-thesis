#if !defined(AFX_VERTEXTAB_H__9844F0F0_0096_433C_9E3A_8C5C20A2B679__INCLUDED_)
#define AFX_VERTEXTAB_H__9844F0F0_0096_433C_9E3A_8C5C20A2B679__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VertexTab.h : header file
//
#include "TabPageSSL.h"
/////////////////////////////////////////////////////////////////////////////
// CVertexTab dialog

#include "controlstruct.h"

class CVertexTab : public CTabPageSSL
{
// Construction
public:
	CVertexTab(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVertexTab)
	enum { IDD = IDD_VERTEX_TAB };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVertexTab)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CVertexTab)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnChangeColor();
	afx_msg void OnApply();
	afx_msg void OnSelchangeCombo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bEmptyV;		
	LPCONTROLSTRUCT m_lpControlStruct;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VERTEXTAB_H__9844F0F0_0096_433C_9E3A_8C5C20A2B679__INCLUDED_)
