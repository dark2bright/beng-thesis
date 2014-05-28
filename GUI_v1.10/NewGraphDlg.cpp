// NewGraphDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Thesis.h"
#include "NewGraphDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewGraphDlg dialog


CNewGraphDlg::CNewGraphDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewGraphDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewGraphDlg)
	m_bDirected = TRUE;
	m_bGraphAsLists = FALSE;
	m_uNumberOfVertices = 10;
	//}}AFX_DATA_INIT
}


void CNewGraphDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewGraphDlg)
	DDX_Text(pDX, IDC_EDIT, m_uNumberOfVertices);
	DDV_MinMaxUInt(pDX, m_uNumberOfVertices, 1, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewGraphDlg, CDialog)
	//{{AFX_MSG_MAP(CNewGraphDlg)
	ON_BN_CLICKED(IDC_DIRECTED_RADIO, OnDirectedRadio)
	ON_BN_CLICKED(IDC_UNDIRECTED_RADIO, OnUndirectedRadio)
	ON_BN_CLICKED(IDC_MATRIX_RADIO, OnMatrixRadio)
	ON_BN_CLICKED(IDC_LISTS_RADIO, OnListsRadio)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewGraphDlg message handlers

BOOL CNewGraphDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	((CButton*)GetDlgItem(IDC_DIRECTED_RADIO))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_MATRIX_RADIO))->SetCheck(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN))->SetRange(1,100);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

VOID CNewGraphDlg::getParameters(UINT &numberOfVertices, BOOL &directed,BOOL&graphaslists)
{
	numberOfVertices = m_uNumberOfVertices;
	directed = m_bDirected;
	graphaslists = m_bGraphAsLists;
}

void CNewGraphDlg::OnDirectedRadio() 
{
	m_bDirected = TRUE;
}

void CNewGraphDlg::OnUndirectedRadio() 
{
	m_bDirected = FALSE;	
}

void CNewGraphDlg::OnMatrixRadio() 
{
	m_bGraphAsLists = FALSE;
	
}

void CNewGraphDlg::OnListsRadio() 
{
	m_bGraphAsLists = TRUE;
}
