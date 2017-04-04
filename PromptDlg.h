#pragma once


// CPromptDlg dialog

class CPromptDlg : public CDialog
{
	DECLARE_DYNAMIC(CPromptDlg)

public:
	CPromptDlg(const char *desc, CWnd* pParent = NULL);   // standard constructor
	virtual ~CPromptDlg();

// Dialog Data
	enum { IDD = IDD_PROMPT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_Desc;
	CString m_Value;
};
