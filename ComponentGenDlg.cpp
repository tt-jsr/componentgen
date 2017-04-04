// ComponentGenDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ComponentGen.h"
#include "ComponentGenDlg.h"
#include ".\componentgendlg.h"
#include "time.h"
#include "fstream"
#include "promptdlg.h"
#include <vector>
#include "Xml.h"
#include <io.h>
#include <direct.h>
#include <strstream>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CComponentGenDlg dialog



CComponentGenDlg::CComponentGenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CComponentGenDlg::IDD, pParent)
	, m_TemplateFile(_T(""))
	, m_DestDir(_T(""))
	, m_TTIF_ID(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CComponentGenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TEMPLATE, m_TemplateFile);
	DDX_Text(pDX, IDC_DEST, m_DestDir);
	//DDX_Text(pDX, IDC_TTIF_ID, m_TTIF_ID);
}

BEGIN_MESSAGE_MAP(CComponentGenDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_TEMPLATE_BROWSE, OnBnClickedTemplateBrowse)
	ON_BN_CLICKED(IDC_DEST_BROWSE, OnBnClickedDestBrowse)
	ON_BN_CLICKED(IDC_TTIF_ID_BUTTON, OnBnClickedTtifIdButton)
END_MESSAGE_MAP()


// CComponentGenDlg message handlers

