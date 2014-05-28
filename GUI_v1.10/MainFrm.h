// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__B31BADF0_988D_43E8_B3C7_516462F51F3F__INCLUDED_)
#define AFX_MAINFRM_H__B31BADF0_988D_43E8_B3C7_516462F51F3F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EditBar.h"
#include "MDITabs.h"

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
	virtual void OnUpdateFrameTitle(BOOL bAddToTitle); 
// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CToolBar	m_wndGraphBar;
	CToolBar	m_wndUtilBar;
	CToolBar	m_wndAlgorithmBar;
	CToolBar	m_wndNetworkBar;
//	CToolBar	m_wndNPCompleteBar;
	CMDITabs    m_wndMDITabs;	
public:
	CEditBar	m_wndOutputBar;
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewGraph();
	afx_msg void OnUpdateViewGraph(CCmdUI* pCmdUI);
	afx_msg void OnViewOutput();
	afx_msg void OnUpdateViewOutput(CCmdUI* pCmdUI);
	afx_msg void OnViewUtilities();
	afx_msg void OnUpdateViewUtilities(CCmdUI* pCmdUI);
	afx_msg void OnViewAlgorithms();
	afx_msg void OnUpdateViewAlgorithms(CCmdUI* pCmdUI);
	afx_msg void OnViewNetwork();
	afx_msg void OnUpdateViewNetwork(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__B31BADF0_988D_43E8_B3C7_516462F51F3F__INCLUDED_)
