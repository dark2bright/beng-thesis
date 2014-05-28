#if !defined(AFX_PROPERTIESGDLG_H__2157295F_5FB7_450F_8757_C195C7A4A225__INCLUDED_)
#define AFX_PROPERTIESGDLG_H__2157295F_5FB7_450F_8757_C195C7A4A225__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropertiesGDlg.h : header file
//
#include "controlstruct.h"
/////////////////////////////////////////////////////////////////////////////
// CPropertiesGDlg dialog

class CPropertiesGDlg : public CDialog
{
// Construction
public:
	CPropertiesGDlg(CWnd* pParent,LPCONTROLSTRUCT lpControlStruct);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPropertiesGDlg)
	enum { IDD = IDD_GRAPH_PROPERTIES_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropertiesGDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPropertiesGDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	LPCONTROLSTRUCT m_lpControlStruct;
	BOOL m_bDirected;
	UINT m_uNumberOfVertices;
	UINT m_uNumberOfEdges;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTIESGDLG_H__2157295F_5FB7_450F_8757_C195C7A4A225__INCLUDED_)
