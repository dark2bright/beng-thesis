#if !defined(AFX_ASANIMATIONDLG_H__D3790416_9F6C_4E1D_8BDE_4805170F23E9__INCLUDED_)
#define AFX_ASANIMATIONDLG_H__D3790416_9F6C_4E1D_8BDE_4805170F23E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ASAnimationDlg.h : header file
//
#include "BinaryHeap.h"
#include "Wrapper.h"
/////////////////////////////////////////////////////////////////////////////
// CASAnimationDlg dialog
#include "AnimationDlg.h"
#include "Association.h"

#define INFINITY		SHRT_MAX
#define	UnsignedInt		CWrapper<UINT>

class CASAnimationDlg : public CAnimationDlg
{
	class CGraphViewEx : public CGraphView
	{
		friend class CASAnimationDlg;	
	};
	typedef struct tagASTARSTRUCT
	{
		UINT color; // color = 0 ==> undiscover | color = 1 => in OPEN | color = 2 => in CLOSE
		UINT g; // g
		UINT f; // f = g + h
		UINT p; // predecessor
		tagASTARSTRUCT();
	}ASTARSTRUCT,*LPASTARSTRUCT;

	class CAssoc : public CAssociation
	{
		UnsignedInt priority;
	public:
		CAssoc (UINT, CObjectEx&);
		INT typeId() const;
		CString toString()const;
	};
// Construction
public:
	CASAnimationDlg(NUMBER start,NUMBER goal,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CASAnimationDlg)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CASAnimationDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	UINT getDistance(NUMBER, NUMBER)const;
	void init();
	void drawAnimation(CDC*);
	void changeState();
	void reset();
protected:
	CPriorityQueue* m_pQueue;
	CArrayEx<ASTARSTRUCT>* m_pArray;
	CIterator* m_pIter;
	NUMBER m_start;
	NUMBER m_goal;
	// Generated message map functions
	//{{AFX_MSG(CASAnimationDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASANIMATIONDLG_H__D3790416_9F6C_4E1D_8BDE_4805170F23E9__INCLUDED_)
