#if !defined(AFX_ANIMATIONDLGEX_H__3468CAB2_5555_4B9B_8CE8_62647CB8766E__INCLUDED_)
#define AFX_ANIMATIONDLGEX_H__3468CAB2_5555_4B9B_8CE8_62647CB8766E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AnimationDlgEx.h : header file
//
#include "AnimationDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CAnimationDlgEx dialog

class CAnimationDlgEx : public CAnimationDlg
{
// Construction
public:
	CAnimationDlgEx(CWnd*,CIterator&);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAnimationDlgEx)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnimationDlgEx)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CAnimationDlgEx)
	afx_msg void OnDestroy();
	afx_msg void OnOptionsDelaytime();	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	void drawAnimation(CDC*);
	void changeState();	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANIMATIONDLGEX_H__3468CAB2_5555_4B9B_8CE8_62647CB8766E__INCLUDED_)
