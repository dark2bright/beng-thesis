// ThesisDoc.h : interface of the CThesisDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_THESISDOC_H__9F4390BD_DCDA_4F3F_BB01_924856F06B8F__INCLUDED_)
#define AFX_THESISDOC_H__9F4390BD_DCDA_4F3F_BB01_924856F06B8F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GraphController.h"

class CThesisDoc : public CDocument
{
protected: // create from serialization only
	CThesisDoc();
	DECLARE_DYNCREATE(CThesisDoc)

// Attributes
public:
	CGraphController* m_pController;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThesisDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CThesisDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CThesisDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THESISDOC_H__9F4390BD_DCDA_4F3F_BB01_924856F06B8F__INCLUDED_)
