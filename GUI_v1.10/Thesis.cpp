// Thesis.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Thesis.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "ThesisDoc.h"
#include "ThesisView.h"
#include "ButtonSSL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThesisApp

BEGIN_MESSAGE_MAP(CThesisApp, CWinApp)
	//{{AFX_MSG_MAP(CThesisApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThesisApp construction

CThesisApp::CThesisApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CThesisApp object

CThesisApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CThesisApp initialization

BOOL CThesisApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
//	SetRegistryKey(_T("Dark2Bright Graph Tutorial"));

//	LoadStdProfileSettings(3);  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_GMLTYPE,
		RUNTIME_CLASS(CThesisDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CThesisView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	//* Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);
	//*/
	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	//* Avoid auto new
	if (cmdInfo.m_strFileName !="") 		
		if (!ProcessShellCommand(cmdInfo))
			return FALSE;
	//*/
	/*
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	//*/
	// The main window has been initialized, so show and update it.
	m_nCmdShow |= SW_MAXIMIZE;
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();
	
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	CButtonSSL	m_btnEmail;
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_EMAIL_BUTTON, m_btnEmail);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//{{AFX_MSG_MAP(CAboutDlg)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CThesisApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CThesisApp message handlers


BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	m_btnEmail.SetSSLButtonBitmap (IDB_EMAIL_BITMAP);
	m_btnEmail.SetSSLColor (CButtonSSL::SSL_UP_TEXT_COLOR, RGB (0, 0, 255));
	m_btnEmail.SetSSLColor (CButtonSSL::SSL_OVER_TEXT_COLOR, RGB (0, 0, 255));
	m_btnEmail.SetSSLColor (CButtonSSL::SSL_DOWN_TEXT_COLOR, RGB (0, 0, 255));
	m_btnEmail.SetSSLButtonFont (_T("MS Sans Serif"), 8, TRUE);
	m_btnEmail.SetSSLButtonURL (_T("mailto:dark2bright@gmail.com?Subject=Feedback"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}