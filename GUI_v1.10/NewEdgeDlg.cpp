// NewEdgeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Thesis.h"
#include "NewEdgeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewEdgeDlg dialog


CNewEdgeDlg::CNewEdgeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewEdgeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewEdgeDlg)
	m_strName = _T("");
	m_strWeight = _T("");
	m_strCapacity = _T("");
	//}}AFX_DATA_INIT
}


void CNewEdgeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewEdgeDlg)
	DDX_Text(pDX, IDC_NAME_EDIT, m_strName);
	DDX_Text(pDX, IDC_WEIGHT_EDIT, m_strWeight);
	DDX_Text(pDX, IDC_CAPACITY_EDIT, m_strCapacity);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewEdgeDlg, CDialog)
	//{{AFX_MSG_MAP(CNewEdgeDlg)
	ON_BN_CLICKED(IDC_CHANGE_COLOR_BUTTON, OnChangeColor)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewEdgeDlg message handlers

void CNewEdgeDlg::OnChangeColor() 
{
	CColorDialog dlg;
	if (dlg.DoModal()==IDOK) 
	{
		m_color = dlg.GetColor();
		Invalidate(FALSE);
	}
}

void CNewEdgeDlg::OnPaint() 
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

BOOL CNewEdgeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	GetDlgItem(IDC_WEIGHT_EDIT)->EnableWindow(m_bWeighted);
	GetDlgItem(IDC_CAPACITY_EDIT)->EnableWindow(m_bNetworkEdge);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
