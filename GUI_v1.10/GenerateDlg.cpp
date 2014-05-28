// GenerateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "thesis.h"
#include "GenerateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGenerateDlg dialog
tagGENERATESTRUCT::tagGENERATESTRUCT()
{
	numberOfVertices = 25;
	numberOfEdges = 25;
	vertexType = 0;
	edgeType = 0 ;
	networkEdge = FALSE;
	vertexWeightUpperBound = INT_MAX;
	edgeWeightUpperBound = INT_MAX;
	capacityUpperBound = INT_MAX;
}

CGenerateDlg::CGenerateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGenerateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGenerateDlg)
	//}}AFX_DATA_INIT
}


void CGenerateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGenerateDlg)
	DDX_Text(pDX, IDC_NUMV_EDIT, m_generateStruct.numberOfVertices);
	DDX_Text(pDX, IDC_NUME_EDIT, m_generateStruct.numberOfEdges);
	DDX_Text(pDX, IDC_VWU_EDIT, m_generateStruct.vertexWeightUpperBound);
	DDX_Text(pDX, IDC_EWU_EDIT, m_generateStruct.edgeWeightUpperBound);
	DDX_Text(pDX, IDC_ECU_EDIT, m_generateStruct.capacityUpperBound);
	DDX_CBIndex(pDX, IDC_VERTEX_COMBO, m_generateStruct.vertexType);
	DDX_CBIndex(pDX, IDC_EDGE_COMBO, m_generateStruct.edgeType);
	DDX_Check(pDX, IDC_CHECK, m_generateStruct.networkEdge);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGenerateDlg, CDialog)
	//{{AFX_MSG_MAP(CGenerateDlg)
	ON_BN_CLICKED(IDC_CHECK, OnCheck)
	ON_CBN_SELCHANGE(IDC_EDGE_COMBO, OnSelchangeEdgeCombo)
	ON_CBN_SELCHANGE(IDC_VERTEX_COMBO, OnSelchangeVertexCombo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGenerateDlg message handlers

BOOL CGenerateDlg::OnInitDialog() 
{
	m_generateStruct.numberOfVertices = m_lpControlStruct->maxSize;
	m_generateStruct.numberOfEdges = m_lpControlStruct->maxSize;

	CDialog::OnInitDialog();
	
	((CComboBox*)GetDlgItem(IDC_VERTEX_COMBO))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_EDGE_COMBO))->SetCurSel(0);
	((CButton*)GetDlgItem(IDC_CHECK))->SetCheck(0);
	GetDlgItem(IDC_VWU_EDIT)->EnableWindow(FALSE);
	GetDlgItem(IDC_EWU_EDIT)->EnableWindow(FALSE);
	GetDlgItem(IDC_ECU_EDIT)->EnableWindow(FALSE);
	((CSpinButtonCtrl*)GetDlgItem(IDC_VERTEX_SPIN))->SetRange(0,m_lpControlStruct->maxSize);
	((CSpinButtonCtrl*)GetDlgItem(IDC_EDGE_SPIN))->SetRange(0,m_lpControlStruct->maxSize * m_lpControlStruct->maxSize);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGenerateDlg::OnCheck() 
{
	int nRet = ((CButton*)GetDlgItem(IDC_CHECK))->GetCheck();
	GetDlgItem(IDC_ECU_EDIT)->EnableWindow(nRet == 1);
}

void CGenerateDlg::OnSelchangeEdgeCombo() 
{
	int nCurSel = ((CComboBox*)GetDlgItem(IDC_EDGE_COMBO))->GetCurSel();
	GetDlgItem(IDC_EWU_EDIT)->EnableWindow(nCurSel != 0);
	CButton* pCheck = (CButton*)GetDlgItem(IDC_CHECK);
	if (nCurSel == 0) pCheck->SetCheck(0);
	pCheck->EnableWindow(nCurSel != 0 && m_bDirected);
	GetDlgItem(IDC_ECU_EDIT)->EnableWindow(nCurSel != 1 && pCheck->GetCheck() == 1);
}

void CGenerateDlg::OnSelchangeVertexCombo() 
{
	int nCurSel = ((CComboBox*)GetDlgItem(IDC_VERTEX_COMBO))->GetCurSel();
	GetDlgItem(IDC_VWU_EDIT)->EnableWindow(nCurSel != 0);	
}
