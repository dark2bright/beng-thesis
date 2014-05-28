// PropertiesVDlg.cpp : implementation file
//

#include "stdafx.h"
#include "thesis.h"
#include "PropertiesVDlg.h"
#include "WrapperUtilities.h"
#include "WeightedVertex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertiesVDlg dialog


CPropertiesVDlg::CPropertiesVDlg(CWnd* pParent /*=NULL*/,CVertex* pModel /*=NULL*/)
	: CDialog(CPropertiesVDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPropertiesVDlg)
	m_strName = _T("");
	//}}AFX_DATA_INIT
	ASSERT(pModel);
	m_pModel = pModel;
}


void CPropertiesVDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertiesVDlg)
	DDX_Text(pDX, IDC_NAME_EDIT, m_strName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropertiesVDlg, CDialog)
	//{{AFX_MSG_MAP(CPropertiesVDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CHANGE_COLOR_BUTTON, OnChangeColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertiesVDlg message handlers

BOOL CPropertiesVDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString strNumber;
	strNumber.Format("%d",(NUMBER)(*m_pModel));
	GetDlgItem(IDC_NUMBER_EDIT)->SetWindowText(strNumber);
	GetDlgItem(IDC_TYPE_EDIT)->SetWindowText(CWrapperUtilities::getType(m_lpControlStruct->vertexType));
	if (m_pModel->typeId() == VERTEXID) // Unweighted Vertex
		GetDlgItem(IDC_WEIGHT_EDIT)->EnableWindow(FALSE);
	else
	{
		GetDlgItem(IDC_WEIGHT_EDIT)->EnableWindow(TRUE);
		GetDlgItem(IDC_WEIGHT_EDIT)->SetWindowText(((CWeightedVertex*)m_pModel)->getWeight().toString());
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPropertiesVDlg::OnPaint() 
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

void CPropertiesVDlg::OnChangeColor() 
{
	CColorDialog dlg;
	if (dlg.DoModal()==IDOK) 
	{
		m_color = dlg.GetColor();
		Invalidate(FALSE);
	}
}

void CPropertiesVDlg::OnOK() 
{
	if (m_pModel->typeId() == WEIGHTEDVERTEXID) // if unweighted vertex => update
	{
		CString strWeight;
		CWeightedVertex* pModel = (CWeightedVertex*)m_pModel;
		GetDlgItem(IDC_WEIGHT_EDIT)->GetWindowText(strWeight);
		pModel->setWeight(CWrapperUtilities::buildWrapper(m_lpControlStruct->vertexType,strWeight));
	}
	CDialog::OnOK();
}
