// PropertiesEDlg.cpp : implementation file
//

#include "stdafx.h"
#include "thesis.h"

#include "PropertiesEDlg.h"
#include "WrapperUtilities.h"
#include "WeightedVertex.h"
#include "NetworkEdge.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertiesEDlg dialog


CPropertiesEDlg::CPropertiesEDlg(CWnd* pParent /*=NULL*/,CEdge* pModel /*=NULL*/)
	: CDialog(CPropertiesEDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPropertiesEDlg)
	m_strName = _T("");
	//}}AFX_DATA_INIT
	ASSERT(pModel);
	m_pModel = pModel;
}


void CPropertiesEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertiesEDlg)
	DDX_Text(pDX, IDC_NAME_EDIT, m_strName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropertiesEDlg, CDialog)
	//{{AFX_MSG_MAP(CPropertiesEDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CHANGE_COLOR_BUTTON, OnChangeColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertiesEDlg message handlers

BOOL CPropertiesEDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	NUMBER from = m_pModel->firstEndPoint();
	NUMBER to = m_pModel->secondEndPoint();
	CString str;
	str.Format("From	     %d	   to	 %d",from,to);
	GetDlgItem(IDC_MODEL)->SetWindowText(str);
	GetDlgItem(IDC_TYPE_EDIT)->SetWindowText(CWrapperUtilities::getType(m_lpControlStruct->edgeType));
	INT type = m_pModel->typeId();
	if (type == WEIGHTEDEDGEID || type == NETWORKEDGEID) 
	{
		CWeightedEdge* pW = (CWeightedEdge*)m_pModel;
		GetDlgItem(IDC_WEIGHT_EDIT)->EnableWindow(TRUE);
		GetDlgItem(IDC_WEIGHT_EDIT)->SetWindowText(pW->getWeight().toString());
	}
	else GetDlgItem(IDC_WEIGHT_EDIT)->EnableWindow(FALSE);
	if (type == NETWORKEDGEID) 
	{
		CNetworkEdge* pN = (CNetworkEdge*)m_pModel;
		GetDlgItem(IDC_CAPACITY_EDIT)->EnableWindow(TRUE);
		GetDlgItem(IDC_CAPACITY_EDIT)->SetWindowText(pN->getCapacity().toString());
	}
	else GetDlgItem(IDC_CAPACITY_EDIT)->EnableWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPropertiesEDlg::OnPaint() 
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

void CPropertiesEDlg::OnChangeColor() 
{
	CColorDialog dlg;
	if (dlg.DoModal()==IDOK) 
	{
		m_color = dlg.GetColor();
		Invalidate(FALSE);
	}
}

void CPropertiesEDlg::OnOK() 
{
	INT type = m_pModel->typeId();
	if (type == WEIGHTEDEDGEID || type == NETWORKEDGEID) 
	{
		CWeightedEdge* pW = (CWeightedEdge*)m_pModel;
		CString strWeight;
		GetDlgItem(IDC_WEIGHT_EDIT)->GetWindowText(strWeight);
		pW->setWeight(CWrapperUtilities::buildWrapper(m_lpControlStruct->edgeType,strWeight));
	}
	if (type == NETWORKEDGEID) 
	{
		CNetworkEdge* pN = (CNetworkEdge*)m_pModel;
		CString strCapacity;
		GetDlgItem(IDC_CAPACITY_EDIT)->GetWindowText(strCapacity);
		pN->setCapacity(CWrapperUtilities::buildWrapper(m_lpControlStruct->edgeType,strCapacity));
	}
	CDialog::OnOK();
}
