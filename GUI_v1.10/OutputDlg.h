#if !defined(AFX_OUTPUTDLG_H__9A65C8FF_A797_4FD7_B4FE_029C52B83410__INCLUDED_)
#define AFX_OUTPUTDLG_H__9A65C8FF_A797_4FD7_B4FE_029C52B83410__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OutputDlg.h : header file
//
// #include "GraphView.h"
#include "DialogEx.h"
/////////////////////////////////////////////////////////////////////////////
// COutputDlg dialog

class COutputDlg : public CDialogEx
{
// Construction
public:
	COutputDlg(CWnd* pParent,CGraphView*pGraphView);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COutputDlg)
	enum { IDD = IDD_OUTPUT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutputDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COutputDlg)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
/*
public:
	CString m_strCaption;
	CGraphView*m_pGraphView;
//*/
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTPUTDLG_H__9A65C8FF_A797_4FD7_B4FE_029C52B83410__INCLUDED_)