BOOL CComponentGenDlg::OnInitDialog()
{
	OnBnClickedTtifIdButton();

	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CComponentGenDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CComponentGenDlg::OnPaint() 
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CComponentGenDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CComponentGenDlg::OnBnClickedOk()
{
	OnOK();

	Xml xml;
	ifstream ifs;

	ifs.open(m_TemplateFile);

	xml.open(ifs);
	CString out;

	xml.GetNextElement();
	while (xml.IsEndElement("root") == false) {
		if (xml.IsStartElement("file") == true) {
			IOFiles file;
			while (xml.IsEndElement("file") == false) {
				if (xml.IsStartElement("input") == true) {
					file.infile = xml.GetValue("input");
				}
				if (xml.IsStartElement("output") == true) {
					file.outfile = xml.GetValue("output");
				}
				if (xml.IsStartElement("desc") == true) {
					file.desc = xml.GetValue("desc");
				}
				xml.GetNextElement();
			}
			m_Files.push_back(file);
		}
        if (xml.IsStartElement("command") == true) {
            const char *cmd = xml.GetValue("command");
            system(cmd);
        }
		if (xml.IsStartElement("variable") == true) {
			string name;
			string value;
			string prompt;
			while(xml.IsEndElement("variable") == false) {				
				if (xml.IsStartElement("name") == true) {
					name = xml.GetValue("name");
				}
				if (xml.IsStartElement("prompt") == true) {
					prompt = xml.GetValue("prompt");
				}
				if (xml.IsStartElement("value") == true) {
					value = xml.GetValue("value");
					istrstream strmin(value.c_str());
					ostrstream strmout;
					Process(strmin, strmout);
					strmout << ends;
					m_Vars.insert(varmap_t::value_type(name, strmout.str()));
				}
				if (xml.IsStartElement("file") == true) {
					string filename = xml.GetValue("file");
					m_Vars.insert(varmap_t::value_type(name, filename));
				}
				xml.GetNextElement();
			}
			if (prompt.size()) {
				// <prompt> was defined, so pop up a dialog box
				CPromptDlg dlg(prompt.c_str());
				if (dlg.DoModal() == IDOK) {
					value = dlg.m_Value;
					m_Vars.insert(varmap_t::value_type(name, value));
				}
			}
		}
		xml.GetNextElement();
	}

	for (size_t i = 0; i < m_Files.size(); i++) {
		IOFiles &file = m_Files[i];
		strstream in((char *)file.outfile.c_str(), (streamsize)file.outfile.size());
		strstream out;
		Process(in, out);	// substitute any vars
		in << ends;
		out << ends;
		file.outfile = m_DestDir;
		file.outfile += "\\";
		file.outfile += out.str();
		mkpath(file.outfile);
		Process(file.infile.c_str(), file.outfile.c_str());
	}
}

// Craeted any needed directories
bool CComponentGenDlg::mkpath(const string& path)
{
	char drive[_MAX_DRIVE], buf[255];
	strcpy(buf, path.c_str());
	string pp;

	_splitpath(path.c_str(), drive, buf, NULL, NULL);
    pp = drive;
	char *p = strtok(buf, "/\\");
	while (p) {
		pp += '\\';
		pp += p;	
        int n = _access(pp.c_str(), 00);
 		if (n < 0) {
			_mkdir(pp.c_str());
		}
		p = strtok(NULL, "/\\");
	}
	return true;
}

void CComponentGenDlg::Process(const char *in, const char *out)
{
	ifstream ifs;
	ofstream ofs;

	ifs.open(in);
	if (ifs.is_open() == false) {
		CString s;
		s = "Cannot open ";
		s += in;
		AfxMessageBox(s);
		return;
	}
	ofs.open(out);
	if (ofs.is_open() == false) {
		CString s;
		s = "Cannot open ";
		s += out;
		AfxMessageBox(s);
		return;
	}
	Process(ifs, ofs);
}

void CComponentGenDlg::Process(istream& istr, ostream& ostr)
{
	char c;
    enum {UPPER,LOWER,NORMAL};
    int ForceCase = NORMAL;
    char ForceCaseChar = '$';

	while (istr.eof() == false) {
		c = istr.get();
		if (istr.eof())
			return;
        ForceCase = NORMAL;
		switch (c) {
		case '$':
        case '%':
        case '@':
            if ('%' == c)
            {
                ForceCase = LOWER;
                ForceCaseChar = '%';
            }
            if ('@' == c)
            {
                ForceCase = UPPER;
                ForceCaseChar = '@';
            }
            if ('$' == c)
            {
                ForceCase = NORMAL;
                ForceCaseChar = '$';
            }
			c = istr.get();
			if (c == '(') {
				string var;
				c = istr.get();
				while (c != ')') {
					var += c;
					c = istr.get();
				}
				if (stricmp(var.c_str(), "DATE") == 0) {
					time_t t = time(NULL);
					char *p = ctime(&t);
					p[24] = '\0';
					ostr << p;
				} else if (stricmp(var.c_str(), "TIMESTAMP") == 0) {
					ostr << time(NULL);
				} else if (stricmp(var.c_str(), "RANDOM") == 0) {
					ostr << rand() << rand();
				} else if (stricmp(var.c_str(), "GUID") == 0) {
					UUID   uuid;
					UCHAR          *uuidStr;

					UuidCreate(&uuid);
					UuidToString(&uuid, &uuidStr);
					ostr << uuidStr << rand();
					RpcStringFree(&uuidStr);
				} else {
					varmap_t::iterator it = m_Vars.find(var);
					if (it == m_Vars.end())
                    {
						ostr << ForceCaseChar <<"(" << var.c_str() << ")";
                    }
					else
                    {
                        if (ForceCase == LOWER)
                        {
                            string::iterator sit = (*it).second.begin();
                            while (sit != (*it).second.end())
                            {
                                ostr << (char)tolower(*sit);
                                ++sit;
                            }
                        }
                        if (ForceCase == UPPER)
                        {
                            string::iterator sit = (*it).second.begin();
                            while (sit != (*it).second.end())
                            {
                                ostr << (char)toupper(*sit);
                                ++sit;
                            }
                        }
                        if (ForceCase == NORMAL)
                        {
						    ostr << (*it).second;
                        }
                    }
				}				
			} else {
				ostr << ForceCaseChar << c;
			}
			break;
		default:
			ostr << c;
			break;
		}
	}
}

void CComponentGenDlg::OnBnClickedTemplateBrowse()
{
	CFileDialog dlg(TRUE);
	dlg.m_ofn.lpstrFilter = "Template files\0*.tmpl\0All files\0*.*\0\0";
	if (dlg.DoModal() == IDOK) {
		m_TemplateFile = dlg.GetPathName();
		UpdateData(FALSE);
	}
}

void CComponentGenDlg::OnBnClickedDestBrowse()
{
	BROWSEINFO bi;
	LPITEMIDLIST pidl;
	char buf[MAX_PATH];

	bi.hwndOwner = GetSafeHwnd();
	bi.pidlRoot = NULL;
	bi.pszDisplayName = buf;
	bi.lpszTitle = "Select dest directory";
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;


	pidl = SHBrowseForFolder(&bi);
	if (pidl == NULL)
		return;

	if (SHGetPathFromIDList(pidl, buf) == FALSE) {
		AfxMessageBox("Directory selection failed");
		return;
	}
    
	m_DestDir = buf;
	CoTaskMemFree(pidl);	
	
	UpdateData(FALSE);
}

void CComponentGenDlg::OnBnClickedTtifIdButton()
{
	time_t t = time(NULL);

	char *p = m_TTIF_ID.GetBuffer(64);
	sprintf(p, "%ld", t);
	m_TTIF_ID.ReleaseBuffer();

	UpdateData(FALSE);
}
