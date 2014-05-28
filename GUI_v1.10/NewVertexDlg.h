#if !defined(AFX_NEWVERTEXDLG_H__16E1467A_9214_4F44_8096_1834421D824D__INCLUDED_)
#define AFX_NEWVERTEXDLG_H__16E1467A_9214_4F44_8096_1834421D824D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewVertexDlg.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CNewVertexDlg dialog

class CNewVertexDlg : public CDialog
{
// Construction
public:
	CNewVertexDlg(CWnd* pParent = NULL,BOOL bWeighted = FALSE);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CNewVertexDlg)
	enum { IDD = IDD_NEW_VERTEX_DIALOG };
	CString	m_strWeight;
	CString	m_strName;
	//}}AFX_DATA
	COLORREF m_color;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewVertexDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
public:
// Implementation
protected:
	BOOL m_bWeighted;
	// Generated message map functions
	//{{AFX_MSG(CNewVertexDlg)
	afx_msg void OnChangeColor();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWVERTEXDLG_H__16E1467A_9214_4F44_8096_1834421D824D__INCLUDED_)
