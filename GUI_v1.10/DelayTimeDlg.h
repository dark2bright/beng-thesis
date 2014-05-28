#if !defined(AFX_DELAYTIMEDLG_H__0C6EE5B6_2223_4D9B_A2B2_BEA4CC5AB8AC__INCLUDED_)
#define AFX_DELAYTIMEDLG_H__0C6EE5B6_2223_4D9B_A2B2_BEA4CC5AB8AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DelayTimeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDelayTimeDlg dialog

class CDelayTimeDlg : public CDialog
{
// Construction
public:
	CDelayTimeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDelayTimeDlg)
	enum { IDD = IDD_DELAY_TIME_DIALOG };
	UINT	m_newDelayTime;
	//}}AFX_DATA

	UINT	m_oldTimeDelay;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDelayTimeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDelayTimeDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DELAYTIMEDLG_H__0C6EE5B6_2223_4D9B_A2B2_BEA4CC5AB8AC__INCLUDED_)
