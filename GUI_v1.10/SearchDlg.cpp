// SearchDlg.cpp : implementation file
//

#include "stdafx.h"
#include "thesis.h"
#include "SearchDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSearchDlg dialog


CSearchDlg::CSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSearchDlg)
	m_uGoal = 0;
	m_uStart = 0;
	//}}AFX_DATA_INIT
}


void CSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchDlg)
	DDX_Text(pDX, IDC_GOAL_EDIT, m_uGoal);
	DDX_Text(pDX, IDC_START_EDIT, m_uStart);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSearchDlg, CDialog)
	//{{AFX_MSG_MAP(CSearchDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchDlg message handlers

BOOL CSearchDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	((CSpinButtonCtrl*)GetDlgItem(IDC_START_SPIN))->SetRange(0,m_uGoal);
	((CSpinButtonCtrl*)GetDlgItem(IDC_GOAL_SPIN))->SetRange(0,m_uGoal);
	m_uStart = 0 ;
	m_uGoal = 0;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
