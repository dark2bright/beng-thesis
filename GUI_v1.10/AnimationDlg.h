#if !defined(AFX_ANIMATIONDLG_H__DDDB0DF6_0815_4363_9D76_DDF1D74A0086__INCLUDED_)
#define AFX_ANIMATIONDLG_H__DDDB0DF6_0815_4363_9D76_DDF1D74A0086__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AnimationDlg.h : header file
//
#include "Iterator.h"
#include "GraphView.h"
/////////////////////////////////////////////////////////////////////////////
// CAnimationDlg dialog

#define WM_CHANGE_STATE	100
#define MAXCOLOR		2

class CAnimationDlg : public CDialog
{
// Construction
public:
	CAnimationDlg(CWnd* pParent = NULL);
	CAnimationDlg(CWnd* pParent,CIterator& graphicsIterator);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAnimationDlg)
	enum { IDD = IDD_ANIMATION_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	enum {TRACK_EDGE = 1,TRACK_VERTEX = 2};
	enum {AUTOMATIC = 1, MANUAL = 2};
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnimationDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CAnimationDlg)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnOptionsDelaytime();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	virtual void drawAnimation(CDC*);
	virtual void changeState();
	virtual void reset();
	void updateMenuUI();
protected:
	CIterator& m_graphicsIterator;
	COLORREF m_trackColor[MAXCOLOR];
	BOOL m_bFinished;	
	UINT m_currentColor;
	UINT m_delayTime;
public:
	CGraphView*m_pGraphView;
	CString m_strCaption;
	UINT m_mode;
	UINT m_state;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANIMATIONDLG_H__DDDB0DF6_0815_4363_9D76_DDF1D74A0086__INCLUDED_)
