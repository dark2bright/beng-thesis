// ToolBar.cpp : implementation file
//
#include "Stdafx.h"
#include "Resource.h"
#include "ToolBarWrapper.h"


////////////////////////////////////////////////////////////////////////////////
// Clas:	CToolBarWrapper

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	CToolBarWrapper::CToolBarWrapper
// 
// DESCRIPTION:	CToolBarWrapper default constructor loads up main toolbar resource and bitmap
// 
// INPUTS:		
// 
// RETURNS:		
// 
// NOTES:	
// 
// MODIFICATIONS:
// 
// Name			Date		Version	Comments
// N T ALMOND	04002001	1.0		Origin
// 
////////////////////////////////////////////////////////////////////////////////
CToolBarWrapper::CToolBarWrapper()
{
	m_bmHeight	= 0;
	m_bmWidth	= 0;
	m_hGlobal	= NULL;
	m_pData		= NULL;
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	CToolBarWrapper::~CToolBarWrapper
// 
// DESCRIPTION:	CToolBarWrapper default destructor
// 
// INPUTS:		
// 
// RETURNS:		
// 
// NOTES:	
// 
// MODIFICATIONS:
// 
// Name			Date		Version	Comments
// N T ALMOND	04002001	1.0		Origin
// 
////////////////////////////////////////////////////////////////////////////////
CToolBarWrapper::~CToolBarWrapper()
{
	// Free up resources
	UnlockResource(m_hGlobal);
	FreeResource(m_hGlobal);
}

////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	CToolBarWrapper::GetWidth
//
// DESCRIPTION: Helper function to return bitmap button width
//
// INPUTS:		
//
// RETURNS:     Returns the width of the button in pixels
//
// NOTES:       
//
// MODIFICATIONS:
//
// Name			Date      Version	Comments
// N T ALMOND   04002001  1.0		Origin
//
////////////////////////////////////////////////////////////////////////////////
int CToolBarWrapper::GetWidth()
{
	return m_bmWidth;
}

////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	CToolBarWrapper::GetHeight
//
// DESCRIPTION: Helper function to return bitmap button height
//
// INPUTS:		
//
// RETURNS:     Returns the height of the button in pixels
//
// NOTES:       
//
// MODIFICATIONS:
//
// Name			Date      Version	Comments
// N T ALMOND   04002001  1.0		Origin
//
////////////////////////////////////////////////////////////////////////////////
int CToolBarWrapper::GetHeight()
{
	return m_bmHeight;
}

////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	CToolBarWrapper::SetBkColor
//
// DESCRIPTION: Sets image;list background color
//
// INPUTS:		Colorref of color to use when painting background
//
// RETURNS:     
//
// NOTES:       
//
// MODIFICATIONS:
//
// Name			Date      Version	Comments
// N T ALMOND   04002001  1.0		Origin
//
////////////////////////////////////////////////////////////////////////////////
void CToolBarWrapper::SetBkColor(COLORREF crBkColor)
{
	m_imgList.SetBkColor(crBkColor);
}

////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	CToolBarWrapper::DrawByIndex
//
// DESCRIPTION: Draw bitmap from toolbar bitmap by its index
//
// INPUTS:		Pointer to DC, index of Menu Item/Toolbar item, Position.
//
// RETURNS:     
//
// NOTES:       
//
// MODIFICATIONS:
//
// Name			Date      Version	Comments
// N T ALMOND   04002001  1.0		Origin
//
////////////////////////////////////////////////////////////////////////////////
void CToolBarWrapper::DrawByIndex(CDC *pDC,int nIndex,CPoint pt)
{
	m_imgList.Draw(pDC,nIndex,pt,ILD_NORMAL);
}

////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	CToolBarWrapper::DrawByIdentifier
//
// DESCRIPTION: Draw bitmap from toolbar bitmap by its menu Identifer
//
// INPUTS:		Pointer to DC, ID of Menu Item/Toolbar item, Position.
//
// RETURNS:     
//
// NOTES:       
//
// MODIFICATIONS:
//
// Name			Date      Version	Comments
// N T ALMOND   04002001  1.0		Origin
//
////////////////////////////////////////////////////////////////////////////////
void CToolBarWrapper::DrawByIdentifier(CDC *pDC,UINT nId,CPoint pt)
{
	
	int nPos = FindImagePos(nId);
	if (-1 != nPos)
		m_imgList.Draw(pDC,nPos,pt,ILD_NORMAL);
}

////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	CToolBarWrapper::FindImagePos
//
// DESCRIPTION: Finds an command Id within "ToolBar" resource array.
//
// INPUTS:		Command to search for.
//
// RETURNS:     Position minus any ID_SEPARATORS
//
// NOTES:       
//
// MODIFICATIONS:
//
// Name			Date      Version	Comments
// N T ALMOND   04002001  1.0		Origin
//
////////////////////////////////////////////////////////////////////////////////
int CToolBarWrapper::FindImagePos(UINT nID)
{
	int nPos = -1; // Start of with invalid position

	int nAlignment = 0; // Alignment (Total number of ID_SEPARATORS)

	if (m_pData != NULL)
	{
		// Loop down array
		for (int i = 0; i < m_pData->wItemCount; i++)
		{
			if (!m_pData->items()[i])
					nAlignment++; // Count up separators

			if (nID == m_pData->items()[i]) // Match
			{
				nPos = i - nAlignment; // Position of command id in toolbar resource
				break;
			}
		}
	}
	return nPos; // Real image position
}

////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	CToolBarWrapper::LoadResource
//
// DESCRIPTION: Loads a toolbar resource into memory
//
// INPUTS:		Resource Identifier
//
// RETURNS:     T/F
//
// NOTES:       
//
// MODIFICATIONS:
//
// Name			Date      Version	Comments
// N T ALMOND   04002001  1.0		Origin
//
////////////////////////////////////////////////////////////////////////////////
BOOL CToolBarWrapper::LoadResource(UINT nResourceID)
{
	BOOL bRet;

	HINSTANCE hInst = AfxFindResourceHandle(MAKEINTRESOURCE(nResourceID), RT_TOOLBAR);
	HRSRC hRsrc = ::FindResource(hInst, MAKEINTRESOURCE(nResourceID), RT_TOOLBAR);
	if (hRsrc != NULL)
	{
		m_hGlobal = ::LoadResource(hInst, hRsrc);
		if (m_hGlobal != NULL)
		{
			// Load in data 
			m_pData = (CToolBarData*)LockResource(m_hGlobal);

			if (m_pData)
			{
				m_bmHeight	= m_pData->wHeight;
				m_bmWidth	= m_pData->wWidth;

				// Create resource as image list with correct width.
				m_imgList.Create(nResourceID, m_pData->wWidth,1,RGB(192,192,192)); 
				bRet = TRUE;
			}
		}
	}

	return bRet;
}
