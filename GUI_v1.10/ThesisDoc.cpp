// ThesisDoc.cpp : implementation of the CThesisDoc class
//

#include "stdafx.h"
#include "Thesis.h"

#include "ThesisDoc.h"
#include "GraphFactory.h"
#include "NewGraphDlg.h"
#include "GraphLoader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThesisDoc

IMPLEMENT_DYNCREATE(CThesisDoc, CDocument)

BEGIN_MESSAGE_MAP(CThesisDoc, CDocument)
	//{{AFX_MSG_MAP(CThesisDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThesisDoc construction/destruction

CThesisDoc::CThesisDoc()
{
	// TODO: add one-time construction code here
	m_pController = NULL;
}

CThesisDoc::~CThesisDoc()
{
	if (m_pController) delete m_pController;
}

BOOL CThesisDoc::OnNewDocument()
{
	CNewGraphDlg dlg;
	int nRet = dlg.DoModal();
	if (nRet == IDCANCEL) return FALSE;
	if (!CDocument::OnNewDocument())
		return FALSE;
	// nRet == IDOK :create graph with specified paramenters
	UINT numberOfVertices;
	BOOL directed;
	BOOL graphaslists;
	CString strOut;
	dlg.getParameters(numberOfVertices,directed,graphaslists);
	m_pController = new CGraphController(numberOfVertices);
	CGraphFactory fact;
	CAbstractGraph* pGraph;
	if (graphaslists) {
		pGraph = fact.buildGraphAsLists(numberOfVertices,directed);
		if (directed)
			strOut.Format("New directed graph as lists\n>> Maximum number of vertices : %d",numberOfVertices);
		else
			strOut.Format("New undirected graph as lists\n>> Maximum number of vertices : %d",numberOfVertices);
	}else{
		pGraph = fact.buildGraphAsMatrix(numberOfVertices,directed);
		if (directed)
			strOut.Format("New directed graph as matrix\n>> Maximum number of vertices : %d",numberOfVertices);
		else
			strOut.Format("New undirected graph as matrix\n>> Maximum number of vertices : %d",numberOfVertices);
	}
	m_pController->attachModelToView(pGraph);
	m_pController->out(strOut);
	m_pController->m_control.maxSize = numberOfVertices;
	m_pController->m_control.edgeStorage = graphaslists ? 1 : 0;
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CThesisDoc serialization

void CThesisDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		m_pController->Serialize(ar);
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CThesisDoc diagnostics

#ifdef _DEBUG
void CThesisDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CThesisDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CThesisDoc commands

BOOL CThesisDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	CGraphLoader loader;
	m_pController = loader.load(lpszPathName);
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	// TODO: Add your specialized creation code here
	return TRUE;
}
