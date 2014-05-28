// EdgeTab.cpp : implementation file
//

#include "stdafx.h"
#include "Thesis.h"
#include "EdgeTab.h"
//#include <afxdlgs.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEdgeTab dialog


CEdgeTab::CEdgeTab(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(CEdgeTab::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEdgeTab)
	//}}AFX_DATA_INIT
}

void CEdgeTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEdgeTab)
	DDX_Text(pDX, IDC_CAPACITY_EDIT, m_lpControlStruct->defaultCapacity);
	DDX_CBIndex(pDX, IDC_COMBO, m_lpControlStruct->edgeType);
	DDX_Check(pDX, IDC_FAST_INSERT_CHECK, m_lpControlStruct->fastInsertEdge);
	DDX_Check(pDX, IDC_NETWORK_EDGE_CHECK, m_lpControlStruct->isNetWork);
	DDX_Text(pDX, IDC_WEIGHT_EDIT, m_lpControlStruct->defaultWeightOfEdge);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEdgeTab, CDialog)
	//{{AFX_MSG_MAP(CEdgeTab)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CHANGE_COLOR_BUTTON, OnChangeColor)
	ON_BN_CLICKED(IDC_APPLY_BUTTON, OnApply)
	ON_CBN_SELCHANGE(IDC_COMBO, OnSelchangeCombo)
	ON_BN_CLICKED(IDC_NETWORK_EDGE_CHECK, OnNetworkEdgeCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEdgeTab message handlers

BOOL CEdgeTab::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CButton* pButton = (CButton*)GetDlgItem(IDC_NETWORK_EDGE_CHECK);
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_WEIGHT_EDIT);
	pButton->EnableWindow(m_bEmptyE);
	pCombo->EnableWindow(m_bEmptyE);
	pCombo->SetCurSel(m_lpControlStruct->edgeType);
	if (m_lpControlStruct->edgeType == None) {
		pEdit->EnableWindow(FALSE);
		pButton->EnableWindow(FALSE);	
	}
	else{
		pEdit->EnableWindow(TRUE);
		pEdit->SetWindowText(m_lpControlStruct->defaultWeightOfEdge);
	}
	GetDlgItem(IDC_CAPACITY_EDIT)->EnableWindow(pButton->GetCheck() == 1);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEdgeTab::OnPaint() 
{
	CPaintDC dc(this); // device context for painting	
	// TODO: Add your message handler code here
	CRect rect;
	GetDlgItem(IDC_COLOR)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	// Calculate the area borders and divide by 8 
	int Border = (rect.right - rect.left) / 22;
	rect.InflateRect (-Border, -Border);
	CBrush Brush(m_lpControlStruct->edgeColor);
	dc.FillRect(&rect,&Brush);
	CDialog::OnPaint();
}

void CEdgeTab::OnChangeColor() 
{
	CColorDialog dlg;
	if (dlg.DoModal()==IDOK) 
	{
		m_lpControlStruct->edgeColor = dlg.GetColor();
		Invalidate(FALSE);
	}
}

void CEdgeTab::OnApply() 
{
	UpdateData();	
}

void CEdgeTab::OnSelchangeCombo() 
{	
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO);
	CButton* pButton = (CButton*)GetDlgItem(IDC_NETWORK_EDGE_CHECK);
	INT nResult = pCombo->GetCurSel();
	BOOL bEnable = (nResult != None);
	GetDlgItem(IDC_WEIGHT_EDIT)->EnableWindow(bEnable);
	pButton->EnableWindow(bEnable && m_bEmptyE);
	if (!bEnable) 
		pButton->SetCheck(0);
}

void CEdgeTab::OnNetworkEdgeCheck() 
{
	CButton* pButton = (CButton*)GetDlgItem(IDC_NETWORK_EDGE_CHECK);
	int nResult = pButton->GetCheck();
	GetDlgItem(IDC_CAPACITY_EDIT)->EnableWindow(nResult == 1);
}
