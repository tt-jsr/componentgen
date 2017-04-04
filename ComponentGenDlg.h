// ComponentGenDlg.h : header file
//

#pragma once

#include <map>
#include <iostream>
#include <vector>
using namespace std;

// CComponentGenDlg dialog
class CComponentGenDlg : public CDialog
{
// Construction
public:
	CComponentGenDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_COMPONENTGEN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	typedef map<string, string> varmap_t;
	varmap_t m_Vars;

	void Process(const char *in, const char *out);
	void Process(istream& in, ostream& out);

	bool mkpath(const string&);
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	class IOFiles {
	public:
		string infile;
		string outfile;
		string desc;
	};
	vector<IOFiles> m_Files;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedTemplateBrowse();
	afx_msg void OnBnClickedDestBrowse();
	afx_msg void OnBnClickedTtifIdButton();
	CString m_TemplateFile;
	CString m_DestDir;
	CString m_TTIF_ID;
};
