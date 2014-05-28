#if !defined(AFX_NEWGRAPHDLG_H__30AEED32_975E_4ED6_872D_91F10DC33830__INCLUDED_)
#define AFX_NEWGRAPHDLG_H__30AEED32_975E_4ED6_872D_91F10DC33830__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewGraphDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewGraphDlg dialog

class CNewGraphDlg : public CDialog
{
// Construction
public:
	VOID getParameters(UINT&,BOOL&,BOOL&);
	CNewGraphDlg(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CNewGraphDlg)
	enum { IDD = IDD_NEW_GRAPH_DIALOG };
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewGraphDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	UINT	m_uNumberOfVertices;
	BOOL	m_bDirected;
	BOOL	m_bGraphAsLists;
	// Generated message map functions
	//{{AFX_MSG(CNewGraphDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDirectedRadio();
	afx_msg void OnUndirectedRadio();
	afx_msg void OnMatrixRadio();
	afx_msg void OnListsRadio();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWGRAPHDLG_H__30AEED32_975E_4ED6_872D_91F10DC33830__INCLUDED_)
