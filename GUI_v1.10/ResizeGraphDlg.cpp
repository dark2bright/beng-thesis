// ResizeGraphDlg.cpp : implementation file
//

#include "stdafx.h"
#include "thesis.h"
#include "ResizeGraphDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResizeGraphDlg dialog


CResizeGraphDlg::CResizeGraphDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CResizeGraphDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CResizeGraphDlg)
	m_newSize = 0;
	m_currentSize = 0;
	//}}AFX_DATA_INIT
}


void CResizeGraphDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResizeGraphDlg)
	DDX_Text(pDX, IDC_NEW_EDIT, m_newSize);
	DDX_Text(pDX, IDC_CURRENT_EDIT, m_currentSize);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CResizeGraphDlg, CDialog)
	//{{AFX_MSG_MAP(CResizeGraphDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResizeGraphDlg message handlers

BOOL CResizeGraphDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_newSize = m_currentSize + 1;
	UpdateData(FALSE);
	CSpinButtonCtrl* pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN);
	pSpin->SetRange(m_newSize,MAXGRAPHSIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
