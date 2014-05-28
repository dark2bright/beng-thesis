// Popup.cpp : implementation file
//

#include "StdAfx.h"
#include "MenuEx.h"
#include "Resource.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DOT_WIDTH   4
#define DOT_HEIGHT  5

// Bit pattern
// 0110
// 1111
// 1111
// 1111
// 0110
const BYTE _radioDot[] =	{ 0x6, 0xF, 0xF, 0xF, 0x6 }; // simple byte bitmap, 1=> bit on


////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	CMenuEx::CMenuEx
//
// DESCRIPTION: Default Constructor
//
// INPUTS:		
//
// RETURNS:     
//
// NOTES:       
//
// MODIFICATIONS:
//
// Name			Date      Version	Comments
// N T ALMOND   04012001  1.0		Origin
//
////////////////////////////////////////////////////////////////////////////////
CMenuEx::CMenuEx():Spacing(1)
{

}

////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	CMenuEx::LoadMenu
//
// DESCRIPTION: Loads menu and initializes menu with user data
//
// INPUTS:		nId - ID of menu item
//
// RETURNS:     True successful else false
//
// NOTES:       
//
// MODIFICATIONS:
//
// Name			Date      Version	Comments
// N T ALMOND   04012001  1.0		Origin
//
////////////////////////////////////////////////////////////////////////////////
BOOL CMenuEx::LoadMenu(UINT nId)
{
	// Call base and load real menu
	BOOL bRet = CMenu::LoadMenu(nId);
	if (bRet)
	{
		int nCount = GetMenuItemCount();
		for (int nPos=0;nPos < nCount;nPos++)
		{
			CMenuEx *pMenu = (CMenuEx*)GetSubMenu(nPos);
			SetOwnerMenu(pMenu);
		}
	}

	return bRet;
}

