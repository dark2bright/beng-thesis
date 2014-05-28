// PropertiesGDlg.cpp : implementation file
//

#include "stdafx.h"
#include "thesis.h"
#include "PropertiesGDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertiesGDlg dialog


CPropertiesGDlg::CPropertiesGDlg(CWnd* pParent,LPCONTROLSTRUCT lpControlStruct)
	: CDialog(CPropertiesGDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPropertiesGDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	ASSERT(m_lpControlStruct = lpControlStruct);
}


void CPropertiesGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertiesGDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropertiesGDlg, CDialog)
	//{{AFX_MSG_MAP(CPropertiesGDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertiesGDlg message handlers

BOOL CPropertiesGDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	GetDlgItem(IDC_STRUCTURE)->SetWindowText(m_lpControlStruct->edgeStorage == 0 ? "adjacency matrix" : "adjacency lists");
	if (m_bDirected)
	{
		if (m_lpControlStruct->isNetWork) 
			GetDlgItem(IDC_TYPE)->SetWindowText("network");
		else
			GetDlgItem(IDC_TYPE)->SetWindowText("directed");
	}
	else GetDlgItem(IDC_TYPE)->SetWindowText("undirected");
	CString str;
	str.Format("%d",m_lpControlStruct->maxSize);
	GetDlgItem(IDC_MAX_SIZE)->SetWindowText(str);
	str.Format("%d",m_uNumberOfVertices);
	GetDlgItem(IDC_VERTEX_NUM)->SetWindowText(str);
	if (!m_bDirected) // in undirected graph, each edge is counted twice
		m_uNumberOfEdges /= 2; 
	str.Format("%d",m_uNumberOfEdges);
	GetDlgItem(IDC_EDGE_NUM)->SetWindowText(str);
	CString weightType[] = 
	{
		"None",
		"Int",
		"Float"
	};
	GetDlgItem(IDC_VERTEX_TYPE)->SetWindowText(weightType[m_lpControlStruct->vertexType]);
	GetDlgItem(IDC_EDGE_TYPE)->SetWindowText(weightType[m_lpControlStruct->edgeType]);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
