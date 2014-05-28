// NewVertexDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Thesis.h"
#include "NewVertexDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewVertexDlg dialog


CNewVertexDlg::CNewVertexDlg(CWnd* pParent /*=NULL*/,BOOL bWeighted /*=FALSE*/)
	: CDialog(CNewVertexDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewVertexDlg)
	m_strWeight = _T("");
	m_strName = _T("");
	m_bWeighted = bWeighted;
	//}}AFX_DATA_INIT
}

void CNewVertexDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewVertexDlg)
	DDX_Text(pDX, IDC_WEIGHT_EDIT, m_strWeight);
	DDX_Text(pDX, IDC_NAME_EDIT, m_strName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewVertexDlg, CDialog)
	//{{AFX_MSG_MAP(CNewVertexDlg)
	ON_BN_CLICKED(IDC_CHANGE_COLOR_BUTTON, OnChangeColor)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewVertexDlg message handler

void CNewVertexDlg::OnChangeColor() 
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg;
	if (dlg.DoModal()==IDOK) 
	{
		m_color = dlg.GetColor();
		Invalidate(FALSE);
	}
}

void CNewVertexDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CRect rect;
	GetDlgItem(IDC_COLOR)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	// Calculate the area borders and divide by 8 
	int Border = (rect.right - rect.left) / 22;
	rect.InflateRect (-Border, -Border);
	CBrush Brush(m_color);
	dc.FillRect(&rect,&Brush);
	CDialog::OnPaint();
}

BOOL CNewVertexDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	GetDlgItem(IDC_WEIGHT_EDIT)->EnableWindow(m_bWeighted);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