////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	CMenuEx::~CMenuEx
//
// DESCRIPTION: Destructor - Delete user objects associated with menu items
//
// INPUTS:		
//
// RETURNS:     
//
// NOTES:       
//
// MODIFICATIONS:
//
// Name			Date      Version	Comments
// N T ALMOND   04012001  1.0		Origin
//
////////////////////////////////////////////////////////////////////////////////
CMenuEx::~CMenuEx()
{
	if (m_hMenu)
	{
		int nCount = GetMenuItemCount();
		for (int nPos=0;nPos < nCount;nPos++)
		{
			CMenuEx *pMenu = (CMenuEx*)GetSubMenu(nPos);
			UnSetOwnerMenu(pMenu);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	CMenuEx::DrawItem
//
// DESCRIPTION: Draws entire menu
//
// INPUTS:		
//
// RETURNS:     
//
// NOTES:       
//
// MODIFICATIONS:
//
// Name			Date      Version	Comments
// N T ALMOND   04012001  1.0		Origin
//
////////////////////////////////////////////////////////////////////////////////
void CMenuEx::DrawItem( LPDRAWITEMSTRUCT lpDIS )
{
	if (ODT_MENU == lpDIS->CtlType)
	{
		// Lets make use of MFC wrappers
		CDC *pDC = CDC::FromHandle(lpDIS->hDC);
		CRect rc(lpDIS->rcItem);
				
		// Check box dimensions
		long lDims = GetMenuCheckMarkDimensions();
		WORD wCheckWidth  = LOWORD(lDims);
		WORD wCheckHeight = HIWORD(lDims);
 
		WORD wWidth  = max(m_wrapperToolBar.GetWidth(), wCheckWidth) + (Spacing*2);
		WORD wHeight = max(m_wrapperToolBar.GetHeight(),wCheckHeight) + (Spacing*2);

		CRect rcFrame(rc.left,rc.top,rc.left+rc.Height(),rc.top+wHeight);

		CRect rcBox(rcFrame);
		rcBox.DeflateRect(1,1);
		// Save off context attributes
		int nIndexDC = pDC->SaveDC();

		CBrush brushFill;
		
		// create brush for selection state
		if (lpDIS->itemState & ODS_SELECTED)
		{
			brushFill.CreateSolidBrush(::GetSysColor(COLOR_HIGHLIGHT));
			pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
		}
		else
			brushFill.CreateSolidBrush(pDC->GetBkColor());

		pDC->SetBkMode(TRANSPARENT);

		CMenuItem* pData = (CMenuItem*)lpDIS->itemData;
		ASSERT(pData);

		// Has this menu item a bitmap?
		BOOL bBitmap = pData->m_nPos != -1;

		// Add some spacing before drawing the text and hi-lite
		CRect rcFill(rc);
		rcFill.top-=1;

		if ((lpDIS->itemState & ODS_SELECTED) && (bBitmap || lpDIS->itemState & ODS_CHECKED))
			rcFill.left+=wWidth+Spacing;

		pDC->FillRect(rcFill, &brushFill);
	
		rc.left += wWidth+Spacing;

		// Make sure we dont include radio buttons...
		if ((lpDIS->itemState & 
			ODS_CHECKED) && 
			!bBitmap)
		{
			CPoint pt(rcFrame.left+(Spacing*2),rcFrame.top+(Spacing*2));
			if (pData->m_bRadio)
				DrawDot(pDC, pt, rcBox, lpDIS->itemState);		
			else
				DrawTick(pDC, pt, rcBox, lpDIS->itemState);		
		}


		// Draw out the bitmap associated with the menu item.
		if (bBitmap)
		{
			// Draw checked state for bitmap
			if (lpDIS->itemState & ODS_CHECKED)
			{		
				CBrush br(GetSemiColor());
				pDC->FillRect(rcBox,&br);
			}

			CPoint pt;

			pt.x = rcFrame.left+((rcFrame.Width() - m_wrapperToolBar.GetWidth())/2);
			pt.y = rcFrame.top+((rcFrame.Height() - m_wrapperToolBar.GetHeight())/2);
			
			m_wrapperToolBar.DrawByIndex(pDC, pData->m_nPos, pt);

		}
			
		// Draw bounding frame			
		if ((lpDIS->itemState & ODS_CHECKED) &&
			!pData->m_bRadio)
		{
			if (!bBitmap)
				rcFrame.DeflateRect(Spacing,Spacing);

			pDC->DrawEdge(rcFrame,BDR_SUNKENOUTER,BF_RECT);
		}
		else
		{
			if (bBitmap && lpDIS->itemState & ODS_SELECTED)
				pDC->DrawEdge(rcFrame,BDR_RAISEDINNER,BF_RECT);
		}

		rc.left+=Spacing;


		DWORD dwDrawFlags = DT_SINGLELINE|DT_VCENTER|DT_LEFT|DT_EXPANDTABS;
		// Draw out menu item caption - text.
		if ((lpDIS->itemState & ODS_GRAYED))
		{
			// This will give it a disable text look 
			if (!(lpDIS->itemState & ODS_SELECTED))
			{
				pDC->SetTextColor(GetSysColor(COLOR_3DHILIGHT));			
				rc.OffsetRect(1,1);
				pDC->DrawText(pData->m_strMenu,rc,dwDrawFlags);
				rc.OffsetRect(-1,-1);

				pDC->SetTextColor(GetSysColor(COLOR_GRAYTEXT));
				pDC->DrawText(pData->m_strMenu,rc,dwDrawFlags);

			}
			else
			{
				COLORREF crGray = (GetSysColor(COLOR_GRAYTEXT) + RGB(64,64,64));
				pDC->SetTextColor(crGray);
				pDC->DrawText(pData->m_strMenu,rc,dwDrawFlags);
			}			

		}
		else
			pDC->DrawText(pData->m_strMenu,rc,dwDrawFlags);

		pDC->RestoreDC(nIndexDC);
	}
}
  
////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	CMenuEx::MeasureItem
//
// DESCRIPTION: Determine menu item width and height.
//
// INPUTS:		Standard API
//
// RETURNS:     Standard API
//
// NOTES:       
//
// MODIFICATIONS:
//
// Name			Date      Version	Comments
// N T ALMOND   04012001  1.0		Origin
//
////////////////////////////////////////////////////////////////////////////////
void CMenuEx::MeasureItem(CWnd* pWnd,LPMEASUREITEMSTRUCT lpMIS)
{
	// Measure out the menu width 'n' height
	// Get the default GUI font and the the extents for the text for the menu string.

	// The menu width is a little bit tricky.
	// Firstly we get the string size (extents)
	// then we add the bitmap width + 2 (for a gap between bitmap and text)
	// if the bitmap has a check mark we add a check mark width.

	if (ODT_MENU == lpMIS->CtlType)
	{
		CDC* pDC = pWnd->GetDC();

		NONCLIENTMETRICS ncm;
		ZeroMemory(&ncm,sizeof(ncm));
		ncm.cbSize = sizeof(ncm);

		// Get the menu dimensions
		SystemParametersInfo(SPI_GETNONCLIENTMETRICS,0,(PVOID)&ncm,FALSE);
		
		// Create a font based on menu metrics
		CFont fnt;
		fnt.CreateFontIndirect(&ncm.lfMenuFont);
		CFont *pFont = pDC->SelectObject(&fnt);
		CMenuItem* pData = (CMenuItem*)lpMIS->itemData;

		CRect rc(0,0,0,0);
		pDC->DrawText(pData->m_strMenu,&rc,DT_SINGLELINE|DT_VCENTER|DT_LEFT|DT_CALCRECT|DT_EXPANDTABS);
		
		CSize sz(rc.Width(),rc.Height());

		// Clean up resources
		pDC->SelectObject(pFont);
		fnt.DeleteObject();
		pWnd->ReleaseDC(pDC);

		// Text width
		lpMIS->itemWidth  = sz.cx;

		// Text Height
		lpMIS->itemHeight = sz.cy;

		long lDims = GetMenuCheckMarkDimensions();
		WORD wCheckWidth  = (WORD)(LOWORD(lDims)+Spacing);
		WORD wCheckHeight = (WORD)(HIWORD(lDims)+Spacing);

		wCheckWidth  = (WORD)max( m_wrapperToolBar.GetWidth(),wCheckWidth);
		wCheckHeight = (WORD)max( m_wrapperToolBar.GetHeight(),wCheckHeight);
		
		lpMIS->itemWidth	+=  wCheckWidth + (Spacing*2);
		lpMIS->itemHeight    = max(lpMIS->itemHeight,wCheckHeight);
		lpMIS->itemHeight	+= (Spacing*2);

	}
}

////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	CMenuEx::SetOwnerMenu
//
// DESCRIPTION: Sets menu up to be ownerdrawn
//
// INPUTS:		Pointer to popup menu
//
// RETURNS:     
//
// NOTES:       Recursive
//
// MODIFICATIONS:
//
// Name			Date      Version	Comments
// N T ALMOND   04012001  1.0		Origin
//
////////////////////////////////////////////////////////////////////////////////
void CMenuEx::SetOwnerMenu(CMenuEx *pMenu)
{
	CString strMenu;
			
	int nCount = pMenu->GetMenuItemCount();

	for (int nPos=0;nPos < nCount;nPos++)
	{
		// Exclude any ole menu IDs
		UINT nID = pMenu->GetMenuItemID(nPos);
		if ((nID >= ID_OLE_VERB_FIRST && nID <= ID_OLE_VERB_LAST) 
			&& (nID >= ID_FILE_MRU_FILE1 && nID <= ID_FILE_MRU_FILE1+15))
		{
			MENUITEMINFO mmi;
			ZeroMemory(&mmi,sizeof(mmi));
			mmi.cbSize = sizeof(mmi);
			
			// Assign user data to menu item
			mmi.fMask = MIIM_TYPE;
			mmi.fType = MFT_OWNERDRAW;
			continue;
		}

		UINT nState = pMenu->GetMenuState(nPos,MF_BYPOSITION);

		// Recurse down any sub-menus
		CMenuEx* pSubMenu = (CMenuEx*)pMenu->GetSubMenu(nPos);

		// Determine if separator - let the system draw this items
		if (!(nState & MF_SEPARATOR))
		{	
			pMenu->GetMenuString(nPos,strMenu,MF_BYPOSITION);

			CMenuItem *pDat = new CMenuItem;

			pDat->m_strMenu = strMenu;			
			pDat->m_nPos = m_wrapperToolBar.FindImagePos(nID);
			pDat->m_bRadio = FALSE;
		
						
			MENUITEMINFO mmi;
			ZeroMemory(&mmi,sizeof(mmi));
			mmi.cbSize = sizeof(mmi);
			
			// Assign user data to menu item
			mmi.fMask = MIIM_DATA | MIIM_TYPE;
			mmi.fType = MFT_OWNERDRAW;
			mmi.dwItemData = (DWORD) pDat;
			::SetMenuItemInfo(pMenu->m_hMenu,nPos,TRUE,&mmi);			

			if (pSubMenu)
				SetOwnerMenu(pSubMenu); // Recursive...Recursive...Recursive...
		
		}
	}
}


////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	CMenuEx::UnSetOwnerMenu
//
// DESCRIPTION: Unsets menu up to be ownerdrawn
//
// INPUTS:		Pointer to popup menu
//
// RETURNS:     
//
// NOTES:       Recursive
//
// MODIFICATIONS:
//
// Name			Date      Version	Comments
// N T ALMOND   04012001  1.0		Origin
//
////////////////////////////////////////////////////////////////////////////////
void CMenuEx::UnSetOwnerMenu(CMenuEx* pMenu)
{
	int nCount = pMenu->GetMenuItemCount();
	for (int nPos=0;nPos < nCount;nPos++)
	{
		// Recurse down any sub-menus
		CMenuEx* pSubMenu = (CMenuEx*)pMenu->GetSubMenu(nPos);

		// Determine if separator
		UINT nState = pMenu->GetMenuState(nPos,MF_BYPOSITION);
		if (!(nState & MF_SEPARATOR))
		{	
			MENUITEMINFO mmi;
			ZeroMemory(&mmi,sizeof(mmi));
			mmi.cbSize = sizeof mmi;
			
			mmi.fMask = MIIM_DATA;
			::GetMenuItemInfo(pMenu->m_hMenu,nPos,TRUE,&mmi);
			
			CMenuItem* pData = (CMenuItem*)mmi.dwItemData;
			
			// Any clean up allocated object
			delete pData;			
			if (pSubMenu)
				UnSetOwnerMenu(pSubMenu); // Recursive...Recursive...Recursive..
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	CMenuEx::GetSemiColor
//
// DESCRIPTION: Creates buttons checked (pressed) color from system palette
//
// INPUTS:		
//
// RETURNS:     Color
//
// NOTES:       
//
// MODIFICATIONS:
//
// Name			Date      Version	Comments
// N T ALMOND   04012001  1.0		Origin
//
////////////////////////////////////////////////////////////////////////////////
COLORREF CMenuEx::GetSemiColor()
{
	COLORREF crHigh3DLite = ::GetSysColor(COLOR_3DHIGHLIGHT);
	COLORREF cr3DFace    = ::GetSysColor(COLOR_3DFACE);

	// Get the different of hilte and face color
	// 
	// PressColor = (Face-HiLite/2)+Face
	//
	DWORD rVal = (GetRValue(crHigh3DLite) - GetRValue(cr3DFace)) / 2;
	DWORD gVal = (GetGValue(crHigh3DLite) - GetGValue(cr3DFace)) / 2;
	DWORD bVal = (GetBValue(crHigh3DLite) - GetBValue(cr3DFace)) / 2;

	return RGB(GetRValue(cr3DFace)+rVal,GetGValue(cr3DFace)+gVal,GetBValue(cr3DFace)+bVal);
}

////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	CMenuEx::Initialize
//
// DESCRIPTION: Initializes the menu 
//
// INPUTS:		Resource ID and Parent Window
//
// RETURNS:     T/F
//
// NOTES:       Called usually after OnCreate in the Parent window creation
//
// MODIFICATIONS:
//
// Name			Date      Version	Comments
// N T ALMOND   04012001  1.0		Origin
//
////////////////////////////////////////////////////////////////////////////////
BOOL CMenuEx::Initialize(UINT nIDR, CWnd* pParent)
{
	m_wrapperToolBar.LoadResource(nIDR);

	if (!LoadMenu(nIDR))
	{
		// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		// !!! Does menu resource exist !!! 
		// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		ASSERT(0);
		return FALSE;
	}

	// If parent window supplied fix up as the default menu
	if (pParent)
	{
		ASSERT(pParent != NULL);
		CMenu* pPreviousMenu = pParent->GetMenu();

		pParent->SetMenu(this);
		
		if (pPreviousMenu)
			pPreviousMenu->DestroyMenu();
	}

	BuildDotBitmap();

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	CMenuEx::DrawTick
//
// DESCRIPTION: Draws of menu Checkmark
//
// INPUTS:		
//
// RETURNS:     
//
// NOTES:       
//
// MODIFICATIONS:
//
// Name			Date      Version	Comments
// N T ALMOND   04012001  1.0		Origin
//
////////////////////////////////////////////////////////////////////////////////
BOOL CMenuEx::DrawTick(CDC* pDC,CPoint pt, CRect rcFill, UINT nState)
{
	
	pDC->FillRect(rcFill,&CBrush(
		nState & ODS_SELECTED ?
		GetSemiColor() :
		GetSysColor(COLOR_3DFACE)		
		));

	CDC dcMem;
	CBitmap	bmTick;

	long lDims = GetMenuCheckMarkDimensions();
	WORD wCheckWidth  = LOWORD(lDims);
	WORD wCheckHeight = HIWORD(lDims);
	CRect rectTick(0,0,wCheckWidth,wCheckHeight);
	
	bmTick.	CreateCompatibleBitmap(pDC,wCheckWidth,wCheckHeight);			
	// Draw checkmark onto bitmap

	dcMem.CreateCompatibleDC(pDC);

	CBitmap* pBitmap = dcMem.SelectObject(&bmTick);
	dcMem.DrawFrameControl(rectTick, DFC_MENU, DFCS_MENUCHECK);

	// Our check is monochrome black on white
	pDC->BitBlt(pt.x, pt.y,wCheckWidth, wCheckHeight, &dcMem, 0,0 ,SRCAND);

	dcMem.SelectObject(pBitmap);
	dcMem.DeleteDC();

	return TRUE;
}	


////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	CMenuEx::SetRadio
//
// DESCRIPTION: Especially designed for MFC
//				Called when pCmdUI->SetRadio(...) is set
//
// INPUTS:		
//
// RETURNS:     
//
// NOTES:       GetRadio is not needed!
//
// MODIFICATIONS:
//
// Name			Date      Version	Comments
// N T ALMOND   04012001  1.0		Origin
//
////////////////////////////////////////////////////////////////////////////////
void CMenuEx::SetRadio(CCmdUI* pCmdUI, BOOL bSet)
{

	MENUITEMINFO mmi;
	ZeroMemory(&mmi,sizeof(mmi));
	mmi.cbSize = sizeof(mmi);
	
	mmi.fMask = MIIM_DATA;

	pCmdUI->m_pMenu->GetMenuItemInfo(pCmdUI->m_nID,&mmi);

	CMenuItem* pData = (CMenuItem*)mmi.dwItemData;

	ASSERT(pData);
	
	pData->m_bRadio = bSet;
}

////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	CMenuEx::BuildDotBitmap
//
// DESCRIPTION: Builds up the DOT menu bitmap
//
// INPUTS:		
//
// RETURNS:     
//
// NOTES:       Ripped from MFC!!!
//
// MODIFICATIONS:
//
// Name			Date      Version	Comments
// N T ALMOND   04012001  1.0		Origin
//
////////////////////////////////////////////////////////////////////////////////
void CMenuEx::BuildDotBitmap()
{
	
	// attempt to load special bitmap, else default to arrow
	CSize size = ::GetMenuCheckMarkDimensions();
	if (size.cx > 32)
		size.cx = 32;

	int iwRow = (size.cx + 15) >> 4;    // # of WORDs per raster line
	int nShift = (size.cx - DOT_WIDTH) / 2;     // # of bits to shift over

	nShift += ((iwRow * 16) - size.cx); // padding for word alignment

	if (nShift > 16 - DOT_WIDTH)
		nShift = 16 - DOT_WIDTH;    // maximum shift for 1 word

	if (size.cy > 32)
		size.cy = 32;

	// bitmap 2/4/4/4/2 pixels wide - centered (0 => black)
	BYTE rgbBitmap[32 * 2 * sizeof(WORD)];
	memset(rgbBitmap, 0xff, sizeof(rgbBitmap));

	BYTE* pbOut = &rgbBitmap[iwRow * sizeof(WORD) *
							((size.cy - (DOT_HEIGHT+1)) >> 1)];

	const BYTE* pbIn = _radioDot;

	for (int y = 0; y < DOT_HEIGHT; y++)
	{
		WORD w = (WORD)~(((DWORD)*pbIn++) << nShift);
		// bitmaps are always hi-lo
		pbOut[0] = HIBYTE(w);
		pbOut[1] = LOBYTE(w);
		pbOut += iwRow * sizeof(WORD);
	}

	if (!m_bmDot.CreateBitmap(size.cx, size.cy, 1, 1,
			(LPVOID)&rgbBitmap) == TRUE)
	{
		TRACE0("Warning: using system arrow bitmap instead of dot.\n");
		#define OBM_MNARROW         32739
		m_bmDot.LoadBitmap(MAKEINTRESOURCE(OBM_MNARROW));
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	CMenuEx::DrawDot
//
// DESCRIPTION: Draw the Radio DOT for MFC menus
//
// INPUTS:		
//
// RETURNS:     
//
// NOTES:       
//
// MODIFICATIONS:
//
// Name			Date      Version	Comments
// N T ALMOND   04012001  1.0		Origin
//
////////////////////////////////////////////////////////////////////////////////
BOOL CMenuEx::DrawDot(CDC* pDC,CPoint pt, CRect rcFill, UINT nState)
{

	long lDims = GetMenuCheckMarkDimensions();
	WORD wCheckWidth  = LOWORD(lDims);
	WORD wCheckHeight = HIWORD(lDims);

	CRect rectDot(0,0,wCheckWidth,wCheckHeight);

	CDC dcMem;
	dcMem.CreateCompatibleDC(pDC);

	CBitmap* pBitmap = dcMem.SelectObject(&m_bmDot);

	// Our check is monochrome black on white
	pDC->BitBlt(pt.x, pt.y,wCheckWidth, wCheckHeight, &dcMem, 0,0 ,SRCAND);

	dcMem.SelectObject(pBitmap);
	dcMem.DeleteDC();

	return TRUE;
}
