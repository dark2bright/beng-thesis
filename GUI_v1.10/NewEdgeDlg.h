#if !defined(AFX_NEWEDGEDLG_H__9388C060_8AA3_4D7F_B91F_FEEDACDCA088__INCLUDED_)
#define AFX_NEWEDGEDLG_H__9388C060_8AA3_4D7F_B91F_FEEDACDCA088__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewEdgeDlg.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CNewEdgeDlg dialog

class CNewEdgeDlg : public CDialog
{
// Construction
public:
	CNewEdgeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewEdgeDlg)
	enum { IDD = IDD_NEW_EDGE_DIALOG };
	CString	m_strName;
	CString	m_strWeight;
	CString	m_strCapacity;
	//}}AFX_DATA
	COLORREF m_color;	
	BOOL m_bNetworkEdge;
	BOOL m_bWeighted;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewEdgeDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CNewEdgeDlg)
	afx_msg void OnChangeColor();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWEDGEDLG_H__9388C060_8AA3_4D7F_B91F_FEEDACDCA088__INCLUDED_)
