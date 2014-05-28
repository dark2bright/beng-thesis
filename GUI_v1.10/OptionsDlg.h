#if !defined(AFX_OPTIONSDLG_H__7A5A09AA_9682_4E8C_863F_99C26FA8C198__INCLUDED_)
#define AFX_OPTIONSDLG_H__7A5A09AA_9682_4E8C_863F_99C26FA8C198__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsDlg.h : header file
//
#include "ButtonSSL.h"
#include "TabCtrlSSL.h"

#include "VertexTab.h"
#include "EdgeTab.h"
/////////////////////////////////////////////////////////////////////////////
// COptionsDlg dialog

class COptionsDlg : public CDialog
{
// Construction
public:
	COptionsDlg(CWnd* pParent = NULL,LPCONTROLSTRUCT lpControlStruct = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COptionsDlg)
	enum { IDD = IDD_OPTIONS_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COptionsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnNextButton();
	afx_msg void OnPrevButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void setState(BOOL,BOOL);
protected:
	CButtonSSL	m_btnPrev;
	CButtonSSL	m_btnNext;
	CTabCtrlSSL	m_tabOptions;
private:
	CVertexTab	m_vertexTab;
	CEdgeTab	m_edgeTab;
	LPCONTROLSTRUCT m_lpControlStruct;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSDLG_H__7A5A09AA_9682_4E8C_863F_99C26FA8C198__INCLUDED_)