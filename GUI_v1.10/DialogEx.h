#if !defined(AFX_DIALOGEX_H__F00DBDF1_2AB1_4F14_9F5C_CE9A8E2172C5__INCLUDED_)
#define AFX_DIALOGEX_H__F00DBDF1_2AB1_4F14_9F5C_CE9A8E2172C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogEx dialog
#include "DrawTool.h"

class CDialogEx : public CDialog
{
// Construction
public:
	CDialogEx(UINT nIDTemplate,CWnd* pParent = NULL);
// Dialog Data
	//{{AFX_DATA(CDialogEx)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogEx)
	protected:
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogEx)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void docToClient(CRect&);
	void docToClient(CPoint&);
	void clientToDoc(CPoint&);
	void clientToDoc(CRect&);
public:
	CString m_strCaption;
	CGraphView*m_pGraphView;
protected:
	CDrawTool m_drawTool;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGEX_H__F00DBDF1_2AB1_4F14_9F5C_CE9A8E2172C5__INCLUDED_)
