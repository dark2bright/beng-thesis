#if !defined(AFX_PROPERTIESEDLG_H__F9DC7470_628F_4AD9_A11A_9A8C6F9399A7__INCLUDED_)
#define AFX_PROPERTIESEDLG_H__F9DC7470_628F_4AD9_A11A_9A8C6F9399A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropertiesEDlg.h : header file
//
#include "Edge.h"
/////////////////////////////////////////////////////////////////////////////
// CPropertiesEDlg dialog
#include "controlstruct.h"

class CPropertiesEDlg : public CDialog
{
// Construction
public:
	CPropertiesEDlg(CWnd* pParent = NULL,CEdge* pModel = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPropertiesEDlg)
	enum { IDD = IDD_EDGE_PROPERTIES_DIALOG };
	CString	m_strName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropertiesEDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEdge* m_pModel;
	// Generated message map functions
	//{{AFX_MSG(CPropertiesEDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnChangeColor();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	COLORREF m_color;
	LPCONTROLSTRUCT m_lpControlStruct;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTIESEDLG_H__F9DC7470_628F_4AD9_A11A_9A8C6F9399A7__INCLUDED_)
