// DelayTimeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "thesis.h"
#include "DelayTimeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDelayTimeDlg dialog


CDelayTimeDlg::CDelayTimeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDelayTimeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDelayTimeDlg)
	m_newDelayTime = 500;
	//}}AFX_DATA_INIT
}


void CDelayTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDelayTimeDlg)
	DDX_Text(pDX, IDC_NEW_EDIT, m_newDelayTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDelayTimeDlg, CDialog)
	//{{AFX_MSG_MAP(CDelayTimeDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDelayTimeDlg message handlers

BOOL CDelayTimeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	CString str;
	str.Format("%d",m_oldTimeDelay);
	GetDlgItem(IDC_OLD)->SetWindowText(str);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
