// ToolbarWrapper.h : header file
//
#ifndef __TOOLBARWRAPPER__
#define __TOOLBARWRAPPER__


/////////////////////////////////////////////////////////////////////////////
// Structure or "ToolBar" Resource - ripped straight from MFC headers
struct CToolBarData
{
	WORD wVersion;
	WORD wWidth;
	WORD wHeight;
	WORD wItemCount;

	WORD* items() { return (WORD*)(this+1); }
};

class CToolBarWrapper
{
public:
	CToolBarWrapper();
	~CToolBarWrapper();

	int		GetHeight();
	int		GetWidth();

	int		FindImagePos(UINT nID);

	void	SetBkColor(COLORREF crBkColor);
	void	DrawByIdentifier(CDC *pDC,UINT nId,CPoint pt);
	void	DrawByIndex(CDC *pDC,int nIndex,CPoint pt);
	BOOL	LoadResource(UINT nResourceID);

protected:

	HANDLE			m_hGlobal;		// Handle of resource
	WORD			m_bmHeight;		// Button Height
	WORD			m_bmWidth;		// Button Width
	CImageList		m_imgList;		// Image list
	CToolBarData*	m_pData;		// Pointer to resource

};

#endif // __TOOLBARWRAPPER__
