// OptionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Thesis.h"
#include "OptionsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg dialog


COptionsDlg::COptionsDlg(CWnd* pParent /*=NULL*/,LPCONTROLSTRUCT lpControlStruct)
	: CDialog(COptionsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptionsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	ASSERT(lpControlStruct);
	m_lpControlStruct = lpControlStruct;
	m_vertexTab.m_lpControlStruct = lpControlStruct;
	m_edgeTab.m_lpControlStruct = lpControlStruct;
}


void COptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_TAB, m_tabOptions);	
	DDX_Control(pDX, IDC_PREV_BUTTON, m_btnPrev);
	DDX_Control(pDX, IDC_NEXT_BUTTON, m_btnNext);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsDlg, CDialog)
	//{{AFX_MSG_MAP(COptionsDlg)
	ON_BN_CLICKED(IDC_NEXT_BUTTON, OnNextButton)
	ON_BN_CLICKED(IDC_PREV_BUTTON, OnPrevButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg message handlers

BOOL COptionsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_btnNext.SetSSLButtonBitmap (IDB_NEXT_BITMAP);
	m_btnNext.SetSSLImageAlign (SSL_IMAGE_RIGHT | SSL_IMAGE_VCENTER);
	m_btnNext.SetSSLTextAlign (SSL_TEXT_LEFT | SSL_TEXT_VCENTER);
	m_btnPrev.SetSSLButtonBitmap (IDB_PREV_BITMAP);
	m_btnPrev.SetSSLImageAlign (SSL_IMAGE_LEFT | SSL_IMAGE_VCENTER);
	m_btnPrev.SetSSLTextAlign (SSL_TEXT_RIGHT | SSL_TEXT_VCENTER);
	// Setup the tab control
	int nPageID = 0;
	m_vertexTab.Create(IDD_VERTEX_TAB,this);
	m_tabOptions.AddSSLPage (_T("Vertex"), nPageID++, &m_vertexTab);
	m_edgeTab.Create(IDD_EDGE_TAB,this);
	m_tabOptions.AddSSLPage (_T("Edge"), nPageID++, &m_edgeTab);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COptionsDlg::OnNextButton() 
{
	int nCurPage = m_tabOptions.GetSSLActivePage ();
	int nNextPage = nCurPage;
	if (m_tabOptions.GetSSLPageCount () - 1 == nCurPage) {
		// Already at last tab, so go to first tab
		nNextPage = 0;
	}
	else {
		nNextPage = nCurPage + 1;
	}
	
	m_tabOptions.ActivateSSLPage (nNextPage);
}

void COptionsDlg::OnPrevButton() 
{
	int nCurPage = m_tabOptions.GetSSLActivePage ();
	int nPrevPage = nCurPage;
	if (0 == nCurPage) {
		// Already at first tab, so go to last tab
		nPrevPage = m_tabOptions.GetSSLPageCount () - 1;
	}
	else {
		nPrevPage = nCurPage - 1;
	}
	
	m_tabOptions.ActivateSSLPage (nPrevPage);
}

void COptionsDlg::setState(BOOL bEmptyV, BOOL bEmptyE)
{
	m_vertexTab.m_bEmptyV = bEmptyV;
	m_edgeTab.m_bEmptyE = bEmptyE;
}
