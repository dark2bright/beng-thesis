#if !defined(AFX_GENERATEDLG_H__454C31FA_E1BC_4BDC_8988_2FB512BA307C__INCLUDED_)
#define AFX_GENERATEDLG_H__454C31FA_E1BC_4BDC_8988_2FB512BA307C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GenerateDlg.h : header file
//
#include "controlstruct.h"
/////////////////////////////////////////////////////////////////////////////
// CGenerateDlg dialog

typedef struct tagGENERATESTRUCT
{
	INT numberOfVertices;
	INT numberOfEdges;
	INT vertexType;
	INT edgeType;
	BOOL networkEdge;
	INT vertexWeightUpperBound;
	INT edgeWeightUpperBound;
	INT capacityUpperBound;
	tagGENERATESTRUCT();
}GENERATESTRUCT,*LPGENERATESTRUCT;

class CGenerateDlg : public CDialog
{
// Construction
public:
	CGenerateDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGenerateDlg)
	enum { IDD = IDD_GENERATE_GRAPH_DIALOG };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGenerateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGenerateDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheck();
	afx_msg void OnSelchangeEdgeCombo();
	afx_msg void OnSelchangeVertexCombo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	LPCONTROLSTRUCT m_lpControlStruct;
	GENERATESTRUCT m_generateStruct;
	BOOL m_bDirected;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GENERATEDLG_H__454C31FA_E1BC_4BDC_8988_2FB512BA307C__INCLUDED_)
