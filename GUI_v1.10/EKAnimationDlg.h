#if !defined(AFX_EKANIMATIONDLG_H__E45A8241_4821_45C2_958D_5F7236AB621C__INCLUDED_)
#define AFX_EKANIMATIONDLG_H__E45A8241_4821_45C2_958D_5F7236AB621C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EKAnimationDlg.h : header file
//
#include "AnimationDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CEKAnimationDlg dialog : animation dialog for Edmonds-Karp's Algorithm

class CEKAnimationDlg : public CAnimationDlg
{
	class CGraphViewEx : public CGraphView
	{
		friend class CEKAnimationDlg;
	};
// Construction
public:
	void setParas(NUMBER,NUMBER);
	void drawAnimation(CDC*);
	CEKAnimationDlg(CWnd* pParent,CGraphView* pView);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEKAnimationDlg)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEKAnimationDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void init();
	void reset();
	void changeState();
	CAbstractGraph* buildResidualNetwork();

	// Generated message map functions
	//{{AFX_MSG(CEKAnimationDlg)
		// NOTE: the ClassWizard will add member functions here
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	NUMBER m_uSource, m_uSink;
	CIterator* m_pIter;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EKANIMATIONDLG_H__E45A8241_4821_45C2_958D_5F7236AB621C__INCLUDED_)
