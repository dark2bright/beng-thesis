#if !defined(AFX_PROPERTIESVDLG_H__A253B2F0_8F6A_4A2C_A248_9313BB68C8D6__INCLUDED_)
#define AFX_PROPERTIESVDLG_H__A253B2F0_8F6A_4A2C_A248_9313BB68C8D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropertiesVDlg.h : header file
//
#include "Vertex.h"
#include "controlstruct.h"
/////////////////////////////////////////////////////////////////////////////
// CPropertiesVDlg dialog

class CPropertiesVDlg : public CDialog
{
// Construction
public:
	CPropertiesVDlg(CWnd* pParent = NULL,CVertex* pModel = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPropertiesVDlg)
	enum { IDD = IDD_VERTEX_PROPERTIES_DIALOG };
	CString	m_strName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropertiesVDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CVertex*m_pModel;
	// Generated message map functions
	//{{AFX_MSG(CPropertiesVDlg)
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

#endif // !defined(AFX_PROPERTIESVDLG_H__A253B2F0_8F6A_4A2C_A248_9313BB68C8D6__INCLUDED_)
