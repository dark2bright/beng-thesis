#if !defined(AFX_RESIZEGRAPHDLG_H__BDCEBA2E_BA9E_4812_891A_4787CDAD08A6__INCLUDED_)
#define AFX_RESIZEGRAPHDLG_H__BDCEBA2E_BA9E_4812_891A_4787CDAD08A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ResizeGraphDlg.h : header file
//
#define MAXGRAPHSIZE	100
/////////////////////////////////////////////////////////////////////////////
// CResizeGraphDlg dialog

class CResizeGraphDlg : public CDialog
{
// Construction
public:
	CResizeGraphDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CResizeGraphDlg)
	enum { IDD = IDD_RESIZE_GRAPH_DIALOG };
	UINT	m_newSize;
	UINT	m_currentSize;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResizeGraphDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CResizeGraphDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESIZEGRAPHDLG_H__BDCEBA2E_BA9E_4812_891A_4787CDAD08A6__INCLUDED_)
