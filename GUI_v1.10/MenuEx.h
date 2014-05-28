// Popup.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMenuEx window

#ifndef _MENUEX_H__
#define _MENUEX_H__

#include "ToolBarWrapper.h"

#define RGB_WHITE         RGB( 255, 255, 255 )

class CMenuEx : public CMenu
{
// Construction
public:
	CMenuEx();
	void DrawItem( LPDRAWITEMSTRUCT lpDIS);
	void MeasureItem(CWnd* pWnd,LPMEASUREITEMSTRUCT lpMIS);
	BOOL Initialize(UINT nIDR, CWnd* pParent);
	void SetRadio(CCmdUI* pCmdUI, BOOL bSet);

	// Attributes
protected:
	WORD			Spacing;
	CToolBarWrapper	m_wrapperToolBar;
	CBitmap			m_bmDot;

// Operations
protected:
	COLORREF GetSemiColor();

	BOOL LoadMenu(UINT nId);
	BOOL DrawTick(CDC* pDC,CPoint pt, CRect rcFill, UINT nState);
	BOOL DrawDot(CDC* pDC,CPoint pt, CRect rcFill, UINT nState);

	void SetOwnerMenu(CMenuEx *pMenu);
	void UnSetOwnerMenu(CMenuEx *pMenu);
	void BuildDotBitmap();


// Implementation
public:
	virtual ~CMenuEx();

};

// Data for to associate with a menu item
class CMenuItem
{
public:
	CString		m_strMenu;	// Caption
	int			m_nPos;		// Ordinal
	int			m_bRadio;	// MFC Radio Flag
};

#endif _MENUEX_H__
/////////////////////////////////////////////////////////////////////////////
