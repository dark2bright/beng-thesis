/****************************************************************************\
Datei  : MDITabs.h
Projekt: MDITabs, a tabcontrol for switching between MDI-views
Inhalt : CMDITabs declaration
Datum  : 03.10.2001
Autor  : Christian Rodemeyer
Hinweis: © 2001 by Christian Rodemeyer
\****************************************************************************/
#pragma once

#ifndef __MDITABS_H
#define __MDITABS_H

/****************************************************************************\
CMdiTabs: Deklaration
\****************************************************************************/
class CMDITabs : public CTabCtrl
{
public:
	CMDITabs();
	
	void Create(CFrameWnd* pMainFrame, bool bImages = true);
	void Update(); // sync the tabctrl with all views
	
private:
	HWND       m_mdiClient;
	int        m_height;
	int        m_width;
	CImageList m_images;
	bool       m_bImages;
	
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMDITabs)
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CMDITabs)
	afx_msg void OnSelChange(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaint();
	afx_msg void OnNcPaint();
	//}}AFX_MSG
	afx_msg LRESULT OnSizeParent(WPARAM, LPARAM lParam);
	
	DECLARE_MESSAGE_MAP()
};

#endif
