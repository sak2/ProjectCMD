
// ProjectCMDDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "ProjectCMD.h"
#include "ProjectCMDDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <string>
#include <stdexcept>
#include <array>
#include <memory>

// CProjectCMDDlg dialog



CProjectCMDDlg::CProjectCMDDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROJECTCMD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProjectCMDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_TextBox);
}

BEGIN_MESSAGE_MAP(CProjectCMDDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CProjectCMDDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CProjectCMDDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CProjectCMDDlg message handlers

BOOL CProjectCMDDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CProjectCMDDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CProjectCMDDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CProjectCMDDlg::OnBnClickedCancel() {
	OnCancel();
}

using namespace std;

void CProjectCMDDlg::OnBnClickedOk()
{
	/* Step 1:  Get user input */

	CString TheCommand;
	m_TextBox.GetWindowText(TheCommand);   // Retrieves the text input and stores it as "TheCommand"
	CStringA TheCommandAsChar(TheCommand); // The command comes in as a CString used by MFC, the API requires simple char*


	/* Step 2: Running the command and getting the result */

	array<char, 128> buffer; // The display from CMD itself comes in line by line, which is temporarily stored in this Array
	string result;           // And then added together into this normal String
	unique_ptr<FILE, decltype(&_pclose)> pipe(_popen((const char*)TheCommandAsChar, "r"), _pclose);
	if (!pipe) throw std::runtime_error("popen() failed!"); // The normal error check, if CMD failed to launch
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
		result += buffer.data();
	}

	/* Step 3: Converting the string to MFC's CString for display */
	CString cs(result.c_str());
	AfxMessageBox(cs);
}
