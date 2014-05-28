// DrawTool.h: interface for the CDrawTool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWTOOL_H__D8DAA51F_1E9A_4E7D_92D3_C45DD1871B57__INCLUDED_)
#define AFX_DRAWTOOL_H__D8DAA51F_1E9A_4E7D_92D3_C45DD1871B57__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GraphView.h"

class CDialogEx;
// Graph Controller for output dialogs
class CDrawTool  
{
public:
	CDrawTool();
	virtual ~CDrawTool();
public:
	void OnLButtonDown(CDialogEx*,UINT, CPoint);
	void OnLButtonUp(CDialogEx*,UINT , CPoint);
	void OnMouseMove(CDialogEx*,UINT, CPoint);
	void draw(CDC*);
	HCURSOR getCusorHandle() const;
public:
	CGraphView* m_pGraphView;
private:
	CGraphics*m_pSelected;
	CGraphics*m_pTmpSel; // temporary selected by mouse move over
	UINT m_nHitTest;
	CPoint m_prevPoint;
};

#endif // !defined(AFX_DRAWTOOL_H__D8DAA51F_1E9A_4E7D_92D3_C45DD1871B57__INCLUDED_)
