// PromptDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ComponentGen.h"
#include "PromptDlg.h"


// CPromptDlg dialog

IMPLEMENT_DYNAMIC(CPromptDlg, CDialog)
CPromptDlg::CPromptDlg(const char *desc, CWnd* pParent /*=NULL*/)
	: CDialog(CPromptDlg::IDD, pParent)
	, m_Desc(desc)
	, m_Value(_T(""))
{
}

CPromptDlg::~CPromptDlg()
{
}

void CPromptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Desc, m_Desc);
	DDX_Text(pDX, IDC_VALUE, m_Value);
}


BEGIN_MESSAGE_MAP(CPromptDlg, CDialog)
END_MESSAGE_MAP()


// CPromptDlg message handlers
