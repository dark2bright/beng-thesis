// VertexTab.cpp : implementation file
//

#include "stdafx.h"
#include "Thesis.h"
#include "VertexTab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVertexTab dialog


CVertexTab::CVertexTab(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(CVertexTab::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVertexTab)
	//}}AFX_DATA_INIT
}


void CVertexTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVertexTab)
	DDX_Check(pDX, IDC_CHECK, m_lpControlStruct->fastInsertVertex);
	DDX_CBIndex(pDX, IDC_COMBO, m_lpControlStruct->vertexType);
	DDX_Text(pDX, IDC_WEIGHT_EDIT, m_lpControlStruct->defaultWeightOfVertex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVertexTab, CDialog)
	//{{AFX_MSG_MAP(CVertexTab)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CHANGE_COLOR_BUTTON, OnChangeColor)
	ON_BN_CLICKED(ID_APPLY_BUTTON, OnApply)
	ON_CBN_SELCHANGE(IDC_COMBO, OnSelchangeCombo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVertexTab message handlers

BOOL CVertexTab::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_WEIGHT_EDIT);
	pCombo->EnableWindow(m_bEmptyV);
	pCombo->SetCurSel(m_lpControlStruct->vertexType);
	if (m_lpControlStruct->vertexType == None) {
		pEdit->EnableWindow(FALSE);
		return TRUE;
	}
	// Reach here => weighted vertex
	pEdit->EnableWindow(TRUE);
	pEdit->SetWindowText(m_lpControlStruct->defaultWeightOfVertex);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CVertexTab::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CRect rect;
	GetDlgItem(IDC_COLOR)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	// Calculate the area borders and divide by 8 
	int Border = (rect.right - rect.left) / 22;
	rect.InflateRect (-Border, -Border);
	CBrush Brush(m_lpControlStruct->vertexColor);
	dc.FillRect(&rect,&Brush);
	CDialog::OnPaint();
}

void CVertexTab::OnChangeColor() 
{	
	CColorDialog dlg;
	if (dlg.DoModal()==IDOK) 
	{
		m_lpControlStruct->vertexColor = dlg.GetColor();
		Invalidate(FALSE);
	}
}

void CVertexTab::OnApply() 
{
	UpdateData();
}

void CVertexTab::OnSelchangeCombo() 
{
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO);
	INT nResult = pCombo->GetCurSel();
	GetDlgItem(IDC_WEIGHT_EDIT)->EnableWindow(nResult != None);
}

